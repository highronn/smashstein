#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

//#include <BoxmanState.hpp>
#include <Robot.hpp>
class Movement //: public Boxman // marche po
{
public:
	 //Movement(kn::smashstein::Robot & robot);
	virtual ~Movement(){}
	 virtual void act()=0;
 private:
	// kn::smashstein::Robot & bot;

};

#endif // MOVEMENT_HPP
