#ifndef _PROJECTILES_HPP
#define _PROJECTILES_HPP
#include <iostream>
#include <OpenKN/math/Vector3.hpp>
#include "BillBoard.hpp"
#include "SystemParticles.hpp"
#include "Wrap.hpp"
#include "RTMath.hpp"
#include "RTPoint.hpp"

class Projectiles{

	private :

		float posX;
		float posy;
		float largeur;
		float hauteur;
		BillBoard image;//l'image du projectile
		kn::Vector3f vectPos;//vecteur position
		kn::Vector3f vectDir;//vecteur direction
		kn::Vector3f vectVit;//vecteur vitesse
		Wrap boundingBox;//gestion des collisions

	public :

		Projectiles(void);
		Projectiles(
				RTPoint::point3 camera,
				float x,float y,
				float w,float h,
				kn::Vector3f vitesse,
				kn::Vector3f position,
				kn::Vector3f direction,
				const Wrap & box
		);
		Projectiles(const Projectiles & project);
		~Projectiles(void);

		//speficife en fonction du type de projectile, le placement du systeme de particules
		void drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles);
		//renvoie les id de tex pour les projectiles concern�s(ex: boule de feu ; feu)
		static std::pair<unsigned int,unsigned int> loadTextureProjectile(void);//first = projectile ; second = particules

};

#endif

