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

void Builder::setColor(osg::Node*& node,osg::Vec4 color=osg::Vec4(1,1,1,1)){
	osg::ShapeDrawable* shape= dynamic_cast<osg::ShapeDrawable*>(node->asTransform()->getChild(0)->asGeode()->getDrawable(0));
	shape->setColor(color);
}

void Builder::setTexture(osg::Node*& node, std::string textureFileName=""){
	if(textureFileName.length()==0)
		return;
	//Check for valid texture and load it
	osg::Texture2D* texture = new osg::Texture2D;
	texture->setDataVariance(osg::Object::DYNAMIC); 
	osg::Image* image = osgDB::readImageFile(textureFileName);
	if (!image)
	{
		std::cout << " couldn't find texture setting default color" << std::endl;
		setColor(node);
		return;
	}
	texture->setImage(image);

	osg::StateSet* ss=node->asTransform()->getChild(0)->asGeode()->getOrCreateStateSet();
	ss->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
	node->asTransform()->getChild(0)->asGeode()->setStateSet(ss);
	return;
}
osg::MatrixTransform* Builder::makeBlock(SceneCommand sc, btDynamicsWorld* bw )
{
	osg::MatrixTransform* root = new osg::MatrixTransform;
	const std::string fileName( "dice.osg" );
	osg::Node* node = createOSGBox(sc.blockSize);
	if( node == NULL )
	{
		osg::notify( osg::FATAL ) << "Can't find \"" << fileName << "\". Make sure OSG_FILE_PATH includes the osgBullet data directory." << std::endl;
		exit( 0 );
	}
	setColor(node,sc.color);
	setTexture(node,sc.textureFileName);
	root->addChild( node );

	//Place in the Physics world
	if(sc.commandType==SceneCommand::ADD_BLOCK){
		btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG( node );

		osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
		cr->_sceneGraph = root;
		cr->_shapeType = BOX_SHAPE_PROXYTYPE;
		cr->_mass = 1.f;
		cr->_restitution = 1.f;
		btRigidBody* body = osgbDynamics::createRigidBody( cr.get(), cs );
	
		//Move block to correct position in the physics world
		osgbDynamics::MotionState* motion = static_cast< osgbDynamics::MotionState* >( body->getMotionState() );
		osg::Matrix m( osg::Matrix::translate( sc.position ) );
		motion->setParentTransform( m );
		body->setWorldTransform( osgbCollision::asBtTransform( m ) );

		bw->addRigidBody( body );
	}
	return( root );
}

osg::Node* Builder::createBlock(SceneCommand sc){ 
	/*blockproperty p;
	p.pos=sc.position;
	switch(sc.command){
	case(SceneCommand::CommandType::ADD_BLOCK):
		return makeBlock(sc,bulletWorld);
		break;
	case(SceneCommand::CommandType::TRANSPARENT_BLOCK):
		return ;
		break;
	}*/
	return makeBlock(sc,bulletWorld);
	//return NULL;
}

osg::Node* Builder::throwProjectile(osg::Vec3 initialposition, osg::Vec3 impulse){
	osg::MatrixTransform* root = new osg::MatrixTransform;
	osg::Sphere* ball = new osg::Sphere();
    ball->setRadius(0.1);

    osg::ShapeDrawable* shape = new osg::ShapeDrawable( ball );
    shape->setColor( osg::Vec4( 1., 1., 1., 1. ) );
    osg::Geode* geode = new osg::Geode();
    geode->addDrawable( shape );

    osg::MatrixTransform* mt = new osg::MatrixTransform();
    mt->addChild( geode );
	root->addChild(mt);

	btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG( mt );

	osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
	cr->_sceneGraph = root;
	cr->_shapeType = SPHERE_SHAPE_PROXYTYPE;
	cr->_mass = 0.01f;
	cr->_restitution = 1.f;
	btRigidBody* body = osgbDynamics::createRigidBody( cr.get(), cs );
	
	//Move block to correct position in the physics world
	osgbDynamics::MotionState* motion = static_cast< osgbDynamics::MotionState* >( body->getMotionState() );
	osg::Matrix m( osg::Matrix::translate( initialposition ) );
	motion->setParentTransform( m );
	body->setWorldTransform( osgbCollision::asBtTransform( m ) );

	bulletWorld->addRigidBody( body );
	body->applyCentralImpulse(btVector3(impulse.x(),impulse.y(),impulse.z()));
    return( root );
}

void Builder::update(double t){
	double elapsed(t);
	//if( viewer.getFrameStamp()->getFrameNumber() < 3 )
	//elapsed = 1./60.;
	//osg::notify( osg::ALWAYS ) << elapsed / 3. << ", " << 1./180. << std::endl;
	bulletWorld->stepSimulation( elapsed, 4, elapsed/4. );
}
