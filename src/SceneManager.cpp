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
		switch(commands[i].commandType)
		{
			case SceneCommand::ADD_BLOCK: {
//				_scene->add_model_node(commands[i]);
			}
			case SceneCommand::MODE_CHANGE: {
				;
			}
			case SceneCommand::MOVE: {
				if (_scene->gameMode() == SceneCommand::PHYSICS) {
					_scene->moveHead(commands[i].direction);
				}
				else {
					_scene->moveCursor(commands[i].direction);
				}
				break;
			}
			case SceneCommand::THROW_BLOCK: {
				_scene->throwProjectile(v3(0,0,-5));
				break;
			}
			default: {
				std::cout << "SceneManager::update - Unhandled command type" << std::endl;
			}
		}

		if(commands[i].commandType == SceneCommand::ADD_BLOCK)
			_scene->add_model_node(commands[i],false);
		if(commands[i].commandType == SceneCommand::MODE_CHANGE)
			_scene->changemode();
	}
	_scene->update(t);
}