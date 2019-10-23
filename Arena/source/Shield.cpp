#include "Shield.hpp"

Shield::Shield(void){

	//bidons values
	posX = -1.0f;
	posY = -1.0f;
	sizeShield = 1.0f;
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

Shield::Shield(
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
	sizeShield = 1.0f;
	image.position.x = camera.x;	image.position.y = camera.y;	image.position.z = camera.z;
	image.height = w;
	image.width = h;
	fx = new NoPhysik(speedo, lifeTimeMaximum, size, nbMaxParticless);//les effets de particules associées au projectile
	vectPos = position;
	vectDir = direction;
	vectVit = vitesse;
	boundingBox = box;

	sizeSystemP = size;
	speedSystemP = speedo;
	lifeMaxSystemP = lifeTimeMaximum;
	nbMaxParticleSystemP = nbMaxParticless;	
}

void Shield::drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles)
{

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_LIGHTING);

	glPushMatrix();

		glBindTexture(GL_TEXTURE_2D,idTexProjectile);

		glTranslatef(posX,posY,0.0);
		float resize = rand()*1.0f/RAND_MAX/30000.0f;
		
		if(sizeShield<0.1f)
			sizeShield=1.0;
		else
			glScalef(sizeShield-resize,sizeShield-resize,sizeShield-resize);
			
		sizeShield -= resize;		

		image.draw(camera);

		glBindTexture(GL_TEXTURE_2D,0);

	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

std::pair<unsigned int,unsigned int> Shield::loadTextureProjectile(void)
{
	//NB : first = projectile ; second = particules
	int largeurW;
	int longueurH;
	
  	//Creation et chargement des textures dans la carte graphique
  	unsigned char *tex_shield = NULL;
  	tex_shield = load_PPM_RGBA("projectiles/shield.ppm", &largeurW, &longueurH, RTColor::color(0.0,0.0,0.0), NORMAL);
  	
	unsigned int idShield;
	InitGLRGBA(tex_shield,largeurW,longueurH,idShield);

	std::pair<unsigned int,unsigned int> resPair = std::make_pair(idShield, 0);
	return resPair;

}

void Shield::updateProjectiles(void)
{
	//sizeShield+=0.1;
}

