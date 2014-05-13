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
    
    //reads in an input from the Application Manager
    void listenAppManger(const SceneCommand& commands);
    
    //Intended to store the location of the blocks in the scene in progress
    //may end up moving somewhere else
    void storeBlock(const SceneCommand& commands);

private:
	
	/** iVars. */
	osg::ref_ptr<SceneCommand> _scene;
};

#endif /* defined(__VRBuilder__sceneMgr__) */
