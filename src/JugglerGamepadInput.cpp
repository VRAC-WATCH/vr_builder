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
	_axis0.init("Left Joystick Horizontal Axis");
	_axis1.init("Left Joystick Vertical Axis");
	_axis2.init("Right Joystick Vertical Axis");
	_axis3.init("Right Joystick Horizontal Axis");
	_axis4.init("DirectionPad Horizontal Axis");
	_axis5.init("DirectionPad Vertical Axis");
}

JugglerGamepadInput::~JugglerGamepadInput()
{
	std::cout << "JugglerGamepadInput Destructor" << std::endl;
}

void JugglerGamepadInput::populateSceneCommand(std::vector<SceneCommand>& commandList)
{
	_updateJugglerInput();

	// Append all of our latest scene commands to the list requested then clear it
	commandList.insert(commandList.end(),
					   _sceneCommandList.begin(), _sceneCommandList.end());
	_sceneCommandList.clear();
}

void JugglerGamepadInput::_updateJugglerInput()
{
	//Navigation speed modify		
/*	if (_button[4]->getData() == gadget::Digital::TOGGLE_ON)
	{
		if (_navSpeed > 0.02)
			_navSpeed -= 0.05;
		if (_rotSpeed < 200)
			_rotSpeed += 5;
	}
	else if (_button[5]->getData() == gadget::Digital::TOGGLE_ON)
	{
		_navSpeed += 0.1;
		if (_rotSpeed >= 10)
		_rotSpeed -= 5;
	}*/
	//================== UPDATE WAND NAVIGATION ==================
	// User navigation with the joysticks
	float axis0 = _axis0->getData();
	float axis1 = _axis1->getData();
	float axis2 = _axis2->getData();
	float axis3 = _axis3->getData();
	float axis4 = _axis4->getData();
	float axis5 = _axis5->getData();

	// The gamepad provides 0.0 - 1.0, this makes the origin 0.0 instead of 0.5
	axis0 -= 0.5; axis1 -= 0.5; axis2 -= 0.5; axis3 -= 0.5; axis4 -= 0.5; axis5 -= 0.5;
	if (axis0 != 0.0 || axis1 != 0.0 || axis2 != 0.0 || axis3 != 0.0 || axis4 != 0.0 || axis5 != 0.0)
	{			
		SceneCommand nav_update;
		nav_update.commandType = SceneCommand::NAVIGATION;
		
		nav_update.joystickAxisValues[0] = axis0;
		nav_update.joystickAxisValues[1] = axis1;
		nav_update.joystickAxisValues[2] = axis2;
		nav_update.joystickAxisValues[3] = axis3;
		nav_update.joystickAxisValues[4] = axis4;
		nav_update.joystickAxisValues[5] = axis5;

		_sceneCommandList.push_back(nav_update);
		
		// Only allow Yaw (rot y) for navigation
		//gmtl::EulerAngleXYZf euler(0.0f, -axis3, 0.0f);
		//_osgNavigator.setRotationalVelocity(gmtl::makeRot<gmtl::Matrix44f>(euler));
		//_osgNavigator.setVelocity(gmtl::Vec3f(axis0, -axis2, axis1));

		// Only allow Pitch (rot x) and Roll (rot z) for tilt
		//gmtl::EulerAngleXYZf eulerTilt(-axis5, 0.0f, axis4);
		//_osgNavigator.setTiltVelocity(gmtl::makeRot<gmtl::Matrix44f>(eulerTilt));
	
	}
}

/*
void JugglerGamepadInput::_keyboardSpecial(int key, int x, int y)
{
	switch(key)
	{
		//handle key input
		case GLUT_KEY_UP: {
			SceneCommand cmd;
			cmd.commandType = SceneCommand::MOVE;
			cmd.direction = v3(0,0,1);
			s_keyboardSceneCommands.push_back(cmd);
			break;
		}
		case GLUT_KEY_DOWN: {
			SceneCommand cmd;
			cmd.commandType = SceneCommand::MOVE;
			cmd.direction = v3(0,0,-1);
			s_keyboardSceneCommands.push_back(cmd);
			break;
		}
		case GLUT_KEY_LEFT: {
			SceneCommand cmd;
			cmd.commandType = SceneCommand::MOVE;
			cmd.direction = v3(-1,0,0);
			s_keyboardSceneCommands.push_back(cmd);
			break;
		}
		case GLUT_KEY_RIGHT: {
			SceneCommand cmd;
			cmd.commandType = SceneCommand::MOVE;
			cmd.direction = v3(1,0,0);
			s_keyboardSceneCommands.push_back(cmd);
			break;
		}
		default:
			printf("Unrecognized key.\n");
            break;
    }
	glutPostRedisplay();
}

void JugglerGamepadInput::_keyboardNormal(unsigned char key, int x, int y)
{
	switch(key)
	{
	case('t'):{
		SceneCommand cmd;
		cmd.commandType = SceneCommand::MODE_CHANGE;
		s_keyboardSceneCommands.push_back(cmd);
		break;
	}
	case ' ': {
		SceneCommand cmd;
		cmd.commandType = SceneCommand::THROW_BLOCK;
		s_keyboardSceneCommands.push_back(cmd);
		break;
	}
	default:
		printf("Unrecognized key \n");
		break;
	}
	glutPostRedisplay();
}

JugglerGamepadInput::special_func_ptr JugglerGamepadInput::keyboardSpecial_ptr() {
	return &_keyboardSpecial;
}

JugglerGamepadInput::normal_func_ptr JugglerGamepadInput::keyboardNormal_ptr() {
	return &_keyboardNormal;
}*/

