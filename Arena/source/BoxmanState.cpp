/*
 * Internal Includes
 */
#include <BoxmanState.hpp>

BoxmanState::BoxmanState(const float velocity, const kn::Vector3f & direction, const kn::Vector3f & position, const kn::Vector3f & acceleration)
	:onTheFloor(true), noPrerun_(false)
{
	this->velocity = velocity;
	this->direction = direction;
	this->position = position;
	this->acceleration = acceleration;
	jump = false;
	dead = false;
	block= false;
	attack = 0;
	damages = 0;
	shootBlocked_ = false;
}

BoxmanState::BoxmanState():onTheFloor(true), noPrerun_(false)
{
	velocity.fill(0.0f);
	acceleration.fill(0.0f);
	position.fill(0.0f);
	direction[0] = 0.0f;//(float) rand() / RAND_MAX * 2.0 -1.0 ;
	direction[1] = 0.0f;
	direction[2] = 0.0f;
	
	//direction.normalize();

	position[0] = (float) rand() / RAND_MAX;
	position[1] = 0.0f;
	position[2] = 0.0f;

	jump = false;
	dead = false;
	block= false;
	attack = 0;
	damages = 0;
	shootBlocked_ = false;

}

