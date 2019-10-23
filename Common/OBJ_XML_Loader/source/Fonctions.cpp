#include "../include/Fonctions.hpp"
#include "../include/Mesh.hpp"

unsigned char* load_PPM(const char *nom, int *w, int *h)
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
                    /*m = 0;
                    n = (*h)-1;
                    i = n*(*w)*3 + m;
                    do//on charge l'image en la copiant dans un tableau
                    {

                        rec = fgetc(fichier);
                        if(rec == EOF) table[i++] = 0;
                        else table[i++] = rec;

                        rec = fgetc(fichier);
                        if(rec == EOF) table[i++] = 0;
                        else table[i++] = rec;

                        rec = fgetc(fichier);
                        if(rec == EOF) table[i++] = 0;
                        else table[i++] = rec;

                        if(m == (*w - 1)*3)
                        {
                            m = 0;
                            n--;
                        }
                        else m += 3;
						
                        i = n*(*w)*3 + m;
						//printf("i %d, n %d|", i, n);
                    }
                    while (n > -1);*/
					
					 i=0;
                    do//on charge l'image en la copiant dans un tableau
                    {
                        table[i++] = fgetc(fichier);
                        table[i++] = fgetc(fichier);
                        table[i++] = fgetc(fichier);
                    }
                    while (i < (*w)*(*h)*3);

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
	
	int new_w, new_h;
	
	//glEnable(GL_DEPTH_TEST); 	//Active le depth test
	//glEnable(GL_TEXTURE_2D);
	
	glGenTextures(1, &id); 	//Génère un n° de texture
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); // permet de créer un effet de perspetive
	glBindTexture(GL_TEXTURE_2D, id); 	//Sélectionne ce n°
	
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// conversion de l'image en taille de puissance de 2
	new_w = convert_puissance_2(w);	
	new_h = convert_puissance_2(h);	
	
	if((new_h != h) || (new_w != w))
	{
		gluScaleImage(GL_RGB, w, h, GL_UNSIGNED_BYTE, image, new_w, new_h, GL_UNSIGNED_BYTE, image);
	
		w = new_w;
		h = new_h;
	}
	
	//GL_MODULATE, GL_DECAL, GL_BLEND, or GL_REPLACE
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	glTexImage2D (
		GL_TEXTURE_2D, 	//Type : texture 2D
		0, 	//Mipmap : aucun
		3, 	//Couleurs : 3
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

int readXML(const char* path, std::vector<Mesh> & maps, std::vector<Mesh> & elements)
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
		  std::cout << "path = \"" << path << "\"";            //récupère l’attribut path
		  
		  double x = (double)((mesure.attribute("x")).toFloat());
		  std::cout << " x = \"" << x << "\"";            //récupère l’attribut x
		  
		  double y = (double)((mesure.attribute("y")).toFloat());
		  std::cout << " y = \"" << y << "\"";            //récupère l’attribut y
		  
		  double z = (double)((mesure.attribute("z")).toFloat());
		  std::cout << " z = \"" << z << "\"";            //récupère l’attribut z
		  
		  double xrot = (double)((mesure.attribute("xrot")).toFloat());
		  std::cout << " xrot = \"" << xrot << "\"";            //récupère l’attribut xrot
		  
		  double yrot = (double)((mesure.attribute("yrot")).toFloat());
		  std::cout << " yrot = \"" << yrot << "\"";            //récupère l’attribut yrot
		  
		  double zrot = (double)((mesure.attribute("zrot")).toFloat());
		  std::cout << " zrot = \"" << zrot << "\"";            //récupère l’attribut zrot
		  
		  //int val = noeud.firstChild().toText().data().toInt();
		  std::string val = noeud.firstChild().toText().data().toStdString();
		  
		  // add this new object to the list of maps
		  Mesh m;
		  m.load(path.c_str());
		  m.name_ = val;
		  m.x_ = x;
		  m.y_ = y;
		  m.z_ = z;
		  m.xrot_ = xrot;
		  m.yrot_ = yrot;
		  m.zrot_ = zrot;
		  
		  maps.push_back(m);
		  
		  tab = mesure.childNodes();       //crée un tableau des enfants de « mesure »
		  
		  /*for(unsigned int i=0;i<tab.length();i++)
		  {
			  //pour chaque enfant, on extrait la donnée et on concatène
			  n = tab.item(i);
			  int val = n.firstChild().toText().data().toInt();
			  //std::string val = val = n.firstChild().toText().data().toStdString();
			  std::cout << "\tvalue " << val << std::endl;
		  }*/
	  }
	  else if (mesure.tagName() == "element")
	  {
		  std::string path = (mesure.attribute("path")).toStdString();
		  std::cout << "path = \"" << path << "\"";            //récupère l’attribut path
		  
		  double x = (double)((mesure.attribute("x")).toFloat());
		  std::cout << " x = \"" << x << "\"";            //récupère l’attribut x
		  
		  double y = (double)((mesure.attribute("y")).toFloat());
		  std::cout << " y = \"" << y << "\"";            //récupère l’attribut y
		  
		  double z = (double)((mesure.attribute("z")).toFloat());
		  std::cout << " z = \"" << z << "\"";            //récupère l’attribut z
		  
		  double xrot = (double)((mesure.attribute("xrot")).toFloat());
		  std::cout << " xrot = \"" << xrot << "\"";            //récupère l’attribut xrot
		  
		  double yrot = (double)((mesure.attribute("yrot")).toFloat());
		  std::cout << " yrot = \"" << yrot << "\"";            //récupère l’attribut yrot
		  
		  double zrot = (double)((mesure.attribute("zrot")).toFloat());
		  std::cout << " zrot = \"" << zrot << "\"";            //récupère l’attribut zrot
		  
		  //int val = noeud.firstChild().toText().data().toInt();
		  std::string val = noeud.firstChild().toText().data().toStdString();
		  
		  // add this new object to the list of maps
		  Mesh m;
		  m.load(path.c_str());
		  m.name_ = val;
		  m.x_ = x;
		  m.y_ = y;
		  m.z_ = z;
		  m.xrot_ = xrot;
		  m.yrot_ = yrot;
		  m.zrot_ = zrot;
		  		  
		  elements.push_back(m);
		  
		  tab = mesure.childNodes();       //crée un tableau des enfants de « mesure »
		  
		  /*for(unsigned int i=0;i<tab.length();i++)
		  {
			  //pour chaque enfant, on extrait la donnée et on concatène
			  n = tab.item(i);
			  int val = n.firstChild().toText().data().toInt();
			  //std::string val = val = n.firstChild().toText().data().toStdString();
			  std::cout << "\tvalue " << val << std::endl;
		  }*/
	  }
	  
	  noeud = noeud.nextSibling();         //passe à la “mesure” suivante
	}
	
	return 1;
}

void readMTL(Mesh & m, const std::string & path)
{
	std::cout << "load MTL file : " << path << std::endl;
	
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
		}
		
		m.matAmbient[3] = m.alpha;
		m.matDiffuse[3] = m.alpha;
		m.matSpecular[3] = m.alpha;
	}
}
