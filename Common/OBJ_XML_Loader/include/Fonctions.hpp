#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

#include <math.h>
#include <vector>

#include <GL/glew.h>
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

class Mesh;

#define TAILLE_TYPE 5

unsigned char* load_PPM(const char *nom, int *w, int *h);
int convert_puissance_2(int n);
void InitGL(unsigned char* image, int & w, int & h, GLuint & id);
int readXML(const char* path, std::vector<Mesh> & maps, std::vector<Mesh> & elements);
void readMTL(Mesh & m, const std::string & path);

#endif
