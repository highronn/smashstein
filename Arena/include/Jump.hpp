#ifndef JUMP_HPP
#define JUMP_HPP

#include <Movement.hpp>
#include <Boxman.hpp>

class Jump : public Movement
{
public:
	 //Run(kn::smashstein::Robot & robot);
	Jump(Boxman * robot);

private:
	 //kn::smashstein::Robot & bot;
	Boxman * bot;
public:
	 void act();
};
#endif // JUMP_HPP
