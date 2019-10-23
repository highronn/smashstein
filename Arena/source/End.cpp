#include <End.hpp>
#include <Fonctions.hpp>

End::End()
{
	// Dumb values
	posX = -1.0f;
	posY = -1.0f;
	timeEnd = 15;
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

End::End(
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
	timeEnd = 15;
	image.position.x = camera.x;	image.position.y = camera.y;	image.position.z = camera.z;
	image.height = w;
	image.width = h;
	fx = new EndPhysik(speedo,lifeTimeMaximum,size,nbMaxParticless);//les effets de particules associées au projectile
	vectPos = position;
	vectDir = direction;
	vectVit = vitesse;
	boundingBox = box;

	sizeSystemP = size;
	speedSystemP = speedo;
	lifeMaxSystemP = lifeTimeMaximum;
	nbMaxParticleSystemP = nbMaxParticless;	
}

//Specify placement of particle system
void End::drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_LIGHTING);

	glPushMatrix();
		// Draweach particles
		glTranslatef(posX,posY,0.0);
		fx->drawSystemParticles(camera,idTexSystemParticles);
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

std::pair<unsigned int,unsigned int> End::loadTextureProjectile()
{
	//NB : first = projectile ; second = particules
	int largeurW;
	int longueurH;
	
  	//Creation et chargement des textures dans la carte graphique
  	unsigned char *tex_end = NULL;
  	tex_end = load_PPM_RGBA("particles/end.ppm", &largeurW, &longueurH, RTColor::color(0.0,0.0,0.0),NORMAL);
  	
	unsigned int idEnd;
	InitGLRGBA(tex_end,largeurW,longueurH,idEnd);

	std::pair<unsigned int,unsigned int> resPair = std::make_pair(0,idEnd);
	return resPair;

}

void End::updateProjectiles()
{
	fx->updateSystemParticles();
}

