/* 
 * File:   Fonctions.hpp
 * Author: highronn
 *
 * Created on 24 décembre 2009, 11:15
 */

#ifndef _FONCTIONS_HPP
#define	_FONCTIONS_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

//#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glui.h>

#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include <QtGui/QApplication>
#include <QObject>
#include <Qt/qgl.h>
#include <QtGui/QtGui>

#include <QDomDocument>
#include <QFile>

#include <Arena.hpp>
#include <RTColor.hpp>

class Mesh;
class BackTexture;
//class Wrap;

#define TAILLE_TYPE 5

// Sens de chargement en PPM
#define NORMAL 1
#define MIRROR 2

typedef float vec3_t[3];

void vector(const vec3_t & u, const vec3_t & v, vec3_t & w);
void normalize(vec3_t & v);
float scalaire(const vec3_t & u, const vec3_t & v);
void vectoriel(const vec3_t & u, const vec3_t & v, vec3_t & w);

void camera2DMode(float width, float height);
void drawSquare(unsigned int id, float x, float y, float z, float Width, float Height);
unsigned char* load_PPM(const char *path, int *w, int *h, const int & type);
unsigned char* load_PPM_RGBA(const char *path, int *w, int *h, const RTColor::color & col, const int & type);
int convert_puissance_2(int n);
void InitGL(unsigned char* image, int & w, int & h, GLuint & id);
void InitGLRGBA(unsigned char* image, int & w, int & h, GLuint & id);
int readXML(const char* path, std::vector<Mesh*> & maps, std::vector<Mesh*> & elements, BackTexture & backTex, std::string & musicPath);
void readMTL(Mesh & m, const std::string & path);
void loadGraph(ArenaGraph & graphe, const char* nodePath, const char* edgePath);
void drawCanonicCircle(int nbEdge);
void drawLine(float xA, float yA, float xB, float yB, float w);
void drawGraphe(const ArenaGraph & graphe);
bool isInNode(const float& x, const float& y, const Node&);
void Fleche(GLdouble r, GLdouble h, GLfloat col[3]);
void drawAxes(void);
int absi(const int & n);

#endif	/* _FONCTIONS_HPP */

