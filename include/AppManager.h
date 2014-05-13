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
#include "SceneManager.h"

class AppManager {
    
public:

	/** Default Constructor. */
	AppManager();

	/** Destructor. */
	~AppManager();
    
    /* pullData retreives the necessary data from the Interaction Manager and UiViewer*/
    void update(void);
    
    /*Declares the wether GLUT or JUGGLER type*/
    //void interactionType(enum type);


protected:
    
    InteractionManager*    _interactionManager;
    InteractionManager*    _interactionGLUTManager;
    SceneManager*          _sceneManager;
    
};

#endif /* defined(____AppManager__) */
