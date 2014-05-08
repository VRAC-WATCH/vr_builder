// System headers
#include <iostream>

// GL headers
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// Local headers
#include "GlutKeyboardInput.h"
#include "SceneCommand.h"


GlutKeyboardInput::GlutKeyboardInput() : Input(Input::KEYBOARD)
{
	std::cout << "Input Constructor" << std::endl;
}

GlutKeyboardInput::~GlutKeyboardInput()
{
	std::cout << "Input Destructor" << std::endl;
}

void GlutKeyboardInput::populateSceneCommand(std::vector<SceneCommand>& commandList)
{
	// Append all of our latest scene commands to the list requested then clear it
	commandList.insert(commandList.end(), _sceneCommandList.begin(), _sceneCommandList.end());
	_sceneCommandList.clear();
}

void GlutKeyboardInput::_keyboardDown(unsigned char key, int x, int y)
{
	switch(key)
	{
		//handle key input
//		case 'q':
//			printf("Strafe Left.\n");
//			break;
//		case 'w':
//			printf("Forward.\n");
//			break;
//		case 'e':
//			printf("Strafe Right.\n");
//			break;
//		case 'a':
//			printf("Turn Left.\n");
//			break;
//		case 's':
//			printf("Backward.\n");
//			break;
//		case 'd':
//			printf("Turn Right.\n");
//			break;
//		case 'z':
//			printf("Down.\n");
//			break;
//		case 'x':
//			printf("Up.\n");
//			break;
		case GLUT_KEY_UP: {
			SceneCommand cmd;
			cmd.commandType = SceneCommand::SET_CURSOR_POS;
			cmd.magnitude = v3(0,0,1);
			break;
		}
		case GLUT_KEY_DOWN: {
			SceneCommand cmd;
			cmd.commandType = SceneCommand::SET_CURSOR_POS;
			cmd.magnitude = v3(0,0,-1);
			break;
		}
		case GLUT_KEY_LEFT: {
			SceneCommand cmd;
			cmd.commandType = SceneCommand::SET_CURSOR_POS;
			cmd.magnitude = v3(-1,0,0);
			break;
		}
		case GLUT_KEY_RIGHT: {
			SceneCommand cmd;
			cmd.commandType = SceneCommand::SET_CURSOR_POS;
			cmd.magnitude = v3(0,0,1);
			break;
		}
		case 27:
			exit(1);
			break;
		default:
			printf("Unrecognized key.\n");
            break;
    }
	glutPostRedisplay();
}

void GlutKeyboardInput::_keyboardUp(unsigned char key, int x, int y) {
	switch(key)
	{
		//handle key input
		case 'q':
			printf("Strafe Left Off.\n");
			break;
		case 'w':
			printf("Forward Off.\n");
			break;
		case 'e':
			printf("Strafe Right Off.\n");
			break;
		case 'a':
			printf("Turn Left Off.\n");
			break;
		case 's':
			printf("Backward Off.\n");
			break;
		case 'd':
			printf("Turn Right Off.\n");
			break;
		case 'z':
			printf("Down Off.\n");
			break;
		case 'x':
			printf("Up Off.\n");
			break;
		default:
			printf("Unrecognized key Off.\n");
            break;
    }
	glutPostRedisplay();
}

GlutKeyboardInput::func_ptr GlutKeyboardInput::keyboardDown_ptr() {
	return &_keyboardDown;
}

GlutKeyboardInput::func_ptr GlutKeyboardInput::keyboardUp_ptr() {
	return &GlutKeyboardInput::_keyboardUp;
}