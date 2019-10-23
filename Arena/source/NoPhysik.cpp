#include "NoPhysik.hpp"

NoPhysik::NoPhysik(float speedo,int lifeTimeMaximum,float size,int nbMaxParticless)
{

	speedo = 0;
	lifeTimeMaximum = 0;
	size = 0.0;
	nbMaxParticless = 0;

	nbparticles = 0;	
	speedMax = 0.0f;
	lifeTimeMax = 0;
	radius = 0.0f;
	nbMaxParticle = 0;
	
	generateParticles();
}

void NoPhysik::generateParticles(void)
{
	//NoPhysik = pas de particules
}

