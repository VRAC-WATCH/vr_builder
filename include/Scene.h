//
//  Scene.h
//  VRBuilder
//
//  Created by Bhaskar Bhattacharya on 5/13/14.
//
//
#pragma once

#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/io_utils>
#include <osg/Texture2D>

//OSGBULLET Header
#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbCollision/Utils.h>

//BULLET Headers
#include <btBulletDynamicsCommon.h>

//STD HEADERS
#include <vector>
using namespace std;

#include "SceneCommand.h"
#include "Builder.h"

#define BLINK_SPEED 20

/*
	This is the Scene class
	It will contain hooks to add and maybe remove nodes from the 
	scenegraph
	You can add models to the scene
	You can update the various navigation matrices
*/
class Scene{
    //private members
    osg::ref_ptr<osg::Group> _root;
	osg::ref_ptr<osg::MatrixTransform> _navigation_matrix;
	osg::ref_ptr<osg::MatrixTransform> _model_matrix;
	osg::ref_ptr<osg::MatrixTransform> _cursor_matrix;
	osg::ref_ptr<osg::Switch> _cursor_switch;
	osg::ref_ptr<osg::LightSource> _lightsource;

	int _gridsize,_gridblocksize;
	vector<vector<vector<SceneCommand> > > _grid;

	SceneCommand::GameMode _gamemode;

	btDynamicsWorld* bulletWorld; //The physics world
	osgbDynamics::MotionState* _motion; //State of the object

	/* Make cursor blink using this parameter*/
	int blink;
	//private functions
	/*Create the floor with grid lines*/
	osg::Node* createFloor( float w, float h, const osg::Vec3& center);
	/* Setup the cursor*/
	void set_cursor(osg::Node*);
	
	/*Move the cursor*/
	void set_cursor_position(osg::Matrix);

	/*Check cursor position according to the grid*/
	void check_cursor_position();
	/*Check cursor bounds*/
	bool check_cursor_bounds(osg::Vec3);
	/*Throw projectiles*/
	osg::Node* throwProjectile(osg::Vec3 initialposition, osg::Vec3 impulse);
	/*Remake the whole scene as before*/
	void remake_scene();
public:
	/*Constructor  
		GridSize - Input the size of the grid (assumed square)
		e.g. if the grid is 20X20, GridSize = 20
	
	*/
    Scene(int GridSize,float GridBlockSize);

	/* Destructor */
	~Scene();

	/* Get the root of the scenegraph*/
	osg::Group* getRoot(){return _root;}

	/* Set and get the navigation matrix*/
	void set_navigation_matrix(osg::Matrix);
	osg::Matrix get_navigation_matrix(){_navigation_matrix->getMatrix();}

	/*Add model node
	
		model - Input is the regular model
		
		Output - As of now returns 1 
		Future Work -  it will provide a node id which later can be used to remove the ids etc.

	*/
	int add_model_node(SceneCommand sc,bool remake);

	/*Remove the model node based on id - does nothing now*/
	void remove_model_node(int);

	/*Update the scene
	
		In the future we will move the physics world from Builder to here so there is consistency
		Other features such as blinking cursor can be added later here.

	*/
	void update(double);

	/* Move the cursor*/
	void movecursor_left();
	void movecursor_right();
	void movecursor_up();
	void movecursor_down();

	/*Change the mode*/
	void changemode();

	/*Throw the projectile*/
	void projectile_throw(osg::Vec3 initialposition,osg::Vec3 impulse);
};
