#ifndef EDGE_HPP
#define EDGE_HPP

class Edge
{
	private :
		float value_;
		
	public :
		inline const float & value() const {return value_;}
		inline float & value() {return value_;}
};

#endif
