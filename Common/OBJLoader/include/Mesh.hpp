#ifndef MESH_HPP
#define MESH_HPP

#include "main.hpp"
#include "Vertex.hpp"

class Mesh
{
	private:
		char path_[PATH_LENGTH];
		unsigned int nbVertex_;
		unsigned int nbPolygon_;
		std::vector <Vertex> vertexData_;
		std::vector <Vertex> normalData_;
		std::vector < std::pair<unsigned int, unsigned int> > indexData_;
		unsigned int nbPointToRead_;

		GLuint idVBO_;
		GLuint idIndexVBO_;
		GLuint idTexVBO_;
		
	public:
		Mesh();
		Mesh(const Mesh &);		
		~Mesh();
		
		inline const char* path() const {return path_;}
		inline char* path() {return path_;}
		
		inline const unsigned int & nbVertex() const {return nbVertex_;}
		inline unsigned int & nbVertex() {return nbVertex_;}
		
		inline const unsigned int & nbPolygon() const {return nbPolygon_;}
		inline unsigned int & nbPolygon() {return nbPolygon_;}
		
		inline const std::vector<Vertex> & vertexData() const {return vertexData_;}
		inline std::vector<Vertex> & vertexData() {return vertexData_;}
		
		inline const std::vector<Vertex> & normalData() const {return normalData_;}
		inline std::vector<Vertex> & normalData() {return normalData_;}
		
		inline const std::vector < std::pair <unsigned int, unsigned int> > & indexData() const {return indexData_;}
		inline std::vector < std::pair <unsigned int, unsigned int> > & indexData() {return indexData_;}
		
		inline const unsigned int & nbPointToRead() const {return nbPointToRead_;}
		inline unsigned int & nbPointToRead() {return nbPointToRead_;}
		
		inline const GLuint & idVBO() const {return idVBO_;}
		inline GLuint & idVBO() {return idVBO_;}
		
		inline const GLuint & idIndexVBO() const {return idIndexVBO_;}
		inline GLuint & idIndexVBO() {return idIndexVBO_;}
		
		inline const GLuint & idTexVBO() const {return idTexVBO_;}
		inline GLuint & idTexVBO() {return idTexVBO_;}
		
		bool load(const char* path);
		bool draw();
		bool clear();
};

#endif
