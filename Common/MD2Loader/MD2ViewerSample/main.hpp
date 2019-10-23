#ifndef MAIN_HPP
#define MAIN_HPP


#include <math.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#include "MD2Model.h"


GLfloat lightPosition[] = {2.0f,2.0f,0.0f,0.0f};

int frames = 0;
int timebase = 0;
int ListeArbre;
int i, j;
char BoolAfficheRepere=0;
float up[3]; //vecteur orientation de la caméra
float direction[3]; //vecteur direction
float right[3]; //produit vectoriel direction * up
float position[3]; //position de la caméra
float aim[3]; //point de visée de la caméra
float translation[3]; //vecteur de translation
float rayon=20.;
float angleAlpha=0, angleTeta=0;
float OldMouseX, OldMouseY;

float blue[3] = {0.0,0.0,1.0};
float green[3] = {0.0,1.0,0.0};
float red[3] = {1.0,0.0,0.0};

int NUM_FRAME = 0;

int TYPE_AFFICHAGE_POLYGONS = 1;

CMD2Model m;

#endif
