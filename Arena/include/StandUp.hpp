#ifndef STANDUP_HPP
#define STANDUP_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class StandUp : public Movement
{
public:
	StandUp(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
public:
	 void act();
};



#endif // STANDUP_HPP
