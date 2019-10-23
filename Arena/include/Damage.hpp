#ifndef DAMAGE_HPP
#define DAMAGE_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class Damage : public Movement
{
public:
	Damage(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
public:
	 void act();
};



#endif // DAMAGE_HPP
