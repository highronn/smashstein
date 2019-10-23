#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "main.hpp"

struct Triplet
{
	unsigned int idTex, idNormal, idVertex;
};

class Vertex
{
	private:
		float u_, v_, w_;
		float nx_, ny_, nz_;
		float x_, y_, z_;
		
	public:
		Vertex();
		Vertex(float, float, float, float, float, float, float, float, float);
		Vertex(const Vertex &);
		~Vertex();
		
		inline const float & u() const {return u_;}
		inline float & u() {return u_;}
		
		inline const float & v() const {return v_;}
		inline float & v() {return v_;}
		
		inline const float & w() const {return w_;}
		inline float & w() {return w_;}
		
		inline const float & nx() const {return nx_;}
		inline float & nx() {return nx_;}
		
		inline const float & ny() const {return ny_;}
		inline float & ny() {return ny_;}
		
		inline const float & nz() const {return nz_;}
		inline float & nz() {return nz_;}
		
		inline const float & x() const {return x_;}
		inline float & x() {return x_;}
		
		inline const float & y() const {return y_;}
		inline float & y() {return y_;}
		
		inline const float & z() const {return z_;}
		inline float & z() {return z_;}
};

std::ostream & operator<<(std::ostream & stream, const Vertex & v);

#endif
