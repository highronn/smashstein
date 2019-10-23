#include <Fonctions.hpp>
#include <Mesh.hpp>
#include <DecorMesh.hpp>
#include <IOMesh.hpp>
#include <BackTexture.hpp>
#include <Arena.hpp>
//#include <RTColor.hpp>

void normalize(vec3_t & v)
{
	float n = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	
	if(n < 1e-10) return;
	
	v[0] /= n;
	v[1] /= n;
	v[2] /= n;
}

float scalaire(const vec3_t & u, const vec3_t & v)
{
	return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

void vectoriel(const vec3_t & u, const vec3_t & v, vec3_t & w)
{
	w[0] = u[1]*v[2] - u[2]*v[1];
	w[1] = u[2]*v[0] - u[0]*v[2];
	w[2] = u[0]*v[1] - u[1]*v[0];
}

void vector(const vec3_t & u, const vec3_t & v, vec3_t & w)
{
	w[0] = v[0] - u[0];
	w[1] = v[1] - u[1];
	w[2] = v[2] - u[2];
}

void camera2DMode(float width, float height)
{
	//printf("\t########## draw in window %.2f %.2f\n", width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width, height, 0, -1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
}

unsigned char* load_PPM(const char *nom, int *w, int *h, const int & type)
{
    char chaine[TAILLE_TYPE];
    unsigned char car;
    unsigned char* table = NULL;
    int max = 0, bon = 1, i = 0, n = 0;

    FILE* fichier = fopen(nom,"r+");

    if ( NULL == fichier) return NULL;
    else
    {
        fgets(chaine,TAILLE_TYPE,fichier);

        if((chaine[0] != 'P' || chaine[1] != '6') && (chaine[0] != 'p' || chaine[1] != '6')) return NULL;
        else
        {
            car = fgetc(fichier);
			//printf("car %c\n", car);
            if (car == '#')//on lit jusqu'a la fin du commentaire
            {
              while(car != '\n') car = fgetc(fichier);
			  
			  // on lit la longueur
			  fscanf(fichier,"%d",w);
               car = fgetc(fichier);
            }
            else//si on a lu le premier caractere de la longueur
            {
               fseek(fichier,-2,SEEK_CUR);
               bon = (fscanf(fichier,"%d",w) != EOF);
               car = fgetc(fichier);
            }

            if (!bon) return NULL;
            else//on lit la hauteur
            {
                fscanf(fichier,"%d",h);
                car = fgetc(fichier);
                fscanf(fichier,"%d",&max);
                fgetc(fichier);

                //On commence a ecrire les pixels de l'image
				n = (*w)*(*h);
                i = 0;
				// 2 359 295

                table = (unsigned char*)malloc( (*h)*(*w)*sizeof(unsigned char)*3 );
				
                if(table == NULL) return NULL;
                else if (bon)//si on a pu allouer la memoire
                {
					if(type == NORMAL)
					{
						int m = 0;
						n = (*h)-1;
						i = n*(*w)*3 + m;
						do//on charge l'image en la copiant dans un tableau
						{
							table[i++] = fgetc(fichier);
							table[i++] = fgetc(fichier);
							table[i++] = fgetc(fichier);

							if(m == (*w - 1)*3)
							{
								m = 0;
								n--;
							}
							else m += 3;
							
							i = n*(*w)*3 + m;
							//printf("i %d, n %d|", i, n);
						}
						while (n > -1);
					}
					else if(type == MIRROR)
					{
						i=0;
						do//on charge l'image en la copiant dans un tableau
						{
							table[i++] = fgetc(fichier);
							table[i++] = fgetc(fichier);
							table[i++] = fgetc(fichier);
						}
						while (i < (*w)*(*h)*3);
					}

                    return table;
                }//Fin de l'ecriture du tableau de l'image
                else return NULL;
            }
        }
    }
}

unsigned char * load_PPM_RGBA(const char *path, int *w, int *h, const RTColor::color & c, const int & type)
{
	char chaine[TAILLE_TYPE];
    unsigned char car;
    unsigned char* table = NULL;
    int max = 0, bon = 1, i = 0, n = 0;

    FILE* fichier = fopen(path,"r+");

    if ( NULL == fichier) return NULL;
    else
    {
        fgets(chaine,TAILLE_TYPE,fichier);

        if((chaine[0] != 'P' || chaine[1] != '6') && (chaine[0] != 'p' || chaine[1] != '6')) return NULL;
        else
        {
            car = fgetc(fichier);
			//printf("car %c\n", car);
            if (car == '#')//on lit jusqu'a la fin du commentaire
            {
              while(car != '\n') car = fgetc(fichier);
			  
			  // on lit la longueur
			  fscanf(fichier,"%d",w);
               car = fgetc(fichier);
            }
            else//si on a lu le premier caractere de la longueur
            {
               fseek(fichier,-2,SEEK_CUR);
               bon = (fscanf(fichier,"%d",w) != EOF);
               car = fgetc(fichier);
            }

            if (!bon) return NULL;
            else//on lit la hauteur
            {
                fscanf(fichier,"%d",h);
                car = fgetc(fichier);
                fscanf(fichier,"%d",&max);
                fgetc(fichier);

                //On commence a ecrire les pixels de l'image
				n = (*w)*(*h);
                i = 0;
				// 2 359 295

                table = (unsigned char*)malloc( (*h)*(*w)*sizeof(unsigned char)*4 );
				
                if(table == NULL) return NULL;
                else if (bon)//si on a pu allouer la memoire
                {
					if(type == NORMAL)
					{
						int m = 0;
						n = (*h)-1;
						i = n*(*w)*4 + m;
						do//on charge l'image en la copiant dans un tableau
						{
							unsigned char r = table[i++] = fgetc(fichier);
							unsigned char g = table[i++] = fgetc(fichier);
							unsigned char b = table[i++] = fgetc(fichier);
							
							if(r==c.r && g==c.g && b==c.g)
								table[i++] = 0;
							else
								table[i++] = 255;

							if(m == (*w - 1)*4)
							{
								m = 0;
								n--;
							}
							else m += 4;
							
							i = n*(*w)*4 + m;
							//printf("i %d, n %d|", i, n);
						}
						while (n > -1);
					}
					else if(type == MIRROR)
					{
						i=0;
						do//on charge l'image en la copiant dans un tableau
						{
							unsigned char r = table[i++] = fgetc(fichier);
							unsigned char g = table[i++] = fgetc(fichier);
							unsigned char b = table[i++] = fgetc(fichier);
							
							if(r==c.r && g==c.g && b==c.g)
								table[i++] = 0;
							else
								table[i++] = 255;
						}
						while (i < (*w)*(*h)*4);
					}

                    return table;
                }//Fin de l'ecriture du tableau de l'image
                else return NULL;
            }
        }
    }
}

int convert_puissance_2(int n)
{
	int res = 1;
	
	while(res*2 <= n)
		res *= 2;
	
	return res;
}

void InitGL(unsigned char* image, int & w, int & h, GLuint & id)
{ 	
	if(image == NULL) return;
	
	//glEnable(GL_DEPTH_TEST); 	//Active le depth test
	//glEnable(GL_TEXTURE_2D);
	
	glGenTextures(1, &id); 	//Génère un n° de texture
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); // permet de créer un effet de perspetive
	glBindTexture(GL_TEXTURE_2D, id); 	//Sélectionne ce n°
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// conversion de l'image en taille de puissance de 2
	/*
	int new_w, new_h;
	 
	new_w = convert_puissance_2(w);	
	new_h = convert_puissance_2(h);	
	
	if((new_h != h) || (new_w != w))
	{
		gluScaleImage(GL_RGB, w, h, GL_UNSIGNED_BYTE, image, new_w, new_h, GL_UNSIGNED_BYTE, image);
		
		w = new_w;
		h = new_h;
	}*/
	//GL_MODULATE, GL_DECAL, GL_BLEND, or GL_REPLACE
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	glTexImage2D (
		GL_TEXTURE_2D, 	//Type : texture 2D
		0, 	//Mipmap : aucun
		GL_RGB, 	//Couleurs : 3
		w, 	//Largeur 
		h, 	//Hauteur 
		0, 	//Largeur du bord : 0
		GL_RGB, 	//Format : RGB
		GL_UNSIGNED_BYTE, 	//Type des couleurs
		image 	//Addresse de l'image
		); 
	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/
}

void InitGLRGBA(unsigned char* image, int & w, int & h, GLuint & id)
{
	if(image == NULL) return;

	glGenTextures(1, &id); 	// Create an ID
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); // Permit the perspective effect
	glBindTexture(GL_TEXTURE_2D, id); 	// Select this ID

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//GL_MODULATE, GL_DECAL, GL_BLEND, or GL_REPLACE
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D (
		GL_TEXTURE_2D, 	// Type : texture 2D
		0,				// Mipmap : aucun
		GL_RGBA,		// Couleurs : 4
		w,				// Largeur
		h,				// Hauteur
		0,				// Largeur du bord : 0
		GL_RGBA,		// Format : RGB
		GL_UNSIGNED_BYTE, 	// Type des couleurs
		image			// Addresse de l'image
		);

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	//glBindTexture(GL_TEXTURE_2D, 0); 	// Select this ID

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/
}

void drawSquare(unsigned int id, float x, float y, float z, float Width, float Height)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);
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
		glVertex3f(x, y, z);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x, y+Height, z);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x+Width, y+Height, z);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x+Width, y, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}



int readXML(const char* path, std::vector<Mesh*> & maps, std::vector<Mesh*> & elements, BackTexture & backTex, std::string & musicPath)
{	
	QDomDocument doc( "map" );
	QFile file(path);
	
	// loading in memory of xml file
	if( !file.open( QIODevice::ReadOnly ) )
		return -1;
	  
	if( !doc.setContent( &file ) )
	{
		file.close();
		return -2;
	}
	
	file.close();
	
	QString affichage;
	QDomNodeList tab;
	QDomElement mesure;
	QDomNode n;
	
	QDomElement racine = doc.documentElement();           //renvoie la balise racine
	QDomNode noeud = racine.firstChild();          //renvoie la 1ère balise « mesure »
	
	while(!noeud.isNull())
	{
		//convertit le nœud en élément pour utiliser les
		//méthodes tagName() et attribute()
		mesure = noeud.toElement();
	  //vérifie la présence de la balise « mesure »
	  //QString tmp = mesure.tagName();
	  //std::cout << "tag : " << tmp.toStdString() << std::endl;
	  if (mesure.tagName() == "mesh")
	  {	  
		  std::string path = (mesure.attribute("path")).toStdString();
		  //std::cout << "path = \"" << path << "\"";            //récupère l’attribut path
		  
		  double x = (double)((mesure.attribute("x")).toFloat());
		  //std::cout << " x = \"" << x << "\"";            //récupère l’attribut x
		  
		  double y = (double)((mesure.attribute("y")).toFloat());
		  //std::cout << " y = \"" << y << "\"";            //récupère l’attribut y
		  
		  double z = (double)((mesure.attribute("z")).toFloat());
		  //std::cout << " z = \"" << z << "\"";            //récupère l’attribut z
		  
		  double xrot = (double)((mesure.attribute("xrot")).toFloat());
		  //std::cout << " xrot = \"" << xrot << "\"";            //récupère l’attribut xrot
		  
		  double yrot = (double)((mesure.attribute("yrot")).toFloat());
		  //std::cout << " yrot = \"" << yrot << "\"";            //récupère l’attribut yrot
		  
		  double zrot = (double)((mesure.attribute("zrot")).toFloat());
		  //std::cout << " zrot = \"" << zrot << "\"";            //récupère l’attribut zrot		  
		  
		  double xBox = (double)((mesure.attribute("xBox")).toFloat());
		  //std::cout << " xBox = \"" << xBox << "\"";            //récupère l’attribut xrot
		  
		  double yBox = (double)((mesure.attribute("yBox")).toFloat());
		  //std::cout << " yBox = \"" << yBox << "\"";            //récupère l’attribut yrot
		  
		  double widthBox = (double)((mesure.attribute("widthBox")).toFloat());
		  //std::cout << " widthBox = \"" << widthBox << "\"";            //récupère l’attribut xrot
		  
		  double heightBox = (double)((mesure.attribute("heightBox")).toFloat());
		  //std::cout << " heightBox = \"" << heightBox << "\"";            //récupère l’attribut yrot
		  
		  int type = (int)((mesure.attribute("type")).toInt());
		  //std::cout << " int = \"" << int << "\"";            //récupère l’attribut yrot
		  
		  //int val = noeud.firstChild().toText().data().toInt();
		  std::string val = noeud.firstChild().toText().data().toStdString();
		  
		  // add this new object to the list of maps
		  Mesh* m = new IOMesh();
		  m->load(path.c_str());
		  m->name_ = val;
		  m->x_ = x;
		  m->y_ = y;
		  m->z_ = z;
		  m->xrot_ = xrot;
		  m->yrot_ = yrot;
		  m->zrot_ = zrot;
		  ((IOMesh*)m)->type() = type;
		  ((IOMesh*)m)->getBoundingBox().x = xBox;
		  ((IOMesh*)m)->getBoundingBox().y = yBox;
		  ((IOMesh*)m)->getBoundingBox().width = widthBox;
		  ((IOMesh*)m)->getBoundingBox().height = heightBox;
		  
		  maps.push_back(m);
		  
		  //tab = mesure.childNodes(); 
	  }
	  else if (mesure.tagName() == "element")
	  {
		  std::string path = (mesure.attribute("path")).toStdString();
		  //std::cout << "path = \"" << path << "\"";            //récupère l’attribut path
		  
		  double x = (double)((mesure.attribute("x")).toFloat());
		  //std::cout << " x = \"" << x << "\"";            //récupère l’attribut x
		  
		  double y = (double)((mesure.attribute("y")).toFloat());
		  //std::cout << " y = \"" << y << "\"";            //récupère l’attribut y
		  
		  double z = (double)((mesure.attribute("z")).toFloat());
		  //std::cout << " z = \"" << z << "\"";            //récupère l’attribut z
		  
		  double xrot = (double)((mesure.attribute("xrot")).toFloat());
		  //std::cout << " xrot = \"" << xrot << "\"";            //récupère l’attribut xrot
		  
		  double yrot = (double)((mesure.attribute("yrot")).toFloat());
		  //std::cout << " yrot = \"" << yrot << "\"";            //récupère l’attribut yrot
		  
		  double zrot = (double)((mesure.attribute("zrot")).toFloat());
		  //std::cout << " zrot = \"" << zrot << "\"";            //récupère l’attribut zrot
		  
		  //int val = noeud.firstChild().toText().data().toInt();
		  std::string val = noeud.firstChild().toText().data().toStdString();
		  
		  // add this new object to the list of maps
		  Mesh* m = new DecorMesh();
		  m->load(path.c_str());
		  m->name_ = val;
		  m->x_ = x;
		  m->y_ = y;
		  m->z_ = z;
		  m->xrot_ = xrot;
		  m->yrot_ = yrot;
		  m->zrot_ = zrot;
		  		  
		  elements.push_back(m);
	  }
	  else if(mesure.tagName() == "bgmusic")
	  {
		  std::string path = (mesure.attribute("path")).toStdString();
		  //std::cout << "bgMusic = \"" << path << "\"";            //récupère l’attribut path
		  
		  musicPath = path;
	  }
	  else if(mesure.tagName() == "background")
	  {
		  std::string path = (mesure.attribute("path")).toStdString();
		  //std::cout << "backPath = \"" << path << "\"";            //récupère l’attribut path
		  
		  double x = (double)((mesure.attribute("x")).toFloat());
		  //std::cout << " x = \"" << x << "\"";            //récupère l’attribut x
		  
		  double y = (double)((mesure.attribute("y")).toFloat());
		  //std::cout << " y = \"" << y << "\"";            //récupère l’attribut y
		  
		  double z = (double)((mesure.attribute("z")).toFloat());
		  //std::cout << " z = \"" << z << "\"";            //récupère l’attribut z
		  
		  double width = (double)((mesure.attribute("width")).toFloat());
		  //std::cout << " width = \"" << width << "\"";            //récupère l’attribut width
		  
		  double height = (double)((mesure.attribute("height")).toFloat());
		  //std::cout << " height = \"" << height << "\"";            //récupère l’attribut height
			
		  backTex.initTexture(path.c_str(), x, y, z, width, height);
      }
	  
	  noeud = noeud.nextSibling();         //next node
	}
	
	return 1;
}

void readMTL(Mesh & m, const std::string & path)
{
	//std::cout << "load MTL file : " << path << std::endl;
	
	std::ifstream file(path.c_str(), std::ios::in);
	std::string line, text;
	std::istringstream readBuffer;
	
	while(std::getline(file, line))
	{
		readBuffer.clear();
		readBuffer.str(line);
		
		//std::cout << line << std::endl;
		readBuffer >> text;
		
		if(text == "d") // alpha
		{
			readBuffer >> m.alpha;
		}
		else if(text == "Tr") // transparency
		{
			readBuffer >> m.transparency;
		}
		else if(text == "Ns") // shininess
		{
			readBuffer >> m.shininess;
		}
		else if(text == "illum") // ilumation model
		{
			readBuffer >> m.illum;
		}
		else if(text == "Ka") // ambient color
		{
			readBuffer >> m.matAmbient[0];
			readBuffer >> m.matAmbient[1];
			readBuffer >> m.matAmbient[2];
		}
		else if(text == "Kd") // ambient color
		{
			readBuffer >> m.matDiffuse[0];
			readBuffer >> m.matDiffuse[1];
			readBuffer >> m.matDiffuse[2];
		}
		else if(text == "Ks") // ambient color
		{
			readBuffer >> m.matSpecular[0];
			readBuffer >> m.matSpecular[1];
			readBuffer >> m.matSpecular[2];
		}
		else if(text == "map_Kd")
		{
			readBuffer >> text;
			m.texPath().append(text);
			
			//m.hasTex() = true;
		}
		
		m.matAmbient[3] = m.alpha;
		m.matDiffuse[3] = m.alpha;
		m.matSpecular[3] = m.alpha;
	}
}

void loadGraph(ArenaGraph & graphe, const char* nodePath, const char* edgePath)
{
	printf("\n\t######## Load ArenaGraph from (\"%s\", \"%s\") ########\n", nodePath, edgePath);
	
	// On crée dabord tous les sommets
	
	std::ifstream nodeFile(nodePath, std::ios::in);
	std::string line;
	std::istringstream readBuffer;
	
	std::vector<ArenaNodeID> arenaNodes;
	printf("\tNODES :\n");
	while(std::getline(nodeFile, line))
	{
		readBuffer.clear();
		readBuffer.str(line);
		
		if((line[0] >= '0') && (line[0] <= '9'))
		{
			unsigned int nodeID;
			int nodeType;
			float nodeXPos, nodeYPos, nodeWidth, nodeHeight;
			
			readBuffer >> nodeID;
			readBuffer >> nodeType;
			readBuffer >> nodeXPos;
			readBuffer >> nodeYPos;
			readBuffer >> nodeWidth;
			readBuffer >> nodeHeight;
			
			printf("\t\t%d | %d | %.2f | %.2f | %.2f | %.2f\n", nodeID, nodeType, nodeXPos, nodeYPos, nodeWidth, nodeHeight);
			ArenaNodeID anID = boost::add_vertex(graphe); // anID est l'indice d'un nouveau sommet qui a été ajouté dans graphe
			(graphe)[anID].id() = nodeID;
			(graphe)[anID].x() = nodeXPos;
			(graphe)[anID].y() = nodeYPos;
			(graphe)[anID].width() = nodeWidth;
			(graphe)[anID].height() = nodeHeight;
			(graphe)[anID].nodeType() = 1;
			
			// On stocke l'ID du noeud nouvellement crée
			arenaNodes.push_back(anID);
		}
	}
	
	nodeFile.close();
	
	printf("\tEDGES :\n");
	//std::vector<ArenaNodeID> arenaNodes;
	std::ifstream edgeFile(edgePath, std::ios::in);
	readBuffer.clear();
	line.clear();
	
	ArenaEdgeMap weightmap = boost::get(boost::edge_weight, graphe);
	
	while(std::getline(edgeFile, line))
	{
		readBuffer.clear();
		readBuffer.str(line);
		
		if((line[0] >= '0') && (line[0] <= '9'))
		{
			unsigned int nodeStartID, nodeEndID;
			float edgeValue;
			
			readBuffer >> nodeStartID;
			readBuffer >> nodeEndID;
			readBuffer >> edgeValue;
			
			printf("\t\t%d | %d | %.2f ", nodeStartID, nodeEndID, edgeValue);
	 
			ArenaEdgeID edge;
			bool good;
			boost::tie(edge, good) = boost::add_edge(arenaNodes[nodeStartID], arenaNodes[nodeEndID], graphe); // boost::add_edge renvoie une std::pai>WayPointConnectionID,bool>. C'est compliqué à écrire, alors on laisse boost::tie le faire pour nous.
	 
			if(good)  // Si le graphe a bel et bien été ajouté ( pas de doublon, par exemple, sauf si spécifié dans le typedef de WayPointGraph )
			{
				//graphe[edge].value() = edgeValue;
				weightmap[edge] = edgeValue;
				printf("GOOD\n");
			}
			else
				printf("BAD\n");		
		}
	}
	
	edgeFile.close();

	printf("\t########################\n");
}

void drawCanonicCircle(int nbEdge)
{
	double angle = 0.0;
	double x = cos(angle), y = sin(angle);
	double da = 2.0*M_PI / ((double)nbEdge);
	
	glBegin(GL_POLYGON);
		for(int i=0; i<nbEdge; ++i)
		{
			glVertex3f(x, y, 0.0);
			angle += da;
			x = cos(angle);
			y = sin(angle);
		}
	glEnd();
}

void drawCanonicSquare()
{
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
	glEnd();
}

void drawArrow(float xA, float yA, float xB, float yB)
{
	float dx = xB-xA;
	float dy = yB-yA;
	int d = 20;
	float dv = 1.0/(float)d;
	
	glBegin(GL_LINES);
		for(int i = 0; i<d; i++)
		{
			glColor3f(i*dv, 0.0, i*dv);
			glVertex3f(xA+i*dv*dx, yA+i*dv*dy, 0.0);
			glVertex3f(xA+(i+1)*dv*dx, yA+(i+1)*dv*dy, 0.0);
		}
	glEnd();
	
	/*glColor3f(0.0, 0.0, 1.0);
	glPointSize(10.0);
	glBegin(GL_POINTS);
		glVertex3f(xB, yB, 0.0);
	glEnd();
	glPointSize(1.0);*/
}

void drawGraphe(const ArenaGraph & graphe)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA);
	
	glPushMatrix();		
		// Parcourt des noeuds du graphe et dessin de ces noeuds
		//printf("num_vertices %d\n", (int)boost::num_vertices(graphe));
		
		ArenaEdgeIterator first, last;
		ArenaNodeIterator nfirst, nlast;
		//EdgeLengthMap eMap;
		//ArenaNodeIndexMapT nBox;
		//NodeBoundingBox<Node, float> nBox;
		
		for(boost::tie(nfirst, nlast) = boost::vertices(graphe); nfirst != nlast; ++nfirst)
		{
			//((ArenaNodeID)((*first).m_source)).x();
			//ArenaNodeID nId = boost::get(nBox, *nfirst);
			//std::cout << "node " <<  boost::get(nBox, *nfirst);
			Node N = (graphe[*nfirst]);
			//NodeBoundingBox n;
			//std::cout << " node " << boost::get(n, N);
			glPushMatrix();
				// drawing of node
				glTranslatef(N.x(), N.y(), 0.0);
				glPushMatrix();
					float scale = 0.25;
					glScalef(scale, scale, scale);
					glColor4f(1.0, 0.0, 0.0, 0.5);
					drawCanonicCircle(20);
				glPopMatrix();
				
				// drawing of node area
				glTranslatef(0.0, 0.0, -0.001);
				glScalef(N.width(), N.height(), 1.0);
				glColor4f(1.0, 1.0, 0.0, 0.5);
				drawCanonicSquare();
			glPopMatrix();
				
			//Node p = boost::get(graphe, *nfirst);
			//printf("noeud %d x %.2f y %.2f : w %.2f h %.2f\n", p.id(), p.x(), p.y(), p.width(), p.height());
		}
		
		//ArenaEdgeMap distances;
	    // first and last have type
		//boost::detail::edge_desc_impl<boost::bidirectional_tag, long unsigned int>
		for(boost::tie(first, last) = boost::edges(graphe); first != last; ++first)
		{
			Node start = graphe[boost::source(*first, graphe)];
			Node end = graphe[boost::target(*first, graphe)];
			//std::cout << *((float*)((*first).m_eproperty));
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glLineWidth(2.0);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 0.001);
				drawArrow(start.x(), start.y(), end.x(), end.y());
			glPopMatrix();
			glLineWidth(1.0);
			//std::cout << std::endl;
			
			//std::cout << boost::get(distances, *first) << std::endl;
		}
		
		
	glPopMatrix();
	
	glColor4f(0.0, 1.0, 1.0, 1.0);
	// Parcourt des arretes du graphe et dessin de ces arretes
	
	glDisable(GL_ALPHA);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

bool isInNode(const float& x, const float& y, const Node& n)
{
	bool inside = (x >= (n.x() - n.width()/2.0)) &&
				  (x <= (n.x() + n.width()/2.0)) &&
				  (y >= (n.y() - n.height()/2.0)) &&
				  (y <= (n.y() + n.height()/2.0));
				  
	return inside;
}

int absi(const int & n)
{
	if(n < 0)
		return -n;
	else
		return n;
}

/*======================*/
/*= dessine une flèche =*/
/*======================*/
void Fleche(GLdouble r, GLdouble h, GLfloat col[3])
{
    static GLUquadricObj *qobj=NULL;
    if (!qobj) qobj=gluNewQuadric();
    glPushMatrix();

    glColor4fv(col);
    gluQuadricDrawStyle(qobj,GLU_FILL);
    gluCylinder(qobj,r,r,h,8,2);	
    //glTranslatef(0.,0.,h);
    //glutSolidCone(4.*r,8.*r,8,2);
    glPopMatrix();
}

/*======================*/
/*= dessine le Repere =*/
/*======================*/
void drawAxes(void)
{
	GLfloat col[3] = {0.0, 0.0, 1.0};
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    Fleche(0.015,1.0,col);
    glPushMatrix();
    
    glRotatef(-90.,1.,0.,0.);
    col[0] = col[2] = 0.0;
    col[1] = 1.0;
    Fleche(0.015,1.0,col);
    glPopMatrix();  
    
    glPushMatrix();
    glRotatef(+90.,0.,1.,0.);
    col[1] = col[2] = 0.0;
    col[0] = 1.0;
    Fleche(0.015,1.0,col);
    glPopMatrix();
    glPopAttrib();
}
