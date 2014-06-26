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

#define PRINTVECTOR(v) cout<<v.x()<<" "<<v.y()<<" "<<v.z()<<endl;

SceneManager::SceneManager()
{
	// Setup an initial grid of size 40x40
	grid_size = 300;
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
	_floor = Builder::instance().createFloor(grid_block_size*grid_size,grid_block_size*grid_size,osg::Vec3(0,0,0),grid_size,grid_block_size);
	_physics->add(_floor,osg::Vec3(0,0,0),Physics::FLOOR);
	_scene->add(_floor);
	
	//Cursor initialization with red
	Add_Block ab;
	ab.color = osg::Vec4(1.0,1.0,1.0,0.5);
	_cursor = new Cursor(Builder::instance().createBlock(ab),grid_size, grid_block_size);
	_scene->add(_cursor->getCursor());

	//_head_matrix = osg::Matrix();
}

SceneManager::~SceneManager()
{
	delete _cursor;
	delete _grid;
	delete _physics;
	delete _scene;
}

void SceneManager::clearScene()
{
	// Clear and repopulate the scene
	_scene->clear();
	_scene->add(_floor);
	_scene->add(_cursor->getCursor());
	_cursor->move(osg::Vec3(0,0,0), 0);

	_grid->reset();
	_physics->clearBoxes();
}

osg::Vec3 SceneManager::computeGridIntersection(osg::Matrix mat)
{
	// Get the direction pointing
    osg::Vec3 direction(mat.ptr()[8], mat.ptr()[9], mat.ptr()[10]);
    
    // Grab the position
    osg::Vec3d start_pos(mat.ptr()[12], mat.ptr()[13],mat.ptr()[14]);

    // Approximate the end position using the direction pointing
    float line_length = 1.0;
    osg::Vec3d end_pos = start_pos + direction * line_length;


	// Create the line segment shooting out to intersect the grid
    osg::ref_ptr<osg::LineSegment> intersector = new osg::LineSegment(start_pos, end_pos);
    
    // Continue to increase the segment length until it runs entirely through the grid
	float grid_world_size = grid_size * grid_block_size;
	osg::BoundingBox bounding_box(-grid_world_size/2.0,-0.005,-grid_world_size/2.0,
									grid_world_size/2.0,0.005,grid_world_size/2.0);
	float r1, r2;
    while (!intersector->intersect(bounding_box, r1, r2))
    {
		//std::cout << "Intersecting" << std::endl;
        if(line_length > grid_world_size * 10)
		{
			//std::cout << "never found one" << std::endl;
            break;
		}
        end_pos = end_pos + direction * (-line_length);
        intersector->set(start_pos, end_pos);
        line_length *= 2.0;
    }

	if (!intersector->intersect(bounding_box))
		std::cout << "Never intersected" << std::endl;
	else
		std::cout << "R1: " << r1 << std::endl;

	osg::Vec3 intersection = start_pos + (end_pos-start_pos)  * r1;

	return intersection;
}

void SceneManager::update(double t,std::vector<SceneCommand*> &commands )
{
	//std::cout << "Updating: " << commands.size() << " elements" << std::endl;

	static Add_Block ab;
	static ClearSceneCommand clear_scene_cmd;
	static HeadTrackChangeCommand head_track_cmd;
	static Mode_Change mc;
	static Move m;
	static Navigation nav;
	static Throw_Block tb;
	if(commands.size())
		cout<<"CSIZE "<<commands.size()<<endl;
	static WandTrackChangeCommand wand_track_cmd;
	for(int i=0;i<commands.size();i++){		
		
		//Commands in common mode
		
		// Head tracking change
		if(!string(commands[i]->CommandType()).compare(head_track_cmd.CommandType())){
			osg::Matrix temp = _scene->get_navigation_matrix();
			temp.invert(temp);
			osg::Vec3 eye,center,up;
			temp.getLookAt(eye,center,up);
			PRINTVECTOR(eye);
			PRINTVECTOR(center);
			PRINTVECTOR(up);
			_head_matrix = dynamic_cast<HeadTrackChangeCommand*>(commands[i])->headMatrix * temp;			
		}

		// Wand tracking change
		if(!string(commands[i]->CommandType()).compare(wand_track_cmd.CommandType())){
			osg::Matrix nav_mat = _scene->get_navigation_matrix();
			nav_mat.invert(nav_mat);
			std::cout << "Updating wand" << std::endl;			
			_wandMatrix = dynamic_cast<WandTrackChangeCommand*>(commands[i])->wandMatrix * nav_mat;
		}

		//Mode change
		if(!string(commands[i]->CommandType()).compare(mc.CommandType())){
			std::cout << "SceneManager - Changing interaction mode" << std::endl;
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

			// Clear scene
			if(!string(commands[i]->CommandType()).compare(clear_scene_cmd.CommandType())){
				std::cout << "SceneManager - Clearing scene" << std::endl;
				clearScene();
			}
			
			// d-Pad Cursor Movements
			if(!string(commands[i]->CommandType()).compare(m.CommandType())){
				//std::cout << "SceneManager - Moving cursor" << std::endl;
				_cursor->move(dynamic_cast<Move*>(commands[i])->direction,0);//update the xz position
				_cursor->move(osg::Vec3(0,0,0),_grid->cursor_height(_cursor->getCursorCurrentPosition()));//update the y position
			}
			
			// Wand cursor movements
			if(!string(commands[i]->CommandType()).compare(wand_track_cmd.CommandType())){
				// Set the position of the cursor using the intersection point
				osg::Vec3 intersection_point = computeGridIntersection(_wandMatrix);
				osg::Vec3 grid_point = _grid->computeNearestGridPoint(intersection_point);
				//std::cout << "x: " << intersection_point.x() << " z: " << intersection_point.z() << std::endl;
				//PRINTVECTOR(intersection_point);
				_cursor->setPosition(grid_point);
			}

			//Add Block
			if(!string(commands[i]->CommandType()).compare(ab.CommandType())){
				//std::cout << "SceneManager - Adding block" << std::endl;
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
				//std::cout << "SceneManager - Throwing projectile" << std::endl;
				osg::ref_ptr<osg::Node> n = Builder::instance().createProjectile();

				//Trying to get Head Position Will have to fixed in Juggler version
				osg::Vec3 eye,center,up; 
				_head_matrix.getLookAt(eye,center,up);
				osg::Vec3 head=_head_matrix.getTrans();
				eye.set(eye.x(),eye.y(),-eye.z());
				center.set(center.x(),center.y(),-center.z());
				//PRINTVECTOR(eye);
				//PRINTVECTOR(center);
				osg::Vec3 dir = eye - center;
				dir.normalize();
				_physics->add_projectile(n,center,dir*0.5);
				_scene->add(n);
			}
		}

		// Clean up the command
		delete commands[i];		
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
	_head_matrix = m;
}
