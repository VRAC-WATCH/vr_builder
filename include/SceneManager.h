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
public:
	
	/** Default constructor. */
	SceneManager();
	
	/** Destructor. */
	~SceneManager();
    
	/** Clears out all visuals in the scene. */
	void clearScene();

	/** 
	 * Computes an intersection of a ray cast from the matrix
	 * to the grid plane.
	 */ 
	osg::Vec3 computeGridIntersection(osg::Matrix mat);

    // Takes updates in the form of SceneCommands and
	// turns them into something visualized in the scene
    void update(double t,std::vector<SceneCommand*> &commands);

	//Return root
	osg::ref_ptr<osg::Group> sceneRoot(){return _scene->getRoot();}

	//Head Matrix
	void set_head_matrix(osg::Matrix);


protected:
	
	/** iVars. */
	Builder* 					_builder;
	bool 						creationMode;
	Cursor* 					_cursor;
	osg::ref_ptr<osg::Node> 			_floor;
	Grid* 						_grid;
	float 						grid_block_size;
	int 						grid_size;
	osg::Matrix 				_head_matrix;
	osg::Matrix 				_wandMatrix;
	Physics* 					_physics;
	Scene*						_scene;
};

#endif /* defined(__VRBuilder__sceneMgr__) */
