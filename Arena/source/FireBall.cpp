#include <FireBall.hpp>
#include <Fonctions.hpp>

//unsigned char* load_PPMRGBA(const char *path, int *w, int *h, const RTColor::color col, const int & type);

FireBall::FireBall(void)
{

	//bidons values
	posX = -1.0f;
	posY = -1.0f;
	image.position.x = 0;	image.position.y = 0;	image.position.z = 0; 
	image.height = 0.0;
	image.width = 0.0;
	fx = NULL;
	vectPos[0]= 0.0;	vectPos[1]= 0.0;	vectPos[2]= 0.0;
	vectDir[0]= 0.0;	vectDir[1]= 0.0;	vectDir[2]= 0.0;
	vectVit[0]= 0.0;	vectVit[1]= 0.0;	vectVit[2]= 0.0;
	boundingBox.x = 0.0;
	boundingBox.y = 0.0;
	boundingBox.width = 0.0;
	boundingBox.height = 0.0;

	sizeSystemP = 0.0;
	speedSystemP = 0.0;
	lifeMaxSystemP = 0;
	nbMaxParticleSystemP = 0;
}

FireBall::FireBall(
			RTPoint::point3 camera,
			float x,float y,
			float w,float h,
			kn::Vector3f vitesse,
			kn::Vector3f position,
			kn::Vector3f direction,
			const Wrap & box,

			float size,
			float speedo,
			int lifeTimeMaximum,
			int nbMaxParticless )
{

	posX = x;
	posY = y;
	image.position.x = camera.x;	image.position.y = camera.y;	image.position.z = camera.z;
	image.height = w;
	image.width = h;
	fx = new FirePhysik(speedo,lifeTimeMaximum,size,nbMaxParticless);//les effets de particules associées au projectile
	vectPos = position;
	vectDir = direction;
	vectVit = vitesse;
	boundingBox = box;

	sizeSystemP = size;
	speedSystemP = speedo;
	lifeMaxSystemP = lifeTimeMaximum;
	nbMaxParticleSystemP = nbMaxParticless;	
}

//Speficife en fonction du type de projectile, le placement du systeme de particules
void FireBall::drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles)
{
	glDisable(GL_LIGHTING);
	
	glEnable(GL_TEXTURE_2D);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);// activation de la transparence
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ZERO);

	glAlphaFunc(GL_EQUAL, 1);

	glPushMatrix();

	//Dessine le projectile
	glBindTexture(GL_TEXTURE_2D,idTexProjectile);

		glTranslatef(posX,posY,0.0);
		image.draw(camera);

	glBindTexture(GL_TEXTURE_2D,0);

	//Dessine chaque particule du système
	fx->drawSystemParticles(camera,idTexSystemParticles);

	glPopMatrix();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_LIGHTING);
}

//Renvoie les id de tex pour les projectiles concernés(ex: boule de feu ; feu)
std::pair<unsigned int,unsigned int> FireBall::loadTextureProjectile(void)
{

	//NB : first = projectile ; second = particules
	int largeurW;
	int longueurH;
	
  	//Creation et chargement des textures dans la carte graphique
  	unsigned char *tex_boule = NULL;
	tex_boule = load_PPM_RGBA("projectiles/fireball.ppm",&largeurW,&longueurH,RTColor::color(0.0,0.0,0.0),NORMAL);//NORMAL type=1 ; MIRROIR type=2
	unsigned int idBoule;
	InitGLRGBA(tex_boule,largeurW,longueurH,idBoule);
  	unsigned char *tex_feu = NULL;
	tex_feu = load_PPM_RGBA("projectiles/fireballParticle.ppm",&largeurW,&longueurH,RTColor::color(0.0,0.0,0.0),NORMAL);
	unsigned int idFeu;
	InitGLRGBA(tex_feu,largeurW,longueurH,idFeu);

	std::pair<unsigned int,unsigned int> resPair(idBoule,idFeu);
	return resPair;

}

void FireBall::updateProjectiles(void)
{
	//posX += 0.01f;
	fx->updateSystemParticles();
}

