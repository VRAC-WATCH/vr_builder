/*
 *  Builder.h
 *
 *	Created by Bhaskar Bhattacharya on 5/1/2014.
 *  Copyright 2014 Iowa State University. All rights reserved.
 *
 * This is a static class for creating building blocks
 *
 */


#ifndef BUILDER_H
#define BUILDER_H

//OSG Headers
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/io_utils>
#include <osg/Texture2D>

//STL Headers
#include <string>

//Scene Command Header
#include <SceneCommand.h>
/**
 * The Builder class is used to create each individual 
 * scenegraph node
 */


class Builder{
private:
	/** Makes the block node*/
	osg::MatrixTransform* makeBlock(Add_Block sc);
	
	/** Sets color of the node otherwise default green color is used*/
	void setColor(osg::Node* &node,osg::Vec4 color);

	/** Texture is applied if it doesnt exist then default color is applied*/
	void setTexture(osg::Node* &node,std::string textureFile);

protected:
	/** Constructor*/
	Builder();
public:
	/** Singletone Instance*/
	static Builder& instance() { static Builder builder;  return builder; }

	/**Initialization (doesn't do anything now)*/
	void init();

	/** Creates the block with any additional properties*/
	osg::Node* createBlock(Add_Block block);


	/** Create the sphere for each projectile*/
	osg::Node* createProjectile();


	/** Create the Floor node*/
	osg::Node* createFloor( float width, float height, const osg::Vec3& center, int _gridsize, float _gridblocksize);
};

#endif	// End of BUILDER_H





