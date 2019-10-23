#include <WorldBillBoard.hpp>

#include <cmath>
#include <GL/gl.h>

void WorldBillBoard::draw(RTPoint::point3 camera)
{

	float x = width / 2.0f;
	float y = height / 2.0f;

	glPushMatrix();
		RTVector::vec3 dir(camera.x - position.x, 0.0, camera.z - position.z);
		dir.normalize();

		RTVector::vec3 origine(0, 0, 1);
		RTVector::vec3 cross = origine.cross(dir);

		double dot = origine.dot(dir);

		glTranslatef(position.x, position.y, position.z);
		if((dot > -0.99999999999999) && (dot < 0.9999999999999999))
			glRotatef(acos(dot)*180.0/M_PI, cross[0], cross[1], cross[2]);

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
