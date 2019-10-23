#include "main.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

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
    glTranslatef(0.,0.,h);
    glutSolidCone(4.*r,8.*r,8,2);
    glPopMatrix();
}



/*======================*/
/*= dessine le Repere =*/
/*======================*/
void drawAxes(void)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    Fleche(0.015,1.0,blue);
    glPushMatrix();
    glRotatef(-90.,1.,0.,0.);
    Fleche(0.015,1.0,green);
    glPopMatrix();  
    glPushMatrix();
    glRotatef(+90.,0.,1.,0.);
    Fleche(0.015,1.0,red);
    glPopMatrix();
    glPopAttrib();
}

//_____________________________________________________________________________
void UpdateRightVector()
{
    right[0]=up[1]*direction[2]-up[2]*direction[1];
    right[1]=up[2]*direction[0]-up[0]*direction[2];
    right[2]=up[0]*direction[1]-up[1]*direction[0];
}
//_____________________________________________________________________________
void UpdatePositionVector()
{
    //coordonnées sphériques (attention aux axes)
    position[0]=sin(angleTeta)*cos(angleAlpha);
    position[1]=sin(angleAlpha);
    position[2]=cos(angleTeta)*cos(angleAlpha);
}

//_____________________________________________________________________________
void InitVector()
{
    up[0]=0.;up[1]=1.;up[2]=0.;
    direction[0]=0;direction[1]=0;direction[2]=-1;
    
    UpdateRightVector(); //maintenir le repère orthogonal
    position[0]=0.5;position[1]=0;position[2]=0;
    
    aim[0]=aim[1]=aim[2]=0.0;
    translation[0]=translation[1]=translation[2]=0;
}

//_____________________________________________________________________________
/**
 * Fonction appellee pour redessiner le contenu de la fenetre
 **/
static void displayFunc(void){ 
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	
    glTranslatef(translation[0],translation[1],translation[2]);
	
    gluLookAt(rayon*position[0],rayon*position[1],rayon*position[2],
	      aim[0],aim[1],aim[2],up[0], up[1], up[2]);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		
    glDisable(GL_LIGHTING);
    //if(BoolAfficheRepere)
      drawAxes();
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); 
    glPushMatrix();
    
    glRotatef(90,0,0,1);
    // rotate debug
    //glRotatef(-90,1,0,0);
    ///////////////////
		m.RenderFrame(NUM_FRAME);
		/*m.animeType = LOOP;
		//m.animeType = ONE_SHOT;
		
		m.animeStartFrame = 0;
		m.animeEndFrame = 0;
		m.fps = 30;
		
		m.AnimeFrame();*/
    glPopMatrix();
    
    glDisable(GL_LIGHTING);

    glutSwapBuffers();
    ++frames;
}

//_____________________________________________________________________________
/**
 *
 * Fonction appelee si aucun autre evenement n'est en attente
 * 
 **/
static void idleFunc(void){ 
    int time = glutGet(GLUT_ELAPSED_TIME);
    if((time - timebase) >= 1000)
    {
		printf("fps : %f\n", frames*1000.0f/(time - timebase));
		frames = 0;
		timebase = time;
    }
    glutPostRedisplay();
}

//_____________________________________________________________________________
/**
 *
 * Fonction appelée lorsque la fenetre est deplacée ou redimensionnée
 * 
 **/
static void reshapeFunc(int w,int h){ 

    float ratio = (float)w/(float)h;
    glViewport(0, 0, (GLint)w, (GLint)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//_____________________________________________________________________________
void init()
{

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SMOOTH);

    timebase = glutGet(GLUT_ELAPSED_TIME);
	
	glClearColor(1.0, 0.0, 1.0, 1.0);
}
//_____________________________________________________________________________
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
		case 27:
			exit(EXIT_SUCCESS);
		break;
		
		case 'p':
			if(TYPE_AFFICHAGE_POLYGONS == 1)
			{
				TYPE_AFFICHAGE_POLYGONS = 2;
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				TYPE_AFFICHAGE_POLYGONS = 1;
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		break;
		
		case 'a':
			BoolAfficheRepere=!BoolAfficheRepere;
		break;
		
		case 'q':
			exit(0);
		break;
		
		case '+':
			++NUM_FRAME;
		break;
		
		case '-':
			if(NUM_FRAME > 0)
				--NUM_FRAME;
		break;
    }
    glutPostRedisplay();
}
//_____________________________________________________________________________
void specfunc(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_RIGHT:	
	translation[0]++;
	break;			
		
    case GLUT_KEY_LEFT:		
	translation[0]--;
	break;		

    case GLUT_KEY_UP:		
	translation[2]++;
	break;		

    case GLUT_KEY_DOWN:		
	translation[2]--;
	break;				
		
    case GLUT_KEY_PAGE_UP:		
	translation[1]--;
	break;				
		
    case GLUT_KEY_PAGE_DOWN:		
	translation[1]++;
	break;				
		

    }
    glutPostRedisplay();
}
//_____________________________________________________________________________
void mouse(int x, int y)
{
    int vectX, vectY;
    float step=0.03;
	
    vectX=x-OldMouseX;
    vectY=y-OldMouseY;
    OldMouseX=x;
    OldMouseY=y;
	
    if(vectX>0)
	angleTeta+=step;
    else
	if(vectX<0)
	    angleTeta-=step;
		
	
    if(vectY>0)
    {
	if(angleAlpha<(M_PI/2.0-step) )
	    angleAlpha+=step;
    }
    else
	if(vectY<0)
	{
	    if(angleAlpha>- (M_PI/2.0-step))
		angleAlpha-=step;
	}
		
    //	printf("vx : %d vy : %d\n", vectX, vectY);
	
    UpdatePositionVector();	
	
    glutPostRedisplay();
}

//_____________________________________________________________________________
void mouseInit(int button, int state, int x, int y)
{
	
    if(state==GLUT_DOWN)
    {
	OldMouseX=x;	
	OldMouseY=y;
    }
}

//_____________________________________________________________________________
/**
 *
 * Fonction principale
 * 
 **/
int main(int argc,char **argv){ 

    /// Initialise GLUT
    glutInit(&argc, argv);
    
    /// Specifie le mode d'affichage de la fenetre
    /// Le mode RGBA est utilisé ainsi que la double memoire tampon
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    /// Recuperation des parametres du programme
    int width = 800, height = 600, posx = 0, posy = 0;
    if( argc > 1 && argc%2 == 1){
	int i;
	for(i=1; i < argc; i+=2){
	    if(strcmp(argv[i],"-w")==0)
		width = atoi(argv[i+1]);
	    if(strcmp(argv[i],"-h")==0)
		height = atoi(argv[i+1]);
	    if(strcmp(argv[i],"-x")==0)
		posx = atoi(argv[i+1]);
	    if(strcmp(argv[i],"-y")==0)
		posy = atoi(argv[i+1]);
	}
    }

    /// Definition de la position de la fenetre
    glutInitWindowPosition(posx, posy);

    /// Definition des dimensions de la fenetre
    glutInitWindowSize(width, height);

    /// Creation de la fenetre (le nom de la fenetre est passé en argument)
    if(glutCreateWindow("Pile de matrices") == 0)
		return 1;
  
    ///Enregistrement des fonctions de callback
    /// Specification de la fonction de redimensionnement
    glutReshapeFunc(reshapeFunc);
  
    /// Specification de la fonction d'affichage
    glutDisplayFunc(displayFunc);

    /// Specification de la fonction "passive"
    glutIdleFunc(idleFunc);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specfunc);
    glutMotionFunc(mouse);
    glutMouseFunc(mouseInit);
    init();
	
	// Initializing variables
	InitVector();   
    
    if (!m.LoadModel("p_bandicoot3.md2"))
      std::cout << "Erreur " << std::endl;
     
    m.LoadTexture("p_bandicoot2.ppm");
    /*if (!m.LoadModel("p_boxman.md2"))
      std::cout << "Erreur " << std::endl;
      
    m.LoadTexture("p_boxman.ppm");*/

    /// Execution de la boucle de traitement evenementielle
    glutMainLoop();

    return 0;
}

