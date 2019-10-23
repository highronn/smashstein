#include "../include/Mesh.hpp"
#include "../include/Fonctions.hpp"

Mesh::Mesh():
x_(0), y_(0), z_(0), xrot_(0), yrot_(0), zrot_(0),
illum(2), alpha(1.0), transparency(1.0), shininess(0.5),
nbVertex_(0), nbPolygon_(0), nbPointToRead_(0), 
hasTex_(false), texPath_("obj/"), idTex_(0), idVBO_(0), idIndexVBO_(0), idTexVBO_(0)
{	
	matAmbient[0] = 0.2;
	matAmbient[1] = 0.2;
	matAmbient[2] = 0.2;
	matAmbient[3] = alpha;

	matDiffuse[0] = 0.8;
	matDiffuse[1] = 0.8;
	matDiffuse[2] = 0.8;
	matDiffuse[3] = alpha;

	matSpecular[0] = 0.0;
	matSpecular[1] = 0.0;
	matSpecular[2] = 0.0;
	matSpecular[3] = alpha;
}

Mesh::Mesh(const Mesh & m):
name_(m.name_), x_(m.x_), y_(m.y_), z_(m.z_), xrot_(m.xrot_), yrot_(m.yrot_), zrot_(m.zrot_), 
illum(m.illum), alpha(m.alpha), transparency(m.transparency), shininess(m.shininess),
path_(m.path_), nbVertex_(m.nbVertex_), nbPolygon_(m.nbPolygon_), nbPointToRead_(m.nbPointToRead_), 
hasTex_(m.hasTex_), texPath_(m.texPath_), idTex_(m.idTex_), idVBO_(m.idVBO_), idIndexVBO_(m.idIndexVBO_), idTexVBO_(m.idTexVBO_)
{	
	// material setting
	matAmbient[0] = m.matAmbient[0];
	matAmbient[1] = m.matAmbient[1];
	matAmbient[2] = m.matAmbient[2];
	matAmbient[3] = m.matAmbient[3];

	matDiffuse[0] = m.matDiffuse[0];
	matDiffuse[1] = m.matDiffuse[1];
	matDiffuse[2] = m.matDiffuse[2];
	matDiffuse[3] = m.matDiffuse[3];

	matSpecular[0] = matSpecular[0];
	matSpecular[1] = matSpecular[1];
	matSpecular[2] = matSpecular[2];
	matSpecular[3] = matSpecular[3];
	
	for(unsigned int i=0; i<(m.vertexData()).size(); ++i)
		vertexData_.push_back((m.vertexData())[i]);
		
	for(unsigned int i=0; i<(m.normalData()).size(); ++i)
		normalData_.push_back((m.normalData())[i]);
		
	for(unsigned int i=0; i<(m.texData()).size(); ++i)
		texData_.push_back((m.texData())[i]);
		
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
	path_ = path;
	std::cout << "load obj file : " << path_ << std::endl;
	
	std::ifstream file(path_.c_str(), std::ios::in);
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
		if(text == "mtllib")
		{
			std::string mtlFile("obj/");
			readBuffer >> text;
			
			if(!hasTex_) mtlFile.append(text);;			
			hasTex_ = true;
			
			readMTL(*this, mtlFile);
		}
		else if(text == "v")
		{
			readBuffer >> v.x();
			readBuffer >> v.y();
			readBuffer >> v.z();
			vertexData_.push_back(v);
						
			//std::cout << "v " << vertexData_[idVertex] << std::endl;			
			++idVertex;
		}
		else if(text == "vt")
		{			
			readBuffer >> v.u();
			readBuffer >> v.v();
			readBuffer >> v.w();
			texData_.push_back(v);
			
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
						
						std::string s1 = text.substr(0, posStart); // reading of first number
						std::string s2 = text.substr(posEnd+1, text.length());	// reading of late number					
						std::string s3 = text.substr(posStart+1, posEnd - posStart - 1); // reading of middle number					
						
						std::istringstream nbBuffer1(s1);
						std::istringstream nbBuffer2(s2);
						std::istringstream nbBuffer3(s3);
						
						unsigned int vertexId, normalId, texId;
						nbBuffer1 >> vertexId;
						nbBuffer2 >> normalId;
						nbBuffer3 >> texId;
						
						//std::cout << " -- (" << vertexId << ", " << normalId << ")";
						//std::pair <unsigned int, unsigned int> p(vertexId, normalId);
						Triplet tri;
						tri.idNormal = normalId;
						tri.idVertex = vertexId;
						tri.idTex = texId;
						indexData_.push_back(tri);
						//std::cout << "(" << indexData_[indexData_.size() - 1].idVertex << " ," << indexData_[indexData_.size() - 1].idTex << " ," << indexData_[indexData_.size() - 1].idNormal << ") " << std::endl;
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
	// material properties
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	if(illum == 1)  glShadeModel(GL_FLAT);
	else if(illum == 2) glShadeModel(GL_SMOOTH);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);  
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);  
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);                   
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	
	// texture properties
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	
	if(idTex_ == 0) // texture not already loaded
	{
		unsigned char* image = NULL;
		int width, height;
		
		if(hasTex_)
		{
			image = load_PPM(texPath_.c_str(), &width, &height);
			InitGL(image, width, height, idTex_);
		}
		else
		{
			image = load_PPM("obj/textures/DEFAULT.ppm", &width, &height);
			InitGL(image, width, height, idTex_);
			
			std::cout << " NO MAT " << matDiffuse[0] << " " << matDiffuse[1] << " " << matDiffuse[2] << " " << matDiffuse[3] << std::endl;
			std::cout << " NO MAT " << matAmbient[0] << " " << matAmbient[1] << " " << matAmbient[2] << " " << matAmbient[3] << std::endl;
		}
		
		if(image != NULL)
			free(image);
	}
	
	glBindTexture(GL_TEXTURE_2D, idTex_);
	
	// drawing of object
	unsigned int numTex = 1;
	bool first = true;
	
	glPushMatrix();
		glTranslatef(x_, y_, z_);
		glRotatef(xrot_, 1.0, 0.0, 0.0);
		glRotatef(yrot_, 0.0, 1.0, 0.0);
		glRotatef(zrot_, 0.0, 0.0, 1.0);
	
		glBegin(GL_TRIANGLES);
		
			for(unsigned int i=0; i<indexData_.size(); ++i)
			{
				glNormal3f( normalData_[(indexData_[i]).idNormal-1].nx(), normalData_[(indexData_[i]).idNormal-1].ny(), normalData_[(indexData_[i]).idNormal-1].nz() );
				
				if(hasTex_)
					glTexCoord2f(texData_[(indexData_[i]).idTex-1].u(), texData_[(indexData_[i]).idTex-1].v());
				else
				{
					switch(numTex)
					{
						case 1:
							if(first)
								glTexCoord2f(0.0, 1.0);
							else
								glTexCoord2f(1.0, 1.0);
							
							++numTex;
						break;
						
						case 2:							
							if(first)
								glTexCoord2f(1.0, 0.0);
							else
								glTexCoord2f(0.0, 0.0);
								
							++numTex;
						break;
						
						case 3:							
							if(first)
								glTexCoord2f(0.0, 0.0);
							else
								glTexCoord2f(1.0, 0.0);
								
							numTex = 1;
							first = !first;
						break;						
					}
				}
				
				glVertex3f( vertexData_[(indexData_[i]).idVertex-1].x(), vertexData_[(indexData_[i]).idVertex-1].y(), vertexData_[(indexData_[i]).idVertex-1].z() );
			}
			
		glEnd();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	
	return true;
}

bool Mesh::clear()
{
	vertexData_.clear();
	normalData_.clear();
	indexData_.clear();
	
	return true;
}
