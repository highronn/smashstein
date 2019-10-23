/*
 * Anti-doublon
 */
#ifndef BOXMANSTATE_HPP
#define BOXMANSTATE_HPP


/*
 * External Includes
 */
#include <RobotState.hpp>
#include <OpenKN/math/Vector3.hpp>

class BoxmanState  : public kn::smashstein::RobotState
{

	public:
		BoxmanState(const float velocity, 
					   const kn::Vector3f & direction, 
						const kn::Vector3f & position,
						const kn::Vector3f & acceleration);
		BoxmanState();
		~BoxmanState() {};


	private :
		kn::Vector3f velocity;
	public :
		inline const kn::Vector3f & getVelocity()const {return velocity;}
		inline kn::Vector3f & getVelocity() {return velocity;}

	private :	
		kn::Vector3f direction;
	public : 
		inline const kn::Vector3f & getDirection()const {return direction;}
		inline  kn::Vector3f & getDirection() {return direction;}

	private :
		kn::Vector3f position;
	public :
		inline const kn::Vector3f & getPosition()const {return position;}
		inline  kn::Vector3f & getPosition() {return position;}

	private :
		kn::Vector3f acceleration;
	public :
		inline const kn::Vector3f & getAcceleration()const {return acceleration;}
		inline  kn::Vector3f & getAcceleration() {return acceleration;}
		
	private :
		kn::Vector3f rotation;
	public :
		inline const kn::Vector3f & getRotation()const {return rotation;} 			
		inline  kn::Vector3f & getRotation() {return rotation;}

	private:
		float scale;
	public:
		inline const float & getScale() const {return scale;}
		inline float & getScale() {return scale;}

	private:
		bool jump;
	public:
		inline const bool & isJumping() const {return jump;}
		inline bool & isJumping() {return jump;}

	private:
		bool shootBlocked_;
	public:
		inline const bool & shootBlocked() const {return shootBlocked_;}
		inline bool & shootBlocked() {return shootBlocked_;}

	private:
		int attack;
	public:
		inline const int & isAttacking() const {return attack;}
		inline int & isAttacking() {return attack;}

	private:
		bool dead;
	public:
		inline const bool & isDead() const {return dead;}
		inline bool & isDead() {return dead;}

	private:
		bool block;
	public:
		inline const bool & isBlocking() const {return block;}
		inline bool & isBlocking() {return block;}

	private:
		bool onTheFloor;
	public:
		inline const bool & isOnTheFloor() const {return onTheFloor;}
		inline bool & isOnTheFloor() {return onTheFloor;}

	private:
		bool noPrerun_; // permet de désactiver le prerun à certains moments
	public:
		inline const bool & noPrerun() const {return noPrerun_;}
		inline bool & noPrerun() {return noPrerun_;}

		// GESTION DES DÉGÂTS
	private:
		int damages;
	public:
		inline const int & getDamages() const {return damages;}
		inline int & getDamages() {return damages;}

};


/*
 * End Anti-doublon
 */
#endif
