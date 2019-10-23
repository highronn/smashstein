#ifndef __ENDPHYSIK_HPP
#define __ENDPHYSIK_HPP

#include <iostream>#include "SystemParticles.hpp"

class EndPhysik:public SystemParticles{

	private :
	
		std::vector<Particle*> particles;//Ensemble des particules du systeme
		int nbMaxParticle;//le nombre maximum de particules dans le systeme
		int nbparticles;//nombre de particules utilisées dans le systeme
		float speedMax;//la vitesse des particules du systeme
		int lifeTimeMax;//la duree de vie maximum des particules du systeme
		float radius;//la rayon du systeme de particules
		
	public :
	
		EndPhysik(float speedo,int lifeTimeMaximum,float size,int nbMaxParticless);
		EndPhysik(const EndPhysik & fin);
		~EndPhysik(void);
		
		void generateParticles(void);//Creer les particules
		void drawSystemParticles(RTPoint::point3 camera,unsigned int idTexSystemParticles);//Dessine chaque particule du système
		void updateSystemParticles(void);//Actualise le système de particules

};

#endif

