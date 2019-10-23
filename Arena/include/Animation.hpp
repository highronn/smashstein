#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#define ONE_SHOT 1
#define LOOP 2

#define STANDBY 1
#define PRERUN 2
#define RUN 3
#define JUMP 4
#define FALL 5
#define POSTJUMP 6
#define ATTACK1 7
#define THROW 8
#define DAMAGE 9
#define PREBLOCK 10
#define BLOCK 11
#define POSTBLOCK 12
#define PREDEATH 13
#define DEATH 14
#define POSTDEATH 15
#define STANDUP 16
#define ATTACK2 17
#define ROTATE 18
#define POSTRUN 19
#define VICTORY 20

#define NB_ANIM 20

#include <fstream>
#include <sstream>
#include <Sound.hpp>

class CMD2Model;

class Animation
{
	public :
		Animation();
		Animation(const Animation &);
		~Animation() {}
		
	private:
		bool anime;
		int animeStartFrame;
		int animeEndFrame;
		int animeCurrentFrame;
		int fps_;
		int animeInterFrameTime;
		int animeType;

		int idAnime;
		std::vector< std::pair<int,int> > animationTable;

		std::vector<Sound*> sounds;
	
	public :
		inline const int & getAnimeType() const {return animeType;}
		inline int & getAnimeType() {return animeType;}
		
		inline const int & getCurrentFrame() const {return animeCurrentFrame;}
		inline int & getCurrentFrame() {return animeCurrentFrame;}
		
	public :
		void animeModel(CMD2Model & m);
		void loadAnimationTab(const char* tabPath);
		void setAnimation(int type, int fps);
		void loadAnimationSounds(std::vector<Sound*> & importedSounds);
		
	public :
		bool isTerminate();
};


#endif
