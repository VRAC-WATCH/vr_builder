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


/**
 * Static iVars.
 * Really don't like doing this, but Glut cannot accept the func pointer
 * properly unless we have the func pointer methods static. Need to look
 * into other methods for future work.
 */
static std::vector<SceneCommand> s_keyboardSceneCommands;

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
	commandList.insert(commandList.end(),
					   s_keyboardSceneCommands.begin(), s_keyboardSceneCommands.end());
	s_keyboardSceneCommands.clear();
}

void GlutKeyboardInput::_keyboardDown(int key, int x, int y)
{
	switch(key)
	{
		//handle key input
		case GLUT_KEY_UP: {
			SceneCommand cmd;
			cmd.cursormovement = SceneCommand::CURSOR_UP;
			s_keyboardSceneCommands.push_back(cmd);
			break;
		}
		case GLUT_KEY_DOWN: {
			SceneCommand cmd;
			cmd.cursormovement = SceneCommand::CURSOR_DOWN;
			s_keyboardSceneCommands.push_back(cmd);
			break;
		}
		case GLUT_KEY_LEFT: {
			SceneCommand cmd;
			cmd.cursormovement = SceneCommand::CURSOR_LEFT;
			s_keyboardSceneCommands.push_back(cmd);
			break;
		}
		case GLUT_KEY_RIGHT: {
			SceneCommand cmd;
			cmd.cursormovement = SceneCommand::CURSOR_RIGHT;
			s_keyboardSceneCommands.push_back(cmd);
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

void GlutKeyboardInput::_keyboardnormal(int key, int x, int y)
{
	switch(key)
	{
	case('t'):{
		SceneCommand cmd;
		cmd.command = SceneCommand::MODE_CHANGE;
		s_keyboardSceneCommands.push_back(cmd);
		break;
	}
	default:
		printf("Unrecognized key \n");
		break;

	}
	glutPostRedisplay();
}

GlutKeyboardInput::func_ptr GlutKeyboardInput::keyboardDown_ptr() {
	return &_keyboardDown;
}

GlutKeyboardInput::func_ptr GlutKeyboardInput::keyboardnormal_ptr() {
	return &_keyboardnormal;
}
