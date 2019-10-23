#ifndef SOUND_HPP
#define SOUND_HPP

#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
//#include <string>

typedef enum enumSoundType{STREAMED_MUSIC, LOADED_SOUND, NOSOUND} soundType;
typedef enum enumSoundEffect{LOWPASS, HIGHPASS, ECHO, FLANGE, DISTO, CHORUS, PARAMEQ} soundEffect;

class Sound{
    // constructeur, destructeur
    public:
		  Sound(const char* file, soundType type, bool loop);
		  Sound(); // son vide.
		  ~Sound();
    private:
        // vars statiques
        // systeme
        static FMOD::System  *sys;
		static bool globalSoundError;
        // effects
        static FMOD::DSP        *dsplowpass    ;
        static FMOD::DSP        *dsphighpass   ;
        static FMOD::DSP        *dspecho       ;
        static FMOD::DSP        *dspflange     ;
        static FMOD::DSP        *dspdistortion ;
        static FMOD::DSP        *dspchorus     ;
        static FMOD::DSP        *dspparameq    ;
        //volume
		  //static float masterVolume;
		  //musiques
		  static FMOD::ChannelGroup *musicGroup;
		  static FMOD::ChannelGroup *effectGroup;

        // vars locales
        FMOD::Sound   *sound;
		  FMOD::Channel *channel;
        bool error;
        float volume;
		  soundType type;

        // Méthodes
        // - "globales" (statiques)
    public:
		  static bool globalSoundInit();
		  static void setMasterVolume(const float level);
		  static float getMasterVolume();
		  static void setMusicVolume(const float level);
		  static float getMusicVolume();
		  static void setEffectVolume(const float level);
		  static float getEffectVolume();
        // - locales
    public:
        void play();
        void pause();
        void unPause();
        void startEffect(soundEffect effect);
        void stopEffect(soundEffect effect);
        void setVolume(float level); // note: à placer APRES la commande play()
    private:
        void startEffect(FMOD::DSP * effect);
        void stopEffect(FMOD::DSP * effect);
        void TRY(FMOD_RESULT result);
};

#endif // SOUND_HPP
