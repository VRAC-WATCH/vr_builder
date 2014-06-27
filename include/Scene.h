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

//STD HEADERS
#include <vector>
using namespace std;

#include "SceneCommand.h"
#include "Builder.h"



/*
	This is the Scene class
	It will contain hooks to add and maybe remove nodes from the 
	scenegraph
	You can add models to the scene
	You can update the various navigation matrices
*/
class Scene{
    
	/** iVars*/
	osg::ref_ptr<osg::Group> _root;
	osg::ref_ptr<osg::MatrixTransform> _navigation_matrix;
	osg::ref_ptr<osg::MatrixTransform> _model_matrix;
	osg::ref_ptr<osg::LightSource> _lightsource;
	int projno;
	bool rebuilt;

public:
	/*Constructor  
		GridSize - Input the size of the grid (assumed square)
		e.g. if the grid is 20X20, GridSize = 20
	
	*/
	Scene();

	/** Destructor*/
	~Scene();

	/** Add a node into the scene
	    This is dumb addition (doesn't know what its adding, just does it)
	*/
	void add(osg::Node*);

	/** Removes all visible blocks from the scene. */
	void clear();

	/** Rebuild the scene (removes projectiles only)*/
	void rebuild();

	/** Mark the beginning of the physics mode so that we can remove any stray projectiles*/
	void physicsmode();

	/* Get the root of the scenegraph*/
	osg::Group* getRoot(){return _root;}

	/* Set the navigation matrix*/
	void set_navigation_matrix(osg::Matrix);

	/** Get the navigation matrix*/
	inline osg::Matrix get_navigation_matrix(){ return _navigation_matrix->getMatrix(); }
};
