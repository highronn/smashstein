/*
 * Anti-doublon
 */
#ifndef BOXMAN_HPP
#define BOXMAN_HPP


//
// External Includes
//
#include <Robot.hpp>

//
// Internal Includes
//
#include <BoxmanState.hpp>
#include <NormalSpeaker.hpp>
#include <BoxmanRadarReport.hpp>
#include <MD2Model.hpp>
#include <RobotInfo.hpp>
#include <Wrap.hpp>

//#include <Behavior.hpp>

#include <Sound.hpp>

#define ROBOT 1
#define AVATAR 2

class Behavior;

class Boxman : public kn::smashstein::Robot
{
	private :
		int type_;
		int id_;
		Wrap box_;
	public :
		inline const int & id() const {return id_;}
		inline int & id() {return id_;}

		inline const int & type() const {return type_;}
		inline int & type() {return type_;}

		//const Wrap & box() const;
		Wrap & box();
		bool lost;
		int lives;
	
	public:
		RobotInfo botInfo;
		Animation animation;
		// SON: tableau static des sons qui vont être joués lors de l'anim du perso.
		// passer en privé?
		static std::vector< std::vector<Sound*> > animSoundsAll;
		//std::vector<Sound*> animSounds;
		static void loadSounds(const std::vector<const char*> soundList, int type); // à déplacer plus bas apres

	public:
		Boxman();
		Boxman(const RobotInfo &, int type);
		~Boxman();

	private :
		unsigned int modelIndex; // Pour dire quel modele utiliser dans le modelTab
		static std::vector< std::pair<CMD2Model*, int> > modelTab; // tableau contenant les différents modèles MD2 : first donne un pointeur sur le modèle, second type du modèle
		static std::vector<std::string> modelTexPath; // tableau contenant le chemin vers la texture de chaque modèle
	public :
		inline CMD2Model & getRobotModel() {return *(modelTab[modelIndex].first);}
		bool loadModel(const char* modelPath, const std::string & texPath , int type);
		bool loadTexture(int type, const char* texPath);
		bool loadTexture();
		
	private :
		std::vector<Behavior*> actionBar;
	public :
		inline std::vector<Behavior*> & getActionBar() {return actionBar;}
		
	private :
		BoxmanState state;
	public:
		//inline const kn::smashstein::RobotState & getRobotState() const {return state;}
		inline const kn::smashstein::RobotState & getRobotState() const {return state;}
		inline BoxmanState & getRobotState()  {return state;}

	private :
		NormalSpeaker speaker;
	public :
		inline const kn::smashstein::Speaker & getSpeaker() const {return speaker;}			
		inline  NormalSpeaker & getSpeaker()  {return speaker;}			

	private :
		BoxmanRadarReport radarReport;
	public :
		inline const kn::smashstein::RadarReport & getRadarReport()const {return radarReport;}
		inline  BoxmanRadarReport & getRadarReport() {return radarReport;}
		
		inline const kn::smashstein::RadarReport * getRadarReportP() const {return &radarReport;}// virtual function in Robot.hpp
		inline BoxmanRadarReport * getRadarReportP() {return &radarReport;}// virtual function in Robot.hpp

	private :
		float radarRange;
	public :
		inline float getRadarRange()const {return radarRange;}
							
	private:
		kn::Vector3f maxSpeed;
	public:	
		inline kn::Vector3f getMaxSpeed()const{return maxSpeed;}
		
	private:
		float weight;
	public:	
		inline float getWeight()const{return weight;}						

	private:
		float gunFrequency;
		float gunProjectileVelocity;
		float gunPower;
	public:	
		inline float getGunFrequency()const{return gunFrequency;}						
		inline float getGunPower()const{return gunPower;}						
		inline float getGunProjectileVelocity()const{return gunProjectileVelocity;}

	public:
		void beTouched(int direction, Boxman* agressor);
		
	public :// memory to manage IA changing
		std::vector< std::pair<int,int> > revenge;//dès que le bot encaisse des dégâts on incrémente d'autant la valeur associée(second) à l'attaquant(first)
		std::vector< std::pair<int,int> > victim;//dès que le bot fait des dégâts on incrémente d'autant la valeur associée à la cible
	public :
		inline const std::vector< std::pair<int,int> > & getRevenge() const {return revenge;}
		inline std::vector< std::pair<int,int> > & getRevenge() {return revenge;}
		
		inline const std::vector< std::pair<int,int> > & getVictim() const {return victim;}
		inline std::vector< std::pair<int,int> > & getVictim() {return victim;}

	//private:
	public:
		Movement * movement;
	public:
		void setMovement(Movement * newMovement);
};


//
// End Anti-doublon
//
#endif
