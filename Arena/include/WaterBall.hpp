#ifndef __WATERBALL_HPP
#define __WATERBALL_HPP

#include <iostream>
#include "Projectiles.hpp"
//#include "Fonctions.hpp"
#include "WaterPhysik.hpp"
#include "RTPoint.hpp"

class WaterBall:public Projectiles
{
	public :
		float posX;//position
		float posY;
		float size;//taille
		BillBoard image;//l'image du projectile
		WaterPhysik *fx;//les effets de particules associées au projectile
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
		float rot;
		int timeStart;
		int idLauncher;
		
	public :
	
		WaterBall(void);
		WaterBall(
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
		WaterBall(const WaterBall & project);
		~WaterBall(void);
		
		//speficife en fonction du type de projectile, le placement du systeme de particules
		void drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles);
		//renvoie les id de tex pour les projectiles concernés(ex: boule de feu ; feu)
		static std::pair<unsigned int,unsigned int> loadTextureProjectile(void);//first = projectile ; second = particules
		void updateProjectiles(void);//Actualise le projectile
	
};

#endif

