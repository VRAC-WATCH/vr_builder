//
//  AppManager.h
//  
//
//  Created by Adam Kohl on 4/23/14.
//
//

#ifndef ____AppManager__
#define ____AppManager__

// Forward declarations
class InteractionManager;
class SceneManager;

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
	
	/** Returns the interaction manager. */
	inline InteractionManager* interactionManager() { return _interactionManager; }
	
	/** Returns the scene manager. */
	inline SceneManager* sceneManager() { return _sceneManager; }


protected:
    
	/** iVars. */
    InteractionManager*		_interactionManager;
    SceneManager*			_sceneManager;
    
};

#endif /* defined(____AppManager__) */
