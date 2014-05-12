//
//  AppManager.h
//  
//
//  Created by Adam Kohl on 4/23/14.
//
//

#ifndef ____AppManager__
#define ____AppManager__

#include "InteractionManager.h"
//#include "SceneManager.h"

class AppManager {
    
public:
    
    /* pullData retreives the necessary data from the Interaction Manager and UiViewer*/
    void pullData(void);
    
    /*pushData sends data to update the scene manager*/
    void pushData(void);

protected:
    
    InteractionManager*    _interactionManager;
    
    std::vector<SceneCommand> _sceneCommandList;

};

#endif /* defined(____AppManager__) */
