/*
 * Internal Includes
 */
#include <Application.hpp>
#include <ctime>

Application::Application()
{
}

Application::Application(const Application & app)
:mainwindow(app.mainwindow), qtapplication(app.qtapplication)
{
    
}

Application::~Application()
{
	delete mainwindow;
	delete qtapplication;
}


int Application::execute(int argc, char **argv)
{
    long long int r=0;
	srand(time(NULL));

	/*
	 * Command line arguments processing
	 */
    while (-1 != (r = getopt(argc,argv,"h")))
    {
        switch (r)
        {
            case 'h' :
                print_help();
                exit(EXIT_SUCCESS);
            break;
	}
    }
	
	
	/*
	 * Launching QtApplication
     */
    qtapplication = new QApplication(argc,argv);    

	
	/*
	 * Main window initialisation
	 */
	mainwindow = new MainWindow();
	mainwindow->getQMainWindow().show();
	

	return qtapplication->exec();
}

void Application::print_help()
{
	 //std::cout << "td8 [-h]\n\t " << std::endl;
}
