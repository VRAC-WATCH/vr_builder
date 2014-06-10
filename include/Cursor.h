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
	osg::ref_ptr<osg::Switch> _cursor;
	osg::ref_ptr<osg::PositionAttitudeTransform> _cursorpat;
	int _gridsize;
	float _gridblocksize;
	int blink;

	bool check_cursor_bounds(osg::Vec3 trans);
public:
	Cursor(osg::Node*,int gridsize = 20 ,float gridblocksize = 1.0f);
	osg::Node* getCursor(){ return _cursor; }
	void move(osg::Vec3,int gridheight = 0);
	void update();

	osg::Vec3 getCursorCurrentPosition(){ return _cursorpat->getPosition(); }

	void on();
	void off();
};