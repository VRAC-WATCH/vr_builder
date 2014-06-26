/**
 *  Cursor.h
 *  VRBuilder
 *
 *  Created by Bhaskar Bhattacharya on 10/6/14.
 *  Copyright 2014 Iowa State University. All rights reserved.
 */


#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/io_utils>
#include <osg/Texture2D>
#include <osg/PositionAttitudeTransform>

//STD HEADERS
#include <vector>
using namespace std;

#define BLINK_SPEED 20

class Cursor{
	
	/** Cursor switch node - enables us to do blinking*/
	osg::ref_ptr<osg::Switch> _cursor;

	/** Cursor PAT to move it around*/
	osg::ref_ptr<osg::PositionAttitudeTransform> _cursorpat;
	int _gridsize;
	float _gridblocksize;

	/** How we blink:
		1. Set blink value to zero
		2. If blink is zero switch on the cursor
		3. If blink reaches BLINK_SPEED switch off the cursor and set blink to zero
		4. Increment blink every frame		
	*/
	int blink;

	/** Check to see whether the cursor is within bounds of the floor*/
	bool check_cursor_bounds(osg::Vec3 cursorposition);
public:
	/** Constructor with floor input information*/
	Cursor(osg::Node*,int gridsize = 20 ,float gridblocksize = 1.0f);
	
	/** Get the cursor switch*/
	osg::Node* getCursor(){ return _cursor; }

	/** Move the cursor according the predetermined definition*/
	void move(osg::Vec3 vectordirection,int gridheight = 0);
	
	/** Update the cursor [as of now only used for blinking]*/
	void update();

	/** Get cursor absolute position*/
	osg::Vec3 getCursorCurrentPosition(){ return _cursorpat->getPosition(); }
	
	/** Switch on the cursor*/
	void on();

	/** Switch off the cursor*/
	void off();
};
