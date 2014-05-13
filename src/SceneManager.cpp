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
	int scene_grid_size = 40;
	_scene = new Scene(scene_grid_size);
}

SceneManager::~SceneManager()
{
	delete _scene;
}

void SceneManager::update(const std::vector<SceneCommand> &commands)
{
	std::cout << "Updating: " << commands.size() << " elements" << std::endl;
}