// System headers
#include <iostream>

// Local headers
#include "InteractionManager.h"
#include "KeyboardInput.h"
#include "SceneCommand.h"

InteractionManager::InteractionManager()
{
	_setupGlutInputs();
}

InteractionManager::InteractionManager(InterfaceType type)
{
	if (JUGGLER_INTERFACE)
		_setupGlutInputs();
	else
		_setupJugglerInputs();
}

InteractionManager::~InteractionManager()
{
	std::cout << "InteractionManager Destructor" << std::endl;
	
	for (unsigned int i=0; i<_inputs.size(); ++i) {
		delete _inputs.at(i);
	}
}

void InteractionManager::update()
{
	std::cout << "Updating InteractionManager" << std::endl;
	
	std::vector<SceneCommand> command_list;
	for (unsigned int i=0; i<_inputs.size(); ++i) {
		_inputs.at(i)->populateSceneCommand(command_list);
	}
}

#pragma mark Class Setup

void InteractionManager::_setupGlutInputs()
{
	std::cout << "Setting up glut input" << std::endl;
	
	// Setup the keyboard
	Input* keyboard = new KeyboardInput;
	_inputs.push_back(keyboard);
	
	// Setup the mouse
	
}

void InteractionManager::_setupJugglerInputs()
{
	std::cout << "Setting up juggler input" << std::endl;
}