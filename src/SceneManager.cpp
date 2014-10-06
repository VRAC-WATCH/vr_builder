//
//  sceneMgr.cpp
//  VRBuilder
//
//  Created by Frederick Thompson on 4/25/14.
//
//

// OSG headers
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/IntersectVisitor>

// Local headers
#include "Scene.h"
#include "SceneManager.h"

#define PRINTVECTOR(v) cout<<v.x()<<" "<<v.y()<<" "<<v.z()<<endl;

SceneManager::SceneManager(int cursors)
{
	std::cout<<"Scene Manager constructor begin"<<std::endl;
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
	
	//Cursor initialization
	for(int i=0;i<cursors;i++){
		double c1 = ((double) rand() / (RAND_MAX));
		double c2 = ((double) rand() / (RAND_MAX));
		double c3 = ((double) rand() / (RAND_MAX));
		Add_Block ab;
		ab.color = osg::Vec4(c1,c2,c3,0.5);
		_cursor.push_back(new Cursor(Builder::instance().createBlock(ab),grid_size, grid_block_size));
		_scene->add(_cursor[i]->getCursor());
	}
	//_head_matrix = osg::Matrix();

	std::cout<<"No of cursors "<<cursors<<std::endl;
	std::cout<<"Scene Manager constructor end"<<std::endl;
}

SceneManager::~SceneManager()
{
	for(int i=0;i<_cursor.size();i++)		
		delete _cursor[i];
	_cursor.clear();
	delete _grid;
	delete _physics;
	delete _scene;
}

void SceneManager::clearScene()
{
	// Clear and repopulate the scene
	_scene->clear();
	_scene->add(_floor);
	for(int i=0;i<_cursor.size();i++){		
		_scene->add(_cursor[i]->getCursor());
		_cursor[i]->move(osg::Vec3(0,0,0), 0);
	}
	_grid->reset();
	_physics->clearBoxes();
}

bool SceneManager::computeBoxIntersection(osg::Matrix mat, osg::Vec3 &intersection)
{
	// Get the direction pointing
    osg::Vec3 direction(mat.ptr()[8], mat.ptr()[9], mat.ptr()[10]);
    
    // Grab the position
    osg::Vec3d start_pos(mat.ptr()[12], mat.ptr()[13],mat.ptr()[14]);

    // Approximate the end position using the direction pointing
	float grid_world_size = grid_size * grid_block_size;
    float line_length = grid_world_size * 10.0;
    osg::Vec3d end_pos = start_pos + direction * -line_length;

	// Build an intersector for our geometry
	osg::ref_ptr<osg::LineSegment> intersector = new osg::LineSegment(start_pos, end_pos);
	osgUtil::IntersectVisitor iv;
	iv.addLineSegment(intersector);
	_scene->modelMatrix()->accept(iv);

	// Grab the first intersection if there are any found
	osgUtil::IntersectVisitor::HitList intersections = iv.getHitList(intersector);
	if (!intersections.empty()) {		
		intersection = intersections.front().getWorldIntersectPoint();
		
		// Add a half block to make sure we select the block we intersect with, not the one in front
		intersection += direction * -(grid_block_size / 2.0);
		return true;
	}

	return false;
}

bool SceneManager::computeGridIntersection(osg::Matrix mat, osg::Vec3 &intersection)
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

	// Set intersection point if we intersected and return intersection truth
	if (!intersector->intersect(bounding_box))
		return false;
	else {
		intersection = start_pos + (end_pos-start_pos)  * r1;
		return true;
	}
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
	static WandTrackChangeCommand wand_track_cmd;

	for(int i=0;i<commands.size();i++){		
		
		//Commands in common mode
		
		// Head tracking change
		if(!string(commands[i]->CommandType()).compare(head_track_cmd.CommandType())){
			osg::Matrix nav_mat = _scene->get_navigation_matrix();
			nav_mat.invert(nav_mat);
			_head_matrix = dynamic_cast<HeadTrackChangeCommand*>(commands[i])->headMatrix * nav_mat;

/* Check to see if there is head movement/updating
			osg::Vec3 eye,center,up;
			_head_matrix.getLookAt(eye,center,up);
			PRINTVECTOR(eye);
			PRINTVECTOR(center);			
*/
		}

		// Wand tracking change
		if(!string(commands[i]->CommandType()).compare(wand_track_cmd.CommandType())){
			osg::Matrix nav_mat = _scene->get_navigation_matrix();
			nav_mat.invert(nav_mat);
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
				std::cout << "d-Pad moving cursor" << std::endl;
				_cursor[commands[i]->id]->move(dynamic_cast<Move*>(commands[i])->direction,0);//update the xz position
				_cursor[commands[i]->id]->move(osg::Vec3(0,0,0),_grid->cursor_height(_cursor[commands[i]->id]->getCursorCurrentPosition()));//update the y position
			}
			
			// Wand cursor movements
			if(!string(commands[i]->CommandType()).compare(wand_track_cmd.CommandType()))
			{
				// Set the position of the cursor using the intersection point
				osg::Vec3 intersection_point;
				bool did_intersect = computeBoxIntersection(_wandMatrix, intersection_point);
				if (did_intersect)
				{
					osg::Vec3 grid_point = _grid->computeNearestGridPoint(intersection_point);
					_cursor[commands[i]->id]->setPosition(grid_point);
				}
			}

			//Add Block
			if(!string(commands[i]->CommandType()).compare(ab.CommandType())){
				//std::cout << "SceneManager - Adding block" << std::endl;
				osg::Vec3 curr = _cursor[commands[i]->id]->getCursorCurrentPosition();
				osg::Node* n = Builder::instance().createBlock(*dynamic_cast<Add_Block*>(commands[i]));
				_physics->add(n,curr);
				_scene->add(n);
				_grid->add(curr);
				_cursor[commands[i]->id]->move(osg::Vec3(0,0,0),_grid->cursor_height(curr));//update the cursor y position
			}
		}
		//In Physics Mode
		else{
			if(!string(commands[i]->CommandType()).compare(tb.CommandType())){				
				//std::cout << "SceneManager - Throwing projectile" << std::endl;
				osg::ref_ptr<osg::Node> n = Builder::instance().createProjectile();

				//Trying to get Head Position Will have to fixed in Juggler version
				osg::Vec3 head=_head_matrix.getTrans();
				osg::Quat rot = _head_matrix.getRotate();
				osg::Vec3 dir = rot * osg::Vec3(0,0,-1);
				dir.normalize();
				_physics->add_projectile(n,head,dir*20.0f);
				_scene->add(n);
			}
		}

		// Clean up the command
		delete commands[i];		
	}

	if(creationMode){
		for(int i=0;i<_cursor.size();i++)		
			_cursor[i]->update();	
		_physics->rebuild();
		_scene->rebuild();
	}
	else{
		for(int i=0;i<_cursor.size();i++)		
			_cursor[i]->off();
		_physics->update();
		_scene->physicsmode();
	}
}

void SceneManager::set_head_matrix(osg::Matrix m){
	_head_matrix = m;
}
