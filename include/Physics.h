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
	/** Enum to ID the different types of nodes
	    Note that: Properties of each node changes accordingly
	*/
	enum Type{FLOOR,BOX,BALL};

private:

	/** Physics element structure to keep track of all that we pass to the Physics World*/
	struct Physicselement{
		btRigidBody* ebody;
		osg::Vec3 epos;
		Type etype;
	};

	/** The Physics World*/
	btDynamicsWorld* bulletWorld;

	/** List of Physics elements*/
	vector<Physicselement> list;

	/** Set the Position of the body*/
	void setRigidBodyPosition(btRigidBody*& rBody, osg::Vec3 position);
public:
	
	/** Constructor*/
	Physics();

	/** Destructor*/
	~Physics();

	/** Add a node to the Physics World of a certain type and positon*/
	void add(osg::Node* node, osg::Vec3 position, Type type = BOX);

	/** Rebuild the Physics scene as it was in the Creation Mode*/
	void rebuild();

	/** Add a projectile in the Physics world from a certain point 
	    with a certain Impulse
	*/
	void add_projectile(osg::Node* node, osg::Vec3 startPosition, osg::Vec3 directionImpulse);

	/** Clears all simulated box objects. */
	void clearBoxes();	

	/** Update the Physics World (Simulation of physics begins)*/
	void update();
};
