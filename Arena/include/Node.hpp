#ifndef NODE_HPP
#define NODE_HPP

#include <Robot.hpp>
#include <vector>
#include <list>

class Boxman;

class Node
{
	private :
		unsigned int id_;
		float x_, y_;
		float width_, height_;
		int nodeType_;
		std::vector<kn::smashstein::Robot*> robots;
		
	public :
		inline const unsigned int & id() const {return id_;}
		inline unsigned int & id() {return id_;}	
	
		inline const float & x() const {return x_;}
		inline float & x() {return x_;}
		
		inline const float & y() const {return y_;}
		inline float & y() {return y_;}
		
		inline const float & width() const {return width_;}
		inline float & width() {return width_;}
		
		inline const float & height() const {return height_;}
		inline float & height() {return height_;}
		
		inline const int & nodeType() const {return nodeType_;}
		inline int & nodeType() {return nodeType_;}
		
		inline const std::vector<kn::smashstein::Robot*> & getBotsInside() const {return robots;}
		inline std::vector<kn::smashstein::Robot*> & getBotsInside() {return robots;}
};

#endif
