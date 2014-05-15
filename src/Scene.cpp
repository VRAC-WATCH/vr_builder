//
//  Scene.cpp
//  VRBuilder
//
//  Created by Bhaskar Bhattacharya on 5/13/14.
//
//

#include "Scene.h"

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

//function to create the box
osg::Transform* createOSGBox( osg::Vec3 size )
{
    osg::Box* box = new osg::Box();
    box->setHalfLengths( size/2 );

    osg::ShapeDrawable* shape = new osg::ShapeDrawable( box );
    shape->setColor( osg::Vec4( 1., 1., 1., 1. ) );
    osg::Geode* geode = new osg::Geode();
    geode->addDrawable( shape );

    osg::MatrixTransform* mt = new osg::MatrixTransform();
    mt->addChild( geode );

    return( mt );
}

Scene::Scene(int GridSize,float GridBlockSize){

	/*Initialize the scene graph*/
	_root = new osg::Group;
	_model_matrix = new osg::MatrixTransform;
	_cursor_switch = new osg::Switch;
	_cursor_matrix = new osg::MatrixTransform;
	_navigation_matrix = new osg::MatrixTransform;

	_root->addChild(_navigation_matrix);
	_navigation_matrix->addChild(_model_matrix);
	_navigation_matrix->addChild(_cursor_switch);
	_cursor_switch->addChild(_cursor_matrix);
	_cursor_switch->setAllChildrenOn();

	_root->getOrCreateStateSet()->setMode(GL_NORMALIZE, true);
	_lightsource = new osg::LightSource;
	_navigation_matrix->addChild(_lightsource.get());
	osg::Light* light = _lightsource->getLight();
	light->setDiffuse(osg::Vec4(0.7f, 0.7f, 0.7f, 1.0f));
	light->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAmbient(osg::Vec4(0.05f, 0.05f, 0.05f, 1.0f));
	light->setPosition(osg::Vec4(0.0f, 100.0f, 0.0f, 0.0f));

	/*Initialize the grid*/
	_gridsize = GridSize;
	_gridblocksize = GridBlockSize;
	_grid.resize(_gridsize);
	for(int i=0;i<_gridsize;i++)
		_grid[i].resize(_gridsize);

	//build physics world
	bulletWorld = initPhysics();
	//add floor with configuration
	_model_matrix->addChild(createFloor(_gridsize*_gridblocksize,_gridsize*_gridblocksize,osg::Vec3(0,0,0)));
	//osg::Node* n=drawGrid();
	//_model_matrix->addChild(n);

	//add red cursor
	set_cursor(createOSGBox(osg::Vec3(_gridblocksize,_gridblocksize,_gridblocksize)));
	set_cursor_position(osg::Matrix::translate(0,double(_gridblocksize)/2,0));
	blink=0;
	
	//default gamemode
	_gamemode = SceneCommand::CREATION;

	Builder::instance().init();
}

Scene::~Scene()
{
	std::cout << "Scene destructor called" << std::endl;
}

void Scene::set_navigation_matrix(osg::Matrix mat){
	_navigation_matrix->setMatrix(mat);
}

void Scene::set_cursor(osg::Node* node){
	osg::ShapeDrawable* shape= dynamic_cast<osg::ShapeDrawable*>(node->asTransform()->getChild(0)->asGeode()->getDrawable(0));
	shape->setColor(osg::Vec4(1,0,0,1));
	_cursor_matrix->addChild(node);
}

void Scene::set_cursor_position(osg::Matrix pos){

	_cursor_matrix->setMatrix(pos);
}

int Scene::add_model_node(SceneCommand cmd){

	//Get the current cursor position
	cmd.position=_cursor_matrix->getMatrix().getTrans();
	//Add to grid
	int gridx=(cmd.position.x()/_gridblocksize)+_gridsize/2;
	int gridy=(cmd.position.z()/_gridblocksize)+_gridsize/2;
	_grid[gridx][gridy].push_back(cmd);
	//Create the block
	osg::Node* model = Builder::instance().createBlock(cmd);
	model->asTransform()->asMatrixTransform()->setMatrix(osg::Matrix::translate(cmd.position));
	//Place in the Physics world
	btCollisionShape* cs = osgbCollision::btBoxCollisionShapeFromOSG( model );

	osg::ref_ptr< osgbDynamics::CreationRecord > cr = new osgbDynamics::CreationRecord;
	cr->_sceneGraph = model;
	cr->_shapeType = BOX_SHAPE_PROXYTYPE;
	cr->_mass = 1.f;
	cr->_restitution = 1.f;
	btRigidBody* body = osgbDynamics::createRigidBody( cr.get(), cs );
	
	//Move block to correct position in the physics world
	osgbDynamics::MotionState* motion = static_cast< osgbDynamics::MotionState* >( body->getMotionState() );
	osg::Matrix m(osg::Matrix::translate(cmd.position) );
	motion->setParentTransform( m );
	body->setWorldTransform( osgbCollision::asBtTransform( m ) );

	bulletWorld->addRigidBody( body );
	_model_matrix->addChild(model);

	return 1;
}

void Scene::remove_model_node(int id){

}

void Scene::check_cursor_position(){
	//Get the current cursor position
	osg::Vec3 position=_cursor_matrix->getMatrix().getTrans();
	//Add to grid
	int gridx=(position.x()/_gridblocksize)+_gridsize/2;
	int gridy=(position.z()/_gridblocksize)+_gridsize/2;

	position.set(osg::Vec3(position.x(),
		double(_grid[gridx][gridy].size())*_gridblocksize + double(_gridblocksize)/2,
		position.z()));

	_cursor_matrix->setMatrix(osg::Matrix::translate(position));

	//cout<<"Cursor position"<<position.x()<<" "<<position.y()<<" "<<position.z()<<endl;
}

void Scene::update(double t){
	double elapsed(t);
	if(_gamemode == SceneCommand::PHYSICS)
		bulletWorld->stepSimulation( elapsed, 4, elapsed/4. );

	//Make the cursor blink - mini hack 
	if(blink==0){
		_cursor_switch->setAllChildrenOn();
	}
	if(blink==BLINK_SPEED){
		_cursor_switch->setAllChildrenOff();
		blink=-BLINK_SPEED;
	}
	blink++;
	
	check_cursor_position();
}

bool Scene::check_cursor_bounds(osg::Vec3 trans){
	if(trans.x() <= -_gridsize/2*_gridblocksize ||
		trans.z() <= -_gridsize/2*_gridblocksize ||
		trans.x() >= _gridsize/2*_gridblocksize ||
		trans.z() >= _gridsize/2*_gridblocksize)
		return false;
	return true;
}
void Scene::movecursor_left(){
	osg::Vec3d trans=_cursor_matrix->getMatrix().getTrans();
	trans.set(trans.x()-_gridblocksize,trans.y(),trans.z());
	if(check_cursor_bounds(trans))
		_cursor_matrix->setMatrix(osg::Matrix::translate(trans));
}

void Scene::movecursor_right(){
	osg::Vec3d trans=_cursor_matrix->getMatrix().getTrans();
	trans.set(trans.x()+_gridblocksize,trans.y(),trans.z());
	if(check_cursor_bounds(trans))
		_cursor_matrix->setMatrix(osg::Matrix::translate(trans));
}

void Scene::movecursor_up(){
	osg::Vec3d trans=_cursor_matrix->getMatrix().getTrans();
	trans.set(trans.x(),trans.y(),trans.z()-_gridblocksize);
	if(check_cursor_bounds(trans))
		_cursor_matrix->setMatrix(osg::Matrix::translate(trans));
}

void Scene::movecursor_down(){
	osg::Vec3d trans=_cursor_matrix->getMatrix().getTrans();
	trans.set(trans.x(),trans.y(),trans.z()+_gridblocksize);
	if(check_cursor_bounds(trans))
		_cursor_matrix->setMatrix(osg::Matrix::translate(trans));
}

osg::Node* Scene::createFloor( float w, float h, const osg::Vec3& center)
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

	//Draw Grid lines
	osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array;
	osg::ref_ptr<osg::Geometry> lines =  new osg::Geometry; 
	int count=0;
	for(double i=-_gridsize/2*_gridblocksize;i<_gridsize/2*_gridblocksize;i+=_gridblocksize,count+=2){
		osg::Vec3 sp(i,0.05,-_gridsize/2*_gridblocksize); 
		osg::Vec3 ep(i+_gridblocksize,0.05,_gridsize/2*_gridblocksize);
		points->push_back(sp);
		points->push_back(ep);
		osg::DrawElementsUInt* line =  new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
		line->push_back(count);
		line->push_back(count+1);
		lines->addPrimitiveSet(line);
	}
	for(double i=-_gridsize/2*_gridblocksize;i<_gridsize/2*_gridblocksize;i+=_gridblocksize,count+=2){
		osg::Vec3 sp(-_gridsize/2*_gridblocksize,0.05,i); 
		osg::Vec3 ep(_gridsize/2*_gridblocksize,0.05,i+_gridblocksize);
		points->push_back(sp);
		points->push_back(ep);
		osg::DrawElementsUInt* line =  new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
		line->push_back(count);
		line->push_back(count+1);
		lines->addPrimitiveSet(line);
	}
	
	osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array; 
	color->push_back(osg::Vec4(1.0,0.0,0.0,1.0)); 
	lines->setVertexArray(points); 
	lines->setColorArray(color); 
	lines->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f,1.0f,0.0f));
	lines->setNormalArray(normals);
	lines->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(lines);

	ground->addChild(geode);

    return( ground );
}

void Scene::changemode(){
	if(_gamemode == SceneCommand::CREATION)
		_gamemode = SceneCommand::PHYSICS;
	else{
		_gamemode = SceneCommand::CREATION;
	}
}

osg::Node* Scene::throwProjectile(osg::Vec3 impulse){
	
	osg::ref_ptr<osg::MatrixTransform> root(_navigation_matrix);
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
	motion->setParentTransform(root->getMatrix());
	body->setWorldTransform( osgbCollision::asBtTransform(root->getMatrix()));

	bulletWorld->addRigidBody( body );
	body->applyCentralImpulse(btVector3(impulse.x(),impulse.y(),impulse.z()));
    return( root );
}