/*
 * Anti-doublon
 */
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

/*
 * External Includes
 */
#include <QApplication>
#include <dlfcn.h>

/*
 * Internal Includes
 */
#include <MainWindow.hpp>
#include <Boxman.hpp>

/** Main class for DumbArena
 * 
 */
class Application
{

/*
 * Constructors & Destructors
 */
public:
    /** empty Constructor
     */
    Application();
    /** copy Constructor
     */
    Application(const Application & app);
    /** Destructor
     */
  ~Application();
 
    /*
     * GUI Elements
     */
private: 
    MainWindow * mainwindow;
public :
    /** verify if Application has MainWindow
     * bool True if MainWindow has else False
     */
    bool hasMainWindow() const { return mainwindow;}
    /** returns a read only reference on mainwindow
     * \return a read only reference on mainwindow
     */
    inline const MainWindow & getMainWindow() const {return *mainwindow;}
    /** returns a read/write  reference on mainwindow
     * \return a read/write  reference on mainwindow
     */
    inline  MainWindow & getMainWindow()  {return *mainwindow;}
    /** Set the mainwindow
     * \param mainwindow
     */
    inline void setMainWindow(MainWindow & mainwindow) { this->mainwindow = &mainwindow; }
  
    /*
     * Qt non-GUI elements
     */
private: 
    QApplication * qtapplication;
    
    
public:
    /** Initialize the application with command line parameters.
     * @param argc number of command line arguments
     * @param argv array of command line arguments
     * @return returns 0 if everything is okay  else returns 
     * a positive number
     */
    int execute(int argc, char **argv);
private:
    void print_help();
};


/*
 * End Anti-doublon
 */
#endif

