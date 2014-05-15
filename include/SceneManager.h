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
#include "Scene.h"


class SceneManager
{

private:
	
	/** iVars. */
	Scene*	_scene;
public:
	
	/** Default constructor. */
	SceneManager();
	
	/** Destructor. */
	~SceneManager();
    
    // Takes updates in the form of SceneCommands and
	// turns them into something visualized in the scene
    void update(double t,const std::vector<SceneCommand> &commands);

	//Return root
	osg::ref_ptr<osg::Group> getRoot(){return _scene->getRoot();}

protected:
	
	/** Calculates a navigation matrix and updates the scene. */
	void _updateNavigation(SceneCommand navigationCommand);
};

#endif /* defined(__VRBuilder__sceneMgr__) */
