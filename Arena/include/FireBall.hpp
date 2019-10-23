#ifndef __FIREBALL_HPP
#define __FIREBALL_HPP

#include <iostream>
#include <Projectiles.hpp>
#include <Fonctions.hpp>
#include <FirePhysik.hpp>
#include <RTPoint.hpp>

class FireBall:public Projectiles
{
	public:
			float posX;//position
			float posY;
			int timeStart;
			int idLauncher; // robot qui a lancé le projectile
	private :
			BillBoard image;//l'image du projectile
			FirePhysik *fx;//les effets de particules associées au projectile
			kn::Vector3f vectPos;//vecteur position
			kn::Vector3f vectDir;//vecteur direction
	public:
			kn::Vector3f vectVit;//vecteur vitesse
			float rot;// rotation
			Wrap boundingBox;//gestion des collisions
	private:
			//Attribut lies aux particules
			float sizeSystemP;
			float speedSystemP;
			int lifeMaxSystemP;
			int nbMaxParticleSystemP;
		
	public :
	
		FireBall(void);
		FireBall(
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
		FireBall(const FireBall & project);
		~FireBall(void);
		
		//speficife en fonction du type de projectile, le placement du systeme de particules
		void drawProjectiles(RTPoint::point3 camera,unsigned int idTexProjectile,unsigned int idTexSystemParticles);
		//renvoie les id de tex pour les projectiles concernés(ex: boule de feu ; feu)
		static std::pair<unsigned int,unsigned int> loadTextureProjectile(void);//first = projectile ; second = particules
		void updateProjectiles(void);//Actualise le projectile
	
};

#endif

