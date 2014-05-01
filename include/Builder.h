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

//OSGBULLET Header
#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbCollision/Utils.h>

//BULLET Headers
#include <btBulletDynamicsCommon.h>

//STL Headers
#include <string>

struct blockproperty{
	osg::Vec3 pos;
};

class Builder{
private:
	//function to create the block within the physics world
	osg::MatrixTransform* makeBlock(blockproperty, btDynamicsWorld* bw );

	//Member variables
	btDynamicsWorld* bulletWorld; //The physics world
	osgbDynamics::MotionState* _motion; //State of the object
protected:
	//Constructor - not allow object creation
	Builder();
public:
	//Builder is a singleton
	static Builder& instance() { static Builder builder;  return builder; }

	//Initialization
	void init();
	//Create the floor
	osg::Node* createFloor( float w, float h, const osg::Vec3& center);
	//Create the block
	osg::Node* createBlock(osg::Vec3 pos);
	//Create a projectile
	//osg::Node* throwProjectile();
	//Update the simulation
	void update(double);
};

#endif	// End of BUILDER_H





