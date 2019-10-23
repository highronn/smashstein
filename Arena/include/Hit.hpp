#ifndef __HIT_HPP
#define __HIT_HPP

#include <iostream>
#include "Projectiles.hpp"
#include "Fonctions.hpp"
#include "HitPhysik.hpp"

class Hit:public Projectiles{

	private :

		float posX;//position
		float posY;
		int timeHit;//durée de vie du bilboard
		BillBoard image;//l'image du projectile
		HitPhysik *fx;//les effets de particules associées au projectile
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
	
		Hit(void);
		Hit(
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
		Hit(const Hit & project);
		~Hit(void);
		
		void drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles);
		static std::pair<unsigned int,unsigned int> loadTextureProjectile(void);
		void updateProjectiles(void);
	
};

#endif

