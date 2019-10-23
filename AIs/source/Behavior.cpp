#include <Behavior.hpp>
#include <iostream>
#include <cstdio>
#include <cstdlib>

Behavior::Behavior(void)
{
	typeAction = "";
	objectif = -1.0;
	priorite = -1;
}

Behavior::Behavior(const std::string & type, float val, int priorite)
{
	typeAction = type; 
	objectif = val;
	priorite = 50;//Normal priority
}

Behavior::Behavior(const Behavior & action)
{
	typeAction = action.typeAction;
	
	objectif = action.objectif;
	priorite = action.priorite;
}

/*Behavior::~Behavior(void)
{}*/

/*void Behavior::setTypeAction(const std::string & type)
{
	typeAction = type;
}*/

