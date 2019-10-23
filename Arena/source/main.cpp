#include <main.hpp>
#include <Application.hpp>
#include <variables.hpp>
#include <Fonctions.hpp>
#include <Sound.hpp>
#include <Animation.hpp>
#include <EffectFactory.hpp>

QTime TIMER;

int TEST = RUN;
/*
void onQuit()
{
	std::cout << "Thanks for playing" << std::endl << std::endl;
}*/

int main(int argc, char **argv)
{
	//std::set_terminate(onQuit);

	// Load the sound system
	Sound::globalSoundInit();
	Sound::setMasterVolume(0.7);
	Sound::setMusicVolume(0.7);

	// Load the projectile system
	EffectFactory factory = EffectFactory::getInstance();

	Application app;
	app.execute(argc,argv);

	return EXIT_SUCCESS;
}

