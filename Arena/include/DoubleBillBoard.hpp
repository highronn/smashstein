#ifndef _DOUBLEBILLBOARD_HPP_
#define _DOUBLEBILLBOARD_HPP_

#include <BillBoard.hpp>
//#include <GL/gl.h>

class DoubleBillBoard : public BillBoard // heritage doublebillbaord herite de billboard
{
	public:
		DoubleBillBoard(RTPoint::point3 p = RTPoint::point3(0.0f,0.0f,0.0f), float h = 1.0f, float v = 1.0f):BillBoard(p,h,v)
		{}

		~DoubleBillBoard()
		{}

		void draw(RTPoint::point3);
};

#endif
