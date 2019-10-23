#include "EffectFactory.hpp"

//Initialisé à NULL
EffectFactory* EffectFactory::instance = NULL;

EffectFactory & EffectFactory::getInstance(void)
{
	if(instance==NULL)
	{
		instance = new EffectFactory();
		instance->camera = RTPoint::point3(0.0,0.0,0.0);

		instance->vitesse[0] = 2.0;
		instance->vitesse[1] = 0.0;
		instance->vitesse[2] = 0.0;

		instance->position[0] = 0.0;
		instance->position[1] = 0.0;
		instance->position[2] = 0.0;

		instance->direction[0] = 1.0;
		instance->direction[1] = 0.0;
		instance->direction[2] = 0.0;
	}
	/*else
	{
		std::cout << "In function __static UniqueObject* EffectFactory::getInstance__ : singleton already created " << std::endl;
	}*/

	return *instance;
}

EffectFactory::EffectFactory(const EffectFactory & factory)
{
	instance->camera = factory.camera;
	instance->vitesse[0] = factory.vitesse[0];
	instance->vitesse[1] = factory.vitesse[1];
	instance->vitesse[2] = factory.vitesse[2];
	instance->position[0] = factory.position[0];
	instance->position[1] = factory.position[1];
	instance->position[2] = factory.position[2];
	instance->direction[0] = factory.direction[0];
	instance->direction[1] = factory.direction[1];
	instance->direction[2] = factory.direction[2];		
}

EffectFactory::~EffectFactory(void)
{

}

RTPoint::point3 EffectFactory::getCamera(void)
{
	//remporaire
	return RTPoint::point3(0.0,0.0,0.0);
}


CocoNut* EffectFactory::giveMeACocoNut(void)
{
	camera = getCamera();

	//Construction de la bounding box
	Wrap *box = new Wrap();
	box->x = 0.0f;	box->y = 0.0f;//Position bounding box
	box->width = 5.0f;	box->height = 5.0f;//Taille bounding box

	//Construction du projectile
	CocoNut *tmp = NULL; 
	tmp = new CocoNut(
		camera,//Position camera
		0.0f,0.0f,//Position du projectile
		5.0f,5.0f,//Largeur et hauteur du projectile
		vitesse,position,direction,//Vecteurs associés au projectile (initialisés à 0)
		*box,//Bounding box
		0.0f,//Rayon du sytème de particules	
		0.0f,//vitesse particules
		0,//durée de vie des particules
		0//nb de particules		
	);

	return tmp;
}


End* EffectFactory::giveMeTheEnd(void)
{
	
	camera = getCamera();

	//Construction de la bounding box
	Wrap *box = new Wrap();
	box->x = 0.0f;	box->y = 0.0f;//Position bounding box
	box->width = 0.1f;	box->height = 0.1f;//Taille bounding box

	//Construction du projectile
	End *tmp = NULL; 
	tmp = new End(
		camera,//Position camera
		0.0f,0.0f,//Position du projectile
		0.1f,0.1f,//Largeur et hauteur du projectile
		vitesse,position,direction,//Vecteurs associés au projectile (initialisés à 0)
		*box,//Bounding box
		0.5f,//Rayon du sytème de particules	
		100.0f,//vitesse particules
		75,//durée de vie des particules
		50//nb de particules		
	);

	return tmp;
}

ExplodingCube* EffectFactory::giveMeAnExplodingCube(void)
{

	camera = getCamera();

	//Construction de la bounding box
	Wrap *box = new Wrap();
	box->x = 0.0f;	box->y = 0.0f;//Position bounding box
	box->width = 5.0f;	box->height = 5.0f;//Taille bounding box

	//Construction du projectile
	ExplodingCube *tmp = NULL; 
	tmp = new ExplodingCube(
		camera,//Position camera
		0.0f,0.0f,//Position du projectile
		5.0f,5.0f,//Largeur et hauteur du projectile
		vitesse,position,direction,//Vecteurs associés au projectile (initialisés à 0)
		*box,//Bounding box
		0.0f,//Rayon du sytème de particules	
		0.0f,//vitesse particules
		0,//durée de vie des particules
		0//nb de particules		
	);

	return tmp;
}

FireBall* EffectFactory::giveMeAFireBall(void)
{

	camera = getCamera();

	//Construction de la bounding box
	Wrap *box = new Wrap();
	box->x = 0.0f;	box->y = 0.0f;//Position bounding box
	box->width = 5.0f;	box->height = 5.0f;//Taille bounding box

	//Construction du projectile
	FireBall *tmp = NULL; 
	tmp = new FireBall(
		camera,//Position camera
		0.0f,0.0f,//Position du projectile
		5.0f,5.0f,//Largeur et hauteur du projectile
		vitesse,position,direction,//Vecteurs associés au projectile (initialisés à 0)
		*box,//Bounding box
		2.5f,//Rayon du sytème de particules	
		300.0f,//vitesse particules
		150,//durée de vie des particules
		100//nb de particules		
	);

	return tmp;
}

Hit* EffectFactory::giveMeAHit(void)
{

	camera = getCamera();

	//Construction de la bounding box
	Wrap *box = new Wrap();
	box->x = 0.0f;	box->y = 0.0f;//Position bounding box
	box->width = 0.1f;	box->height = 0.1f;//Taille bounding box

	//Construction du projectile
	Hit *tmp = NULL; 
	tmp = new Hit(
		camera,//Position camera
		0.0f,0.0f,//Position du projectile
		10.0f,5.0f,//Largeur et hauteur du projectile
		vitesse,position,direction,//Vecteurs associés au projectile (initialisés à 0)
		*box,//Bounding box
		1.0f,//Rayon du sytème de particules	
		100.0f,//vitesse particules
		200,//durée de vie des particules
		50//nb de particules		
	);

	return tmp;
}


Shield* EffectFactory::giveMeAShield(void)
{
	camera = getCamera();

	//Construction de la bounding box
	Wrap *box = new Wrap();
	box->x = 0.0f;	box->y = 0.0f;//Position bounding box
	box->width = 0.1f;	box->height = 0.1f;//Taille bounding box

	//Construction du projectile
	Shield *tmp = NULL; 
	tmp = new Shield(
		camera,//Position camera
		0.0f,0.0f,//Position du projectile
		10.0f,10.0f,//Largeur et hauteur du projectile
		vitesse,position,direction,//Vecteurs associés au projectile (initialisés à 0)
		*box,//Bounding box
		0.0f,//Rayon du sytème de particules	
		0.0f,//vitesse particules
		0,//durée de vie des particules
		0//nb de particules		
	);

	return tmp;
}

WaterBall* EffectFactory::giveMeAWaterBall(void)
{
	camera = getCamera();

	//Construction de la bounding box
	Wrap *box = new Wrap();
	box->x = 0.0f;	box->y = 0.0f;//Position bounding box
	box->width = 5.0f;	box->height = 5.0f;//Taille bounding box

	//Construction du projectile
	WaterBall *tmp = NULL; 
	/*tmp = new WaterBall(
		camera,//Position camera
		0.0f,0.0f,//Position du projectile
		5.0f,5.0f,//Largeur et hauteur du projectile
		vitesse,position,direction,//Vecteurs associés au projectile (initialisés à 0)
		*box,//Bounding box
		2.5f,//Rayon du sytème de particules	
		50.0f,//vitesse particules
		800,//durée de vie des particules
		100//nb de particules		
	);*/
	
	tmp = new WaterBall(
		camera,//Position camera
		0.0f,0.0f,//Position du projectile
		5.0f,5.0f,//Largeur et hauteur du projectile
		vitesse,position,direction,//Vecteurs associés au projectile (initialisés à 0)
		*box,//Bounding box
		2.5f,//Rayon du sytème de particules	
		50.0f,//vitesse particules
		165,//durée de vie des particules
		100//nb de particules		
	);

	return tmp;	
}

