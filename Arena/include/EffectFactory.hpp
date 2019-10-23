#ifndef __EFFECTFACTORY_HPP
#define __EFFECTFACTORY_HPP

#include <iostream>
#include <OpenKN/math/Vector3.hpp>
#include "RTVector.hpp"
#include "RTPoint.hpp"
#include "CocoNut.hpp"
#include "End.hpp"
#include "ExplodingCube.hpp"
#include "FireBall.hpp"
#include "Hit.hpp"
#include "Shield.hpp"
#include "WaterBall.hpp"

class EffectFactory
{
	private :

		//Attribut
		static EffectFactory* instance;
		RTPoint::point3 camera;
		kn::Vector3f vitesse;
		kn::Vector3f position;
		kn::Vector3f direction;

		//constructeur en privé
		EffectFactory(void) {};
	public :

		static EffectFactory & getInstance(void);
		EffectFactory(const EffectFactory & factor);
		~EffectFactory(void);

		RTPoint::point3 getCamera(void);

		CocoNut* giveMeACocoNut(void);
		End* giveMeTheEnd(void);
		ExplodingCube* giveMeAnExplodingCube(void);
		FireBall* giveMeAFireBall(void);
		Hit* giveMeAHit(void);
		Shield* giveMeAShield(void);
		WaterBall* giveMeAWaterBall(void);						
			
};

#endif

