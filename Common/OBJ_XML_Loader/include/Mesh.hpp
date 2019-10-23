#ifndef MESH_HPP
#define MESH_HPP

#include "main.hpp"
#include "Vertex.hpp"

class Mesh
{
	public:
		std::string name_;
		double x_, y_, z_;
		double xrot_, yrot_, zrot_;
		
		GLuint illum;
		GLfloat matAmbient[4];
		GLfloat matDiffuse[4];
		GLfloat matSpecular[4];
		GLfloat alpha;
		GLfloat transparency;
		GLfloat shininess;
		
	private:
		std::string path_;
		unsigned int nbVertex_;
		unsigned int nbPolygon_;
		std::vector <Vertex> vertexData_;
		std::vector <Vertex> normalData_;
		std::vector <Vertex> texData_;
		std::vector < Triplet > indexData_;
		unsigned int nbPointToRead_;
		
		bool hasTex_;
		std::string texPath_;
		GLuint idTex_;
		
		GLuint idVBO_;
		GLuint idIndexVBO_;
		GLuint idTexVBO_;
		
	public:
		Mesh();
		Mesh(const Mesh &);		
		~Mesh();
		
		inline const std::string & path() const {return path_;}
		inline std::string & path() {return path_;}
		
		inline const unsigned int & nbVertex() const {return nbVertex_;}
		//inline unsigned int & nbVertex() {return nbVertex_;}
		
		inline const unsigned int & nbPolygon() const {return nbPolygon_;}
		//inline unsigned int & nbPolygon() {return nbPolygon_;}
		
		inline const std::vector<Vertex> & vertexData() const {return vertexData_;}
		//inline std::vector<Vertex> & vertexData() {return vertexData_;}
		
		inline const std::vector<Vertex> & normalData() const {return normalData_;}
		//inline std::vector<Vertex> & normalData() {return normalData_;}
		
		inline const std::vector<Vertex> & texData() const {return texData_;}
		//inline std::vector<Vertex> & texData() {return texData_;}
		
		inline const std::vector<Triplet> & indexData() const {return indexData_;}
		//inline std::vector<Triplet> & indexData() {return indexData_;}
		
		inline const unsigned int & nbPointToRead() const {return nbPointToRead_;}
		//inline unsigned int & nbPointToRead() {return nbPointToRead_;}
		
		inline const bool & hasTex() const {return hasTex_;}
		//inline bool & hasTex() {return hasTex_;}
		
		inline const std::string & texPath() const {return texPath_;}
		inline std::string & texPath() {return texPath_;}
		
		inline const GLuint & idTex() const {return idTex_;}
		//inline GLuint & idTex() {return idTex_;}
		
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
