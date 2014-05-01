/*
 *  Builder.cpp
 *
 *	Created by Bhaskar Bhattacharya on 5/1/2014.
 *  Copyright 2014 Iowa State University. All rights reserved.
 *
 */

#include "Builder.h"

//function to create the Geode
osg::Geode* osgBox( const osg::Vec3& center, const osg::Vec3& halfLengths )
{
	osg::Vec3 l( halfLengths * 2. );
	osg::Box* box = new osg::Box( center, l.x(), l.y(), l.z() );
	osg::ShapeDrawable* shape = new osg::ShapeDrawable( box );
	shape->setColor( osg::Vec4( 1., 1., 1., 1. ) );
	osg::Geode* geode = new osg::Geode();
	geode->addDrawable( shape );
	return( geode );
}

//function to create the box
osg::Transform* createOSGBox( osg::Vec3 size )
{
    osg::Box* box = new osg::Box();
    box->setHalfLengths( size );

    osg::ShapeDrawable* shape = new osg::ShapeDrawable( box );
    shape->setColor( osg::Vec4( 1., 1., 1., 1. ) );
    osg::Geode* geode = new osg::Geode();
    geode->addDrawable( shape );

    osg::MatrixTransform* mt = new osg::MatrixTransform();
    mt->addChild( geode );

    return( mt );
}

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

Builder::Builder(){

}

void Builder::init(){
	bulletWorld = initPhysics();
}

osg::Node* Builder::createFloor( float w, float h, const osg::Vec3& center)
{

    osg::Transform* ground = createOSGBox( osg::Vec3( w, .05, h ) );

    osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
    cr->_sceneGraph = ground;
    cr->_shapeType = BOX_SHAPE_PROXYTYPE;
    cr->_mass = 0.f;
    btRigidBody* body = osgbDynamics::createRigidBody( cr.get(),
        osgbCollision::btBoxCollisionShapeFromOSG( ground ) );

    // Transform the box explicitly.
    osgbDynamics::MotionState* motion = static_cast< osgbDynamics::MotionState* >( body->getMotionState() );
    osg::Matrix m( osg::Matrix::translate( center ) );
    motion->setParentTransform( m );
    body->setWorldTransform( osgbCollision::asBtTransform( m ) );

    bulletWorld->addRigidBody( body );

    return( ground );
}

osg::MatrixTransform* Builder::makeBlock(blockproperty prop, btDynamicsWorld* bw )
{
	osg::MatrixTransform* root = new osg::MatrixTransform;
	const std::string fileName( "dice.osg" );
	osg::Node* node = osgDB::readNodeFile( fileName );
	if( node == NULL )
	{
		osg::notify( osg::FATAL ) << "Can't find \"" << fileName << "\". Make sure OSG_FILE_PATH includes the osgBullet data directory." << std::endl;
		exit( 0 );
	}
	root->addChild( node );

	btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG( node );

	osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
	cr->_sceneGraph = root;
	cr->_shapeType = BOX_SHAPE_PROXYTYPE;
	cr->_mass = 1.f;
	cr->_restitution = 1.f;
	btRigidBody* body = osgbDynamics::createRigidBody( cr.get(), cs );
	
	//Move block to correct position in the physics world
	osgbDynamics::MotionState* motion = static_cast< osgbDynamics::MotionState* >( body->getMotionState() );
    osg::Matrix m( osg::Matrix::translate( prop.pos ) );
    motion->setParentTransform( m );
    body->setWorldTransform( osgbCollision::asBtTransform( m ) );

	bw->addRigidBody( body );

	return( root );
}

osg::Node* Builder::createBlock(osg::Vec3 pos){ 
	blockproperty p;
	p.pos=pos;
	return makeBlock(p,bulletWorld);
}

//osg::Node* Builder::throwProjectile(){
//
//}

void Builder::update(double t){
	double elapsed(t);
	//if( viewer.getFrameStamp()->getFrameNumber() < 3 )
	//elapsed = 1./60.;
	//osg::notify( osg::ALWAYS ) << elapsed / 3. << ", " << 1./180. << std::endl;
	bulletWorld->stepSimulation( elapsed, 4, elapsed/4. );
}