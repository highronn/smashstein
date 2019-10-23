/*
 * Anti-doublon
 */
#ifndef MainWindow_HPP
#define MainWindow_HPP

/*
 * External Includes
 */
#include <QMainWindow>

/*
 * Internal Includes
 */
#include <ui_Ui_MainWindow.h>
#include <ui_Ui_DialogPreferences.h>
#include <ui_Ui_DialogKeyboard.h>
#include <ui_Ui_DialogAboutSmashtein.h>
#include <GLWidget.hpp>
#include <Sound.hpp>

/** Fenetre principale de RenderBoy
 *
 */
class MainWindow : public QMainWindow, public Ui_MainWindow
{
	Q_OBJECT

	/*
	 * Constructors & Destructors
	 */
public:
	/** Constructeur vide
	 */
	MainWindow();

	/** Destructeur
	 */
	~MainWindow();


	/*
	 * IHM QT
	 */
private:
	QMainWindow * mainwindow;
	bool checkedStage;
	bool checkedCharacter;


public slots:
	void setPursuitView();
	void setGlobalView();
	void setFreeView();
	void setDebugView();
	void setFourViews();
	void openPreferences();
	void changeMasterVolume(int value);
	void changeBGMVolume(int value);
	void changeSFXVolume(int value);
	void gotoChoice();
	void gotoGame();
	void gotoEnding(bool victory, int perso);

	void selectStage1();
	void selectStage2();
	void selectChar1();
	void selectChar2();
	void selectChar3();
	void selectChar4();
	inline void setShowGraph() { Arena::setShowGraph(); }
	inline void setShowBoundingBox() { Arena::setShowBoundingBox(); }
	void openKeyboard();
	void openAboutSmashtein();

public:
	void resetAllActionViews();
	void checkSelection();


	/*
	 * Sound and Music
	 */
private:
	Sound * musicIntro;
	Sound * musicFight;
	Sound * sndChar1;
	Sound * sndChar2;
	Sound * sndChar3;
	Sound * sndChar4;
	Sound * musicEndingLost;
	Sound * musicEndingWon;




	/*
	 * GLWidget
	 */
private:
	GLWidget * glwidget;


public:

	/** verify if Application has GLWidget
	 * bool True if GLWidget has else False
	 */
	bool hasGLWidget() const
	{
		return glwidget;
	}

	/** returns a read only reference on glwidget
	 * \return a read only reference on glwidget
	 */
	inline const GLWidget & getGLWidget() const
	{
		return *glwidget;
	}

	/** returns a read/write  reference on glwidget
	 * \return a read/write  reference on glwidget
	 */
	inline GLWidget & getGLWidget()
	{
		return *glwidget;
	}

	/** Set the glwidget
	 * \param glwidget
	 */
	inline void setGLWidget(GLWidget & glwidget)
	{
		this->glwidget = &glwidget;
	}


public:

	inline QMainWindow & getQMainWindow()
	{
		return *mainwindow;
	}

};


/*
 * End Anti-doublon
 */
#endif

