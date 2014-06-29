
#pragma once

// System headers
#include <vector>

// Local headers
#include "Input.h"


class InteractionManager{
public:
	
	/** Enum for declaring the Interface type. */
	enum InterfaceType {
		GLUT_INTERFACE,
		JUGGLER_INTERFACE
	};
	
	/** Default Constructor - Sets up the glut interface. */
	InteractionManager();
	
	/** Constructor declaring interface. */
	InteractionManager(InterfaceType type);
	
	/** Destructor. */
	~InteractionManager();
	
	/** Accessors for the specified input type. */
	Input* inputForType(Input::InputType type);
	
	/** 
	 * Builds a list of commands that have been executed from any input. 
	 * This needs to be done every frame before trying to use commands.
	 */
	void update();
	
	/** 
	 * Accessor for the current scene commands. 
	 * Currently, for this to have any data, you must call update()
	 * in order to populate the _sceneCommandList with commands.
	 */
	std::vector<SceneCommand*>& sceneCommands() { return _sceneCommandList; }

	/** Ask the interaction manager how many devices connected need cursor control*/
	int howManyWantCursor();
	
	
protected:
	
	/** Sets up user interaction handlers for Glut. */
	void _setupGlutInputs();
	
	/** Sets up user interaction hanlders for Juggler. */
	void _setupJugglerInputs();
	
	/** Checks the input device if it wants a cursor */	
	void checkNeedForCursor(Input*& input);
	
	/** iVars. */
	std::vector<Input*>			_inputs;
	InterfaceType				_interfaceType;
	std::vector<SceneCommand*>	_sceneCommandList;
	int 					ids;
};
