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

class InteractionManager {
	InteractionManager();
	void update();

};