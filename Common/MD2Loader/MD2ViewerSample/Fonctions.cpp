#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glui.h>

#include "Fonctions.hpp"

bool egalite(const vec3_t & u, const vec3_t & v)
{
	return ((u[0] == v[0]) && (u[1] == v[1]) && (u[2] == v[2]));
}

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
	/*w->x = u.y*v.z - u.z*v.y;
	w->y = u.z*v.x - u.x*v.z;
	w->z = u.x*v.y - u.y*v.x;*/
	
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

void InitGL(unsigned char* image, int & w, int & h, GLuint & idTex)
{ 	
	int new_w, new_h;
	
	//glEnable(GL_DEPTH_TEST); 	//Active le depth test
	glEnable(GL_TEXTURE_2D);
	
	glGenTextures(1, &idTex); 	//Génère un n° de texture
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); // permet de créer un effet de perspetive
	glBindTexture(GL_TEXTURE_2D, idTex); 	//Sélectionne ce n°
	
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
	
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/
	glDisable(GL_TEXTURE_2D);
}

