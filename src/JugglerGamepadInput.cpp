// System headers
#include <iostream>

// Local headers
#include "JugglerGamepadInput.h"
#include "SceneCommand.h"

JugglerGamepadInput::JugglerGamepadInput() : Input(Input::GAMEPAD)
{
	std::cout << "JugglerGamepadInput Constructor" << std::endl;

	// Initialize the gamepad gadget interface
	_button[0].init("Button 1");
	_button[1].init("Button 2");
	_button[2].init("Button 3");
	_button[3].init("Button 4");
	_button[4].init("Button 5");
	_button[5].init("Button 6");
	_button[6].init("Button 7");
	_button[7].init("Button 8");
	_button[8].init("Button 9");
	_button[9].init("Button 10");
	_axis4.init("Left Joystick Horizontal Axis");
	_axis5.init("Left Joystick Vertical Axis");
	_axis2.init("Right Joystick Vertical Axis");
	_axis3.init("Right Joystick Horizontal Axis");
	_axis0.init("DirectionPad Horizontal Axis");
	_axis1.init("DirectionPad Vertical Axis");

	wantCursor = true;
}

JugglerGamepadInput::~JugglerGamepadInput()
{
	std::cout << "JugglerGamepadInput Destructor" << std::endl;
}

void JugglerGamepadInput::populateSceneCommand(std::vector<SceneCommand*>& commandList)
{
	_updateJugglerInput();
	
	for(int i=0;i<_sceneCommandList.size();i++){
		_sceneCommandList[i]->id = getID();
	}
	// Append all of our latest scene commands to the list requested then clear it
	commandList.insert(commandList.end(),
					   _sceneCommandList.begin(), _sceneCommandList.end());
	_sceneCommandList.clear();
}

void JugglerGamepadInput::_updateJugglerInput()
{
	// Joystick hardware rotation values
	float axis0 = _axis0->getData();
	float axis1 = _axis1->getData();
	float axis2 = _axis2->getData();
	float axis3 = _axis3->getData();
	float axis4 = _axis4->getData();
	float axis5 = _axis5->getData();

	///////////////////////
	// Joystick input section
	///////////////////////


	// The gamepad provides 0.0 - 1.0, this makes the origin 0.0 instead of 0.5
	axis0 -= 0.5; axis1 -= 0.5; axis2 -= 0.5; axis3 -= 0.5; axis4 -= 0.5; axis5 -= 0.5;
	
	//std::cout<<axis0<<" "<<axis1<<" "<<axis2<<" "<<axis3<<" "<<axis4<<" "<<axis5<<" "<<std::endl;
	// If user pressing joysticks, create nav command
	if (axis0 != 0.0 || axis1 != 0.0 || axis2 != 0.0 || axis3 != 0.0)
	{
		Navigation* nav_update = new Navigation;

		// Reduce rotation speed
		axis3 /= 20.0;		

		// Calculate movement based on gamepad joysticks
		osg::Matrix gamepad_update;
		gamepad_update.setTrans(-axis0, axis2, -axis1);
		gamepad_update.setRotate(osg::Quat(0,axis3,0,1));
		
		// Finalize the nav command and add it to the list
		nav_update->navMatrixMultiplier = gamepad_update;
		_sceneCommandList.push_back(nav_update);
	}

	///////////////////////
	// D-pad input section
	///////////////////////


	// Make sure the user clicks rather than holds the cursor
	// (only initializes the first pass because static)
	static bool cursor_moving = false;

	// If user pressing dpad, create block move command
	if ((axis4 != 0.0 || axis5 != 0.0) && cursor_moving == false)
	{
		cursor_moving = true;

		Move* cursor_move = new Move;

		// Horizontal cursor movement
		if (axis4 > 0.0)
			cursor_move->direction[0] = 1;
		else if (axis4 < 0.0)
			cursor_move->direction[0] = -1;
		
		// Vertical cursor movement
		if (axis5 > 0.0)
			cursor_move->direction[2] = 1;
		else if (axis5 < 0.0)
			cursor_move->direction[2] = -1;

		_sceneCommandList.push_back(cursor_move);
	}
	else if (axis4 == 0.0 && axis5 == 0.0) 
	{
		cursor_moving = false;
	}

	///////////////////////
	// Button input section
	///////////////////////
	

	// This helps so we don't have to keep updating hard coded numbers each time config changes
	enum BUTTON_NUM { MODE_CHANGE=0, BLOCK_ADD=1, BLOCK_THROW=3, CLEAR_SCENE=9 };

	// Mode change
	if (_button[MODE_CHANGE]->getData() == gadget::Digital::TOGGLE_ON)
	{
		Mode_Change* mode_change = new Mode_Change;
		_sceneCommandList.push_back(mode_change);
	}

	// Add block - note: we allow this button to be held down so that we can add 
	// blocks very quickly to the scene hence we don't check button switch state
	if (_button[BLOCK_ADD]->getData() == gadget::Digital::ON)
	{
		Add_Block* add_block = new Add_Block;
		add_block->color = osg::Vec4(1.0, 0.0, 1.0, 1.0);
		add_block->textureFileName = "../resources/Metalic_texture.bmp";
		_sceneCommandList.push_back(add_block);
	}

	// Throw block
	if (_button[BLOCK_THROW]->getData() == gadget::Digital::TOGGLE_ON)
	{
		Throw_Block* throw_block = new Throw_Block;
		_sceneCommandList.push_back(throw_block);
	}

	// Clear Scene
	if (_button[CLEAR_SCENE]->getData() == gadget::Digital::TOGGLE_ON)
	{
		ClearSceneCommand* clear_scene_cmd = new ClearSceneCommand;
		_sceneCommandList.push_back(clear_scene_cmd);
	}
}

