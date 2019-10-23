#include <MD2Model.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Fonctions.hpp>

// ----------------------------------------------
// LoadModel() - charge un modèle à partir d'un
// fichier <.md2>.
// ----------------------------------------------

CMD2Model::CMD2Model():
m_fScale(1), m_uiTexID(0)/*, anime(false), animeCurrentFrame(-1), animeType(LOOP)*/
{}

bool CMD2Model::LoadModel( std::string szFilename )
{
    std::fstream    file;   // fichier

    // tentative d'ouverture du fichier
    file.open( szFilename.c_str(), std::ios::in | std::ios::binary );

    if( file.fail() )
        return false;

    // lecture du header
    file.read( (char *)&m_kHeader, sizeof( md2_header_t ) );

    // vérification de l'authenticité du modèle
    if( (m_kHeader.version != MD2_VERSION) || m_kHeader.ident != MD2_IDENT )
        return false;

    // allocation de mémoire pour les données du modèle
    m_pSkins = new md2_skin_t[ m_kHeader.num_skins ];
    m_pTexCoords = new md2_texCoord_t[ m_kHeader.num_st ];
    m_pTriangles = new md2_triangle_t[ m_kHeader.num_tris ];
    m_pFrames = new md2_frame_t[ m_kHeader.num_frames ];
    m_pGLcmds = new int[ m_kHeader.num_glcmds ];
    
    /*printf("######## MODEL MD LOADED #########\n");
    printf("num_Skins %d\n", m_kHeader.num_skins);
    printf("num_Texcoords %d\n", m_kHeader.num_st);
    printf("num_Triangles %d\n", m_kHeader.num_tris);
    printf("num_Frames %d\n", m_kHeader.num_frames);
    printf("num_OpenglCommands %d\n", m_kHeader.num_glcmds);*/
    
    // lecture des noms de skins
    file.seekg( m_kHeader.offset_skins, std::ios::beg );
    file.read( (char *)m_pSkins, sizeof( char ) * 68 * m_kHeader.num_skins );

    // lecture des coordonnées de texture
    file.seekg( m_kHeader.offset_st, std::ios::beg );
    file.read( (char *)m_pTexCoords, sizeof( md2_texCoord_t ) * m_kHeader.num_st );

    // lecture des triangles
    file.seekg( m_kHeader.offset_tris, std::ios::beg );
    file.read( (char *)m_pTriangles, sizeof( md2_triangle_t ) * m_kHeader.num_tris );

    // lecture des frames
    file.seekg( m_kHeader.offset_frames, std::ios::beg );

    for( int i = 0; i < m_kHeader.num_frames; i++ )
    {
        // allocation de mémoire pour les vertices
        m_pFrames[i].verts = new md2_vertex_t[ m_kHeader.num_vertices ];

        // lecture des données de la frame
        file.read( (char *)&m_pFrames[i].scale, sizeof( vec3_t ) );
        file.read( (char *)&m_pFrames[i].translate, sizeof( vec3_t ) );
        file.read( (char *)&m_pFrames[i].name, sizeof( char ) * 16 );
        file.read( (char *)m_pFrames[i].verts, sizeof( md2_vertex_t ) * m_kHeader.num_vertices );
    }

    // lecture des commandes opengl
    file.seekg( m_kHeader.offset_glcmds, std::ios::beg );
    file.read( (char *)m_pGLcmds, sizeof( int ) * m_kHeader.num_glcmds );


    // fermeture du fichier
    file.close();

    // succès
    return true;
}


// ----------------------------------------------
// LoadTextures() - charge la texture du modèle
// à partir du chemin d'accès spécifié.
// ----------------------------------------------

bool CMD2Model::LoadTexture( std::string szFilename )
{
    // chargement de la texture
    //m_uiTexID = LoadTextureFromFile( szFilename );
    int width, height;
    unsigned char* image = load_PPM(szFilename.c_str(), &width, &height, MIRROR);
    
    if(image == NULL)
		return false;
		
    InitGL(image, width, height, m_uiTexID);
    //printf("texId %d\n", m_uiTexID);    
    if(image != NULL)
		free(image);
		
	return true;
}



// ----------------------------------------------
// FreeModel() - libère la mémoire allouée pour
// le modèle.
// ----------------------------------------------

void CMD2Model::FreeModel( void )
{
    if( m_pSkins )
        delete [] m_pSkins;

    if( m_pTexCoords )
        delete [] m_pTexCoords;

    if( m_pTriangles )
        delete [] m_pTriangles;

    if( m_pFrames )
    {
        for( int i = 0; i < m_kHeader.num_frames; i++ )
        {
            if( m_pFrames[i].verts )
                delete [] m_pFrames[i].verts;
        }

        delete [] m_pFrames;
    }
}



// table de 162 vecteurs normaux précalculés
vec3_t CMD2Model::m_kAnorms[ NUMVERTEXNORMALS ] = 
{
	#include    <anorms.hpp>
};


// ----------------------------------------------
// RenderFrame() - dessine le modèle à la frame
// spécifiée.
// ----------------------------------------------

void CMD2Model::RenderFrame( int iFrame )
{
    // calcul de l'index maximum d'une frame du modèle
    int iMaxFrame = m_kHeader.num_frames - 1;

    // vérification de la validité de iFrame
    if( (iFrame < 0) || (iFrame > iMaxFrame) )
        return;
	
	glEnable(GL_TEXTURE_2D);
	//std::cout << "frame " << iFrame << std::endl;
    // activation de la texture du modèle
    glBindTexture( GL_TEXTURE_2D, m_uiTexID );
	
	glPushMatrix();
    // dessin du modèle
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin( GL_TRIANGLES );
        // dessine chaque triangle
        for( int i = 0; i < m_kHeader.num_tris; i++ )
        {	  
			// true normal calculating
			/*vec3_t vertex1, vertex2, vertex3;
			
			md2_frame_t *pFrame = &m_pFrames[ iFrame ];

			md2_vertex_t *pVert1 = &pFrame->verts[ m_pTriangles[i].vertex[0] ];
			md2_vertex_t *pVert2 = &pFrame->verts[ m_pTriangles[i].vertex[1] ];
			md2_vertex_t *pVert3 = &pFrame->verts[ m_pTriangles[i].vertex[2] ];
			
			vertex1[0] = (pFrame->scale[0] * pVert1->v[0] + pFrame->translate[0]) * m_fScale;
			vertex1[1] = (pFrame->scale[1] * pVert1->v[1] + pFrame->translate[1]) * m_fScale;
			vertex1[2] = (pFrame->scale[2] * pVert1->v[2] + pFrame->translate[2]) * m_fScale;
			
			vertex2[0] = (pFrame->scale[0] * pVert2->v[0] + pFrame->translate[0]) * m_fScale;
			vertex2[1] = (pFrame->scale[1] * pVert2->v[1] + pFrame->translate[1]) * m_fScale;
			vertex2[2] = (pFrame->scale[2] * pVert2->v[2] + pFrame->translate[2]) * m_fScale;
			
			vertex3[0] = (pFrame->scale[0] * pVert3->v[0] + pFrame->translate[0]) * m_fScale;
			vertex3[1] = (pFrame->scale[1] * pVert3->v[1] + pFrame->translate[1]) * m_fScale;
			vertex3[2] = (pFrame->scale[2] * pVert3->v[2] + pFrame->translate[2]) * m_fScale;
			
			vec3_t u, v, w1, w2;
			vector(vertex1, vertex2, u);
			vector(vertex1, vertex3, v);
			normalize(u);
			normalize(v);
			vectoriel(u, v, w1);
			
			w2[0] = -w1[0];
			w2[1] = -w1[1];
			w2[2] = -w1[2];
		
			vec3_t normalIndex, normal;
			normalIndex[0] = m_kAnorms[ pVert1->normalIndex ][0];
			normalIndex[1] = m_kAnorms[ pVert1->normalIndex ][1];
			normalIndex[2] = m_kAnorms[ pVert1->normalIndex ][2];
			
			float p1 = scalaire(w1, normalIndex);
			float p2 = scalaire(w2, normalIndex);
			
			if(p1 > p2)
			{
				normal[0] = w1[0];
				normal[1] = w1[1];
				normal[2] = w1[3];
			}
			else
			{
				normal[0] = w2[0];
				normal[1] = w2[1];
				normal[2] = w2[3];
			}*/
			
			/////////////////////////////////////////////////////////////
			
            // dessigne chaque vertex du triangle
            for( int k = 0; k < 3; k++ )
            {
                md2_frame_t *pFrame = &m_pFrames[ iFrame ];
                md2_vertex_t *pVert = &pFrame->verts[ m_pTriangles[i].vertex[k] ];


                // [coordonnées de texture]
                GLfloat s = (GLfloat)m_pTexCoords[ m_pTriangles[i].st[k] ].s / m_kHeader.skinwidth;
                GLfloat t = (GLfloat)m_pTexCoords[ m_pTriangles[i].st[k] ].t / m_kHeader.skinheight;

                // application des coordonnées de texture
                glTexCoord2f( s, t );

                // [normale]
                //glNormal3fv( m_kAnorms[ pVert->normalIndex ] );
                //glNormal3fv( normal );

                // [vertex]
                vec3_t v;

                // calcul de la position absolue du vertex et redimensionnement
                v[0] = (pFrame->scale[0] * pVert->v[0] + pFrame->translate[0]) * m_fScale;
                v[1] = (pFrame->scale[1] * pVert->v[1] + pFrame->translate[1]) * m_fScale;
                v[2] = (pFrame->scale[2] * pVert->v[2] + pFrame->translate[2]) * m_fScale;
                glVertex3fv( v );
            }
        }
    glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}
