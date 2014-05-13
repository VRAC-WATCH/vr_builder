/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * osgBullet is (C) Copyright 2009-2012 by Kenneth Mark Bryden
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include "dice.h"


osg::MatrixTransform*
makeDie( btDynamicsWorld* bw )
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
	bw->addRigidBody( body );

	return( root );
}


btDynamicsWorld*
initPhysics()
{
	btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher * dispatcher = new btCollisionDispatcher( collisionConfiguration );
	btConstraintSolver * solver = new btSequentialImpulseConstraintSolver;

	btVector3 worldAabbMin( -10000, -10000, -10000 );
	btVector3 worldAabbMax( 10000, 10000, 10000 );
	btBroadphaseInterface * inter = new btAxisSweep3( worldAabbMin, worldAabbMax, 1000 );

	btDynamicsWorld * dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, inter, solver, collisionConfiguration );

	dynamicsWorld->setGravity( btVector3( 0, 9.8, 0 ) );

	return( dynamicsWorld );
}




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

Dice::Dice(){
		bulletWorld = initPhysics();
		root = new osg::PositionAttitudeTransform;

		root->addChild( makeDie( bulletWorld ) );
		root->addChild( makeDie( bulletWorld ) );


		/* BEGIN: Create environment boxes */
		float xDim( 10. );
		float yDim( 10. );
		float zDim( 6. );
		float thick( .1 );

		osg::MatrixTransform* shakeBox = new osg::MatrixTransform;
		btCompoundShape* cs = new btCompoundShape;
		{ // floor -Z (far back of the shake cube)
		osg::Vec3 halfLengths( xDim*.5, yDim*.5, thick*.5 );
		osg::Vec3 center( 0., 0., zDim*.5 );
		shakeBox->addChild( osgBox( center, halfLengths ) );
		btBoxShape* box = new btBoxShape( osgbCollision::asBtVector3( halfLengths ) );
		btTransform trans; trans.setIdentity();
		trans.setOrigin( osgbCollision::asBtVector3( center ) );
		cs->addChildShape( trans, box );
		}
		{ // top +Z (invisible, to allow user to see through; no OSG analogue
		osg::Vec3 halfLengths( xDim*.5, yDim*.5, thick*.5 );
		osg::Vec3 center( 0., 0., -zDim*.5 );
		//shakeBox->addChild( osgBox( center, halfLengths ) );
		btBoxShape* box = new btBoxShape( osgbCollision::asBtVector3( halfLengths ) );
		btTransform trans; trans.setIdentity();
		trans.setOrigin( osgbCollision::asBtVector3( center ) );
		cs->addChildShape( trans, box );
		}
		{ // left -X
		osg::Vec3 halfLengths( thick*.5, yDim*.5, zDim*.5 );
		osg::Vec3 center( -xDim*.5, 0., 0. );
		shakeBox->addChild( osgBox( center, halfLengths ) );
		btBoxShape* box = new btBoxShape( osgbCollision::asBtVector3( halfLengths ) );
		btTransform trans; trans.setIdentity();
		trans.setOrigin( osgbCollision::asBtVector3( center ) );
		cs->addChildShape( trans, box );
		}
		{ // right +X
		osg::Vec3 halfLengths( thick*.5, yDim*.5, zDim*.5 );
		osg::Vec3 center( xDim*.5, 0., 0. );
		shakeBox->addChild( osgBox( center, halfLengths ) );
		btBoxShape* box = new btBoxShape( osgbCollision::asBtVector3( halfLengths ) );
		btTransform trans; trans.setIdentity();
		trans.setOrigin( osgbCollision::asBtVector3( center ) );
		cs->addChildShape( trans, box );
		}
		{ // bottom of window -Y
		osg::Vec3 halfLengths( xDim*.5, thick*.5, zDim*.5 );
		osg::Vec3 center( 0., -yDim*.5, 0. );
		shakeBox->addChild( osgBox( center, halfLengths ) );
		btBoxShape* box = new btBoxShape( osgbCollision::asBtVector3( halfLengths ) );
		btTransform trans; trans.setIdentity();
		trans.setOrigin( osgbCollision::asBtVector3( center ) );
		cs->addChildShape( trans, box );
		}
		{ // bottom of window -Y
		osg::Vec3 halfLengths( xDim*.5, thick*.5, zDim*.5 );
		osg::Vec3 center( 0., yDim*.5, 0. );
		shakeBox->addChild( osgBox( center, halfLengths ) );
		btBoxShape* box = new btBoxShape( osgbCollision::asBtVector3( halfLengths ) );
		btTransform trans; trans.setIdentity();
		trans.setOrigin( osgbCollision::asBtVector3( center ) );
		cs->addChildShape( trans, box );
		}
		/* END: Create environment boxes */

		osgbDynamics::MotionState * shakeMotion = new osgbDynamics::MotionState();
		shakeMotion->setTransform( shakeBox );
		btScalar mass( 0.0 );
		btVector3 inertia( 0, 0, 0 );
		btRigidBody::btRigidBodyConstructionInfo rb( mass, shakeMotion, cs, inertia );
		btRigidBody* shakeBody = new btRigidBody( rb );
		shakeBody->setCollisionFlags( shakeBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT );
		shakeBody->setActivationState( DISABLE_DEACTIVATION );
		bulletWorld->addRigidBody( shakeBody );
		_motion=shakeMotion;

		root->addChild( shakeBox );
		prevSimTime = 0.;
		_lastX=_lastY=0;
/*
		osgViewer::Viewer viewer;
		viewer.setUpViewInWindow( 150, 150, 400, 400 );
		viewer.setSceneData( root );
		viewer.getCamera()->setViewMatrixAsLookAt(
		osg::Vec3( 0, 0, -20 ), osg::Vec3( 0, 0, 0 ), osg::Vec3( 0, 1, 0 ) );
		viewer.getCamera()->setProjectionMatrixAsPerspective( 40., 1., 1., 50. );
		viewer.addEventHandler( new ShakeManipulator( shakeMotion ) );

		viewer.realize();
		double prevSimTime = 0.;
		while( !viewer.done() )
		{
		
		viewer.frame();
		}
*/
}

void Dice::update(double t){

	double elapsed(t);
	//if( viewer.getFrameStamp()->getFrameNumber() < 3 )
	//elapsed = 1./60.;
	//osg::notify( osg::ALWAYS ) << elapsed / 3. << ", " << 1./180. << std::endl;
	bulletWorld->stepSimulation( elapsed, 4, elapsed/4. );
}

void Dice::buttonpress(int button){
	btVector3 move;
	if(button == 1){
		_lastX-=0.001;
		move[ 0 ] = -0.01;
		move[ 1 ] = _lastY;
		move[ 2 ] = 0.;
		move *= 10.;
		std::cout<<"Button1"<<std::endl;
	}
	
	if(button == 3){
		_lastX+=0.001;
		move[ 0 ] = 0.01;
		move[ 1 ] = _lastY;
		move[ 2 ] = 0.;
		move *= 10.;
		std::cout<<"Button3"<<std::endl;
	}
	btTransform moveTrans; moveTrans.setIdentity();
	moveTrans.setOrigin( move );
	btTransform world;
	_motion->getWorldTransform( world );
	btTransform netTrans = moveTrans * world;
	btVector3 o = netTrans.getOrigin();
	o[ 2 ] = 0.;
	netTrans.setOrigin( o );

	_motion->setWorldTransform( netTrans );

}

/** \page diceexample The Mandatory Dice Example
No physics-based project would be complete without a dice example. Use the
left mouse button to chake the dice shaker.
*/
