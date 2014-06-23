//
//  sceneMgr.cpp
//  VRBuilder
//
//  Created by Frederick Thompson on 4/25/14.
//
//

// Local headers
#include "Scene.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	// Setup an initial grid of size 40x40
	grid_size = 20;
	grid_block_size = 1.0f;
	creationMode = true;

	_scene = new Scene();

	//Initialize Physics
	_physics = new Physics;
	//Initialize Builder
	Builder::instance().init();
	//Grid initialization
	_grid = new Grid(grid_size, grid_block_size);
	//Add floor from builder to physics world and scene world
	osg::Node* floor=Builder::instance().createFloor(grid_block_size*grid_size,grid_block_size*grid_size,osg::Vec3(0,0,0),grid_size,grid_block_size);
	_physics->add(floor,osg::Vec3(0,0,0),Physics::FLOOR);
	_scene->add(floor);
	//Cursor initialization with red
	Add_Block ab;
	ab.color = osg::Vec4(1,0,0,1);
	_cursor = new Cursor(Builder::instance().createBlock(ab),grid_size, grid_block_size);
	_scene->add(_cursor->getCursor());

	_head_matrix = new osg::Matrix;
}

SceneManager::~SceneManager()
{
	delete _scene;
	delete _physics;
	delete _grid;
	delete _cursor;
}

void SceneManager::update(double t,std::vector<SceneCommand*> &commands )
{
	//std::cout << "Updating: " << commands.size() << " elements" << std::endl;

	static Add_Block ab;
	static Mode_Change mc;
	static Move m;
	static Throw_Block tb;
	static Navigation nav;
	for(int i=0;i<commands.size();i++){		
		//Commands in common mode
		//Mode change
		if(!string(commands[i]->CommandType()).compare(mc.CommandType())){
			creationMode = !creationMode;
		}
		//Navigation
		if(!string(commands[i]->CommandType()).compare(nav.CommandType())){
			osg::Matrix current_nav = _scene->get_navigation_matrix();
			osg::Matrix nav_multiplier = dynamic_cast<Navigation*>(commands[i])->navMatrixMultiplier;
			_scene->set_navigation_matrix(current_nav * nav_multiplier);
		}
		//In Creation Mode
		if(creationMode){
			//Cursor Movements
			if(!string(commands[i]->CommandType()).compare(m.CommandType())){
				_cursor->move(dynamic_cast<Move*>(commands[i])->direction,0);//update the xz position
				_cursor->move(osg::Vec3(0,0,0),_grid->cursor_height(_cursor->getCursorCurrentPosition()));//update the y position
			}

			//Add Block
			if(!string(commands[i]->CommandType()).compare(ab.CommandType())){
				osg::Vec3 curr = _cursor->getCursorCurrentPosition();
				osg::Node* n = Builder::instance().createBlock(*dynamic_cast<Add_Block*>(commands[i]));
				_physics->add(n,curr);
				_scene->add(n);
				_grid->add(curr);
				_cursor->move(osg::Vec3(0,0,0),_grid->cursor_height(curr));//update the cursor y position
			}
		}
		//In Physics Mode
		else{
			if(!string(commands[i]->CommandType()).compare(tb.CommandType())){
				osg::ref_ptr<osg::Node> n = Builder::instance().createProjectile();
				//Trying to get Head Position Will have to fixed in Juggler version
				osg::Vec3 eye,center,up; 
				_head_matrix->getLookAt(eye,center,up);
				osg::Vec3 blah=_head_matrix->getTrans();
				eye.set(eye.x(),eye.y(),-eye.z());
				center.set(center.x(),center.y(),-center.z());
				osg::Vec3 dir = eye - center;
				dir.normalize();
				_physics->add_projectile(n,blah,dir*0.5);
				_scene->add(n);
			}
		}
		
	}
	if(creationMode){
		_cursor->update();
		_physics->rebuild();
		_scene->rebuild();
	}
	else{
		_cursor->off();
		_physics->update();
		_scene->physicsmode();
	}
}

void SceneManager::set_head_matrix(osg::Matrix m){
	*_head_matrix = m;
}
