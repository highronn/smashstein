#ifndef DEATH_HPP
#define DEATH_HPP
#include <Movement.hpp>
#include <Boxman.hpp>
#include <variables.hpp>

typedef enum enumStateDeath{DEATH_START, DEATH_FLY, DEATH_FLOOR} stateDeath;

class Death : public Movement
{
public:
	Death(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
	int startTime;
	stateDeath state;

public:
	 void act();
};



#endif // DEATH_HPP
