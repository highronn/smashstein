#ifndef BACKTEXTURE_HPP
#define BACKTEXURE_HPP

#include <iostream>
#include <cstdlib>
#include <cstdio>

class BackTexture
{
	private:
		float x_, y_, z_;
		float width_, height_;
		unsigned int idTexture_;
		
		std::string path_;
		
	public:
		BackTexture();
		BackTexture(const BackTexture &);
		~BackTexture() {}
		
		inline const float & x() const {return x_;}
		inline float & x() {return x_;}
		
		inline const float & y() const {return y_;}
		inline float & y() {return y_;}
		
		inline const float & z() const {return z_;}
		inline float & z() {return z_;}
		
		inline const float & width() const {return width_;}
		inline float & width() {return width_;}
		
		inline const float & height() const {return height_;}
		inline float & height() {return height_;}
		
		inline const unsigned int & idTexture() const {return idTexture_;}
		inline unsigned int & idTexture() {return idTexture_;}
		
		void initTexture(const char* path, float x, float y, float z, float width, float height);
		void draw();
		void loadTexture();
};

#endif
