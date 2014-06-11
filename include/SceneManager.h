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
#include "Builder.h"
#include "Grid.h"
#include "Cursor.h"
#include "Physics.h"
#include <typeinfo>
#include <map>

class SceneManager
{

private:
	int grid_size;
	float grid_block_size;
	/** iVars. */
	Scene*	_scene;
	Builder* _builder;
	Physics* _physics;
	Grid* _grid;
	Cursor* _cursor;

	osg::Matrix* _head_matrix;
	bool creationMode;
public:
	
	/** Default constructor. */
	SceneManager();
	
	/** Destructor. */
	~SceneManager();
    
    // Takes updates in the form of SceneCommands and
	// turns them into something visualized in the scene
    void update(double t,std::vector<SceneCommand*> &commands);

	//Return root
	osg::ref_ptr<osg::Group> getRoot(){return _scene->getRoot();}
	//Head Matrix
	void set_head_matrix(osg::Matrix);
};

#endif /* defined(__VRBuilder__sceneMgr__) */
