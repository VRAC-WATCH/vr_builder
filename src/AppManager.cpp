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
    _sceneCommandList = _interactionManager->sceneCommands();
    
    pushData();
}

void AppManager::pushData(void)
{
    
}