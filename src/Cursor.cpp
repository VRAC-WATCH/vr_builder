/**
 *  Cursor.cpp
 *  VRBuilder
 *
 *  Created by Bhaskar Bhattacharya on 10/6/14.
 *  Copyright 2014 Iowa State University. All rights reserved.
 */

#include "Cursor.h"

Cursor::Cursor(osg::Node* n,int gridsize,float gridblocksize){
	_cursor = new osg::Switch;
	_cursorpat = new osg::PositionAttitudeTransform;
	_cursor->addChild(_cursorpat);
	_cursorpat->addChild(n);

	_gridsize = gridsize;
	_gridblocksize = gridblocksize;
	blink=0;
	move(osg::Vec3(_gridblocksize/2.0,0,_gridblocksize/2.0));
}

bool Cursor::check_cursor_bounds(osg::Vec3 trans){
	if(trans.x() <= -(_gridsize+1)/2*_gridblocksize ||
		trans.z() <= -(_gridsize+1)/2*_gridblocksize ||
		trans.x() >= (_gridsize+1)/2*_gridblocksize ||
		trans.z() >= (_gridsize+1)/2*_gridblocksize)
		return false;
	return true;
}

void Cursor::move(osg::Vec3 direction,int gridheight){
	osg::Vec3d trans=_cursorpat->getPosition();
	trans.set(trans.x()+direction.x()*_gridblocksize,
		double(gridheight)*_gridblocksize + double(_gridblocksize)/2,
		trans.z()+direction.z()*_gridblocksize);
	if(check_cursor_bounds(trans))
		_cursorpat->setPosition(trans);
}

void Cursor::update(){

	if(blink==0){
		on();
	}
	if(blink==BLINK_SPEED){
		off();
		blink=-BLINK_SPEED;
	}
	blink++;
}

void Cursor::on(){
	_cursor->setAllChildrenOn();
}

void Cursor::off(){
	_cursor->setAllChildrenOff();
}
