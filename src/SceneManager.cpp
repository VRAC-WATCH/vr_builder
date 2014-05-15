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
			case SceneCommand::NAVIGATION: {
				_updateNavigation(commands[i]);
				break;
			}
			case SceneCommand::THROW_BLOCK: {
				std::cout << "Throwing block" << std::endl;
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

void SceneManager::_updateNavigation(SceneCommand navigationCommand)
{	
	float* axis = &(*navigationCommand.joystickAxisValues);

	osg::Matrix nav_matrix = _scene->get_navigation_matrix();

	std::cout << "X: " << nav_matrix.getTrans().x() << " Y: " << nav_matrix.getTrans().y() << " Z: " << nav_matrix.getTrans().z() << std::endl;

	//osg::Matrix nav_matrix = _scene->get_navigation_matrix() * osg::Matrix::translate(axis[0], axis[2], axis[1]);
	osg::Matrix move_matrix = osg::Matrix::translate(v3(0.0f,0.0f,0.0f));
	//nav_matrix.
	//_scene->set_navigation_matrix(nav_matrix);
	osg::Matrix mult_matrix = nav_matrix;

	//std::cout << 

	_scene->set_navigation_matrix(nav_matrix);
//	++i;
}
