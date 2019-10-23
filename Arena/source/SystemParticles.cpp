#include "SystemParticles.hpp"
#include "Particle.hpp"

SystemParticles::SystemParticles(void){

	nbparticles = 0;	
	speedMax = 0.0;
	lifeTimeMax = 0;
	radius = 0.0;
	nbMaxParticle = 0;
}

SystemParticles::SystemParticles(float speedo,int lifeTimeMaximum,float size,int nbMaxParticless){

	nbparticles = 0;	
	speedMax = speedo;
	lifeTimeMax = lifeTimeMaximum;
	radius = size;
	nbMaxParticle = nbMaxParticless;
	
	generateParticles();
}

SystemParticles::SystemParticles(const SystemParticles & sys){
	particles = sys.particles;
	nbMaxParticle = sys.nbMaxParticle;
	speedMax = sys.speedMax;
	lifeTimeMax = sys.lifeTimeMax;
	radius = sys.radius;
}

SystemParticles::~SystemParticles(void){
	for(int i=0;i<(int)(particles.size());i++){
		delete particles[i];
	}
}

void SystemParticles::generateParticles(){

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

			BillBoard *bill = new BillBoard(position,0.2f,0.2f);
			Particle *part = new Particle(pttl,pspeed,bill);
			particles.push_back(part);
		}
	}
}

void SystemParticles::drawSystemParticles(RTPoint::point3 camera,unsigned int idTexSystemParticles){
    	//Application texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D,idTexSystemParticles);
	// Affichage des particules
	for(int i=0;i<(int)particles.size();++i){
		particles[i]->drawParticle(camera);
	}
	glBindTexture(GL_TEXTURE_2D,0);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void SystemParticles::updateSystemParticles(void){
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

