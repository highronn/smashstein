#ifndef __PARTICLE_HPP
#define __PARTICLE_HPP

#include <GL/glut.h>
#include <iostream>
#include "BillBoard.hpp"
//#include <variables.hpp>

class Particle{

	private :

		BillBoard *image;
		float alpha;//transparence de la particule
		int lifeTime;//durée de vie totale de la particle
		int currentLifeTime;//durée de vie courante de la particle
		float speed;//vitesse de la particle
		int t;//date de la derniere mise a jour (millisecondes)		
		
	public :

		Particle(void);
		Particle(int currentLifeTime,float speed,BillBoard *bill);
		Particle(const Particle & parti);
		~Particle(void);
	
		inline int getCurrentLifeTime(void){return currentLifeTime;};
		inline void setCurrentLifeTime(int pv){currentLifeTime = pv;};
		void drawParticle(RTPoint::point3 camera);
		void updateParticle(void);
	
};

#endif

