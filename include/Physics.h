/**
 *  Physics.h
 *  VRBuilder
 *
 *  Created by Bhaskar Bhattacharya on 10/6/14.
 *  Copyright 2014 Iowa State University. All rights reserved.
 */

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



class Physics{
public:
	enum Type{FLOOR,BOX,BALL};

private:
	struct Physicselement{
		btRigidBody* ebody;
		osg::Vec3 epos;
		Type etype;
	};

	btDynamicsWorld* bulletWorld;
	vector<Physicselement> list;

	void setRigidBodyPosition(btRigidBody*& , osg::Vec3);
public:
	Physics();
	~Physics();
	void add(osg::Node*, osg::Vec3, Type type = BOX);
	void rebuild();
	void add_projectile(osg::Node*, osg::Vec3, osg::Vec3 );

	/** Clears all simulated box objects. */
	void clearBoxes();	

	void update();
};
