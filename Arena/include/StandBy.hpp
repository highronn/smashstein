#ifndef STANDBY_HPP
#define STANDBY_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class StandBy : public Movement
{
public:
	StandBy(Boxman * robot);

private:
	Boxman * bot;
	int startTime;
public:
	 void act();
};


#endif // STANDBY_HPP
