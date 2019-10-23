#include "../include/Mesh.hpp"

Mesh::Mesh():nbVertex_(0), nbPolygon_(0), nbPointToRead_(0), idVBO_(0), idIndexVBO_(0), idTexVBO_(0)
{
	path_[0] = '\0';
}

Mesh::Mesh(const Mesh & m):
nbVertex_(m.nbVertex_), nbPolygon_(m.nbPolygon_), nbPointToRead_(m.nbPointToRead_), idVBO_(m.idVBO_), idIndexVBO_(m.idIndexVBO_), idTexVBO_(m.idTexVBO_)
{
	strncpy(path_, m.path(), PATH_LENGTH);
	
	for(unsigned int i=0; i<(m.vertexData()).size(); ++i)
		vertexData_.push_back((m.vertexData())[i]);
		
	for(unsigned int i=0; i<(m.normalData()).size(); ++i)
		normalData_.push_back((m.normalData())[i]);
		
	for(unsigned int i=0; i<(m.indexData()).size(); ++i)
		indexData_.push_back((m.indexData())[i]);
}

Mesh::~Mesh()
{
	vertexData_.clear();
	indexData_.clear();
	normalData_.clear();
}

bool Mesh::load(const char* path)
{
	strncpy(path_, path, PATH_LENGTH);
	std::cout << "load obj file : " << path << std::endl;
	
	std::ifstream file(path, std::ios::in);
	std::string line;
	std::string text;
	std::istringstream readBuffer;
	Vertex v;
	
	unsigned int idVertex = 0, idNorm = 0;
	
	while(std::getline(file, line))
	{
		readBuffer.clear();
		readBuffer.str(line);
		
		//std::cout << line << std::endl;
		readBuffer >> text;
		//std::cout << text << std::endl;
		
		if(text == "v")
		{
			readBuffer >> v.x();
			readBuffer >> v.y();
			readBuffer >> v.z();
			vertexData_.push_back(v);
						
			//std::cout << "v " << vertexData_[idVertex] << std::endl;			
			++idVertex;
		}
		else if(text == "vn") // normal informations
		{
			readBuffer >> v.nx();
			readBuffer >> v.ny();
			readBuffer >> v.nz();
			normalData_.push_back(v);	
			
			//std::cout << "vn " << normalData_[idNorm] << std::endl;
			++idNorm;
		}
		else if(text == "f") // polygon informations
		{
			while(readBuffer.good())
			{
				readBuffer >> text;
				
				if(readBuffer.tellg() != -1)
				{					
					if(text.find("//"))
					{
						std::size_t posStart = text.find_first_of('/');
						std::size_t posEnd = text.find_last_of('/');
						
						std::string s1 = text.substr(0, posStart);
						std::string s2 = text.substr(posEnd+1, text.length());						
						
						std::istringstream nbBuffer1(s1);
						std::istringstream nbBuffer2(s2);
						
						unsigned int vertexId, normalId;
						nbBuffer1 >> vertexId;
						nbBuffer2 >> normalId;
						
						//std::cout << " -- (" << vertexId << ", " << normalId << ")";
						std::pair <unsigned int, unsigned int> p(vertexId, normalId);
						indexData_.push_back(p);
						//std::cout << "(" << indexData_[indexData_.size() - 1].first << " ," << indexData_[indexData_.size() - 1].second << ") ";
					}
				}
			}			
			//std::cout << std::endl;
		}
	}
	
	nbVertex_ = vertexData_.size();
	nbPolygon_ = indexData_.size() / 3;
	
	std::cout << nbVertex_ << ", " << nbPolygon_ << std::endl;
	
	file.close();
	
	return true;
}

bool Mesh::draw()
{
	glBegin(GL_TRIANGLES);
	
		for(unsigned int i=0; i<indexData_.size(); ++i)
		{
			glNormal3f( normalData_[(indexData_[i]).second-1].nx(), normalData_[(indexData_[i]).second-1].ny(), normalData_[(indexData_[i]).second-1].nz() );
			glVertex3f( vertexData_[(indexData_[i]).first-1].x(), vertexData_[(indexData_[i]).first-1].y(), vertexData_[(indexData_[i]).first-1].z() );
		}
		
	glEnd();
	
	return true;
}

bool Mesh::clear()
{
	vertexData_.clear();
	normalData_.clear();
	indexData_.clear();
	
	return true;
}
