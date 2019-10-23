/*
 * Anti-doublon
 */
#ifndef ROBOTS_HPP
#define ROBOTS_HPP

/*
 * External Includes
 */
#include <dlfcn.h>
#include <vector>

/*
 * Internal Includes
 */
#include <Boxman.hpp>
//class Boxman;

#define BOXMAN 1
#define BANDICOOT 2
#define HECTOR 3
#define OPERA 4

class Robots
{
	public :
		Robots() 
		{}
		
		~Robots() {unpopulate();}

	private :	
		std::vector<Boxman *> bots;
	public :
		inline const std::vector<Boxman *> & getBots() const {return bots;}
		
	private :
		static Boxman* Avatar;
	
	public :
		static Boxman* getAvatar(int type);

	private :
		// Ces trois vecteurs ont la meme taille
		std::vector<std::pair< void *, std::vector<Boxman *> > > botsPlugins; // plugins des AIs
		std::vector<std::string> pluginsName; // noms des plugins
		std::vector<void * (*)(kn::smashstein::Robot *) > botsPluginsAct; // fonction Act de chaque plugin d'AI

	public :
		void populate(const std::vector<int> & robotTypes, const std::vector<int> & nbForEachType);
		void act();
		void unpopulate();
	
	public :
		void moveBot(const int & idBot, const unsigned int & sourcePlug, const unsigned int & targetPlug);
};


#endif
