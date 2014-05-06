// System headers
#include <stdarg.h>
#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif

// GL headers
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "SceneCommand.h"

class KeyboardInput {
public:
	typedef void (*fptr)(unsigned char, int, int);

	KeyboardInput();
	void update();
	static void keyboardDown(unsigned char key, int x, int y);
	static void keyboardUp(unsigned char key, int x, int y);
	KeyboardInput::fptr keyboardDown_ptr();
	KeyboardInput::fptr keyboardUp_ptr();
};


