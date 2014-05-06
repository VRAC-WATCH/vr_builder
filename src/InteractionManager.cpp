// System headers
#include <iostream>

// Local headers
#include "InteractionManager.h"
#include "KeyboardInput.h"

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
}

void InteractionManager::update()
{
	std::cout << "Updating InteractionManager" << std::endl;
}

#pragma mark Class Setup

void InteractionManager::_setupGlutInputs()
{
	std::cout << "Setting up glut input" << std::endl;
	
	// Setup the keyboard
//	Input* keyboard ;
}

void InteractionManager::_setupJugglerInputs()
{
	std::cout << "Setting up juggler input" << std::endl;
}