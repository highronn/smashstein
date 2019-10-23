#include "Hit.hpp"

Hit::Hit(void){

	//bidons values
	posX = -1.0f;
	posY = -1.0f;
	timeHit = 15;
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

Hit::Hit(
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
			int nbMaxParticless ){

	posX = x;
	posY = y;
	timeHit = 15;
	image.position.x = camera.x;	image.position.y = camera.y;	image.position.z = camera.z;
	image.height = w;
	image.width = h;
	fx = new HitPhysik(speedo,lifeTimeMaximum,size,nbMaxParticless);//les effets de particules associées au projectile
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
void Hit::drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles){

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_LIGHTING);

	glPushMatrix();

		glBindTexture(GL_TEXTURE_2D,idTexProjectile);

		glTranslatef(posX,posY,0.0);
		image.draw(camera);

		glBindTexture(GL_TEXTURE_2D,0);

		//Dessine chaque particule du système
		fx->drawSystemParticles(camera,idTexSystemParticles);

	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

std::pair<unsigned int,unsigned int> Hit::loadTextureProjectile(void){

	//NB : first = projectile ; second = particules
	int largeurW;
	int longueurH;
	
  	//Creation et chargement des textures dans la carte graphique
  	unsigned char *tex_hit = NULL;
  	//tex_hit = load_PPMRGBA("hit.ppm",&largeurW,&longueurH,RTColor::color(0.0,0.0,0.0),NORMAL);//NORMAL type=1 ; MIRROIR type=2
	unsigned int idHit;
	InitGLRGBA(tex_hit,largeurW,longueurH,idHit);

  	unsigned char *tex_blood = NULL;
  	//tex_blood = load_PPMRGBA("blood.ppm",&largeurW,&longueurH,RTColor::color(0.0,0.0,0.0),NORMAL);
	unsigned int idBlood;
	InitGLRGBA(tex_blood,largeurW,longueurH,idBlood);

	std::pair<unsigned int,unsigned int> resPair = std::make_pair(idHit,idBlood);
	return resPair;

}

void Hit::updateProjectiles(void){

	fx->updateSystemParticles();
}

