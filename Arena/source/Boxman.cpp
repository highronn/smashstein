/*
 * Internal Includes
 */
#include <Boxman.hpp>
#include <StandBy.hpp>
#include <Damage.hpp>
#include <Death.hpp>
#include <Robots.hpp>
#include <ctime>

//std::vector<Sound*> Boxman::animSounds(14);// = new vector<Sound*>[2]; // TODO : faire tous les delete qui vont avec lors de la fermeture du programme.
std::vector<std::vector<Sound*> > Boxman::animSoundsAll(4);
std::vector< std::pair<CMD2Model*, int> > Boxman::modelTab;
std::vector<std::string> Boxman::modelTexPath;


Boxman::Boxman():movement(new StandBy(this))
{}

Boxman::Boxman(const RobotInfo & inf, int type):
botInfo(inf), maxSpeed(2.5, 6.0, 10.0), movement(new StandBy(this))
{
	printf("\n\n****************** CREATE NEW BOT WITH TEXTURE ***********************\n");
	type_ = type;
	lost = false;
	lives = 3;
	//std::vector<Sound*>animSounds(20);
	// mise a jour du state	
	state.getPosition()[0] = inf.x();
	state.getPosition()[1] = inf.y();
	state.getPosition()[2] = inf.z();

	state.getRotation()[0] = inf.xrot();
	state.getRotation()[1] = inf.yrot();
	state.getRotation()[2] = inf.zrot();

	state.getScale() = inf.scale();

	animation.loadAnimationTab(inf.anime().c_str());
	
	// Bounding box
	box().x = getRobotState().getPosition()[0];
	box().y = getRobotState().getPosition()[1] + 0.5;
	box().width = 0.8;
	box().height = 1.0;
	
	loadModel(botInfo.model().c_str(), botInfo.texture(), type);
//	// SON qui marche (faire ça ds une fonction séparée serait ptet plus propre)
//	if(Boxman::animSounds[0]==NULL)
//		Boxman::animSounds[0] = new Sound("sounds/simpson.wav", LOADED_SOUND);
//	if(Boxman::animSounds[1]==NULL){
//		Boxman::animSounds[1] = new Sound("sounds/swing1.mp3", LOADED_SOUND);
//		printf("chargement de deux sons static dans Boxman terminé\n");
	std::vector<const char*> soundList;
	printf("\n type de robot : %d \n", type);
	if(type == BANDICOOT)
	{
		soundList.push_back(NULL); //1 STANDBY
		soundList.push_back(NULL); //2 PRERUN
		soundList.push_back(NULL); //3 RUN
		soundList.push_back("sound/bandicoot/bandicoot_combat_3.mp3"); // 4 JUMP
		soundList.push_back("sound/bandicoot/fall.mp3"); //5 FALL
		soundList.push_back("sound/bandicoot/bandicoot_saut.mp3"); //6 POSTJUMP
		soundList.push_back("sound/bandicoot/bandicoot_combat_1.mp3"); //7 ATTACK 1
		soundList.push_back("sound/bandicoot/throw.mp3"); //8 THROW
		soundList.push_back("sound/bandicoot/bandicoot_encaisse.mp3"); //9 DAMAGE
		soundList.push_back(NULL); //10 PREBLOCK
		soundList.push_back("sound/bandicoot/block1.mp3"); //11 BLOCK
		soundList.push_back(NULL); //12 POSTBLOCK
		soundList.push_back("sound/bandicoot/intheair1.mp3"); //13 PREDEATH
		soundList.push_back(NULL); //14 DEATH
		soundList.push_back(NULL); //15 POSTDEATH
		soundList.push_back(NULL); //16 STANDUP
		soundList.push_back("sound/bandicoot/attack2.1.mp3"); //17 ATTACK2
		soundList.push_back(NULL); //18 ROTATE
		soundList.push_back(NULL); //19 POSTRUN
		soundList.push_back("sound/bandicoot/victorywait1.mp3"); //20 VICTORY
		
		
	}
	else if(type == BOXMAN)
	{
		soundList.push_back(NULL); //1 STANDBY
		soundList.push_back(NULL); //2 PRERUN
		soundList.push_back(NULL); //3 RUN
		soundList.push_back("sound/boxman/jump1.mp3"); // 4 JUMP "sound/boxman/boxman_saut.mp3"
		soundList.push_back(NULL); //5 FALL
		soundList.push_back("sound/boxman/postJump.mp3"); //6 POSTJUMP
		soundList.push_back("sound/boxman/attack1.mp3"); //7 ATTACK 1
		soundList.push_back("sound/boxman/throw.mp3"); //8 THROW
		soundList.push_back("sound/boxman/hit1.mp3"); //9 DAMAGE
		soundList.push_back("sound/boxman/block1.mp3"); //10 PREBLOCK
		soundList.push_back(NULL); //11 BLOCK
		soundList.push_back(NULL); //12 POSTBLOCK
		soundList.push_back("sound/boxman/predeath.mp3"); //13 PREDEATH
		soundList.push_back(NULL); //14 DEATH
		soundList.push_back(NULL); //15 POSTDEATH
		soundList.push_back(NULL); //16 STANDUP
		soundList.push_back("sound/boxman/attack2.mp3"); //17 ATTACK2
		soundList.push_back(NULL); //18 ROTATE
		soundList.push_back(NULL); //19 POSTRUN
		soundList.push_back("sound/boxman/victorywait.mp3"); //20 VICTORY
	}
	else if(type == HECTOR)
	{
		soundList.push_back(NULL); //1 STANDBY
		soundList.push_back(NULL); //2 PRERUN
		soundList.push_back(NULL); //3 RUN
		soundList.push_back("sound/hector/jump1.mp3"); // 4 JUMP
		soundList.push_back(NULL); //5 FALL
		soundList.push_back("sound/hector/down.mp3"); //6 POSTJUMP
		soundList.push_back("sound/hector/attack1.1.mp3"); //7 ATTACK 1
		soundList.push_back("sound/hector/throw1.mp3"); //8 THROW
		soundList.push_back("sound/hector/hitself1.mp3"); //9 DAMAGE
		soundList.push_back("sound/hector/preblock1.mp3"); //10 PREBLOCK
		soundList.push_back("sound/hector/block1.mp3"); //11 BLOCK
		soundList.push_back(NULL); //12 POSTBLOCK
		soundList.push_back("sound/hector/fall1.mp3"); //13 PREDEATH
		soundList.push_back(NULL); //14 DEATH
		soundList.push_back(NULL); //15 POSTDEATH
		soundList.push_back(NULL); //16 STANDUP
		soundList.push_back("sound/hector/attack2.1.mp3"); //17 ATTACK2
		soundList.push_back(NULL); //18 ROTATE
		soundList.push_back(NULL); //19 POSTRUN
		soundList.push_back("sound/hector/victorywait1.mp3"); //20 VICTORY
	}
	else if(type == OPERA)
	{
		soundList.push_back(NULL); //1 STANDBY
		soundList.push_back(NULL); //2 PRERUN
		soundList.push_back(NULL); //3 RUN
		soundList.push_back("sound/opera/jump1.mp3"); // 4 JUMP "sound/boxman/boxman_saut.mp3"
		soundList.push_back(NULL); //5 FALL
		soundList.push_back("sound/opera/postJump.mp3"); //6 POSTJUMP
		soundList.push_back("sound/opera/attack1.mp3"); //7 ATTACK 1
		soundList.push_back("sound/opera/throw1.mp3"); //8 THROW
		soundList.push_back("sound/opera/hit.mp3"); //9 DAMAGE
		soundList.push_back("sound/opera/block1.mp3"); //10 PREBLOCK
		soundList.push_back(NULL); //11 BLOCK
		soundList.push_back(NULL); //12 POSTBLOCK
		soundList.push_back("sound/opera/predeath.mp3"); //13 PREDEATH
		soundList.push_back(NULL); //14 DEATH
		soundList.push_back(NULL); //15 POSTDEATH
		soundList.push_back(NULL); //16 STANDUP
		soundList.push_back("sound/opera/attack2.mp3"); //17 ATTACK2
		soundList.push_back(NULL); //18 ROTATE
		soundList.push_back(NULL); //19 POSTRUN
		soundList.push_back("sound/opera/victorywait.mp3"); //20 VICTORY
	}
	else
	{
		// si le perso n'est pas défini au niveau son, on charge des sons vides.
		for(int numAim = 0; numAim<NB_ANIM; ++numAim)
			soundList.push_back(NULL);
	}
	printf("\n soundliste : %d \n",(int)soundList.size());
	printf("\n MISE EN PLACE DU LOADSOUND \n");
	loadSounds(soundList, type);
}

Boxman::~Boxman()
{
	if(movement != NULL)
		delete movement;
}

void Boxman::loadSounds(const std::vector<const char*> soundList, int type)
{
	std::vector<Sound*> animSounds(20);
	
	if(animSounds.size() != soundList.size())
		std::cout << "Attention, le nombre de sons à charger dans Boxman ne correspond pas à la taille du vecteur Boxman::animSounds" << std::endl;
	
	for(unsigned int i = 0; i<animSounds.size() && i<soundList.size(); ++i)
	{
		if(animSounds[i] == NULL)
		{
			if(soundList[i] != NULL)
			{
				animSounds[i] = new Sound(soundList[i], LOADED_SOUND, false);
			}
			else
			{
				animSounds[i] = new Sound();
			}
		}
		
	}

	animSoundsAll[type-1] = animSounds;
	printf("chargement des %d sons static dans Boxman terminé\n", (int)animSounds.size());
}

bool Boxman::loadModel(const char* modelPath, const std::string & texPath , int type)
{
	bool found = false;
	
	// on regarde si le modèle n'a pas deja été crée
	unsigned int i = 0;
	while((i<modelTab.size()) && !found)
	{
		if((modelTab[i].second == type))
		{
			modelIndex = i;
			found = true;
		}
		else
			++i;
	}
	
	// s'il n'a pas été créé on le crée
	if(!found)
	{
		CMD2Model* botMod = new CMD2Model;
		found = botMod->LoadModel(modelPath);
		
		if(found)
		{
			//printf("\t*************** LOAD MODEL %d with tex %s ********************\n", type, texPath.c_str());
			std::pair<CMD2Model*, int> p(botMod, type);
			modelTab.push_back(p);
			modelTexPath.push_back(texPath);
			modelIndex = modelTab.size()-1;
			//modelIndex = modelTexPath.size()-1;
		}
	}

	return found;
}

bool Boxman::loadTexture(int type, const char* texPath)
{
	bool good = false, found = false;
	
	unsigned int i = 0;
	while(!found && (i < modelTab.size()))
	{
		if(modelTab[i].second == type)
		{
			found = true;
			good = modelTab[i].first->LoadTexture(texPath);
		}
		else		
			++i;
	}

	return good;
}

bool Boxman::loadTexture()
{
	bool good = true;
	
	unsigned int i = 0;
	while(good && (i < modelTab.size()))
	{
		if(!modelTab[i].first->LoadTexture(modelTexPath[i].c_str()))
		{
			good = false;
		}
		
		++i;
	}

	return good;
}

Wrap & Boxman::box()
{
	//box_.width = 0.2;
	/*float xmin =1000000, xmax = -10000000, ymin = 100000000, ymax = -10000000000;
	
	//float vertex1[3], vertex2[3], vertex3[3];
	//printf("TESTAGE 0\n");
	int iFrame = animation.getCurrentFrame();
	//printf("TESTAGE 1 %d\n", iFrame);
	if(iFrame == -1)
	{
		printf("Ma box = oain\n");
		box_.x = getRobotState().getPosition()[0];
		box_.y = getRobotState().getPosition()[1] + 0.5;
		box_.width = 0.8;
		box_.height = 1.0;
		
		return box_;
	}
	
	//md2_frame_t *pFrame = &(getRobotModel().m_pFrames[iFrame]);
	
	for( int i = 0; i < getRobotModel().m_kHeader.num_tris; i++ )
	{
		//printf("TESTAGE 3\n");
		//md2_vertex_t *pVert1 = &(pFrame->verts[ getRobotModel().m_pTriangles[i].vertex[0] ]);
		//md2_vertex_t *pVert2 = &(pFrame->verts[ getRobotModel().m_pTriangles[i].vertex[1] ]);
		//md2_vertex_t *pVert3 = &(pFrame->verts[ getRobotModel().m_pTriangles[i].vertex[2] ]);
		
		for( int k = 0; k < 3; k++ )
		{
			md2_frame_t *pFrame = &(getRobotModel().m_pFrames[ iFrame ]);
			md2_vertex_t *pVert = &(pFrame->verts[ getRobotModel().m_pTriangles[i].vertex[k] ]);
			
			float v[3];

			// calcul de la position absolue du vertex et redimensionnement
			v[0] = (pFrame->scale[1] * pVert->v[1] + pFrame->translate[1]) * getRobotModel().m_fScale;
			v[1] = (pFrame->scale[2] * pVert->v[2] + pFrame->translate[2]) * getRobotModel().m_fScale;
			
			// verify on x position
			if(v[0] > xmax)
				xmax = v[0];
			else if(v[0] < xmin)
				xmin = v[0];
		
			// verify on y position
			if(v[1] > ymax)
				ymax = v[1];
			else if(v[1] < ymin)
				ymin = v[1];
		}
	}
	
	xmin *= state.getScale();
	xmax *= state.getScale();
	ymin *= state.getScale();
	ymax *= state.getScale();
	
	printf("CALCUL BOUND BOX xmin %.2f xmax %.2f ymin %.2f ymax %.2f\n", xmin, xmax, ymin, ymax);
	
	box_.x = (xmax-xmin)/2.0 + state.getPosition()[0];
	box_.y = (ymax-ymin)/2.0 + state.getPosition()[1];
	box_.width = xmax-xmin;
	box_.height = ymax-ymin;*/
	
	return box_;
}

void Boxman::setMovement(Movement * newMovement)
{
	//std::cout << "-----SET MOVEMENT" << std::endl;
	if(newMovement == NULL)
		return;
		
	if(movement != NULL)
	{
		delete movement;
	}
	
	movement = newMovement;
}

void Boxman::beTouched(int direction, Boxman* agressor)
{
	int idAgressor = agressor->id();
	//std::cout << "damages: " << this->getRobotState().getDamages() << std::endl;
	if(this->getRobotState().isBlocking())
	{
// A FAIRE
		this->getRobotState().shootBlocked() = true;
	}
	else
	{
		this->getRobotState().shootBlocked() = false;
		this->getRobotState().isJumping() = false;
		int forceDamages = 8;
		// damages
		this->getRobotState().getDamages() +=forceDamages;
		// revenge
		for(unsigned int i=0; i<getRevenge().size(); ++i)
		{
			if(getRevenge()[i].first == idAgressor)
				getRevenge()[i].second+=forceDamages;
		}
		// victim
		for(unsigned int i=0; i<agressor->getVictim().size(); ++i)
		{
			if(agressor->getVictim()[i].first == this->id())
				agressor->getVictim()[i].second+=forceDamages;
		}
		//
		if(direction > 0)
			this->getRobotState().getRotation()[1] = 180;
		else
			this->getRobotState().getRotation()[1] = 0;
		if(this->getRobotState().getDamages() < 80 + (float)(rand()/RAND_MAX)*20) // 70 à 90: peut voler ou pas.
			this->setMovement(new Damage(this));
		else
			this->setMovement(new Death(this));
	}
}
