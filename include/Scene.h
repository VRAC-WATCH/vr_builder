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

	int _gridsize;
	int** _grid;
public:
	/*Constructor  
		GridSize - Input the size of the grid (assumed square)
		e.g. if the grid is 20X20, GridSize = 20
	
	*/
    Scene(int GridSize);

	/* Destructor */
	~Scene();

	/* Get the root of the scenegraph*/
	osg::Group* getRoot(){return _root;}

	/* Set and get the navigation matrix*/
	void set_navigation_matrix(osg::Matrix);
	osg::Matrix get_navigation_matrix(){_navigation_matrix->getMatrix();}

	/* Setup the cursor*/
	void set_cursor(osg::Node*);
	/*Move the cursor*/
	void set_cursor_position(osg::Matrix);

	/*Add model node
	
		model - Input is the regular model
		
		Output - As of now returns 1 
		Future Work -  it will provide a node id which later can be used to remove the ids etc.

	*/
	int add_model_node(osg::Node* model);

	/*Remove the model node based on id - does nothing now*/
	void remove_model_node(int);

	/*Update the scene
	
		In the future we will move the physics world from Builder to here so there is consistency
		Other features such as blinking cursor can be added later here.

	*/
	void update(double);
    
};
