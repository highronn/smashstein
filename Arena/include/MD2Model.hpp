#ifndef MD2MODEL_HPP
#define MD2MODEL_HPP

// identifiant "IDP2" ou 844121161
#define MD2_IDENT               (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// numéro de version
#define MD2_VERSION             8

// functions prototypes
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <Animation.hpp>

typedef float vec3_t[3];

void vector(const vec3_t & u, const vec3_t & v, vec3_t & w);
void normalize(vec3_t & v);
float scalaire(const vec3_t & u, const vec3_t & v);
void vectoriel(const vec3_t & u, const vec3_t & v, vec3_t & w);

unsigned char* load_PPM(const char *nom, int *w, int *h);
int convert_puissance_2(int n);
void InitGL(unsigned char* image, int & w, int & h, unsigned int & id);

// {{!!! À définir avant la déclaration de classe
// nombre de vecteurs normaux précalculés
#define NUMVERTEXNORMALS        162
// !!!}}

#define ONE_SHOT 1
#define LOOP 2

// header md2
typedef struct
{
    int ident;          // numéro magique : "IDP2"
    int version;        // version du format : 8

    int skinwidth;      // largeur texture
    int skinheight;     // hauteur texture

    int framesize;      // taille d'une frame en octets

    int num_skins;      // nombre de skins
    int num_vertices;   // nombre de vertices par frame
    int num_st;         // nombre de coordonnées de texture
    int num_tris;       // nombre de triangles
    int num_glcmds;     // nombre de commandes opengl
    int num_frames;     // nombre de frames

    int offset_skins;   // offset données skins
    int offset_st;      // offset données coordonnées de texture
    int offset_tris;    // offset données triangles
    int offset_frames;  // offset données frames
    int offset_glcmds;  // offset données commandes OpenGL
    int offset_end;     // offset fin de fichier

} md2_header_t;

typedef float vec3_t[3];

// données vertex
typedef struct
{
    unsigned char v[3];         // position dans l'espace (relative au modèle)
    unsigned char normalIndex;  // index normale du vertex

} md2_vertex_t;

// données triangle
typedef struct
{
    unsigned short vertex[3];   // indices vertices du triangle
    unsigned short st[3];       // indices coordonnées de texture

} md2_triangle_t;

// coordonnées de texture
typedef struct
{
    short s;
    short t;

} md2_texCoord_t;

// données frame
typedef struct
{
    vec3_t          scale;      // redimensionnement
    vec3_t          translate;  // vecteur translation
    char            name[16];   // nom de la frame
    md2_vertex_t    *verts;     // liste de vertices

} md2_frame_t;

// texture
typedef struct
{
    char    name[68];    // nom du fichier texture

} md2_skin_t;


// ==============================================
// CMD2Model - classe objet modèle <.md2>
// ==============================================


class CMD2Model
{
public:
    // constructeur/destructeur
  CMD2Model( void );
    ~CMD2Model( void ) { FreeModel(); }


public:
    // fonctions publiques
    bool    LoadModel( std::string szFilename );
    bool    LoadTexture( std::string szFilename );

    void    FreeModel( void );

    void    RenderFrame( int iFrame );

    void    SetScale( float fScale ) { m_fScale = fScale; }
    float GetScaleValue( void ) { return m_fScale; }


public:
    static vec3_t   m_kAnorms[ NUMVERTEXNORMALS ];

    md2_header_t    m_kHeader;      // header md2
    md2_skin_t      *m_pSkins;      // skins datas
    md2_texCoord_t  *m_pTexCoords;  // textures coordinates
    md2_triangle_t  *m_pTriangles;  // triangles datas
    md2_frame_t     *m_pFrames;     // frames datas
    int             *m_pGLcmds;     // OpenGL command list

    float         m_fScale;       // model scaling

    unsigned int          m_uiTexID;      // model texture ID

};

#endif

