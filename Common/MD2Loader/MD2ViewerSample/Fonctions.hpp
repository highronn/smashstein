#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#define TAILLE_TYPE 5

#include <GL/gl.h>

typedef float vec3_t[3];

void vector(const vec3_t & u, const vec3_t & v, vec3_t & w);
void normalize(vec3_t & v);
float scalaire(const vec3_t & u, const vec3_t & v);
void vectoriel(const vec3_t & u, const vec3_t & v, vec3_t & w);

unsigned char* load_PPM(const char *nom, int *w, int *h);
int convert_puissance_2(int n);
void InitGL(unsigned char* image, int & w, int & h, GLuint & id);

#endif
