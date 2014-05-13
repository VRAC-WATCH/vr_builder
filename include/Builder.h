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

//OSGBULLET Header
#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbCollision/Utils.h>

//BULLET Headers
#include <btBulletDynamicsCommon.h>

//STL Headers
#include <string>

//Scene Command Header
#include <SceneCommand.h>

struct blockproperty{
	osg::Vec3 pos;
};

class Builder{
private:
	//Create the block
	osg::MatrixTransform* makeBlock(SceneCommand sc, btDynamicsWorld* bw );
	//Set the color of the block
	void setColor(osg::Node* &,osg::Vec4);
	//Set the texture of the block
	void setTexture(osg::Node* &,std::string);

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
	osg::Node* createBlock(SceneCommand sc);
	//Create a projectile
	osg::Node* throwProjectile(osg::Vec3,osg::Vec3);
	//Update the simulation
	void update(double);
};

#endif	// End of BUILDER_H





