#include <Sound.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
#include <stdio.h>

int channelsplaying = 0;

// Système
FMOD::System  *Sound::sys = NULL;
// Effets
FMOD::DSP *Sound::dsplowpass    = 0;
FMOD::DSP *Sound::dsphighpass   = 0;
FMOD::DSP *Sound::dspecho       = 0;
FMOD::DSP *Sound::dspflange     = 0;
FMOD::DSP *Sound::dspdistortion = 0;
FMOD::DSP *Sound::dspchorus     = 0;
FMOD::DSP *Sound::dspparameq    = 0;
bool Sound::globalSoundError = false;
// Volume général
//float Sound::masterVolume = 1.0f;
FMOD::ChannelGroup *Sound::musicGroup = NULL;
FMOD::ChannelGroup *Sound::effectGroup = NULL;

// Initlalisation du système sonore (static)
bool Sound::globalSoundInit(){
	if(sys == NULL && !globalSoundError){
		FMOD_RESULT result;
		unsigned int fmodVersion;
		 result = FMOD::System_Create(&sys);
		 if(sys == NULL || result != FMOD_OK){
			 printf("fmod can't load : \n(Fmod error n°%d : %s)\n", result, FMOD_ErrorString(result));
			 globalSoundError = true;
			 return false;
		 }
		 result = sys->getVersion(&fmodVersion);
		 if(sys == NULL || result != FMOD_OK){
			 printf("fmod can't load : \n(Fmod error n°%d : %s)\n", result, FMOD_ErrorString(result));
			 globalSoundError = true;
			 return false;
		 }
		 if (fmodVersion < FMOD_VERSION)
		 {
			  printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", fmodVersion, FMOD_VERSION);
			  globalSoundError = true;
			  return false;
		 }
		 result = sys->init(32, FMOD_INIT_NORMAL, NULL);
		 if( result != FMOD_OK)
		 {
			 printf("Error, the sound lib (fmod) may be not correctly installed or your sound card may be busy...\nThe game will be played without sound \n(Fmod error n°%d : %s)\n", result, FMOD_ErrorString(result));
			  globalSoundError = true;
		 }

		 // Chargement d'effets
		 sys->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsplowpass);
		 sys->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &dsphighpass);
		 sys->createDSPByType(FMOD_DSP_TYPE_ECHO, &dspecho);
		 sys->createDSPByType(FMOD_DSP_TYPE_FLANGE, &dspflange);
		 sys->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &dspdistortion);
		 sys->createDSPByType(FMOD_DSP_TYPE_CHORUS, &dspchorus);
		 sys->createDSPByType(FMOD_DSP_TYPE_PARAMEQ, &dspparameq);

		 FMOD::ChannelGroup *masterGroup; // recuperation du masterGroup
		 sys->getMasterChannelGroup(&masterGroup);
		 // Music group
		 sys->createChannelGroup("musics", &musicGroup); // création du groupe "musicGroup"
		 masterGroup->addGroup(musicGroup);
		 sys->getMasterChannelGroup(&masterGroup);
		 // Effect group
		 sys->createChannelGroup("effects", &effectGroup); // création du groupe "effectGroup"
		 masterGroup->addGroup(effectGroup);

	}
	return true;
}


Sound::Sound(const char* file, soundType type, bool loop){
    error = false;
    volume = 1.0f;

	 // Si le système de son n'est pas initialisé, on le fait.
	 if(sys == NULL && !globalSoundError)
		 globalSoundInit();

	 if(globalSoundError){
		 error = true;
		 return;
	 }

    // Création du son à partir du fichier (soit lecture en streaming, soit chargé en mémoire)
	 if(loop)
	 {
		 if(type==STREAMED_MUSIC)
			  TRY(sys->createSound(file, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATESTREAM, 0, &sound));
		 else if(type==LOADED_SOUND)
			  TRY(sys->createSound(file, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound));
		 this->type = type;
	 }
	 else
	 {
		 if(type==STREAMED_MUSIC)
			  TRY(sys->createSound(file, FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D | FMOD_CREATESTREAM, 0, &sound));
		 else if(type==LOADED_SOUND)
			  TRY(sys->createSound(file, FMOD_SOFTWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &sound));
		 this->type = type;
	 }

    // 3 lignes à effacer (TODO)
	 //if(type==STREAMED_MUSIC) std::cout << "STREAMED_MUSIC" << std::endl;
	 //else if(type==LOADED_SOUND) std::cout << "LOADED_SOUND" << std::endl;
	 //else std::cout << "TOO BAD" << std::endl;
}


Sound::Sound():volume(1.0f){
	 error = true;
 }

Sound::~Sound(){
    if(sound!=NULL)
		 if(!this->error)
        sound->release();
    // TODO : faire les 2 lignes ci dessous lors de la fermeture du programme, avec un if sys!=NULL (y'aura ptet un pb car private)
    //sys->close();
    //sys->release();
	 //channelGroup->release(); // pour chaque chgrp
}



// Méthodes globales, qui affectent tout le système ------------------------- >>
void Sound::setMasterVolume(float level){
	if(globalSoundError)
		return;
	 if (level<0.0f) level = 0.0f;
	 else if (level>1.0f) level = 1.0f;


	 FMOD::ChannelGroup *masterGroup;
	 sys->getMasterChannelGroup(&masterGroup);
	 masterGroup->setVolume(level);
}
float Sound::getMasterVolume(){
	if(globalSoundError)
		return (0.0f);
	 FMOD::ChannelGroup *masterGroup;
	 float volume;
	 sys->getMasterChannelGroup(&masterGroup);
	 masterGroup->getVolume(&volume);
	 return (volume);
}

void Sound::setMusicVolume(float level){
	if(globalSoundError)
		return;
	 if (level<0.0f) level = 0.0f;
	 else if (level>1.0f) level = 1.0f;

	 musicGroup->setVolume(level);
}
float Sound::getMusicVolume(){
	if(globalSoundError)
		return (0.0f);
	 float volume;
	 musicGroup->getVolume(&volume);
	 return (volume);
}

void Sound::setEffectVolume(float level)
{
	if(globalSoundError)
		return;
	 if (level<0.0f) level = 0.0f;
	 else if (level>1.0f) level = 1.0f;

	 effectGroup->setVolume(level);
}
float Sound::getEffectVolume()
{
	if(globalSoundError)
		return (0.0f);
	 float volume;
	 effectGroup->getVolume(&volume);
	 return (volume);
}

// Méthodes de maniement du son --------------------------------------------- >>

void Sound::play()
{
	 if(!error) TRY(sys->playSound(FMOD_CHANNEL_FREE, sound, false, &channel));
	 if(!error && channel!=NULL && type == STREAMED_MUSIC)
	 {
		 TRY(channel->setChannelGroup(musicGroup));
	 }
	 else if(!error && channel!=NULL && type == LOADED_SOUND)
	 {
		 TRY(channel->setChannelGroup(effectGroup));
	 }
	 sys->update();

}

void Sound::pause(){
    channel->setPaused(true);
    sys->update();
}

void Sound::unPause()
{
    channel->setPaused(false);
    sys->update();
}
// private
void Sound::startEffect(FMOD::DSP * effect)
{
    bool active;
    effect->getActive(&active);
    if(!active)
        channel->addDSP(effect, 0);
}
void Sound::stopEffect(FMOD::DSP * effect)
{
    bool active;
    effect->getActive(&active);
    if(active)
        effect->remove();
}

//public
void Sound::startEffect(soundEffect effect)
{
    switch(effect)
    {
		case LOWPASS:
			startEffect(dsplowpass);
			break;
		case HIGHPASS:
			startEffect(dsphighpass);
			break;
		case ECHO:
			startEffect(dspecho);
			// dspecho->setParameter(FMOD_DSP_ECHO_DELAY, 50.0f);
			break;
		case FLANGE:
			startEffect(dspflange);
			break;
		case DISTO:
			startEffect(dspdistortion);
			// dspdistortion->setParameter(FMOD_DSP_DISTORTION_LEVEL, 0.8f);
			break;
		case CHORUS:
			startEffect(dspchorus);
			break;
		case PARAMEQ:
			startEffect(dspparameq);
			// dspparameq->setParameter(FMOD_DSP_PARAMEQ_CENTER, 5000.0f);
			// dspparameq->setParameter(FMOD_DSP_PARAMEQ_GAIN, 0.0f);
		break;
    }
}

void Sound::stopEffect(soundEffect effect)
{
    switch(effect)
    {
		case LOWPASS:
			stopEffect(dsplowpass);
			break;
		case HIGHPASS:
			stopEffect(dsphighpass);
			break;
		case ECHO:
			stopEffect(dspecho);
			break;
		case FLANGE:
			stopEffect(dspflange);
			break;
		case DISTO:
			stopEffect(dspdistortion);
			break;
		case CHORUS:
			stopEffect(dspchorus);
			break;
		case PARAMEQ:
			stopEffect(dspparameq);
			break;
    }
}


void Sound::setVolume(float level)
{
    if (level<0.0f) level = 0.0f;
    else if (level>1.0f) level = 1.0f;
    else volume = level;
	 if(!error) TRY(channel->setVolume(volume));
	 //std::cout << "vol: " << volume << std::endl;
    //sys->update();
}

// (end Méthodes de maniement du son) ---------------------------------------- //

void Sound::TRY(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        error = true;
    }


}

/*
A little fade out. (over 2 seconds)

printf("Goodbye!\n");
{
	float pitch = 1.0f;
	float vol = 1.0f;

	for (count = 0; count < 200; count++)
	{
		 masterGroup->setPitch(pitch);
		 masterGroup->setVolume(vol);

		 vol   -= (1.0f / 200.0f);
		 pitch -= (0.5f / 200.0f);

		 Sleep(10);
	}
}
*/
