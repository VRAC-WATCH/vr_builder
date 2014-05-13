//
//  AppManager.cpp
//  
//
//  Created by Adam Kohl on 4/23/14.
//
//

#include "AppManager.h"

AppManager::AppManager()
{
	std::cout << "AppManager constructor called" << std::endl;
}

AppManager::~AppManager()
{
	std::cout << "AppManager destructor called" << std::endl;
}

/* pull data will need to be called inside of one of the main loops */
void AppManager::update(void)
{
    // The sceneCommandList is populated
    _interactionManager->update();
    _sceneCommandList = _interactionManager->sceneCommands();
    
	std::cout << "Updating app manager" << std::endl;
}

