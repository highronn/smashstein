#ifndef __END_HPP
#define __END_HPP

#include <iostream>
#include <Projectiles.hpp>
#include <EndPhysik.hpp>

class End:public Projectiles{

	private :

		float posX;//position
		float posY;
		int timeEnd;//durée de vie du bilboard
		BillBoard image;//l'image du projectile
		EndPhysik *fx;//les effets de particules associées au projectile
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
	
		End();
		End(
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
		End(const End & project);
		~End();
		
		void drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles);
		static std::pair<unsigned int,unsigned int> loadTextureProjectile();
		void updateProjectiles();
};

#endif

