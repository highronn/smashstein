#ifndef THROW_HPP
#define THROW_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class Throw : public Movement
{
public:
	Throw(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
public:
	 void act();
};



#endif // THROW_HPP
