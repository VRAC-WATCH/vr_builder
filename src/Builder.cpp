/*
 *  Builder.cpp
 *
 *	Created by Bhaskar Bhattacharya on 5/1/2014.
 *  Copyright 2014 Iowa State University. All rights reserved.
 *
 */

#include "Builder.h"

//function to create the Geode
osg::Transform* osgBox( osg::Vec3 blocksize )
{
	osg::Box* box = new osg::Box(osg::Vec3(0,0,0), blocksize.x(),blocksize.y(),blocksize.z() );
	osg::ShapeDrawable* shape = new osg::ShapeDrawable( box );
	shape->setColor( osg::Vec4( 1., 1., 1., 1. ) );
	osg::Geode* geode = new osg::Geode();
	geode->addDrawable( shape );
	osg::MatrixTransform* mt = new osg::MatrixTransform();
    mt->addChild( geode );

    return( mt );
}

Builder::Builder(){

}

void Builder::init(){

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
osg::MatrixTransform* Builder::makeBlock(SceneCommand sc)
{
	osg::MatrixTransform* root = new osg::MatrixTransform;
	osg::Node* node = osgBox(osg::Vec3(1,1,1));
	if( node == NULL )
	{
		osg::notify( osg::FATAL ) << "Node generation failed" << std::endl;
		exit( 0 );
	}
	setColor(node,sc.color);
	setTexture(node,sc.textureFileName);
	root->addChild( node );
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
	return makeBlock(sc);
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

	//btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG( mt );

	//osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
	//cr->_sceneGraph = root;
	//cr->_shapeType = SPHERE_SHAPE_PROXYTYPE;
	//cr->_mass = 0.01f;
	//cr->_restitution = 1.f;
	//btRigidBody* body = osgbDynamics::createRigidBody( cr.get(), cs );
	//
	////Move block to correct position in the physics world
	//osgbDynamics::MotionState* motion = static_cast< osgbDynamics::MotionState* >( body->getMotionState() );
	//osg::Matrix m( osg::Matrix::translate( initialposition ) );
	//motion->setParentTransform( m );
	//body->setWorldTransform( osgbCollision::asBtTransform( m ) );

	//bulletWorld->addRigidBody( body );
	//body->applyCentralImpulse(btVector3(impulse.x(),impulse.y(),impulse.z()));
    return( root );
}
