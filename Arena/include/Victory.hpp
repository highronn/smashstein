#ifndef VICTORY_HPP
#define VICTORY_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class Victory : public Movement
{
public:
	Victory(Boxman * robot);

private:
	Boxman * bot;
	//unsigned int frame;
public:
	 void act();
};



#endif // VICTORY_HPP
