#ifndef __BEHAVIOR_HPP
#define __BEHAVIOR_HPP

#include <iostream>
#include <string>

#define AGRESSIVE 1
#define FEARFUL 2
#define SUICIDAL 3

class Behavior
{
	private : 
		std::string typeAction;
		float objectif;
		int priorite;//sur une echelle de 0 à 100

	public :
		Behavior(void);
		Behavior(const std::string & type, float val, int priorite);
		Behavior(const Behavior & action);
		~Behavior() {}

		inline const std::string & getTypeAction(void)const {return typeAction;}
		inline std::string & getTypeAction(void) {return typeAction;}
		
		inline const float & getObjectif() const {return objectif;}
		inline float & getObjectif() {return objectif;}
		
		inline const int & getPriority() const {return priorite;}
		inline int & getPriority() {return priorite;}
		
		inline void setObjectif(const float & val) {objectif=val;}
		inline void setPriorite(const int & prio) {priorite=prio;}
		inline void setTypeAction(const std::string & type) {typeAction = type;}
};

#endif

