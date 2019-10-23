/*
 * Anti-doublon
 */
#ifndef NORMALSPEAKER_HPP
#define NORMALSPEAKER_HPP


/*
 * External Includes
 */
#include <Speaker.hpp>

class NormalSpeaker  : public kn::smashstein::Speaker {

public:
	NormalSpeaker() {this->order = std::pair<std::string, int>("None",0); };
 	~NormalSpeaker() {};


private :
	std::pair<std::string, int> order;
public :
	inline void sendOrder(const std::string order, const int param) { this->order = std::pair<std::string, int>(order,param); }
	inline const std::pair<std::string,int> & getLastOrder()const{return order;}
};


/*
 * End Anti-doublon
 */
#endif
