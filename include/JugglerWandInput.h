#pragma once

// Juggler headers
#include <gadget/Type/DigitalInterface.h>
#include <gadget/Type/PositionInterface.h>

// Local headers
#include "Input.h"
#include "SceneCommand.h"

class JugglerWandInput : public Input
{
public:

	/** Default Constructor. */
	JugglerWandInput();
	
	/** Destructor. */
	~JugglerWandInput();
	
	/** Add any commands we have stored to the list passed in. */
	void populateSceneCommand(std::vector<SceneCommand*>& commandList);


protected:

	/** Pulls information from the gadgets. */
	void _updateJugglerInput();

	/** Juggler gadget interface iVars. */
	gadget::DigitalInterface 	_button[6];
	gadget::PositionInterface  	_wand;
};


