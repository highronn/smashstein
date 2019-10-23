#include "Projectiles.hpp"

Projectiles::Projectiles(void){

	//bidons values
	posX = -1.0f;
	posy = -1.0f;
	image.position.x = 0;
	image.position.y = 0; 
	image.position.z = 0; 
	image.height = 0.0;
	image.width = 0.0;  
	vectPos[0]= 0.0;	vectPos[1]= 0.0;	vectPos[2]= 0.0;
	vectDir[0]= 0.0;	vectDir[1]= 0.0;	vectDir[2]= 0.0;
	vectVit[0]= 0.0;	vectVit[1]= 0.0;	vectVit[2]= 0.0;
	boundingBox.x = 0.0;
	boundingBox.y = 0.0;
	boundingBox.width = 0.0;
	boundingBox.height = 0.0;
}

Projectiles::Projectiles(RTPoint::point3 camera,float x,float y,float w,float h,kn::Vector3f vitesse,kn::Vector3f position,kn::Vector3f direction,const Wrap & box){
	posX = x;
	posy = y;	
	image.position.x = camera.x;
	image.position.y = camera.y;
	image.position.z = camera.z;
	image.height = w;
	image.width = h; 
	vectPos = position;
	vectDir = direction;
	vectVit = vitesse;
	boundingBox = box;
}

Projectiles::Projectiles(const Projectiles & project){
	posX = project.posX;
	posy = project.posy;	
	image = project.image;
	vectPos = project.vectPos;
	vectDir = project.vectDir;
	vectVit = project.vectVit;
	boundingBox = project.boundingBox;
}

Projectiles::~Projectiles(void){

}

