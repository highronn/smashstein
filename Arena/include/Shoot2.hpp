#ifndef SHOOT2_HPP
#define SHOOT2_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class Shoot2 : public Movement
{
public:
	Shoot2(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
public:
	 void act();
};

#endif // SHOOT2_HPP
