/*
 * Anti-doublon
 */
#ifndef GLWidget_HPP
#define GLWidget_HPP

/*
 * External Includes
 */
#include <iostream>
#include <cmath>

#include <QObject>
#include <Qt/qgl.h>
#include <QtGui/QtGui>

#include <GL/gl.h>
#include <GL/glu.h>


/*
 * Internal Includes
 */
#include <Robots.hpp>
//#include <Boxman.hpp>
//#include <Mesh.hpp>
//#include <BackTexture.hpp>
#include <Arena.hpp>

/*
 * define for camera manaing in differents windows
 */
#define PURSUIT 1
#define GLOBAL 2
#define DEBUG 3
#define FREE 4

#define GLOBAL_Y_MIN 0.0
#define MARGIN 2
#define MARGIN_COEFF 0.1
#define VIEW_ANGLE 45.0

class MainWindow;

/** Custom QGLWidget
 * This class is a Q_OBJECT
 */
class GLWidget : public QGLWidget
{
    /*
     * QT MACRO
     */
    Q_OBJECT

  
    /*
     * Constructors & Destructors
     */
    public:
    /** Empty Constructor
        \param parent Parent QWidget
        \param shareWidget QGLWidget to share GL Context with
	\f Qt flags
    */
    
    static int selectPursuit;
    
	 GLWidget(MainWindow* parentWindow, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WFlags f = 0);
	 GLWidget(MainWindow* parentWindow, int window_type, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WFlags f = 0);
    /** Destructor
     */
    ~GLWidget() {};


 private:
	 MainWindow* parentWindow;

 public:
    void setCameraModeToPursuit(const float &, const float &, const float &, const float &);
    void setCameraModeToPursuit(const float & far);
    void setCameraModeToGlobal();
    void setCameraModeToDebug();
    void setCameraModeToFree();
    void update();
    void setLookAt();

    /*
     * GL functions
     */
// public :
//     inline void updateGL(){glDraw();}
//     inline void makeCurrent(){QGLWidget::makeCurrent();}
protected:
	/** Initialize OpenGL - this function only called once on the first call to paintGL
	 *  \sa paintGL
	 */
	void initializeGL(void);

	/** Function called on a resize event
		\param width new width
		\param height new height
	 */
	void resizeGL(int width, int height);

	/** Function called when the screen is refreshed
	 *  allows us to mix OpenGL calls and QPainter operations in a controlled way.
	 */
	void paintEvent(QPaintEvent *event);

    /*
     * IHM Functions
     */
protected :
    void  mouseReleaseEvent(QMouseEvent *e);
    /** Function called on a mouse release event
     * \param e mouse event
     */
//	 void  mousePressEvent(QMouseEvent *e)  { /*std::cout << "Button " << e->button() << std::endl;*/}
    /** Function called on a mouse move event
     * \param e mouse event
     */
    void  mouseMoveEvent(QMouseEvent *e);
    /** Function called on a key press event
     * \param e key event
     */    
    void keyPressEvent(QKeyEvent   *e);
	 void keyReleaseEvent(QKeyEvent   *e);
    /** Init view vectors
     */        
    void InitVector();
    void UpdateRightVector();
    void UpdatePositionVector();

private :
    int type;
    static bool chasingRobotAlreadyChose;
    
    int oldMouseX;
    int oldMouseY;
    
    double angleAlpha;
    double angleTeta;
    double translation[3];

    // PURSUIT camera managing
    float *xRobotChasing, *yRobotChasing, *zRobotChasing;
    float distance;

    // camera parameters
    double up[3]; //vecteur orientation de la caméra
    double direction[3]; //vecteur direction
    double right[3]; //produit vectoriel direction * up
    double position[3]; //position de la caméra
    double aim[3]; //point de visée de la caméra
    double rayon;
    
    //
    // Size
    //
    private :
        int width, height;
        float ratio;
        
    private :
		float lightPosition[4];
		bool textureAlreadyLoaded;
		bool callListAlreadyLoaded;		
        bool md2TexLoaded;
		
	public :
		inline const float* LightPosition() const {return lightPosition;}
		inline float* LightPosition() {return lightPosition;}
    
    public :
		inline const bool & isTextureAlreadyLoaded() const {return textureAlreadyLoaded;}
		inline bool & isTextureAlreadyLoaded() {return textureAlreadyLoaded;}
		
		inline const bool & isCallListAlreadyLoaded() const {return callListAlreadyLoaded;}
		inline bool & isCallListAlreadyLoaded() {return callListAlreadyLoaded;}
		
		inline const bool & isMD2TexLoaded() const {return md2TexLoaded;}
		inline bool & isMD2TexLoaded() {return md2TexLoaded;}
		
	//
	// Time handling
	//
	public:
		static int timeStartOfGame;
	private :
		static int timebase;
		static int lastFrameTime;
		static double relativeTime;
		static int frames;
		QTimer *timer;
		
	public :
		inline static const double & getRelativeTime() {return relativeTime;}

	//
	// KEYBOARD state
	//
	//private :
	public:
		static bool keyJump;
		static bool keyRight;
		static bool keyLeft;
		static bool keyBlock;
		static bool keyAttack1;
		static bool keyAttack2;
		static bool keyThrow;
     
    //    
    // Arene du widget
    //		
	private :
		Arena* arena;
		bool haveArena;

	public :
		static void setSelectedStage(int idStage);
		static void setSelectedCharacter(int idCharacter);
		static int getSelectedStage();
		static int getSelectedCharacter();

	private :
		static int selectedStage;
		static int selectedCharacter;

	public:
		inline int getWidth() const { return width; };
		inline int getHeight() const { return height; };

	// Painter
	private:
		QPainter painter;

	public:
		void setPainter(float ax, float ay, float bx, float by, int damage, int size, bool bold, QFont font, QPen pen);

};


/*
 * End Anti-doublon
 */
#endif

