// System headers
#include <iostream>

// GL headers
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// Local headers
#include "KeyboardInput.h"


KeyboardInput::KeyboardInput()
{
	std::cout << "Input Constructor" << std::endl;
}

void KeyboardInput::update()
{
	std::cout << "Input Destructor" << std::endl;
}

void KeyboardInput::keyboardDown(unsigned char key, int x, int y)
{
	switch(key)
	{
		//handle key input
		case 'q':
			printf("Strafe Left.\n");
			break;
		case 'w':
			printf("Forward.\n");
			break;
		case 'e':
			printf("Strafe Right.\n");
			break;
		case 'a':
			printf("Turn Left.\n");
			break;
		case 's':
			printf("Backward.\n");
			break;
		case 'd':
			printf("Turn Right.\n");
			break;
		case 'z':
			printf("Down.\n");
			break;
		case 'x':
			printf("Up.\n");
			break;
		case 27:
			exit(1);
			break;
		default:
			printf("Unrecognized key.\n");
            break;
    }
	glutPostRedisplay();
}

void KeyboardInput::keyboardUp(unsigned char key, int x, int y) {
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

KeyboardInput::func_ptr KeyboardInput::keyboardDown_ptr() {
	return KeyboardInput::keyboardDown;
}

KeyboardInput::func_ptr KeyboardInput::keyboardUp_ptr() {
	return KeyboardInput::keyboardUp;
}