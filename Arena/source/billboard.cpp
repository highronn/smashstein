#include <billboard.hpp>

#include <GL/gl.h>

void BillBoard::draw(RTPoint::point3 camera)
{
	float x = width / 2.0f;
	float y = height / 2.0f;

	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, y, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x,-y, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( x,-y, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( x, y, 0.0f);

	glEnd();

	glPopMatrix();
}
