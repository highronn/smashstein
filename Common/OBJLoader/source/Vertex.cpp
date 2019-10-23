#include "../include/Vertex.hpp"

Vertex::Vertex():u_(0), v_(0), nx_(0), ny_(0), nz_(0), x_(0), y_(0), z_(0)
{}

Vertex::Vertex(const Vertex & vt):u_(vt.u_), v_(vt.v_), nx_(vt.nx_), ny_(vt.ny_), nz_(vt.nz_), x_(vt.x_), y_(vt.y_), z_(vt.z_)
{}

Vertex::Vertex(float u_, float v_, float nx_, float ny_, float nz_, float x_, float y_, float z_):
u_(u_), v_(v_), nx_(nx_), ny_(ny_), nz_(nz_), x_(x_), y_(y_), z_(z_)
{}

Vertex::~Vertex()
{}

std::ostream & operator<<(std::ostream & stream, const Vertex & v)
{
	stream << "vertex : tex(" << v.u() << ", " << v.v() << ") ";
	stream << " norm(" << v.nx() << ", " << v.ny() << ", " << v.nz() << ") ";
	stream << " coord(" << v.x() << ", " << v.y() << ", " << v.z() << ")" << std::endl;
	
	return stream;
}
