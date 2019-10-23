#include <BackTexture.hpp>
#include <Fonctions.hpp>

BackTexture::BackTexture():
x_(0), y_(0), z_(0),
width_(0), height_(0),
idTexture_(0), path_("")
{}

BackTexture::BackTexture(const BackTexture & t):
x_(t.x_), y_(t.y_), z_(t.z_),
width_(t.width_), height_(t.height_),
idTexture_(t.idTexture_), path_(t.path_)
{}

void BackTexture::initTexture(const char* path, float x, float y, float z, float width, float height)
{
	path_ = path;
	x_ = x;
	y_ = y;
	z_ = z;
	width_ = width;
	height_ = height;
}

void BackTexture::loadTexture()
{
	glEnable(GL_TEXTURE_2D);
	
	unsigned char* image = NULL;
	int Width, Height;

	image = load_PPM(path_.c_str(), &Width, &Height, MIRROR);
	InitGL(image, Width, Height, idTexture_);

	if(image != NULL)
		free(image);
	
	glDisable(GL_TEXTURE_2D);
}

void BackTexture::draw()
{
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, idTexture_);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	/*glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x, y, z);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, y+Height, z);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x+Width, y+Height, z);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x+Width, y, z);
	glEnd();*/
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x_, y_, z_);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x_, y_+height_, z_);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x_+width_, y_+height_, z_);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x_+width_, y_, z_);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

