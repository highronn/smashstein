/*
 * Internal Includes
 */
#include <MainWindow.hpp>

#include "ui_Ui_MainWindow.h"

MainWindow::MainWindow()
{
	musicIntro = new Sound("sound/music/intro.mp3", STREAMED_MUSIC, true);
	musicFight = new Sound("sound/music/fight1.mp3", STREAMED_MUSIC, true);
	musicEndingLost = new Sound("sound/music/ending-lost.mp3", STREAMED_MUSIC, true);
	musicEndingWon = new Sound("sound/music/ending-won.mp3", STREAMED_MUSIC, true);
	musicIntro->play();


	/* Building MainWindow from UI file */
	mainwindow = new QMainWindow();
	setupUi(mainwindow);

	/* At start, only show slash screen */
	frameGame->setVisible(false);
	frameChoice->setVisible(false);
	frameEnding->setVisible(false);
	btnPlay->setFocus();



	/* Adds an image in background */
	QString stylesheet ("QWidget{"
		"background: #FFF url(data/logo-smashtein-garbage.jpg) no-repeat;"
	"}");
	imgIntro->setStyleSheet(stylesheet);



	// Adds GLWidgets
	GLWidget * glwidget1 = new GLWidget(this, PURSUIT, glFramePursuit);
	QHBoxLayout *layout_1 = new QHBoxLayout();
	layout_1->addWidget(glwidget1);
	glFramePursuit->setLayout(layout_1);
	glwidget1->setCameraModeToPursuit(2.0);

	GLWidget * glwidget2 = new GLWidget(this, GLOBAL, glFrameGlobal);
	QHBoxLayout *layout_2 = new QHBoxLayout();
	layout_2->addWidget(glwidget2);
	glFrameGlobal->setLayout(layout_2);

	GLWidget * glwidget3 = new GLWidget(this, FREE, glFrameFree);
	QHBoxLayout *layout_3 = new QHBoxLayout();
	layout_3->addWidget(glwidget3);
	glFrameFree->setLayout(layout_3);

	GLWidget * glwidget4 = new GLWidget(this, DEBUG, glFrameDebug);
	QHBoxLayout *layout_4 = new QHBoxLayout();
	layout_4->addWidget(glwidget4);
	glFrameDebug->setLayout(layout_4);

	// Initialize the default view
	setGlobalView();

	// Connecting "quit" signal from menu to "close" MainWindow
	QObject::connect(actionQuit, SIGNAL(triggered()), mainwindow, SLOT(close()));
	QObject::connect(btnQuit, SIGNAL(clicked()), mainwindow, SLOT(close()));


	// Managing different views
	QObject::connect(actionPursuitView, SIGNAL(triggered()), this, SLOT(setPursuitView()));
	QObject::connect(actionGlobalView, SIGNAL(triggered()), this, SLOT(setGlobalView()));
	QObject::connect(actionDebugView, SIGNAL(triggered()), this, SLOT(setDebugView()));
	QObject::connect(actionFreeView, SIGNAL(triggered()), this, SLOT(setFreeView()));
	QObject::connect(actionFourViews, SIGNAL(triggered()), this, SLOT(setFourViews()));


	// Buttons
	QObject::connect(btnPlay, SIGNAL(clicked()), this, SLOT(gotoChoice()));
	QObject::connect(btnFight, SIGNAL(clicked()), this, SLOT(gotoGame()));

	// Open dialogs
	QObject::connect(actionPreferences,		SIGNAL(triggered()), this, SLOT(openPreferences()));
	QObject::connect(actionKeyboard,		SIGNAL(triggered()), this, SLOT(openKeyboard()));
	QObject::connect(actionAboutSmashtein,	SIGNAL(triggered()), this, SLOT(openAboutSmashtein()));

	// Select a character
	QObject::connect(radioCharBoxman,	SIGNAL(clicked()), this, SLOT(selectChar1()));
	QObject::connect(radioCharCoco,		SIGNAL(clicked()), this, SLOT(selectChar2()));
	QObject::connect(radioCharHector,	SIGNAL(clicked()), this, SLOT(selectChar3()));
	QObject::connect(radioCharOpera,	SIGNAL(clicked()), this, SLOT(selectChar4()));

	// Select a stage
	QObject::connect(radioStageRome, SIGNAL(clicked()), this, SLOT(selectStage1()));
	QObject::connect(radioStageMomo, SIGNAL(clicked()), this, SLOT(selectStage2()));
	
	// View options
	QObject::connect(actionShowGraph, SIGNAL(triggered()), this, SLOT(setShowGraph()));
	QObject::connect(actionShowBoundingBox, SIGNAL(triggered()), this, SLOT(setShowBoundingBox()));
}

MainWindow::~MainWindow()
{
	delete musicIntro;
	delete musicFight;
	delete sndChar1;
	delete sndChar2;
	delete sndChar3;
	delete sndChar4;
	delete musicEndingWon;
	delete musicEndingLost;
}

void MainWindow::setPursuitView()
{
	resetAllActionViews();
	glFramePursuit->setVisible(true);
	actionPursuitView->setChecked(true);
}

void MainWindow::setGlobalView()
{
	resetAllActionViews();
	glFrameGlobal->setVisible(true);
	actionGlobalView->setChecked(true);
}

void MainWindow::setFreeView()
{
	resetAllActionViews();
	glFrameFree->setVisible(true);
	actionFreeView->setChecked(true);	
}

void MainWindow::setDebugView()
{
	resetAllActionViews();
	glFrameDebug->setVisible(true);
	actionDebugView->setChecked(true);
}

void MainWindow::setFourViews()
{
	resetAllActionViews();
	glFramePursuit->setVisible(true);
	glFrameDebug->setVisible(true);
	glFrameGlobal->setVisible(true);
	glFrameFree->setVisible(true);
	actionFourViews->setChecked(true);
}

// Disable the four frames and uncheck every action button
void MainWindow::resetAllActionViews()
{
	glFramePursuit->setVisible(false);
	glFrameDebug->setVisible(false);
	glFrameGlobal->setVisible(false);
	glFrameFree->setVisible(false);

	actionPursuitView->setChecked(false);
	actionGlobalView->setChecked(false);
	actionDebugView->setChecked(false);
	actionFreeView->setChecked(false);
	actionFourViews->setChecked(false);
}


void MainWindow::openPreferences()
{
	/* Opens a dialog box for various settings */
	Ui_DialogPreferences * ui = new Ui_DialogPreferences();
	QDialog * dialog = new QDialog();
	ui->setupUi(dialog);

	/* Initializes the slider with the MasterVolume */
	ui->mainVolumeSlider->setValue(Sound::getMasterVolume()*100);
	ui->mainVolumeValue->setNum(Sound::getMasterVolume()*100);

	QObject::connect(ui->mainVolumeSlider, SIGNAL(valueChanged(int)), ui->mainVolumeValue, SLOT(setNum(int)));
	QObject::connect(ui->mainVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(changeMasterVolume(int)));

	/* Initializes the slider with the BGM volume */
	ui->bgmVolumeSlider->setValue(Sound::getMusicVolume()*100);
	ui->bgmVolumeValue->setNum(Sound::getMusicVolume()*100);

	QObject::connect(ui->bgmVolumeSlider, SIGNAL(valueChanged(int)), ui->bgmVolumeValue, SLOT(setNum(int)));
	QObject::connect(ui->bgmVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(changeBGMVolume(int)));

	/* Initializes the slider with the SFX volume */
	ui->sfxVolumeSlider->setValue(Sound::getEffectVolume()*100);
	ui->sfxVolumeValue->setNum(Sound::getEffectVolume()*100);

	QObject::connect(ui->sfxVolumeSlider, SIGNAL(valueChanged(int)), ui->sfxVolumeValue, SLOT(setNum(int)));
	QObject::connect(ui->sfxVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSFXVolume(int)));

	dialog->show();
}

void MainWindow::changeMasterVolume(int value)
{
	Sound::setMasterVolume(value/100.0);
}

void MainWindow::changeBGMVolume(int value)
{
	Sound::setMusicVolume(value/100.0);
}

void MainWindow::changeSFXVolume(int value)
{
	Sound::setEffectVolume(value/100.0);
}

void MainWindow::gotoChoice()
{
	frameIntro->setVisible(false);
	frameChoice->setVisible(true);
	frameGame->setVisible(false);
	frameEnding->setVisible(false);

	// Init the checkers
	checkedCharacter = false;
	checkedStage = false;
	btnFight->setEnabled(false);

	// Show characters and stages images
	imgCharBoxman->setStyleSheet("QWidget{background: #FFF url(data/boxman.jpg) no-repeat;}");
	imgCharCoco->setStyleSheet("QWidget{background: #FFF url(data/bandicoot.jpg) no-repeat;}");
	imgCharHector->setStyleSheet("QWidget{background: #FFF url(data/hector.jpg) no-repeat;}");
	imgCharOpera->setStyleSheet("QWidget{background: #FFF url(data/opera.jpg) no-repeat;}");

	imgStageMomo->setStyleSheet("QWidget{background: #FFF url(obj/momoshiro/screen.jpg) no-repeat;}");
	imgStageRome->setStyleSheet("QWidget{background: #FFF url(obj/rome/screen.jpg) no-repeat;}");

	// Init characters sounds
	sndChar1 = new Sound("sound/boxman/victorywait.mp3", STREAMED_MUSIC, false);
	sndChar2 = new Sound("sound/bandicoot/victorywait2.mp3", STREAMED_MUSIC, false);
	sndChar3 = new Sound("sound/hector/victorywait1.mp3", STREAMED_MUSIC, false);
	sndChar4 = new Sound("sound/opera/victorywait.mp3", STREAMED_MUSIC, false);
}

void MainWindow::gotoGame()
{
	musicIntro->pause();
	
	musicFight->play();
	musicFight->setVolume(0.3);

	frameIntro->setVisible(false);
	frameChoice->setVisible(false);
	frameGame->setVisible(true);
	frameEnding->setVisible(false);
}

void MainWindow::gotoEnding(bool victory, int perso)
{
	musicFight->pause();

	frameIntro->setVisible(false);
	frameChoice->setVisible(false);
	frameGame->setVisible(false);
	frameEnding->setVisible(true);

	if (victory)
		musicEndingWon->play();
	else
		musicEndingLost->play();

	switch (perso)
	{
		case BOXMAN: // BOXMAN
			if (victory)
				imgEnding->setStyleSheet("QWidget{background: #FFF url(data/ending/boxman_v.ppm) no-repeat;}");
			else
				imgEnding->setStyleSheet("QWidget{background: #FFF url(data/ending/boxman_d.ppm) no-repeat;}");
			break;

		case BANDICOOT: // BANDICOOT
			if (victory)
				imgEnding->setStyleSheet("QWidget{background: #FFF url(data/ending/bandicoot_v.ppm) no-repeat;}");
			else
				imgEnding->setStyleSheet("QWidget{background: #FFF url(data/ending/bandicoot_d.ppm) no-repeat;}");
			break;

		case HECTOR: // HECTOR
			if (victory)
				imgEnding->setStyleSheet("QWidget{background: #FFF url(data/ending/hector_v.ppm) no-repeat;}");
			else
				imgEnding->setStyleSheet("QWidget{background: #FFF url(data/ending/hector_d.ppm) no-repeat;}");
			break;
			
		case OPERA: // OPERA
			if (victory)
				imgEnding->setStyleSheet("QWidget{background: #FFF url(data/ending/opera_v.ppm) no-repeat;}");
			else
				imgEnding->setStyleSheet("QWidget{background: #FFF url(data/ending/opera_d.ppm) no-repeat;}");
			break;
	}
}

void MainWindow::selectStage1() // MOMOSHIRO
{
	checkedStage = true;
	checkSelection();
	GLWidget::setSelectedStage(1);
}

void MainWindow::selectStage2() // ROME
{
	checkedStage = true;
	checkSelection();
	GLWidget::setSelectedStage(2);
}

void MainWindow::selectChar1() // BOXMAN
{
	checkedCharacter = true;
	checkSelection();
	GLWidget::setSelectedCharacter(1);

	sndChar1->play();
}

void MainWindow::selectChar2() // BANDICOOT
{
	checkedCharacter = true;
	checkSelection();
	GLWidget::setSelectedCharacter(2);

	sndChar2->play();
}

void MainWindow::selectChar3() // HECTOR
{
	checkedCharacter = true;
	checkSelection();
	GLWidget::setSelectedCharacter(3);

	sndChar3->play();
}

void MainWindow::selectChar4() // OPERA
{
	checkedCharacter = true;
	checkSelection();
	GLWidget::setSelectedCharacter(4);

	sndChar4->play();
}

// Before starting the fight, you need to select character and stage
// This function checks if you did it or not and then, enables the fight button
void MainWindow::checkSelection()
{
	if (checkedCharacter && checkedStage)
		btnFight->setEnabled(true);
}


void MainWindow::openKeyboard()
{
	/* Opens a dialog box for help & key shortcuts */
	Ui_DialogKeyboard * ui = new Ui_DialogKeyboard();
	QDialog * dialog = new QDialog();
	ui->setupUi(dialog);

	ui->imgKeyboard->setStyleSheet("QWidget{background: #FFF url(data/keyboard.jpg) no-repeat;}");

	dialog->show();
}

void MainWindow::openAboutSmashtein()
{
	/* Opens a dialog box for Smashtein */
	Ui_DialogAboutSmashtein * ui = new Ui_DialogAboutSmashtein();
	QDialog * dialog = new QDialog();
	ui->setupUi(dialog);

	ui->imgAboutSmashtein->setStyleSheet("QWidget{background: #FFF url(data/logo-imac.png) no-repeat;}");

	dialog->show();
}
