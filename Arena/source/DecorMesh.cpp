#include <DecorMesh.hpp>

DecorMesh::DecorMesh():Mesh()
{}

DecorMesh::DecorMesh(const DecorMesh & m):Mesh(m)
{}

DecorMesh::~DecorMesh()
{
	vertexData_.clear();
	indexData_.clear();
	normalData_.clear();
}
