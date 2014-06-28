//
//  AppManager.cpp
//  
//
//  Created by Adam Kohl on 4/23/14.
//
//

// System headers
#include <memory>

// Local headers
#include "AppManager.h"
#include "InteractionManager.h"
#include "SceneManager.h"

// Use this as a temporary solution for defining our current app type
//#define GLUT
#define JUGGLER

AppManager::AppManager()
{
	std::cout << "AppManager constructor called" << std::endl;
	
#ifdef JUGGLER
	_interactionManager = new InteractionManager(InteractionManager::JUGGLER_INTERFACE);
#else
	_interactionManager = new InteractionManager(InteractionManager::GLUT_INTERFACE);
#endif

	_sceneManager = new SceneManager(_interactionManager->howManyWantCursor());
}

AppManager::~AppManager()
{
	std::cout << "AppManager destructor called" << std::endl;
}

/* pull data will need to be called inside of one of the main loops */
void AppManager::update(void)
{
//	std::cout << "Updating app manager" << std::endl;
	
    // Grab any interactions that have happened since the last update
    _interactionManager->update();
    std::vector<SceneCommand*> _sceneCommandList = _interactionManager->sceneCommands();
    
    // Pass along the updates to the scene so that we can see them visually
    _sceneManager->update(1, _sceneCommandList);
}
/*
void AppManager::interactionType(enum type)
{
    _interactionGLUTManager = _interactionManager->InteractionManager(InterfaceType type);
}
*/
