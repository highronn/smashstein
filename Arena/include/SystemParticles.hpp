#ifndef __SYSTEMPARTICLES_HPP
#define __SYSTEMPARTICLES_HPP

#include <iostream>
#include <vector>
#include "RTMath.hpp"
#include "BillBoard.hpp"
#include "Particle.hpp"

class SystemParticles{

	private :
	
		std::vector<Particle*> particles;//Ensemble des particules du systeme
		int nbMaxParticle;//le nombre maximum de particules dans le systeme
		int nbparticles;//nombre de particules utilisées dans le systeme
		float speedMax;//la vitesse des particules du systeme
		int lifeTimeMax;//la duree de vie maximum des particules du systeme
		float radius;//la rayon du systeme de particules
		
	public :
	
		SystemParticles(void);
		SystemParticles(float speedo,int lifeTimeMaximum,float size,int nbMaxParticless);
		SystemParticles(const SystemParticles & sys);
		~SystemParticles(void);
		
		void generateParticles(void);//Creer les particules
		void drawSystemParticles(RTPoint::point3 camera,unsigned int idTexSystemParticles);//Dessine chaque particule du système
		void updateSystemParticles(void);//Actualise le système de particules

};

#endif

