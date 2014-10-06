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

/** 	SceneManager is the brains which handles all the inputs
	and required outputs
	1. Handles all commands
	2. Translates the commands to the various classes and reflects the changes in the scene

*/
class SceneManager
{
public:
	
	/** Default constructor with no of cursors as input */
	SceneManager(int cursors);
	
	/** Destructor. */
	~SceneManager();
    
	/** Clears out all visuals in the scene. */
	void clearScene();
	
	/** 
	 * Computes an intersection of a ray cast from the matrix
	 * to the scene geometry.
	 */ 
	bool computeBoxIntersection(osg::Matrix mat, osg::Vec3 &intersection);
	/** 
	 * Computes an intersection of a ray cast from the matrix
	 * to the grid plane.
	 */ 
	bool computeGridIntersection(osg::Matrix mat, osg::Vec3 &intersection);

	/** 	Update with commands
		Takes updates in the form of SceneCommands and
		turns them into something visualized in the scene
	*/
	void update(double t,std::vector<SceneCommand*> &commands);

	/** Return the root of the scene*/
	osg::ref_ptr<osg::Group> sceneRoot(){return _scene->getRoot();}

	/** Set the Head Matrix*/
	void set_head_matrix(osg::Matrix);


protected:
	
	/** iVars. */
	Builder* 					_builder;
	bool 						creationMode;
	std::vector<Cursor*> 				_cursor;
	osg::ref_ptr<osg::Node> 			_floor;
	Grid* 						_grid;
	float 						grid_block_size;
	int 						grid_size;
	osg::Matrix 					_head_matrix;
	osg::Matrix 					_wandMatrix;
	Physics* 					_physics;
	Scene*						_scene;
};

#endif /* defined(__VRBuilder__sceneMgr__) */
