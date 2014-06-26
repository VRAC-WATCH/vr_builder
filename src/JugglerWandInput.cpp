// System headers
#include <iostream>

// Local headers
#include "JugglerWandInput.h"
#include "SceneCommand.h"

JugglerWandInput::JugglerWandInput() : Input(Input::WAND)
{
	std::cout << "JugglerWandInput Constructor" << std::endl;

	// Initialize the wand interface
	_button[0].init("VJButton0");
	_button[1].init("VJButton1");
	_button[2].init("VJButton2");
	_button[3].init("VJButton3");
	_button[4].init("VJButton4");
	_button[5].init("VJButton5");
	_wand.init("VJWand");
}

JugglerWandInput::~JugglerWandInput()
{
	std::cout << "JugglerWandInput Destructor" << std::endl;
}

void JugglerWandInput::populateSceneCommand(std::vector<SceneCommand*>& commandList)
{
	_updateJugglerInput();

	// Append all of our latest scene commands to the list requested then clear it
	commandList.insert(commandList.end(),
					   _sceneCommandList.begin(), _sceneCommandList.end());
	_sceneCommandList.clear();
}

void JugglerWandInput::_updateJugglerInput()
{
	///////////////////////
	///// Positional input 
	///////////////////////

	// Grab the positional matrix every frame from the device
	osg::Matrixf wand_matrix(_wand->getData().mData);
	
	// Build a command and add it to the list
	WandTrackChangeCommand* wand_change = new WandTrackChangeCommand;
	wand_change->wandMatrix = wand_matrix;
	_sceneCommandList.push_back(wand_change);


	////////////////////
	///// Button input 
	////////////////////

	// This helps so we don't have to keep updating hard coded numbers each time config changes
	enum BUTTON_NUM { BUTTON1=0, BUTTON2=1, BUTTON3=2, BUTTON4=3, 
						JOYSTICK_BUTTON=4, TRIGGER=5 };

	// Mode change
	if (_button[BUTTON2]->getData() == gadget::Digital::TOGGLE_ON)
	{
		std::cout << "Mode change" << std::endl;
		Mode_Change* mode_change = new Mode_Change;
		_sceneCommandList.push_back(mode_change);
	}

	// Add block - note: we allow this button to be held down so that we can add 
	// blocks very quickly to the scene hence we don't check button switch state
	if (_button[TRIGGER]->getData() == gadget::Digital::ON)
	{
		std::cout << "add block" << std::endl;
		Add_Block* add_block = new Add_Block;
		add_block->color = osg::Vec4(0.7, 0.7, 0.7, 1.0);
		_sceneCommandList.push_back(add_block);
	}

	// Throw ball
	if (_button[BUTTON1]->getData() == gadget::Digital::TOGGLE_ON)
	{
		std::cout << "ball throw" << std::endl;
		Throw_Block* throw_block = new Throw_Block;
		_sceneCommandList.push_back(throw_block);
	}

	// Clear Scene
	if (_button[JOYSTICK_BUTTON]->getData() == gadget::Digital::TOGGLE_ON)
	{
		std::cout << "clear scene" << std::endl;
		ClearSceneCommand* clear_scene_cmd = new ClearSceneCommand;
		_sceneCommandList.push_back(clear_scene_cmd);
	}
}

