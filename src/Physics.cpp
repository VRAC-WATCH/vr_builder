/**
 *  Physics.cpp
 *  VRBuilder
 *
 *  Created by Bhaskar Bhattacharya on 10/6/14.
 *  Copyright 2014 Iowa State University. All rights reserved.
 */
#include "Physics.h"

//Create the physics world
btDynamicsWorld* initPhysics()
{
	btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher * dispatcher = new btCollisionDispatcher( collisionConfiguration );
	btConstraintSolver * solver = new btSequentialImpulseConstraintSolver;

	btVector3 worldAabbMin( -10000, -10000, -10000 );
	btVector3 worldAabbMax( 10000, 10000, 10000 );
	btBroadphaseInterface * inter = new btAxisSweep3( worldAabbMin, worldAabbMax, 1000 );

	btDynamicsWorld * dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, inter, solver, collisionConfiguration );

	dynamicsWorld->setGravity( btVector3( 0, -9.8, 0 ) );

	return( dynamicsWorld );
}

Physics::Physics(){
	bulletWorld = initPhysics();
}

Physics::~Physics(){
	for(int i=0;i<list.size();i++){
		bulletWorld->removeRigidBody(list[i].ebody);
		delete list[i].ebody;
	}
	list.clear();
	delete bulletWorld;
}

void Physics::add(osg::Node* model, osg::Vec3 position, Type type){

	//Place in the Physics world
	btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG( model->asTransform()->getChild(0) );
	osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
	cr->_sceneGraph = model;
	cr->_shapeType = BOX_SHAPE_PROXYTYPE;
	cr->_restitution = 1.f;
	switch(type){
	case(FLOOR):
		cr->_mass = 0.0f;
		cr->_restitution = 0.3f;
		break;
	case(BOX):
		cr->_mass = 1.f;
		break;
	case(BALL):
		cr->_shapeType = SPHERE_SHAPE_PROXYTYPE;
		cr->_mass = 0.05f;
		break;
	}
		
	
	btRigidBody* body = osgbDynamics::createRigidBody( cr.get(), cs );
	//Move block to correct position in the physics world
	
	setRigidBodyPosition(body, position);
	bulletWorld->addRigidBody( body );

	//Keep a record of original positions and rigid bodies
	Physicselement e;
	e.ebody = body;
	e.epos = position;
	e.etype = type;
	list.push_back(e);
}

void Physics::add_projectile(osg::Node* n, osg::Vec3 p, osg::Vec3 impulse){

	add(n,p,BALL);
	list[list.size()-1].ebody->applyCentralImpulse(btVector3(impulse.x(),impulse.y(),impulse.z()));
}

void Physics::clearBoxes()
{
	std::vector<int> remove_elements;
	for(int i=0;i<list.size();i++){
		switch(list[i].etype){
			case(BOX):
				remove_elements.push_back(i);
				bulletWorld->removeRigidBody(list[i].ebody);
				delete list[i].ebody;
				list.erase(list.begin()+i);
				--i;
				break;
		}
	}
}

void Physics::rebuild(){
	for(int i=0;i<list.size();i++){
		switch(list[i].etype){
		case(BOX):
			setRigidBodyPosition(list[i].ebody,list[i].epos);
			break;
		case(BALL):
			bulletWorld->removeRigidBody(list[i].ebody);
			list.erase(list.begin()+i);
			i--;
			break;
		}
	}
}

void Physics::setRigidBodyPosition(btRigidBody*& body, osg::Vec3 pos){
	osgbDynamics::MotionState* motion = static_cast< osgbDynamics::MotionState* >( body->getMotionState() );
	osg::Matrix m( osg::Matrix::translate(pos) );
	motion->setParentTransform( m );
	body->setWorldTransform( osgbCollision::asBtTransform( m ) );
}

void Physics::update(){
	bulletWorld->stepSimulation(0.4);
}
