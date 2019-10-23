#ifndef __WATERPHYSIK_HPP
#define __WATERPHYSIK_HPP

#include <iostream>#include "SystemParticles.hpp"

class WaterPhysik:public SystemParticles{

	private :
	
		std::vector<Particle*> particles;//Ensemble des particules du systeme
		int nbMaxParticle;//le nombre maximum de particules dans le systeme
		int nbparticles;//nombre de particules utilisées dans le systeme
		float speedMax;//la vitesse des particules du systeme
		int lifeTimeMax;//la duree de vie maximum des particules du systeme
		float radius;//la rayon du systeme de particules
		float posInitialeX;//position initiale du systeme
		float posInitialeY;
		float delta;
		
	public :
	
		WaterPhysik(float speedo,int lifeTimeMaximum,float size,int nbMaxParticless,float posX,float posY);
		WaterPhysik(const WaterPhysik & water);
		~WaterPhysik(void);
		
		void generateParticles(void);//Creer les particules
		void drawSystemParticles(RTPoint::point3 camera,unsigned int idTexSystemParticles);//Dessine chaque particule du système
		void updateSystemParticles(float newposY);//Actualise le système de particules

};

#endif

