#ifndef BLOCK_HPP
#define BLOCK_HPP
#include <Movement.hpp>
#include <Boxman.hpp>

typedef enum enumStateBlock{BLOCK_START, BLOCK_WAIT, BLOCK_SHOCK, BLOCK_END} stateBlock;

class Block : public Movement
{
public:
	Block(Boxman * robot);

private:
	Boxman * bot;
	unsigned int frame;
	stateBlock state;
public:
	 void act();
};


#endif // BLOCK_HPP
