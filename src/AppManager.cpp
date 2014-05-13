//
//  AppManager.cpp
//  
//
//  Created by Adam Kohl on 4/23/14.
//
//

#include "AppManager.h"

/* pull data will need to be called inside of one of the main loops */
void AppManager::pullData (void)
{
    /*The sceneCommandList is populated*/
    _interactionManager->update();
    std::vector<SceneCommand> _sceneCommandList = _interactionManager->sceneCommands();
    
    /*The sceneCommandList is pushed to the SceneManager*/
    _sceneManager->update(_sceneCommandList);
}

void AppManager::interactionType(enum type)
{
    _interactionGLUTManager = _interactionManager->InteractionManager(InterfaceType type);
}