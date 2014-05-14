// System headers
#include <iostream>

// Local headers
#include "InteractionManager.h"
#include "GlutKeyboardInput.h"
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

Input* InteractionManager::inputForType(Input::InputType type)
{
	// Look through the current list of inputs and return
	// it if we find a match
	for (unsigned int i=0; i<_inputs.size(); ++i) {
		if(_inputs.at(i)->inputType() == type) {
			return _inputs.at(i);
		}
	}
	
	// If we made it here, we didn't find a match so inform
	std::cout << "No input for the requested type." << std::endl;
	
	return NULL;
}

void InteractionManager::update()
{
	//std::cout << "Updating InteractionManager" << std::endl;
	
	// Clear the previous scene commands
	_sceneCommandList.clear();
	
	// Fetch all new commands from each input
	std::vector<SceneCommand> command_list;
	for (unsigned int i=0; i<_inputs.size(); ++i) {
		_inputs.at(i)->populateSceneCommand(command_list);
	}
	_sceneCommandList = command_list;
}

//#pragma mark Class Setup

void InteractionManager::_setupGlutInputs()
{
	std::cout << "Setting up glut input" << std::endl;
	
	// Setup the keyboard
	Input* keyboard = new GlutKeyboardInput;
	_inputs.push_back(keyboard);
	
	// Setup the mouse
	
}

void InteractionManager::_setupJugglerInputs()
{
	std::cout << "Setting up juggler input" << std::endl;
}