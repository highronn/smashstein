/*
 * Internal Includes
 */
#include <cstdlib>
#include <GLWidget.hpp>
#include <Application.hpp> //cross inclusion
//#include <OpenKN/math/MathTools.hpp>
#include <variables.hpp>
#include <Robots.hpp>
#include <Animation.hpp>
#include <Run.hpp>
#include <Damage.hpp>


int GLWidget::selectPursuit = 0;
bool GLWidget::chasingRobotAlreadyChose = false;
void camera2DMode(float width, float height);
void drawSquare(unsigned int id, float x, float y, float z, float Width, float Height);

int GLWidget::timeStartOfGame = TIMER.elapsed();
int GLWidget::timebase = TIMER.elapsed();
int GLWidget::lastFrameTime = TIMER.elapsed();
int GLWidget::frames = 0.0;

double GLWidget::relativeTime = 1000000000.0;

bool GLWidget::keyJump = false;
bool GLWidget::keyRight = false;
bool GLWidget::keyLeft = false;
bool GLWidget::keyBlock = false;
bool GLWidget::keyAttack1 = false;
bool GLWidget::keyAttack2 = false;
bool GLWidget::keyThrow = false;

int GLWidget::selectedStage = 0;
int GLWidget::selectedCharacter = 0;

GLWidget::GLWidget(MainWindow* theParentWindow, QWidget * parent, const QGLWidget * shareWidget, Qt::WFlags f):
  QGLWidget(parent, shareWidget, f), type(GLOBAL), width(parent->width()), height(parent->height()), ratio((float)(parent->width())/(float)(parent->height())),
  textureAlreadyLoaded(false), callListAlreadyLoaded(false), md2TexLoaded(false),
  arena(NULL), haveArena(false)
{

	parentWindow = theParentWindow;

  // la politique de gestion des evenements
  setFocusPolicy(Qt::ClickFocus);

  //default type
  type = FREE;
  InitVector();

  lightPosition[0] = 5.0;
  lightPosition[1] = 1.10;
  lightPosition[2] = 1.5;
  lightPosition[3] = 1.0;

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(50);
}

GLWidget::GLWidget(MainWindow* theParentWindow, int window_type, QWidget * parent, const QGLWidget * shareWidget, Qt::WFlags f):
  QGLWidget(parent, shareWidget, f), type(window_type), width(parent->width()), height(parent->height()), ratio((float)(parent->width())/(float)(parent->height())),
  textureAlreadyLoaded(false), callListAlreadyLoaded(false), md2TexLoaded(false),
  arena(NULL), haveArena(false)
{
	parentWindow =theParentWindow;

  // la politique de gestion des evenements
  setFocusPolicy(Qt::ClickFocus);

  InitVector();

  lightPosition[0] = 5.0;
  lightPosition[1] = 1.10;
  lightPosition[2] = 1.5;
  lightPosition[3] = 1.0;

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(50);
}

void GLWidget::setCameraModeToPursuit(const float & xRobot, const float & yRobot, const float & zRobot, const float & far)
{
    type = PURSUIT;
    xRobotChasing = (float*)&xRobot;
    yRobotChasing = (float*)&yRobot;
    zRobotChasing = (float*)&zRobot;
    distance = far;

    aim[0] = xRobot;
    aim[1] = yRobot;
    aim[2] = zRobot;

    position[0] = aim[0];
    position[1] = aim[1];
    position[2] = aim[2] + distance;
}

void GLWidget::setCameraModeToPursuit(const float & far)
{
	type = PURSUIT;
	distance = far;
}

void GLWidget::setCameraModeToGlobal()
{
	type = GLOBAL;
}

void GLWidget::setCameraModeToDebug()
{
	type = DEBUG;
}

void GLWidget::setCameraModeToFree()
{
	type = FREE;
}

void GLWidget::update()
{
	switch (type)
	{
		case PURSUIT:
			// si les robots n'ont pas encore été chargés
			if (arena->getRobots().getBots().size() == 0)
				return;

			// verifie si un robot a deja été choisi
			if (!chasingRobotAlreadyChose)
			{
				if(GLWidget::selectPursuit == 3)
				{
					xRobotChasing = &(arena->getAvatar()->getRobotState().getPosition()[0]);
					yRobotChasing = &(arena->getAvatar()->getRobotState().getPosition()[1]);
					zRobotChasing = &(arena->getAvatar()->getRobotState().getPosition()[2]);
				}
				else
				{
					xRobotChasing = &((arena->getRobots().getBots()[GLWidget::selectPursuit])->getRobotState().getPosition()[0]);
					yRobotChasing = &((arena->getRobots().getBots()[GLWidget::selectPursuit])->getRobotState().getPosition()[1]);
					zRobotChasing = &((arena->getRobots().getBots()[GLWidget::selectPursuit])->getRobotState().getPosition()[2]);
				}

				aim[0] = *xRobotChasing;
				aim[1] = *yRobotChasing;
				aim[2] = *zRobotChasing;

				position[0] = aim[0];
				position[1] = aim[1];
				position[2] = aim[2] + distance;
				chasingRobotAlreadyChose = true;
			}

			float decalage_y;
			decalage_y = 0.5;

			aim[0] = *xRobotChasing;
			aim[1] = *yRobotChasing + decalage_y;
			aim[2] = *zRobotChasing;

			position[0] = aim[0];
			position[1] = aim[1];
			position[2] = aim[2] + distance;
			break;

		case GLOBAL:
			// si les robots n'ont pas encore été chargés
			if (arena->getRobots().getBots().size() == 0)
				return;

			int size;
			size = arena->getRobots().getBots().size();
			float xmin, xmax, ymin, ymax;

			xmin = (arena->getRobots().getBots()[0])->getRobotState().getPosition()[0];
			xmax = (arena->getRobots().getBots()[0])->getRobotState().getPosition()[0];

			ymin = (arena->getRobots().getBots()[0])->getRobotState().getPosition()[1] + 1.0;
			ymax = (arena->getRobots().getBots()[0])->getRobotState().getPosition()[1] + 1.0;

			for (int i = 1; i < size; ++i)
			{
				if ((arena->getRobots().getBots()[i])->getRobotState().getPosition()[0] < xmin)
					xmin = (arena->getRobots().getBots()[i])->getRobotState().getPosition()[0];
				else if ((arena->getRobots().getBots()[i])->getRobotState().getPosition()[0] > xmax)
					xmax = (arena->getRobots().getBots()[i])->getRobotState().getPosition()[0];

				if ((arena->getRobots().getBots()[i])->getRobotState().getPosition()[1] < ymin)
					ymin = (arena->getRobots().getBots()[i])->getRobotState().getPosition()[1];
				else if ((arena->getRobots().getBots()[i])->getRobotState().getPosition()[1] > ymax)
					ymax = (arena->getRobots().getBots()[i])->getRobotState().getPosition()[1];
			}

			// on regarde l'avatar
			if (arena->getAvatar() != NULL)
			{
				if ((arena->getAvatar())->getRobotState().getPosition()[0] < xmin)
					xmin = (arena->getAvatar())->getRobotState().getPosition()[0];
				else if ((arena->getAvatar())->getRobotState().getPosition()[0] > xmax)
					xmax = (arena->getAvatar())->getRobotState().getPosition()[0];

				if ((arena->getAvatar())->getRobotState().getPosition()[1] < ymin)
					ymin = (arena->getAvatar())->getRobotState().getPosition()[1];
				else if ((arena->getAvatar())->getRobotState().getPosition()[1] > ymax)
					ymax = (arena->getAvatar())->getRobotState().getPosition()[1];
			}

			// calculating of minimal rectangle containing all bots
			float cx, cy, cz, fratio, w, h, resWidth, resHeight, marge, distance;
			cx = (xmax + xmin) / 2.0;
			cy = (ymax + ymin) / 2.0;
			cz = (arena->getRobots().getBots()[0])->getRobotState().getPosition()[2];

			h = ymax - ymin + 1e-4;
			w = xmax - xmin + 1e-4;

			fratio = w / h;

			marge = MARGIN;

			if (ratio > fratio)
			{
				resHeight = h + marge;
				resWidth = ratio * resHeight;
			}
			else
			{
				resWidth = w + marge;
				resHeight = resWidth / ratio;
			}

			if (cy < GLOBAL_Y_MIN)
				cy = GLOBAL_Y_MIN;

			aim[0] = cx;
			aim[1] = cy;
			aim[2] = cz;

			// calculating od camera distance
			if (ratio > 1.0)
				distance = ((float) resWidth / 2.0) / tan(VIEW_ANGLE / 2.0);
			else
				distance = ((float) resHeight / 2.0) / tan(VIEW_ANGLE / 2.0);

			distance += distance*MARGIN_COEFF;
			// printf("distance %.2f\n", distance);
			position[0] = aim[0];
			position[1] = aim[1] + 0.7;
			position[2] = aim[2] + distance;

			if(position[2] >= 10.0) // set distance max
				position[2] = 10.0;
			//printf("C %.2f %.2f -> Carre %.2f %.2f ratio %.2f Rectangle %.2f %.2f ratio %.2f\n", cx, cy, w, h, fratio, resWidth, resHeight, ratio);
			break;

		case DEBUG:
		case FREE:
			UpdateRightVector();
			UpdatePositionVector();
			break;
	}
}

void GLWidget::setLookAt()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(VIEW_ANGLE, ratio, 0.1, 100.0f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (type == PURSUIT)
	{
		gluLookAt(position[0], position[1], position[2],
			aim[0], aim[1], aim[2],
			up[0], up[1], up[2]);
	}
	else if (type == GLOBAL)
	{
		gluLookAt(position[0], position[1], position[2],
			aim[0], aim[1], aim[2],
			up[0], up[1], up[2]);
	}
	else if (type == DEBUG)
	{
		glTranslatef(translation[0], translation[1], translation[2]);
		gluLookAt(position[0], position[1], position[2],
			aim[0], aim[1], aim[2], up[0], up[1], up[2]);
	}
	else if (type == FREE)
	{
		gluLookAt(position[0], position[1], position[2],
			aim[0], aim[1], aim[2],
			up[0], up[1], up[2]);
	}
}

void GLWidget::initializeGL(void)
{
	glClearColor(1.0, 0.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);
}

void GLWidget::resizeGL(int widthS,int heightS)
{
  glViewport(0,0,widthS,heightS);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLfloat r=widthS;
  r/=heightS;
  GLfloat viewAngle=45.0f;
  GLfloat viewNear=0.1f;
  GLfloat viewFar=1000.0f;
  gluPerspective(viewAngle,r,viewNear,viewFar);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  width = widthS;
  height = heightS;
  ratio = (float)width / (float)height;
}

void GLWidget::keyPressEvent(QKeyEvent   *e)
{
  float scale = 0.2;

	if (e->key() == Qt::Key_Left || e->key() == Qt::Key_Q)
	{
		keyLeft = true;
	}
	else if (e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
	{
		keyRight = true;
	}
	else if (e->key() == Qt::Key_Up || e->key() == Qt::Key_Z)
	{
		keyJump = true;
	}
	else if (e->key() == Qt::Key_Down || e->key() == Qt::Key_S)
	{
		keyBlock = true;
	}
	else if (e->key() == Qt::Key_Control || e->key() == Qt::Key_Y)
	{
		keyAttack1 = true;
	}
	else if (e->key() == Qt::Key_Alt || e->key() == Qt::Key_U)
	{
		keyAttack2 = true;
	}
	else if (e->key() == Qt::Key_Space || e->key() == Qt::Key_I)
	{
		keyThrow = true;
	}
	else if (e->key() == Qt::Key_PageUp)
	{
		GLWidget::selectPursuit++;
		if(GLWidget::selectPursuit == 4) GLWidget::selectPursuit = 0;
		chasingRobotAlreadyChose = false;
	}
	else if (e->key() == Qt::Key_PageDown)
	{
		GLWidget::selectPursuit--;
		if(GLWidget::selectPursuit < 0) GLWidget::selectPursuit = 3;
		chasingRobotAlreadyChose = false;
	}
	else if (e->key() == Qt::Key_K)
	{
		//glcamera.turnYaw(-4);
		if(type == DEBUG)
				translation[0]++;
		else if(type == FREE)
		{
			position[0] += right[0] * scale;
			position[1] += right[1] * scale;
			position[2] += right[2] * scale;
		}

		//lightPosition[0] -= 0.1;
		//printf("light %.2f %.2f %.2f %.2f\n", lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	}
	else if (e->key() == Qt::Key_M)
	{
		//glcamera.turnYaw(4);
		if(type == DEBUG)
			translation[0]--;
		else if(type == FREE)
		{
			position[0] -= right[0] * scale;
			position[1] -= right[1] * scale;
			position[2] -= right[2] * scale;
		}

		//lightPosition[0] += 0.1;
		//printf("light %.2f %.2f %.2f %.2f\n", lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	}
	else if (e->key() == Qt::Key_O)
	{
		//glcamera.turnPitch(-4);
		if(type == DEBUG)
			translation[2]++;
		else if(type == FREE)
		{
			position[0] += direction[0] * scale;
			position[1] += direction[1] * scale;
			position[2] += direction[2] * scale;
		}

		//lightPosition[2] += 0.1;
		//printf("light %.2f %.2f %.2f %.2f\n", lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	}
	else if (e->key() == Qt::Key_L)
	{
		//glcamera.turnPitch(4);
		if(type == DEBUG)
			translation[2]--;
		else if(type == FREE)
		{
			position[0] -= direction[0] * scale;
			position[1] -= direction[1] * scale;
			position[2] -= direction[2] * scale;
		}

		//lightPosition[2] -= 0.1;
		//printf("light %.2f %.2f %.2f %.2f\n", lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	}
	else if (e->key() == Qt::Key_I)
	{
		//translation[1]--;
		if(TEST < NB_ANIM) ++TEST;
		//lightPosition[1] += 0.1;
		//printf("light %.2f %.2f %.2f %.2f\n", lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	}
	else if (e->key() == Qt::Key_P)
	{
		//translation[1]++;
		if(TEST > 1) --TEST;
		//lightPosition[1] -= 0.1;
		//printf("light %.2f %.2f %.2f %.2f\n", lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	}

	updateGL();
}


void GLWidget::keyReleaseEvent(QKeyEvent   *e)
{
	if (e->key() == Qt::Key_Left || e->key() == Qt::Key_Q)
	{
		keyLeft = false;
	}
	else if (e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
	{
		keyRight = false;
	}
	else if (e->key() == Qt::Key_Up || e->key() == Qt::Key_Z)
	{
		keyJump = false;
	}
	else if (e->key() == Qt::Key_Down || e->key() == Qt::Key_S)
	{
		keyBlock = false;
	}
	else if (e->key() == Qt::Key_Control || e->key() == Qt::Key_Y)
	{
		keyAttack1 = false;
	}
	else if (e->key() == Qt::Key_Alt || e->key() == Qt::Key_U)
	{
		keyAttack2 = false;
	}
	else if (e->key() == Qt::Key_Space || e->key() == Qt::Key_I)
	{
		keyThrow = false;
	}

}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    int vectX, vectY;
    double step=0.05;


    vectX=e->x()-oldMouseX;
    vectY=e->y()-oldMouseY;
    oldMouseX=e->x();
    oldMouseY=e->y();


    if(vectX>0)
        angleTeta+=step;
    else
    {
        if(vectX<0)
            angleTeta-=step;
    }


    if(vectY>0)
    {
        if(angleAlpha<(M_PI/2.0-step) )
            angleAlpha+=step;
    }
    else
    {
        if(vectY<0)
        {
            if(angleAlpha>- (M_PI/2.0-step))
                angleAlpha-=step;
        }
    }

    UpdatePositionVector();
    UpdateRightVector();
    updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) // LEFT BUTTON
    {

    }
    else if (e->button() == Qt::RightButton) // RIGHT BUTTON
    {

    }
    else if (e->button() == Qt::MidButton) // MIDDLE BUTTON
    {

    }
}

void GLWidget::InitVector()
{
    up[0]=0.;up[1]=1.;up[2]=0.;
    direction[0]=0;direction[1]=0;direction[2]=-1;
    UpdateRightVector(); //maintenir le repère orthogonal

    if(type == FREE)
    {
        angleTeta = M_PI*6.3/5.0;
        angleAlpha = 0.0;
        position[0]=0.0;position[1]=0.0;position[2]=3.0;
    }
    else if(type == DEBUG)
    {
        angleTeta = 0.0;
        angleAlpha = 0.0;
        position[0]=0.0;position[1]=0.0;position[2]=3.0;
    }

    aim[0]=aim[1]=aim[2]=0.0;
    translation[0]=translation[1]=translation[2]=0;

    rayon = 5.0;
    UpdateRightVector();
    UpdatePositionVector();
}

void GLWidget::UpdateRightVector()
{
    right[0] = up[1]*direction[2] - up[2]*direction[1];
    right[1] = up[2]*direction[0] - up[0]*direction[2];
    right[2] = up[0]*direction[1] - up[1]*direction[0];
}

void GLWidget::UpdatePositionVector()
{
    double scale_angle = 0.8;    //coordonnées sphériques (attention aux axes)

    if(type == DEBUG)
    {
        position[0]=aim[0] + rayon*sin(angleTeta)*cos(angleAlpha);
        position[1]=aim[1] + rayon*sin(angleAlpha);
        position[2]=aim[2] + rayon*cos(angleTeta)*cos(angleAlpha);
    }
    else if(type == FREE)
    {
        direction[0] = sin(-angleTeta*scale_angle)*cos(-angleAlpha*scale_angle);
        direction[1] = sin(-angleAlpha*scale_angle);
        direction[2] = cos(-angleTeta*scale_angle)*cos(-angleAlpha*scale_angle);

        aim[0] = position[0] + direction[0];
        aim[1] = position[1] + direction[1];
        aim[2] = position[2] + direction[2];
        //printf("position %.2f %.2f %.2f aim %.2f %.2f %.2f direction %.2f %.2f %.2f\n", position[0],position[1],position[2], aim[0],aim[1],aim[2], direction[0],direction[1],direction[2]);
    }
}

void GLWidget::setSelectedStage(int idStage)
{
	if (idStage <= 0 || idStage > NB_ARENA)
		return;
	else
		selectedStage = idStage;
}

void GLWidget::setSelectedCharacter(int idCharacter)
{
	if (idCharacter <= 0 || idCharacter > NB_CHARACTER)
		return;
	else
		selectedCharacter = idCharacter;
}

int GLWidget::getSelectedStage()
{
	return selectedStage;
}

int GLWidget::getSelectedCharacter()
{
	return selectedCharacter;
}

 void GLWidget::paintEvent(QPaintEvent *)
 {
     painter.begin(this);
     painter.setRenderHint(QPainter::Antialiasing);


	 //////////////////// BEGIN PAINTGL ///////////////////


	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Calcul des fps
	int time = TIMER.elapsed();
	if((time - timebase) >= 1000)
	{
		//printf("fps : %f\n", frames*1000.0f/(time - timebase));
		frames = 0;
		timebase = time;
	}
	int lastFrameDuration = time - lastFrameTime;
	lastFrameTime = time;
	relativeTime = (double)lastFrameDuration/1000.0;

	// Mise a jour des cameras
	this->update();
	this->setLookAt();

	if(!haveArena)
	{
		std::vector<int> botsType;
		std::vector<int> nbBots;

		// Every bots are differents from the player character
		for (int i = 1; i <= NB_CHARACTER; ++i) // NB_CHARACTER
		{
			botsType.push_back(i);
			if (i == selectedCharacter)
				nbBots.push_back(0);
			else
				nbBots.push_back(1);
		}

		arena = &Arena::getArena(GLWidget::selectedStage, botsType, nbBots);
		haveArena = true;
	}
	if(arena->gameEnd)
		parentWindow->gotoEnding(arena->gameWin, arena->getAvatar()->type());
	else
		arena->update(*this);

	++frames;


	//////////////////// END PAINTGL ///////////////////

    painter.end();
}

void GLWidget::setPainter(float ax, float ay, float bx, float by, int damage, int size, bool bold, QFont font, QPen pen)
{
	QColor color;

	if (damage < 20)
	{
		color.setRgb(60, 60, 60, 255);
	}
	else if (damage < 50)
	{
		color.setRgb(255, 145, 60, 255);
	}
	else if (damage < 90)
	{
		color.setRgb(255, 100, 60, 255);
	}
	else if (damage < 125)
	{
		color.setRgb(255, 55, 60, 255);
	}
	else if (damage < 150)
	{
		color.setRgb(255, 30, 60, 255);
	}
	else
	{
		color.setRgb(255, 0, 0, 255);
	}

	pen.setColor(color);
	font.setFamily("Helvetica");
	font.setBold(bold);
	font.setPixelSize(size);

	painter.fillRect(QRect(ax, ay, bx, by), QColor(255, 255, 255, 0));

	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(QRect(ax, ay, bx, by), (Qt::AlignTop, Qt::AlignHCenter), QString::number(damage)+"%");
}
