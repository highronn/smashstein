#ifndef LAND_HPP
#define LAND_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class Land : public Movement
{
public:
	Land(Boxman * robot);

private:
	Boxman * bot;
public:
	 void act();
};


#endif // LAND_HPP
