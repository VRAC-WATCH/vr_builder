
/*----------------------------------------
	mainJuggler.cpp
	This is the main file where execution begins in the program.
	No changes need to be made in this file.
*/

// VRJ
#include <vrj/Kernel/Kernel.h>

// Local
#include "JugglerInterface.h"
//#include <SceneManager.h>

using namespace vrj;
int main(int argc, char* argv[])
{
	// Allocate the kernel object and the application object
	Kernel* kernel = Kernel::instance();

	JugglerInterface* application = new JugglerInterface(kernel, argc, argv);			 // Instantiate an instance of the app

	// If no args passed to the program
	// Display usage information and exit
	if (argc <= 1)
	{
		std::cout << "\n\n";
		std::cout << "Usage: " << argv[0] << " vjconfigfile[0] vjconfigfile[1] ... vjconfigfile[n]" << std::endl;
		exit(1);
	}

//	SceneManager::instance().handleArguments(&argc, argv);
	// Figure out if this node is the slave or master
	// so that master can handle any information needing
	// synced across all nodes.
//	bool slave = false;
//	for( int i = 1; i < argc; ++i )
//	{
//		if(std::string("--vrjslave") == argv[i]) slave = true;
//	}
//	
//	//the app needs to know if it's the master node or a slave node
//	SceneManager::instance().setIsMaster(!slave);

	// Initialize the kernel object
	kernel->init(argc, argv);

	// Load any config files specified on the command line
	//also handle command line arguments
	for( int i = 1; i < argc; ++i )
	{
		system("env");
		
		//skip slave/master args.  they confuse the kernel
		if(std::string("--vrjmaster") == argv[i] || std::string("--vrjslave") == argv[i]) continue;

/*		if(std::string("--noComputer") == argv[i])
		{
			SceneManager::instance().setNoComputer();
			printf("Forcing noComputer\n");
			continue;
		}
*/
		printf("load config file %s\n", argv[i]);
#ifndef __APPLE__
		//mac loads config files automatically when the kernel is inited
		kernel->loadConfigFile(argv[i]);
#endif
	}

	// Start the kernel running
	kernel->start();

	// Give the kernel an application to execute
	kernel->setApplication(application);

	// Keep thread alive and waiting
	kernel->waitForKernelStop();

	delete application;
	return 0;
}

