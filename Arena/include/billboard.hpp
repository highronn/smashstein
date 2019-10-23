#ifndef _SCREENBILLBOARD_HPP_
#define _SCREENBILLBOARD_HPP_

#include <RTColor.hpp>
#include <RTPoint.hpp>
#include <RTVector.hpp>

//#include <GL/gl.h>

class BillBoard 
{
	public:
		RTPoint::point3 position; // Billboard Position
		float width;              // Billboard height
		float height;              // Billboard length

		BillBoard(RTPoint::point3 p = RTPoint::point3(0.0f,0.0f,0.0f), 
			float h = 1.0f,
			float v = 1.0f):
		position(p), width(h), height(v) {}

		virtual ~BillBoard(){}

		void updatePosition(const float& dx, const float& dy, const float& dz)
		{
			position.x += dx;
			position.y += dy;
			position.z += dz;
		}

		void updateSize(const float& percent)
		{
			height *= percent / 100.0f;
			width *= percent / 100.0f;
		}

		virtual void draw(RTPoint::point3);
};

#endif
