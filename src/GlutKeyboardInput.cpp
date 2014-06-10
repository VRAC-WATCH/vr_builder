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
static std::vector<SceneCommand*> s_keyboardSceneCommands;

GlutKeyboardInput::GlutKeyboardInput() : Input(Input::KEYBOARD)
{
	std::cout << "Input Constructor" << std::endl;
}

GlutKeyboardInput::~GlutKeyboardInput()
{
	std::cout << "Input Destructor" << std::endl;
}

void GlutKeyboardInput::populateSceneCommand(std::vector<SceneCommand*>& commandList)
{
	// Append all of our latest scene commands to the list requested then clear it
	if(s_keyboardSceneCommands.size()){
	commandList.insert(commandList.end(),
					   s_keyboardSceneCommands.begin(), s_keyboardSceneCommands.end());
	s_keyboardSceneCommands.clear();
	}
}

void GlutKeyboardInput::_keyboardSpecial(int key, int x, int y)
{
	switch(key)
	{
		//handle key input
		case GLUT_KEY_UP: {
			SceneCommand* move = new Move ;
			dynamic_cast<Move*>(move)->direction = v3(0,0,-1);
			s_keyboardSceneCommands.push_back(move);
			break;
		}
		case GLUT_KEY_DOWN: {
			SceneCommand* move = new Move ;
			dynamic_cast<Move*>(move)->direction = v3(0,0,1);
			s_keyboardSceneCommands.push_back(move);
			break;
		}
		case GLUT_KEY_LEFT: {
			SceneCommand* move = new Move ;
			dynamic_cast<Move*>(move)->direction = v3(-1,0,0);
			s_keyboardSceneCommands.push_back(move);
			break;
		}
		case GLUT_KEY_RIGHT: {
			SceneCommand* move = new Move ;
			dynamic_cast<Move*>(move)->direction = v3(1,0,0);
			s_keyboardSceneCommands.push_back(move);
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
		SceneCommand* cmd = new Mode_Change;
		s_keyboardSceneCommands.push_back(cmd);
		break;
	}
	case 'a': {
		SceneCommand *cmd = new Add_Block;
		dynamic_cast<Add_Block*>(cmd)->textureFileName = "../resources/Metalic_texture.bmp";
		dynamic_cast<Add_Block*>(cmd)->color=osg::Vec4(0,1,0,1);
		s_keyboardSceneCommands.push_back(cmd);
		break;
	}
	case ' ': {
		SceneCommand* cmd = new Throw_Block;
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
