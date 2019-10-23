#include "HitPhysik.hpp"

HitPhysik::HitPhysik(float speedo,int lifeTimeMaximum,float size,int nbMaxParticless){

	nbparticles = 0;	
	speedMax = speedo;
	lifeTimeMax = lifeTimeMaximum;
	radius = size;
	nbMaxParticle = nbMaxParticless;

	generateParticles();
}

void HitPhysik::drawSystemParticles(RTPoint::point3 camera,unsigned int idTexSystemParticles){

	//Application texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D,idTexSystemParticles);
	// Affichage des particules
	glPushMatrix();
	//Rotation(particules à l'horizontale)
	glTranslatef(0.0,-0.5,0.0);
	glRotatef(60.0,0.0,0.0,1.0);
	for(int i=0;i<(int)particles.size();++i){
		float angle = rand()*45.0f/RAND_MAX;
		glPushMatrix();
			glRotatef(angle,0.0,0.0,1.0);
			particles[i]->drawParticle(camera);
		glPopMatrix();
	}
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,0);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void HitPhysik::updateSystemParticles(void){
	//Pour chaque particule
	for(int i=0; i<(int)particles.size();++i){
		//si la particule est arrivée en fin de vie
		if(particles[i]->getCurrentLifeTime() <= 0){
			particles.erase(particles.begin()+i);
			nbparticles--;
		//sinon mise a jour de la particule
		}else{
			particles[i]->updateParticle();
		}
	}
	generateParticles();

}

void HitPhysik::generateParticles(void){

	if(nbparticles < nbMaxParticle){
		int tmp = 0;
		while(tmp==0){
			if(nbMaxParticle - nbparticles == 1) tmp = 1;
			else tmp = RTMath::getRandom(nbMaxParticle - nbparticles);
		}   
		float r1,r2;
		float radius2 = 2.0f * radius;
		float norm;
		nbparticles += tmp;
     
		for(int i=0;i<tmp;++i){       
			do{
				r1 = RTMath::getRandom(radius2) - radius; 
				r2 = RTMath::getRandom(radius2) - radius; 
				norm = sqrtf(r1*r1 + r2*r2);
			}while(norm > radius);

			RTPoint::point3 position(r1,0.0f,r2);
			int pttl = int(lifeTimeMax - (norm * lifeTimeMax / radius));
			float pspeed = RTMath::getRandom(speedMax);

			BillBoard *bill = new BillBoard(position,1.0f,1.0f);
			Particle *part = new Particle(pttl,pspeed,bill);
			particles.push_back(part);
		}
	}
}

