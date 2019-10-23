#ifndef FALL_HPP
#define FALL_HPP

#include <Movement.hpp>
#include <Boxman.hpp>

class Fall : public Movement
{
public:
	Fall(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
public:
	 void act();
};

#endif // FALL_HPP
