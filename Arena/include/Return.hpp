#ifndef RETURN_HPP
#define RETURN_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

class Return : public Movement
{
public:
	Return(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
public:
	 void act();
};


#endif // RETURN_HPP
