#ifndef __SHIELD_HPP
#define __SHIELD_HPP

#include <iostream>
#include "Projectiles.hpp"
#include "Fonctions.hpp"
#include "NoPhysik.hpp"

class Shield:public Projectiles{

	private :

		float posX;//position
		float posY;
		float sizeShield;
		BillBoard image;//l'image du projectile
		NoPhysik *fx;//les effets de particules associées au projectile
		kn::Vector3f vectPos;//vecteur position
		kn::Vector3f vectDir;//vecteur direction
		kn::Vector3f vectVit;//vecteur vitesse
		Wrap boundingBox;//gestion des collisions

		//Attribut lies aux particules
		float sizeSystemP;
		float speedSystemP;
		int lifeMaxSystemP;
		int nbMaxParticleSystemP;
		
	public :
	
		Shield(void);
		Shield(
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
			int nbMaxParticless
		);
		Shield(const Shield & project);
		~Shield(void);
		
		void drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles);
		static std::pair<unsigned int,unsigned int> loadTextureProjectile(void);
		void updateProjectiles(void);
	
};

#endif

