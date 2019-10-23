#include <WaterBall.hpp>
#include <Projectiles.hpp>
#include <Fonctions.hpp>
#include <FirePhysik.hpp>
#include <RTPoint.hpp>

unsigned char* load_PPM(const char *path, int *w, int *h, const int & type);
unsigned char* load_PPM_RGBA(const char *path, int *w, int *h, const RTColor::color & col, const int & type);
void InitGL(unsigned char* image, int & w, int & h, GLuint & id);
void InitGLRGBA(unsigned char* image, int & w, int & h, GLuint & id);

WaterBall::WaterBall(void){

	//bidons values
	posX = -1.0f;
	posY = -1.0f;
	size = 0.0f;
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

WaterBall::WaterBall(
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
	size = 1.0f;
	image.position.x = camera.x;	image.position.y = camera.y;	image.position.z = camera.z;
	image.height = w;
	image.width = h;
	fx = new WaterPhysik(speedo,lifeTimeMaximum,size,nbMaxParticless,posX,posY);//les effets de particules associées au projectile
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
void WaterBall::drawProjectiles(RTPoint::point3 camera, unsigned int idTexProjectile, unsigned int idTexSystemParticles)
{
	glDisable(GL_LIGHTING);
	
	glEnable(GL_TEXTURE_2D);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
	glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND); // Textures melting
	glDisable(GL_BLEND); // Textures melting
	glEnable(GL_ALPHA_TEST); // Transparencing activation
	
	glAlphaFunc(GL_EQUAL, 1);
	
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	glPushMatrix();

	//Dessine le projectile
	glBindTexture(GL_TEXTURE_2D,idTexProjectile);
		/*
		glTranslatef(posX,posY,0.0);
		if(size<2.0f){//la bulle grossie jusqu'à un certain point
			size += 0.001f;
			glScalef(size,size,size);
		}
		*/
		image.draw(camera);

	glBindTexture(GL_TEXTURE_2D,0);

	glPopMatrix();

	//Dessine chaque particule du système
	fx->drawSystemParticles(camera, idTexSystemParticles);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_LIGHTING);
}

std::pair<unsigned int,unsigned int> WaterBall::loadTextureProjectile(void){

	//NB : first = projectile ; second = particules
	int largeurW;
	int longueurH;
	
  	//Creation et chargement des textures dans la carte graphique
  	unsigned char *tex_bulle = NULL;
  	tex_bulle = load_PPM_RGBA("projectiles/waterball.ppm", &largeurW, &longueurH, RTColor::color(0.0,0.0,0.0), NORMAL);//NORMAL type=1 ; MIRROIR type=2
  	
	unsigned int idBulle;
	InitGLRGBA(tex_bulle, largeurW, longueurH, idBulle);
	
  	unsigned char *tex_water = NULL;
  	tex_water = load_PPM_RGBA("projectiles/waterParticle.ppm",&largeurW,&longueurH,RTColor::color(0.0,0.0,0.0),NORMAL);
  	
	unsigned int idWater;
	InitGLRGBA(tex_water, largeurW, longueurH, idWater);

	std::pair<unsigned int,unsigned int> resPair = std::make_pair(idBulle, idWater);
	return resPair;

}

void WaterBall::updateProjectiles(void)
{
	posX += 0.001f;
	fx->updateSystemParticles(posY);
}

