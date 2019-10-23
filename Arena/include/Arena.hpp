#ifndef ARENA_HPP
#define ARENA_HPP

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <Robots.hpp>
#include <Boxman.hpp>
#include <Mesh.hpp>
#include <variables.hpp>
#include <IOMesh.hpp>
#include <DecorMesh.hpp>
#include <QBrush>
#include <QFont>
#include <QPen>

class BackTexture;
class GLWidget;
class Projectiles;
class FireBall;
class CocoNut;
class WaterBall;
class ExplodingCube;

class Arena
{
	private :
		static Arena * arena;
	
	private :
		Arena() {}
		
	public :
		static Arena & getArena(int idArena, std::vector<int> botsType, std::vector<int> nbBots);
		
	private :
		static ArenaGraph* graphe;
	public :
		inline static ArenaGraph & getGraph() {return *graphe;}

		static bool gameEnd;
		static bool gameWin;

    // Robots   
    private :
        static Robots * robots;
        static Boxman * avatar;
    
    public :
		inline static Robots & getRobots() {return *robots;}
		static inline Boxman * getAvatar() {return avatar;}
    
    private :
		static std::vector<Mesh*> * maps;
		static std::vector<Mesh*> * elements;
		static BackTexture * backTexture;
		unsigned int idBackTexture;
		
	public :
		inline const std::vector<Mesh*> & getMaps() const {return *maps;}
		inline std::vector<Mesh*> & getMaps() {return *maps;}
		
		inline const std::vector<Mesh*> & getElements() const {return *elements;}
		inline std::vector<Mesh*> & getElements() {return *elements;}
		
		inline const BackTexture & getBackTexture() const {return *backTexture;}
		inline BackTexture & getBackTexture() {return *backTexture;}

	private : // tex id for characters heads
		GLuint texIdHeadBoxman;
		GLuint texIdHeadBandicoot;
		GLuint texIdHeadHector;
		GLuint texIdHeadOpera;
		
	public :
		void loadCharactersHeads();
		void drawCharactersHeads(GLWidget & widget);

	private :
		//static QPainter * painter;

	private:
		static kn::Vector3f gravity;
		static double vitesseChuteMax;
		
	public:
		inline static const kn::Vector3f & getGravity() {return gravity;}
		inline static const double & getVitesseChuteMax() {return vitesseChuteMax;}
		
	private :
		static std::string musicPath;
	public :
		inline static std::string & getMusicPath() {return musicPath;}
		
	private :
		static bool showGraph;
		static bool showBoundingBox;
	public :
		inline static void setShowGraph() {showGraph = !showGraph;}
		inline static void setShowBoundingBox() {showBoundingBox = !showBoundingBox;}
		
	public :
		void update(GLWidget & widget);
		void checkState(Boxman* avatar);
		void applyPhysics(Boxman* avatar, const GLWidget & Widget);
		void drawBot(Boxman* avatar, GLWidget & Widget);
		void drawBoundingBox(const Wrap & w);
		void drawGraph();
		bool facesTouched(const Wrap & enveloppe, std::vector< std::pair<collisionFace, float> > & listOfFaces);
		std::pair<collisionFace, float> nearestCollisionFace(const Wrap & refWrap, const Wrap & wrap);
		//static void loadGraph(const char* path); // il faudrait peut-etre la retirer du mode static
	
	public : // fonctions utilisant le graphe
		static void setBotsInNodes();
		static void loadGraphe(ArenaGraph & graphe, const char* nodePath, const char* edgePath);
		void draw(GLWidget & Widget, const bool & IO, const bool & Decor);

	public:
		static void fillBotRevengeVictim(Robots* srobots);

		// PROJECTILES
	public:
		void loadProjectilesTextures();
	private:
		std::vector<std::pair<unsigned int,unsigned int> > projectilesTexList;
	public:
		inline const std::vector<std::pair<unsigned int,unsigned int> > & getProjectilesTexList()const {return projectilesTexList;}
		inline std::vector<std::pair<unsigned int,unsigned int> > & getProjectilesTexList() {return projectilesTexList;}
	  /*
	private:
		static std::vector<Projectiles*> projectiles;
	public:
		static inline std::vector<Projectiles*> & getProjectiles() {return projectiles;}
		*/
	private:
		static std::vector<FireBall*> fireballs;
	public:
		static inline std::vector<FireBall*> & getFireballs() {return fireballs;}
		void applyMovementAndDrawFireball(unsigned int position, const GLWidget & Widget);
		
	private:
		static std::vector<CocoNut*> coconuts;
	public:
		static inline std::vector<CocoNut*> & getCocoNuts() {return coconuts;}
		void applyMovementAndDrawCoconut(unsigned int position, const GLWidget & Widget);
		
	private:
		static std::vector<WaterBall*> waterballs;
	public:
		static inline std::vector<WaterBall*> & getWaterBalls() {return waterballs;}
		void applyMovementAndDrawWaterBall(unsigned int position, const GLWidget & Widget);
		
	private:
		static std::vector<ExplodingCube*> explodingcubes;
	public:
		static inline std::vector<ExplodingCube*> & getExplodingCubes() {return explodingcubes;}
		void applyMovementAndDrawExplodingCube(unsigned int position, const GLWidget & Widget);
};

#endif
