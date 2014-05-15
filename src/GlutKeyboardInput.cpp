// System headers
#include <iostream>

// GL headers
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <glut.h>
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

void GlutKeyboardInput::_keyboardSpecial(int key, int x, int y)
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

void GlutKeyboardInput::_keyboardNormal(unsigned char key, int x, int y)
{
	switch(key)
	{
	case('t'):{
		SceneCommand cmd;
		cmd.commandType = SceneCommand::MODE_CHANGE;
		s_keyboardSceneCommands.push_back(cmd);
		break;
	}
	case 'a': {
		SceneCommand cmd;
		cmd.commandType = SceneCommand::ADD_BLOCK;
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

GlutKeyboardInput::special_func_ptr GlutKeyboardInput::keyboardSpecial_ptr() {
	return &_keyboardSpecial;
}

GlutKeyboardInput::normal_func_ptr GlutKeyboardInput::keyboardNormal_ptr() {
	return &_keyboardNormal;
}
