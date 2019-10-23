#include "FirePhysik.hpp"

FirePhysik::FirePhysik(float speedo,int lifeTimeMaximum,float size,int nbMaxParticless)
{
	nbparticles = 0;	
	speedMax = speedo;
	lifeTimeMax = lifeTimeMaximum;
	radius = size;
	nbMaxParticle = nbMaxParticless;

	generateParticles();
}

void FirePhysik::drawSystemParticles(RTPoint::point3 camera, unsigned int idTexSystemParticles)
{
	//Application texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glDisable(GL_LIGHTING);
	
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glBindTexture(GL_TEXTURE_2D,idTexSystemParticles);
	
	// Drawing of particles
	glPushMatrix();
		//Rotation(particules à l'horizontale)
		glRotatef(90.0,0.0,0.0,1.0);
		for(int i=0;i<(int)particles.size();++i)
		{
			particles[i]->drawParticle(camera);
		}	
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,0);
	
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);
	
	glDisable(GL_TEXTURE_2D);
}

void FirePhysik::updateSystemParticles(void)
{
	for(unsigned int i=0; i<particles.size();++i)
	{
		//si la particule est arrivée en fin de vie
		if(particles[i]->getCurrentLifeTime() <= 0)
		{
			particles.erase(particles.begin()+i);
			nbparticles--;
			//sinon mise a jour de la particule
		}
		else
		{
			particles[i]->updateParticle();
		}
	}
	generateParticles();

}

void FirePhysik::generateParticles(void){

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

			BillBoard *bill = new BillBoard(position,0.5f,0.5f);
			Particle *part = new Particle(pttl,pspeed,bill);
			particles.push_back(part);
		}
	}
}

