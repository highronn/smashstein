#ifndef __COCONUT_HPP
#define __COCONUT_HPP

#include <iostream>
#include "Projectiles.hpp"
#include "Fonctions.hpp"
#include "NoPhysik.hpp"

class CocoNut:public Projectiles
{

	public :

		float posX;//position
		float posY;
		
	public :
		float rot;
		int timeStart;
		int idLauncher;
		
	public :
		float rotation;
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
	
		CocoNut(void);
		CocoNut(
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
		CocoNut(const CocoNut & project);
		~CocoNut(void);
		
		//speficife en fonction du type de projectile, le placement du systeme de particules
		void drawProjectiles(const RTPoint::point3 & camera, const unsigned int & idTexProjectile, const unsigned int & idTexSystemParticles);
		//renvoie les id de tex pour les projectiles concernés(ex: boule de feu ; feu)
		static std::pair<unsigned int,unsigned int> loadTextureProjectile(void);//first = projectile ; second = particules
		void updateProjectiles(void);//Actualise le projectile
	
};

#endif

