#ifndef _WORLDBILLBOARD_HPP_
#define _WORLDBILLBOARD_HPP_

#include "BillBoard.hpp"
#include <cmath>
#include <GL/gl.h>

class WorldBillBoard : public BillBoard
{  
	public:
		WorldBillBoard(RTPoint::point3 p = RTPoint::point3(0.0f,0.0f,0.0f), 
					   float h = 1.0f,
					   float v = 1.0f):
					   BillBoard(p,h,v) {}
					   
		~WorldBillBoard(){}

		void draw(RTPoint::point3);
};

#endif
