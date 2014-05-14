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
	int scene_grid_size = 20;
	_scene = new Scene(scene_grid_size,1.0f);
}

SceneManager::~SceneManager()
{
	delete _scene;
}

void SceneManager::update(double t,const std::vector<SceneCommand> &commands )
{
	//std::cout << "Updating: " << commands.size() << " elements" << std::endl;
	for(int i=0;i<commands.size();i++){
		switch(commands[i].cursormovement){
		case(SceneCommand::CURSOR_LEFT):
			_scene->movecursor_left();
			break;
		case(SceneCommand::CURSOR_RIGHT):
			_scene->movecursor_right();
			break;
		case(SceneCommand::CURSOR_UP):
			_scene->movecursor_up();
			break;
		case(SceneCommand::CURSOR_DOWN):
			_scene->movecursor_down();
			break;
		}
		if(commands[i].command == SceneCommand::ADD_BLOCK)
			_scene->add_model_node(commands[i],false);
		if(commands[i].command == SceneCommand::MODE_CHANGE)
			_scene->changemode();
	}
	_scene->update(t);
}

void SceneManager::projectile_throw(){
	_scene->projectile_throw(osg::Vec3(0,0,0),osg::Vec3(0,0,-0.5));
}