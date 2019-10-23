#include <Arena.hpp>
#include <MainWindow.hpp>
#include <Boxman.hpp>

#include <BackTexture.hpp>
#include <GLWidget.hpp>
#include <variables.hpp>

//#include <boost/graph/dijkstra_shortest_paths.hpp>

//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/astar_search.hpp>

#include <RTColor.hpp>
#include <EffectFactory.hpp>

#define NORMAL 1
#define MIRROR 2

int readXML(const char* path, std::vector<Mesh*> & maps, std::vector<Mesh*> & elements, BackTexture & backTex, std::string & musicPath);
void loadGraph(ArenaGraph & graphe, const char* nodePath, const char* edgePath);
void drawGraphe(const ArenaGraph & graphe);
bool isInNode(const float& x, const float& y, const Node&);
void camera2DMode(float width, float height);

unsigned char* load_PPM_RGBA(const char *path, int *w, int *h, const RTColor::color & col, const int & type);

void InitGLRGBA(unsigned char* image, int & w, int & h, GLuint & id);

Arena* Arena::arena = NULL;
ArenaGraph* Arena::graphe = NULL;

Robots * Arena::robots = new Robots();
Boxman * Arena::avatar = NULL;

kn::Vector3f Arena::gravity(0.0, -9.8/1.8, 0.0); // -9.8/scale
double Arena::vitesseChuteMax = -10;

std::vector<Mesh*> * Arena::maps = new std::vector<Mesh*>;
std::vector<Mesh*> * Arena::elements = new std::vector<Mesh*>;
BackTexture * Arena::backTexture = new BackTexture();
std::string Arena::musicPath("");

bool Arena::showGraph = false;
bool Arena::showBoundingBox = false;

bool Arena::gameEnd = false;
bool Arena::gameWin = false;

std::vector<FireBall*> Arena::fireballs;
std::vector<CocoNut*> Arena::coconuts;
std::vector<WaterBall*> Arena::waterballs;
std::vector<ExplodingCube*> Arena::explodingcubes;

Arena & Arena::getArena(int idArena, std::vector<int> botsType, std::vector<int> nbBots)
{
	if(arena == NULL)
	{
		switch(idArena)
		{
			case ROME:
				// chargement des elements de l'arene
				arena = new Arena();
				readXML("data/rome.xml", *maps, *elements, *backTexture, musicPath);
			break;
			
			case MOMOSHIRO:
				// chargement des elements de l'arene
				arena = new Arena();
				readXML("data/momoshiro.xml", *maps, *elements, *backTexture, musicPath);
			break;
		}
		
		robots->populate(botsType, nbBots);
		fillBotRevengeVictim(robots);
		
		switch(idArena)
		{
			case ROME:
				graphe = new ArenaGraph();
				// chargement du graphe pour cette map
				loadGraph(*graphe, "data/romeNode.nod", "data/romeEdge.edg");
			break;
			
			case MOMOSHIRO:
				graphe = new ArenaGraph();
				// chargement du graphe pour cette map
				loadGraph(*graphe, "data/momoshiroNode.nod", "data/momoshiroEdge.edg");
			break;
		}
		
		// mise a jour du radar des bots avec le graphe nouvellement créé
		for(unsigned int i=0; i<robots->getBots().size(); ++i)
		{
			(robots->getBots()[i])->getRadarReport().setGraph(*graphe);
			printf("bot id %d|", (robots->getBots()[i])->id());
		}
		printf("\n");
		
		GLWidget::timeStartOfGame = TIMER.elapsed();
	}
	
	return *arena;
}

void Arena::update(GLWidget & Widget)
{
	// on verifie si l'avatar a été crée
	if(avatar == NULL)
	{
		avatar = Robots::getAvatar(GLWidget::getSelectedCharacter());
	}
	
	// Updating robots nodes positions
	setBotsInNodes();
	
	draw(Widget, true, true);
	//drawCharactersHeads(Widget);
	//
	// Updating of bots radar
	//
	for (unsigned int i=0; i<robots->getBots().size(); i++)
	{
		// Radars have all robots
		(robots->getBots()[i])->getRadarReport().getNearbyRobots().clear();
		(robots->getBots()[i])->getRadarReport().getNearbyObstacles().clear();
		(robots->getBots()[i])->getRadarReport().getNearbyProjectiles().clear();
		//printf("POUR LE ROBOT %d : ", (robots->getBots()[i])->id());
		for (unsigned int j=0;j<robots->getBots().size();j++)
		{
			if (j!=i)
			{
				//printf(" %d -", (robots->getBots()[j])->id());
				(robots->getBots()[j])->getRadarReport().getNearbyRobots().push_back((robots->getBots()[j]));
			}			
		}
		//printf("\n");
	}
	
	// Robots Action
	robots->act();

	if (Widget.keyAttack1)
		avatar->getSpeaker().sendOrder("Attack", 1);
	else if (Widget.keyAttack2)
		avatar->getSpeaker().sendOrder("Attack", 2);
	else if (Widget.keyJump && !avatar->getRobotState().isJumping())
		avatar->getSpeaker().sendOrder("Jump", 1);
	else if (Widget.keyBlock)
		avatar->getSpeaker().sendOrder("Block", 1);
	else if(Widget.keyLeft)
		avatar->getSpeaker().sendOrder("Run", -1);
	else if (Widget.keyRight)
		avatar->getSpeaker().sendOrder("Run", 1);
	else if (Widget.keyThrow)
		avatar->getSpeaker().sendOrder("Throw", 1);
	else
		avatar->getSpeaker().sendOrder("None", 1);

	// on applique la physique de l'arène sur l'avatar
	avatar->movement->act();
	checkState(avatar);
	applyPhysics(avatar, Widget);

	// On applique la physique pour les robots
	for (unsigned int i=0;i<robots->getBots().size();i++)
	{

		checkState(robots->getBots()[i]);

		//(Widget.getRobots().getBots()[i])->setMovement(new Run((Widget.getRobots().getBots()[i])));
		if((robots->getBots()[i])->movement != NULL)
			(robots->getBots()[i])->movement->act();

		applyPhysics((robots->getBots()[i]), Widget);
		
		//Dessin du robot
		drawBot(robots->getBots()[i], Widget);
	}
	
	// dessin du modèle MD2 de l'avatar
	drawBot(avatar, Widget);

	// ------------------------------------------------->
	// ------------ projectiles drawing ------------------>
	// ------------------------------------------------->

	for(unsigned int i=0; i<getFireballs().size(); ++i)
	{
		applyMovementAndDrawFireball(i, Widget);
	}
	
	for(unsigned int i=0; i<getWaterBalls().size(); ++i)
	{
		applyMovementAndDrawWaterBall(i, Widget);
	}
	
	for(unsigned int i=0; i<getCocoNuts().size(); ++i)
	{
		applyMovementAndDrawCoconut(i, Widget);
	}
	
	for(unsigned int i=0; i<getExplodingCubes().size(); ++i)
	{
		applyMovementAndDrawExplodingCube(i, Widget);
	}
	
	// dessin du graphe
	this->drawGraph();

	// Drawing of characters heads
	drawCharactersHeads(Widget);



	// ------------------------------------------------------
	// ------------ condition victoire/défaite --------------
	// ------------------------------------------------------

	int nbRobotsLeft = 0;
	for (unsigned int i=0;i<robots->getBots().size();i++)
		if(!(robots->getBots()[i])->lost)
			++nbRobotsLeft;
	if(nbRobotsLeft==0)
	{
		gameEnd = true;
		gameWin = true;
	}

	if(avatar->lost)
	{
		gameEnd = true;
		gameWin = false;
	}

}

void Arena::drawCharactersHeads(GLWidget & widget)
{
	//const_cast<GLWidget &>(widget);

	camera2DMode(widget.getWidth(), widget.getHeight());
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);

	float imgWidth = 150.0 / 1.6;
	float imgHeight = 100.0 / 1.6;
	float av = 1.0;

	float intervalWidth = 50.0;
	float intervalHeight = widget.getHeight() - imgHeight;

	float addShiftWidth = (widget.getWidth() - imgWidth * 4) / 5.0 + imgWidth;

	// Create a list of texture Id of characters
	std::vector<int> charIdHead;
	charIdHead.push_back(texIdHeadBoxman);
	charIdHead.push_back(texIdHeadBandicoot);
	charIdHead.push_back(texIdHeadHector);
	charIdHead.push_back(texIdHeadOpera);


	// Get the player avatar and show it at the very left side
	switch (avatar->type())
	{
		case BOXMAN:
			glBindTexture(GL_TEXTURE_2D, texIdHeadBoxman);
			charIdHead.erase(charIdHead.begin());
			break;
		case BANDICOOT:
			glBindTexture(GL_TEXTURE_2D, texIdHeadBandicoot);
			charIdHead.erase(charIdHead.begin() + 1);
			break;
		case HECTOR:
			glBindTexture(GL_TEXTURE_2D, texIdHeadHector);
			charIdHead.erase(charIdHead.begin() + 2);
			break;
		case OPERA:
			glBindTexture(GL_TEXTURE_2D, texIdHeadOpera);
			charIdHead.erase(charIdHead.begin() + 3);
			break;
	}

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0);
	glVertex3f(intervalWidth, intervalHeight + imgHeight, av);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(intervalWidth, intervalHeight, av);

	glTexCoord2f(1.0, 0.0f);
	glVertex3f(imgWidth + intervalWidth, intervalHeight, av);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(imgWidth + intervalWidth, intervalHeight + imgHeight, av);
	glEnd();


	float widthI = intervalWidth;

	// Show the bot's heads
	for (unsigned int i = 0; i < this->robots->getBots().size(); ++i)
	{
		glBindTexture(GL_TEXTURE_2D, charIdHead[i]);
		//charIdHead.erase(charIdHead.begin()+i);

		intervalWidth += addShiftWidth;

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0);
		glVertex3f(intervalWidth, intervalHeight + imgHeight, av);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(intervalWidth, intervalHeight, av);

		glTexCoord2f(1.0, 0.0f);
		glVertex3f(imgWidth + intervalWidth, intervalHeight, av);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(imgWidth + intervalWidth, intervalHeight + imgHeight, av);
		glEnd();
	}
	
	charIdHead.clear();

	// initializing of painter parameters
	intervalWidth = widthI;

	QFont textFont;
    QPen textPen;
	int dmg;
	
	dmg = avatar->getRobotState().getDamages();

	widget.setPainter(intervalWidth-20, intervalHeight - imgHeight - 20, intervalWidth+imgWidth, intervalHeight - imgHeight - 50,
					dmg,
					50, true,
					textFont, textPen);

	// Show the bot's heads
	for (unsigned int i = 0; i < this->robots->getBots().size(); ++i)
	{
		dmg = (robots->getBots()[i])->getRobotState().getDamages();

		intervalWidth += addShiftWidth;

		widget.setPainter(intervalWidth-20, intervalHeight - imgHeight - 20, imgWidth+30, intervalHeight - imgHeight - 50,
						dmg,
						50, true,
						textFont, textPen);
	}

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Arena::checkState(Boxman* avatar)
{
	float r = (avatar)->getRobotState().getRotation()[1];
	// -----------------------------------------------------------
	// Test de collision entre les bots et les éléments de l'arène
	std::vector< std::pair<collisionFace, float> > faces;
	Wrap & avatarBox = avatar->box();
	avatarBox.x = (avatar)->getRobotState().getPosition()[0];
	avatarBox.y = (avatar)->getRobotState().getPosition()[1] + 0.5;
	drawBoundingBox(avatarBox);
	facesTouched(avatarBox, faces);

	(avatar)->getRobotState().isOnTheFloor() = false;
	if(faces.size() != 0 )
		for(unsigned int tni=0; tni<faces.size(); ++tni)
		{
			if(faces[tni].first == BOTTOM)
			{
				(avatar)->getRobotState().isOnTheFloor() = true;
				(avatar)->getRobotState().getPosition()[1] = faces[tni].second - 0.01;
			}
			if(faces[tni].first == RIGHT && ((r < 90 && r > -90) || (avatar)->getRobotState().getVelocity()[0]>0.000001)) // wall at right, direction right
			{
				(avatar)->getRobotState().getPosition()[0] = faces[tni].second - 0.3;
				(avatar)->getRobotState().getDirection()[0] = 0.0;
				(avatar)->getRobotState().getVelocity()[0] = 0.0;
			}
			if(faces[tni].first == LEFT && (r >= 90 || r <= -90)) // wall at left, direction left
			{
				(avatar)->getRobotState().getPosition()[0] = faces[tni].second + 0.3;
				(avatar)->getRobotState().getDirection()[0] = 0.0;
				(avatar)->getRobotState().getVelocity()[0] = 0.0;
			}
		}

	if((avatar)->getRobotState().isOnTheFloor() && (avatar)->getRobotState().getVelocity()[1]<0.0)
	{
		(avatar)->getRobotState().getDirection()[1] = 0.0;
		(avatar)->getRobotState().getAcceleration()[1] = 0.0;
		(avatar)->getRobotState().getVelocity()[1] = 0.0;
		//(avatar)->getRobotState().getPosition()[1] = -0.2;
	}

	//----------------------------------------------------------------------
	// test de collision (attaque) entre le robot et les eventuels victimes.
	// FAIRE UNE FCT checkAttack() ? TODO //eh oui ben on le fera un jour...
	if(avatar->getRobotState().isAttacking()==2)
	{
		// bots
		for (unsigned int i=0;i<robots->getBots().size();i++)
		{
			if((robots->getBots()[i])->id() != avatar->id())
			{
				std::pair<collisionFace, float> nearestFace;
				nearestFace = nearestCollisionFace(avatar->box(), (robots->getBots()[i])->box());
				if(nearestFace.first == RIGHT && (r < 90 && r > -90) && nearestFace.second < 0.0) // bot at right, direction right
				{
					(robots->getBots()[i])->beTouched(1, avatar);
					//std::cout << "face RIGHT" << std::endl;
				}
				if(nearestFace.first == LEFT && (r >= 90 || r <= -90) && nearestFace.second < 0.0) // bot at left, direction left
				{
					(robots->getBots()[i])->beTouched(-1, avatar);
					//std::cout << "face LEFT" << std::endl;
				}
				//std::cout << "face " << nearestFace.first << "d: " << nearestFace.second << std::endl;
			}
		}
		
		//avatar
		Boxman* vraiAvatar = Arena::avatar;
		if(vraiAvatar->id() != avatar->id())
		{
			std::pair<collisionFace, float> nearestFace;
			nearestFace = nearestCollisionFace(avatar->box(), vraiAvatar->box());
			if(nearestFace.first == RIGHT && (r < 90 && r > -90) && nearestFace.second < 0.0) // bot at right, direction right
			{
				vraiAvatar->beTouched(1, avatar);
				//std::cout << "face RIGHT" << std::endl;
			}
			if(nearestFace.first == LEFT && (r >= 90 || r <= -90) && nearestFace.second < 0.0) // bot at left, direction left
			{
				vraiAvatar->beTouched(-1, avatar);
				//std::cout << "face LEFT" << std::endl;
			}
			//std::cout << "face " << nearestFace.first << "d: " << nearestFace.second << std::endl;
		}
	}


	//----------------------------------------------------------------------
	// test de collision  entre le robot et les projectiles.
	// FAIRE UNE FCT separee aussi... enfin bref...

	float rangeOfEffect = 0.07;

	// --- FIREBALLS ---
	for (unsigned int i=0; i<this->getFireballs().size(); i++)
	{
		std::pair<collisionFace, float> nearestFace;
		nearestFace = nearestCollisionFace(avatar->box(), (getFireballs()[i])->boundingBox);
		if(avatar->id()!=(getFireballs()[i])->idLauncher  && (nearestFace.first==RIGHT || nearestFace.first==LEFT) && nearestFace.second > -rangeOfEffect && nearestFace.second < rangeOfEffect)
		{
			/*std::cout << "proj fire" << std::endl;
			float projDir = (getFireballs()[i])->vectVit[0];
			std::cout << "projDir fireballs: " << projDir << std::endl;
			avatar->beTouched((projDir>0.)? 1 : -1, avatar);*/
			avatar->beTouched(1, avatar);
		}
	}
	
	// --- WATERBALLS ---
	for (unsigned int i=0; i<this->getWaterBalls().size(); i++)
	{
		std::pair<collisionFace, float> nearestFace;
		nearestFace = nearestCollisionFace(avatar->box(), (getWaterBalls()[i])->boundingBox);
		if(avatar->id()!=(getWaterBalls()[i])->idLauncher  && (nearestFace.first==RIGHT || nearestFace.first==LEFT) && nearestFace.second > -rangeOfEffect && nearestFace.second < rangeOfEffect)
		{/*
			std::cout << "proj water" << std::endl;
			float projDir = (getFireballs()[i])->vectVit[0];
			std::cout << "projDir waterballs: " << projDir << std::endl;
			avatar->beTouched((projDir>0.)? 1 : -1, avatar);*/
			
			avatar->beTouched(1, avatar);
		}

	}

	// --- COCONUTS ---
	for (unsigned int i=0; i<this->getCocoNuts().size(); i++)
	{
		std::pair<collisionFace, float> nearestFace;
		nearestFace = nearestCollisionFace(avatar->box(), (getCocoNuts()[i])->boundingBox);
		if(avatar->id()!=(getCocoNuts()[i])->idLauncher  && (nearestFace.first==RIGHT || nearestFace.first==LEFT) && nearestFace.second > -rangeOfEffect && nearestFace.second < rangeOfEffect)
		{/*
			std::cout << "proj coco" << std::endl;
			float projDir = (getFireballs()[i])->vectVit[0];
			std::cout << "projDir coco: " << projDir << std::endl;
			avatar->beTouched((projDir>0.)? 1 : -1, avatar);*/
			
			avatar->beTouched(1, avatar);
		}

	}
	
	// --- CUBE ---
	for (unsigned int i=0; i<this->getExplodingCubes().size(); i++)
	{
		std::pair<collisionFace, float> nearestFace;
		nearestFace = nearestCollisionFace(avatar->box(), (getExplodingCubes()[i])->boundingBox);
		if(avatar->id()!=(getExplodingCubes()[i])->idLauncher  && (nearestFace.first==RIGHT || nearestFace.first==LEFT) && nearestFace.second > -rangeOfEffect && nearestFace.second < rangeOfEffect)
		{/*
			std::cout << "proj cube" << std::endl;
			float projDir = (getFireballs()[i])->vectVit[0];
			std::cout << "projDir cube: " << projDir << std::endl;
			avatar->beTouched((projDir>0.)? 1 : -1, avatar);*/
			avatar->beTouched(1, avatar);
		}

	}
}

void Arena::applyPhysics(Boxman* avatar, const GLWidget & Widget)
{
	kn::Vector3f vecteurNull(0.0, 0.0, 0.0);
	
	// loi physique de l'arene
	kn::Vector3f localGravity = (avatar)->getRobotState().isOnTheFloor()? vecteurNull : getGravity();
	// acceleration += (direction)
	(avatar)->getRobotState().getAcceleration()	+= ( (avatar)->getRobotState().getDirection()) * 150.0 * Widget.getRelativeTime();
	// vitesse += acceleration + gravite
	(avatar)->getRobotState().getVelocity()		+= ( (avatar)->getRobotState().getAcceleration()  + localGravity )  * Widget.getRelativeTime();
	// vitesse max : vitesse = max(vitesse, vitesseMax) en tenant compte que la vitesse peut être negative.
	// + inertie/frottements : la vitesse diminue constamment.
	for( int k=0; k<3; ++k)
	{
		float & speed = (avatar)->getRobotState().getVelocity()[k];
		float maxSpeed = (avatar)->getMaxSpeed()[k];
		int sign = (speed < 0)? -1 : 1;
		float forceFrottements = (avatar)->getRobotState().isOnTheFloor()? 1.6 : 0.1;
		//if(speed > forceFrottements * sign * relativeTime)
		  //speed -= forceFrottements * sign * relativeTime;
		//else
		  //speed = 0.0;

		speed /= 1.+(forceFrottements*Widget.getRelativeTime());
		if( speed*sign >  maxSpeed && !avatar->getRobotState().isDead())
		  speed = maxSpeed * sign;
	}

	// position += vitesse
	// Au démarrage, on bloque le jeu quelques secondes pour la préparation du joueur humain.
	if(TIMER.elapsed()-Widget.timeStartOfGame < 5000)
	{
		(avatar)->getRobotState().getPosition()[1] = 2.0;
		avatar->lost = false;
		std::cout << "Please wait..." << std::endl;
	}
	else if(avatar->lost)
	{
		kn::Vector3f pInit(0.0, -1.5, 0.0);
		(avatar)->getRobotState().getPosition() = pInit;
	}
	else
		(avatar)->getRobotState().getPosition() += (avatar)->getRobotState().getVelocity() * Widget.getRelativeTime();

	// reset acceleration, qui n'agit que sur 1 frame
	(avatar)->getRobotState().getAcceleration() = vecteurNull;

	// reset robot
	if(avatar->getRobotState().getPosition()[1]< -2.0)
	{
		if(avatar->lives > 0)
		{
			avatar->getRobotState().getPosition()[0] = 1.0;
			avatar->getRobotState().getPosition()[1] = 2.0;
			avatar->getRobotState().getVelocity() = vecteurNull;
			avatar->getRobotState().getDamages() = 0;
			avatar->lives--;
			std::cout << "Player or bot " << avatar->type() << " has " << avatar->lives << " lives left" << std::endl;
		}
		else
		{
			avatar->lost = true;
			std::cout << "A player has lost!" << std::endl;
		}
	}

}

void Arena::drawBot(Boxman* avatar, GLWidget & Widget)
{
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	
	glPushMatrix();
		if(!Widget.isMD2TexLoaded())
		{
			avatar->loadTexture();
			Widget.isMD2TexLoaded() = true;
		}
		
		glTranslatef(avatar->getRobotState().getPosition()[0],
				avatar->getRobotState().getPosition()[1],
				avatar->getRobotState().getPosition()[2]
				);
				
		glRotatef(avatar->getRobotState().getRotation()[0], 1,0,0);
		glRotatef(avatar->getRobotState().getRotation()[1] + avatar->botInfo.yrot(), 0,1,0);
		glRotatef(avatar->getRobotState().getRotation()[2], 0,0,1);
		
		float s = avatar->getRobotState().getScale();
		glScalef(s, s, s);

		avatar->animation.animeModel( avatar->getRobotModel() );  
	glPopMatrix();
			
	glDisable(GL_LIGHTING);
}

void Arena::drawBoundingBox(const Wrap & w)
{
	if(!showBoundingBox) return;
	
	//printf("draw Box %.2f %.2f %.2f %.2f\n", w.x, w.y, w.width, w.height);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glColor3f(1.0, 0.0, 0.0);
	//glPointSize(10);
	float size = 0.03;
	glBegin(GL_QUADS);
		glVertex3f(w.x-size, w.y-size, 0.0);
		glVertex3f(w.x-size, w.y+size, 0.0);
		glVertex3f(w.x+size, w.y+size, 0.0);
		glVertex3f(w.x+size, w.y-size, 0.0);
	glEnd();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	float W = w.width/2.0, H = w.height/2.0;
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(w.x-W, w.y-H, 0);

		glVertex3f(w.x-W, w.y+H, 0);

		glVertex3f(w.x+W, w.y+H, 0);

		glVertex3f(w.x+W, w.y-H, 0);
	glEnd();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
	//glEnable(GL_BLEND);
}

void Arena::drawGraph()
{
	if(!showGraph) return;
	
	drawGraphe(*graphe);
}

bool Arena::facesTouched(const Wrap & w, std::vector< std::pair<collisionFace, float> > & faces)
{
	bool found = false;
	
	for(unsigned int i=0; i<maps->size(); ++i)
	{
		std::pair<collisionFace, float> f( ((IOMesh*)((*maps)[i]))->hitTestObject(w) );
		
		if(f.first != NONE)
		{
			faces.push_back(f);
			found = true;
		}
	}
	
	return found;
}

std::pair<collisionFace, float> Arena::nearestCollisionFace(const Wrap & refWrap, const Wrap & wrap)
{
	std::pair<collisionFace, float> info;
	
	// On donne priorité sur la détection horizontale plutot que verticale
	// cette fonction est plutot utilisée pour gérer les distances entre les personnages
	// pour la gestion des coups
	if(refWrap.x < wrap.x)// - (wrap.width + refWrap.width)/2.0)
	{		
		float dx = (wrap.x - wrap.width/2.0) - (refWrap.x + refWrap.width/2.0);
		float dy = 0.01;
		// si wrap est a droite de refWrap
		if(refWrap.y > wrap.y )
			dy = refWrap.y - wrap.y;
		else 
			dy = wrap.y - refWrap.y;
		
		info.first = RIGHT;
		info.second = sqrt(dx*dx + dy*dy);
			
		//info.second *= -1.0;
		//info.second = (wrap.x - wrap.width/2.0) - (refWrap.x + refWrap.width/2.0);
		if(dy < 1.0)
			info.second = (wrap.x - wrap.width/2.0) - (refWrap.x + refWrap.width/2.0);
		else
			info.second = 111111.0;
	}
	else if(refWrap.x > wrap.x)// + (wrap.width + refWrap.width)/2.0)
	{
		//float dx =  (refWrap.x - refWrap.width/2.0) - (wrap.x + wrap.width/2.0);
		float dy = 0.01;
		// si wrap est a gauche de refWrap
		if(refWrap.y > wrap.y )
			dy = refWrap.y - wrap.y;
		else 
			dy = wrap.y - refWrap.y;
		
		info.first = LEFT;
		//info.second = sqrt(dx*dx + dy*dy);
		if(dy < 1.0)
			info.second = (refWrap.x - refWrap.width/2.0) - (wrap.x + wrap.width/2.0);
		else
			info.second = 111111.0;
	}
	else if(refWrap.y < wrap.y - (wrap.height + refWrap.height)/2.0)
	{
		info.first = TOP;
		info.second = (wrap.y - wrap.height/2.0) - (refWrap.y + refWrap.height/2.0);
	} 
	else if(refWrap.y > wrap.y + (wrap.height + refWrap.height)/2.0)
	{
		info.first = BOTTOM;
		info.second = (refWrap.y - refWrap.height/2.0) - (wrap.y + wrap.height/2.0);
	}
	
	return info;
}

void Arena::setBotsInNodes() // met les robots dans les noeuds où ils sont
{
	std::vector<bool> botAlreadySeen(robots->getBots().size() + 1, false);
	bool avatarAlreadySeen = false;
	
	// on parcourt tous les noeuds du graphe pour mettre les robots dans les noeuds corresponant
	ArenaNodeIterator first, last;
	
	for(boost::tie(first, last) = boost::vertices(*graphe); first != last; ++first)
	{		
		// We should do this with property maps
		// boost::get()
		// boost::put();
		Node& N = const_cast<Node&>((*graphe)[*first]);
		
		N.getBotsInside().clear();
		
		for(unsigned int i=0; i<robots->getBots().size(); ++i)
		{
			float xbot = (robots->getBots()[i])->getRobotState().getPosition()[0];
			float ybot = (robots->getBots()[i])->getRobotState().getPosition()[1] + 0.5;
			
			if(!botAlreadySeen[i] && isInNode(xbot, ybot, N))
			{
				N.getBotsInside().push_back((robots->getBots()[i]));
				botAlreadySeen[i] = true;
			}
		}
		
		float xav = (avatar)->getRobotState().getPosition()[0];
		float yav = (avatar)->getRobotState().getPosition()[1] + 0.5;
		
		if(!avatarAlreadySeen && isInNode(xav, yav, N))
		{
			//N.getBotsInside().push_back(/*(kn::smashstein::Robot*)*/&avatar);
			N.getBotsInside().push_back(avatar);
			avatarAlreadySeen = true;
		}
	}
}

void Arena::loadGraphe(ArenaGraph & graphe, const char* nodePath, const char* edgePath)
{
	printf("\n\t######## Load ArenaGraph from (\"%s\", \"%s\") ########\n", nodePath, edgePath);
	
	// On crée dabord tous les sommets
	
	std::ifstream nodeFile(nodePath, std::ios::in);
	std::string line;
	std::istringstream readBuffer;
	
	std::vector<ArenaNodeID> arenaNodes;
	printf("\tNODES :\n");
	while(std::getline(nodeFile, line))
	{
		readBuffer.clear();
		readBuffer.str(line);
		
		if((line[0] >= '0') && (line[0] <= '9'))
		{
			unsigned int nodeID;
			int nodeType;
			float nodeXPos, nodeYPos, nodeWidth, nodeHeight;
			
			readBuffer >> nodeID;
			readBuffer >> nodeType;
			readBuffer >> nodeXPos;
			readBuffer >> nodeYPos;
			readBuffer >> nodeWidth;
			readBuffer >> nodeHeight;
			
			printf("\t\t%d | %d | %.2f | %.2f | %.2f | %.2f\n", nodeID, nodeType, nodeXPos, nodeYPos, nodeWidth, nodeHeight);
			ArenaNodeID anID = boost::add_vertex(graphe); // anID est l'indice d'un nouveau sommet qui a été ajouté dans graphe
			(graphe)[anID].id() = nodeID;
			(graphe)[anID].x() = nodeXPos;
			(graphe)[anID].y() = nodeYPos;
			(graphe)[anID].width() = nodeWidth;
			(graphe)[anID].height() = nodeHeight;
			(graphe)[anID].nodeType() = 1;
			
			// On stocke l'ID du noeud nouvellement crée
			arenaNodes.push_back(anID);
		}
	}
	
	nodeFile.close();
	
	printf("\tEDGES :\n");
	//std::vector<ArenaNodeID> arenaNodes;
	std::ifstream edgeFile(edgePath, std::ios::in);
	readBuffer.clear();
	line.clear();
	
	ArenaEdgeMap weightmap = boost::get(boost::edge_weight, graphe);
	
	while(std::getline(edgeFile, line))
	{
		readBuffer.clear();
		readBuffer.str(line);
		
		if((line[0] >= '0') && (line[0] <= '9'))
		{
			unsigned int nodeStartID, nodeEndID;
			float edgeValue;
			
			readBuffer >> nodeStartID;
			readBuffer >> nodeEndID;
			readBuffer >> edgeValue;
			
			printf("\t\t%d | %d | %.2f ", nodeStartID, nodeEndID, edgeValue);
	 
			ArenaEdgeID edge;
			bool good;
			boost::tie(edge, good) = boost::add_edge(arenaNodes[nodeStartID], arenaNodes[nodeEndID], graphe); // boost::add_edge renvoie une std::pai>WayPointConnectionID,bool>. C'est compliqué à écrire, alors on laisse boost::tie le faire pour nous.
	 
			if(good)  // Si le graphe a bel et bien été ajouté ( pas de doublon, par exemple, sauf si spécifié dans le typedef de WayPointGraph )
			{
				//graphe[edge].value() = edgeValue;
				weightmap[edge] = edgeValue;
				printf("GOOD\n");
			}
			else
				printf("BAD\n");		
		}
	}
	
	edgeFile.close();

	printf("\t########################\n");
}

void Arena::loadCharactersHeads()
{
	RTColor::color col(255, 255, 255);

	int w, h;
	unsigned char* image = NULL;

	image = load_PPM_RGBA("data/boxman.ppm", &w, &h, col, MIRROR);
	InitGLRGBA(image, w, h, texIdHeadBoxman);

	image = load_PPM_RGBA("data/bandicoot.ppm", &w, &h, col, MIRROR);
	InitGLRGBA(image, w, h, texIdHeadBandicoot);
	
	image = load_PPM_RGBA("data/hector.ppm", &w, &h, col, MIRROR);
	InitGLRGBA(image, w, h, texIdHeadHector);
	
	image = load_PPM_RGBA("data/opera.ppm", &w, &h, col, MIRROR);
	InitGLRGBA(image, w, h, texIdHeadOpera);
}

void Arena::draw(GLWidget & Widget, const bool & IO, const bool & Decor)
{
	Widget.setLookAt();

	if(!Widget.isTextureAlreadyLoaded())
	{
		backTexture->loadTexture();
	}
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, Widget.LightPosition());
	
	backTexture->draw();
	
	if(IO)
	{
		glPushMatrix();
			for(unsigned int i=0; i<(unsigned int)maps->size(); ++i)
			{
				
				if(!Widget.isTextureAlreadyLoaded())
				{
					//printf("map type %d ", type);
					(*maps)[i]->loadTexture();
				}
				
				if(!Widget.isCallListAlreadyLoaded())
					(*maps)[i]->loadCallList();
				else
				{
					glCallList((*maps)[i]->meshId());
				}
				
				drawBoundingBox(((IOMesh*)((*maps)[i]))->getBoundingBox());
			}
		glPopMatrix();
	}
	
	if(Decor)
	{
		glPushMatrix();
			for(unsigned int i=0; i<(unsigned int)elements->size(); ++i)
			{
				if(!Widget.isTextureAlreadyLoaded())
				{
					(*elements)[i]->loadTexture();
				}
				
				if(!Widget.isCallListAlreadyLoaded())
					(*elements)[i]->loadCallList();
				else
				{
					glCallList((*elements)[i]->meshId());
				}
			}	
		glPopMatrix();
	}
	
	if(!Widget.isTextureAlreadyLoaded())
	{
		// Loading of characters heads
		loadCharactersHeads();	
		loadProjectilesTextures();
	}	

	Widget.isTextureAlreadyLoaded() = true;
	Widget.isCallListAlreadyLoaded() = true;
	
	glDisable(GL_LIGHTING);
}

void Arena::loadProjectilesTextures()
{
	getProjectilesTexList().push_back(FireBall::loadTextureProjectile()); // 0
	getProjectilesTexList().push_back(CocoNut::loadTextureProjectile()); // 1
	getProjectilesTexList().push_back(WaterBall::loadTextureProjectile()); // 2
	getProjectilesTexList().push_back(ExplodingCube::loadTextureProjectile()); // 3
	/*printf("load TEXT PROJECtiles %d %d\n",getProjectilesTexList().back().first,
										   getProjectilesTexList().back().second);*/
}

void Arena::fillBotRevengeVictim(Robots* srobots)
{
	for(unsigned int i=0; i<srobots->getBots().size(); ++i)
	{
		//bots <= bots
		for(unsigned int j=0; j<srobots->getBots().size(); ++j)
		{
		if(i != j)
			{
				std::pair<int, int> p((srobots->getBots()[j])->id(), 0);
				// revenge
				(srobots->getBots()[i])->getRevenge().push_back(p);
				// victim
				(srobots->getBots()[i])->getVictim().push_back(p);
			}
		}
		// avatar <= bots
		//std::pair<int, int> pairBot((srobots->getBots()[i])->id(), 0);
		//savatar->getRevenge().push_back(pairBot);

		//bots <= avatar
		//std::pair<int, int> pairAvatar(savatar->id(), 0);
		std::pair<int, int> pairAvatar(-1, 0);
		// revenge
		(srobots->getBots()[i])->getRevenge().push_back(pairAvatar);
		// victim
		(srobots->getBots()[i])->getVictim().push_back(pairAvatar);
	}
}

void Arena::applyMovementAndDrawFireball(unsigned int position, const GLWidget & Widget)
{
	FireBall* ball = getFireballs().at(position);
	// physic : movement
	ball->posX += ball->vectVit[0]*Widget.getRelativeTime();
	ball->boundingBox.x = ball->posX;
	ball->boundingBox.y = ball->posY;
	ball->boundingBox.width = 0.1;
	ball->boundingBox.height = 0.1;

	// draw
	glPushMatrix();
		glTranslatef(ball->posX, ball->posY, 0.0);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(ball->rot, 0., 0., 1.);
		//glRotatef(-90.0, 0., 0., 1.);
		//std::pair<unsigned int,unsigned int> idTex; // test
		//idTex = ball->loadTextureProjectile(); // test
		//ball->drawProjectiles(RTPoint::point3(0.0, 0.0, 5.0),idTex.first,idTex.second);
		ball->drawProjectiles(RTPoint::point3(0.0, 0.0, 5.0),(getProjectilesTexList()[0]).first,(getProjectilesTexList()[0]).second);
		ball->updateProjectiles();
	glPopMatrix();


	// end of life
	if(TIMER.elapsed()-ball->timeStart > 2000)
	{
		//delete ball;
		getFireballs().erase(getFireballs().begin()+position);
	}
}

void Arena::applyMovementAndDrawCoconut(unsigned int position, const GLWidget & Widget)
{
	CocoNut* ball = getCocoNuts().at(position);
	// physic : movement
	ball->posX += ball->vectVit[0]*Widget.getRelativeTime();
	//ball->posY += sin((float)(TIMER.elapsed()-ball->timeStart)*(5.*M_PI/8.)/2000.);
	ball->posY += 2.*sin((float)(TIMER.elapsed()-ball->timeStart)*(M_PI/2.)/1000. + M_PI/2.)*Widget.getRelativeTime();
	ball->boundingBox.x = ball->posX;
	ball->boundingBox.y = ball->posY;
	ball->boundingBox.width = 0.1;
	ball->boundingBox.height = 0.1;

	// draw
	glPushMatrix();
		glTranslatef(ball->posX, ball->posY, 0.0);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(ball->rot, 0., 0., 1.);
		//glRotatef(-90.0, 0., 0., 1.);
		//std::pair<unsigned int,unsigned int> idTex; // test
		//idTex = ball->loadTextureProjectile(); // test
		//ball->drawProjectiles(RTPoint::point3(0.0, 0.0, 5.0),idTex.first,idTex.second);
		ball->drawProjectiles(RTPoint::point3(0.0, 0.0, 5.0),(getProjectilesTexList()[1]).first,(getProjectilesTexList()[1]).second);
		ball->updateProjectiles();
	glPopMatrix();

	// end of life
	if(TIMER.elapsed()-ball->timeStart > 2000)
	{
		//delete ball;
		getCocoNuts().erase(getCocoNuts().begin()+position);
	}
}

void Arena::applyMovementAndDrawWaterBall(unsigned int position, const GLWidget & Widget)
{
	WaterBall* ball = getWaterBalls().at(position);
	// physic : movement
	ball->posX += ball->vectVit[0]*Widget.getRelativeTime();
	ball->boundingBox.x = ball->posX;
	ball->boundingBox.y = ball->posY;
	ball->boundingBox.width = 0.1;
	ball->boundingBox.height = 0.1;

	// draw
	glPushMatrix();
		glTranslatef(ball->posX, ball->posY, 0.0);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(ball->rot, 0., 0., 1.);
		//glRotatef(-90.0, 0., 0., 1.);
		//std::pair<unsigned int,unsigned int> idTex; // test
		//idTex = ball->loadTextureProjectile(); // test
		//ball->drawProjectiles(RTPoint::point3(0.0, 0.0, 5.0),idTex.first,idTex.second);
		ball->drawProjectiles(RTPoint::point3(0.0, 0.0, 5.0), (getProjectilesTexList()[2]).first, (getProjectilesTexList()[2]).second);
		ball->updateProjectiles();
	glPopMatrix();

	// end of life
	if(TIMER.elapsed()-ball->timeStart > 2000)
	{
		//delete ball;
		getWaterBalls().erase(getWaterBalls().begin()+position);
	}
}

void Arena::applyMovementAndDrawExplodingCube(unsigned int position, const GLWidget & Widget)
{
	ExplodingCube* ball = getExplodingCubes().at(position);
	// physic : movement
	ball->posX += ball->vectVit[0]*Widget.getRelativeTime();
	ball->boundingBox.x = ball->posX;
	ball->boundingBox.y = ball->posY;
	ball->boundingBox.width = 0.1;
	ball->boundingBox.height = 0.1;

	// draw
	glPushMatrix();
		glTranslatef(ball->posX, ball->posY, 0.0);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(ball->rot, 0., 0., 1.);
		//glRotatef(-90.0, 0., 0., 1.);
		//std::pair<unsigned int,unsigned int> idTex; // test
		//idTex = ball->loadTextureProjectile(); // test
		//ball->drawProjectiles(RTPoint::point3(0.0, 0.0, 5.0),idTex.first,idTex.second);
		ball->drawProjectiles(RTPoint::point3(0.0, 0.0, 5.0), (getProjectilesTexList()[3]).first, (getProjectilesTexList()[3]).second);
		ball->updateProjectiles();
	glPopMatrix();

	// end of life
	if(TIMER.elapsed()-ball->timeStart > 2000)
	{
		//delete ball;
		getExplodingCubes().erase(getExplodingCubes().begin()+position);
	}
}
