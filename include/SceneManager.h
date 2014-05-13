//
//  sceneMgr.h
//  VRBuilder
//
//  Created by Frederick Thompson on 4/25/14.
//
//

#ifndef __VRBuilder__sceneMgr__
#define __VRBuilder__sceneMgr__

// OSG headers
#include <osg/ref_ptr>

// Local headers
#include "SceneCommand.h"

// Forward declarations
class Scene;

class SceneManager
{
public:
	
	/** Default constructor. */
	SceneManager();
	
	/** Destructor. */
	~SceneManager();
    
    // Takes updates in the form of SceneCommands and
	// turns them into something visualized in the scene
    void update(const std::vector<SceneCommand> &commands);


private:
	
	/** iVars. */
	Scene*	_scene;
};

#endif /* defined(__VRBuilder__sceneMgr__) */
