#ifndef RUN_HPP
#define RUN_HPP

#include <Movement.hpp>
#include <Boxman.hpp>
//#include <BoxmanState.hpp>

typedef enum enumStateRun{RUN_START, RUN_CONTINUE, RUN_STOP} stateRun;

class Run : public Movement
{
public:
	 //Run(kn::smashstein::Robot & robot);
	Run(Boxman * robot);

private:
	 //kn::smashstein::Robot & bot;
	Boxman * bot;
	unsigned int frame;
	unsigned int frameFall;
	stateRun state;
public:
	 void act();
};

#endif // RUN_HPP
