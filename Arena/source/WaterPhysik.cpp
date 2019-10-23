#include "WaterPhysik.hpp"

WaterPhysik::WaterPhysik(float speedo,int lifeTimeMaximum,float size,int nbMaxParticless,float posinitX,float posinitY){

	posInitialeX = posinitX;
	posInitialeY = posinitY;
	delta = 0;
	nbparticles = 0;	
	speedMax = speedo;
	lifeTimeMax = lifeTimeMaximum;
	radius = size;
	nbMaxParticle = nbMaxParticless;

	generateParticles();
}

void WaterPhysik::drawSystemParticles(RTPoint::point3 camera,unsigned int idTexSystemParticles)
{
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D, idTexSystemParticles);

	/*glPushMatrix();
		//Rotation(particules à l'horizontale)
		glRotatef(-70.0,0.0,0.0,1.0);
		float angle = 0.0; 
		
		for(int i=0;i<(int)particles.size();++i)
		{
			angle = rand()*30.0f/RAND_MAX;
			glPushMatrix();
				glRotatef(angle,0.0,0.0,1.0);
				particles[i]->drawParticle(camera);
			glPopMatrix();
		}
	glPopMatrix();*/
	// draw particules around the billboard
	glPushMatrix();
		//Rotation(particules à l'horizontale)
		float angle = 0.0; 
		
		for(int i=0; i<(int)((float)particles.size()/4.0); ++i)
		{
			angle = rand()*30.0f/RAND_MAX;
			glPushMatrix();
				glRotatef(angle,0.0,0.0,1.0);
				particles[i]->drawParticle(camera);
			glPopMatrix();
		}
		
		glRotatef(90.0, 0.0, 0.0, 1.0);
		for(int i=((int)((float)particles.size()/4.0)); i<2*((int)((float)particles.size()/4.0)); ++i)
		{
			angle = rand()*30.0f/RAND_MAX;
			glPushMatrix();
				glRotatef(angle,0.0,0.0,1.0);
				particles[i]->drawParticle(camera);
			glPopMatrix();
		}
		
		glRotatef(90.0, 0.0, 0.0, 1.0);
		for(int i=2*((int)((float)particles.size()/4.0)); i<3*((int)((float)particles.size()/4.0)); ++i)
		{
			angle = rand()*30.0f/RAND_MAX;
			glPushMatrix();
				glRotatef(angle,0.0,0.0,1.0);
				particles[i]->drawParticle(camera);
			glPopMatrix();
		}
		
		glRotatef(90.0, 0.0, 0.0, 1.0);
		for(int i=3*((int)((float)particles.size()/4.0)); i<4*((int)((float)particles.size()/4.0)); ++i)
		{
			angle = rand()*30.0f/RAND_MAX;
			glPushMatrix();
				glRotatef(angle,0.0,0.0,1.0);
				particles[i]->drawParticle(camera);
			glPopMatrix();
		}
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D,0);
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void WaterPhysik::updateSystemParticles(float newposY){
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
	delta = posInitialeY - newposY;
	generateParticles();

}

void WaterPhysik::generateParticles(void){

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

			RTPoint::point3 position(r1,delta,r2);
			int pttl = int(lifeTimeMax - (norm * lifeTimeMax / radius));
			float pspeed = RTMath::getRandom(speedMax);

			BillBoard *bill = new BillBoard(position,2.0f,2.0f);
			Particle *part = new Particle(pttl,pspeed,bill);
			particles.push_back(part);
		}
	}
}

