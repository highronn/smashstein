#ifndef SHOOT_HPP
#define SHOOT_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class Shoot : public Movement
{
public:
	Shoot(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
public:
	 void act();
};


#endif // SHOOT_HPP
