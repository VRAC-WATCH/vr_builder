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

// OSG headers
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

// Local headers
#include "CameraController.h"
#include "InteractionManager.h"
#include "GlutKeyboardInput.h"
#include "VRBuilderApp.h"

int screenWidth = 1024;
int screenHeight = 768;
float gYaw = 45.0;
float gPitch = 45.0;
float gZoom = 1.0;
bool gRightClick = false;
bool gOrbitCam;		//are we using the orbit cam or the C6 cam?
float aspect;
bool gPaused = false;
bool gFullScreen;
int gMouseX, gMouseY;

bool gShowC6 = true;

CameraController gCamera;


osg::ref_ptr<osgViewer::Viewer> viewer;
osg::observer_ptr<osgViewer::GraphicsWindow> window;

void drawStringOnScreen(int x, int y, const char* format, ...);
void drawStatus()
{
	glColor3f(1,1,1);
	static float t=0;
	static float fps=2;
	static float deltat=.2;
	static int reps=0;
	float tnow=glutGet(GLUT_ELAPSED_TIME);
	reps++;

	if(tnow - t > 500)		//update every 500 ms
	{
		//float tnow=glutGet(GLUT_ELAPSED_TIME);
		deltat=tnow-t;
		t=tnow;
		fps=1.f * reps/deltat*1000;
		reps = 0;
	}
	
	drawStringOnScreen(20, 20, "Frame Rate:             %.2f", fps);
	glColor3f(1, 0, 0);
}
void drawC6(bool filled)
{
	glCullFace(GL_BACK);
	if(filled)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glLineWidth(5);
	glColor3f(0.7, 0.7, 0.7);
	if(filled)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, -5);
		glVertex3f(-5, 0, -5);
		glVertex3f(-5, 0, 5);
		glVertex3f(5, 0, 5);
		glVertex3f(5, 0, -5);

		glNormal3f(0, 0, 1);
		glVertex3f(-5, 10, -5);
		glVertex3f(-5, 0, -5);
		glVertex3f(5, 0, -5);
		glVertex3f(5, 10, -5);

		glNormal3f(1, 0, 0);
		glVertex3f(-5, 10, -5);
		glVertex3f(-5, 10, 5);
		glVertex3f(-5, 0, 5);
		glVertex3f(-5, 0, -5);

		glNormal3f(-1, 0, 0);
		glVertex3f(5, 0, -5);
		glVertex3f(5, 0, 5);
		glVertex3f(5, 10, 5);
		glVertex3f(5, 10, -5);

	glEnd();
	
	//if we're using lined mode, draw a grid over the C6
	if(!filled)
	{
		glLineWidth(1);
		int numLines = 20;
		glColor3f(0.4, 0.4, 0.4);
		glBegin(GL_LINES);
			for(int i = 0; i < numLines; i++)
			{
				float coord = -5.0 + 10.0 * i / numLines;
				
				//floor
				glVertex3f(-5,0, coord);
				glVertex3f(5, 0, coord);
				glVertex3f(coord, 0, -5);
				glVertex3f(coord, 0, 5);
				
				//front
				glVertex3f(-5, coord+5, -5);
				glVertex3f(5, coord+5, -5);
				glVertex3f(coord, 0, -5);
				glVertex3f(coord, 10, -5);
				
				//left
				glVertex3f(-5, coord+5, -5);
				glVertex3f(-5, coord+5, 5);
				glVertex3f(-5, 0, coord);
				glVertex3f(-5, 10, coord);

				//right
				glVertex3f(5, coord+5, -5);
				glVertex3f(5, coord+5, 5);
				glVertex3f(5, 0, coord);
				glVertex3f(5, 10, coord);

			} 
		glEnd();
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//square to indicate the C6 floor
	glBegin(GL_QUADS);
		glColor3f(0.9, 0.9, 0.9);
		glVertex3f(-5, -0.01, -5);
		glVertex3f(-5, -0.01, 5);
		glVertex3f(5, -0.01, 5);
		glVertex3f(5, -0.01, -5);
	glEnd();
}


void drawTheFPSGuy()
{
	float red[] = {1, 0, 0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
	glPushMatrix();
		glTranslatef(gCamera.mFPPos.x, gCamera.mFPPos.y, gCamera.mFPPos.z);
		glRotatef(gCamera.mFPYaw * 180.0 / 3.142, 0, 1, 0);
		glRotatef(gCamera.mFPPitch * 180.0 / 3.1412, 1, 0, 0);
		
		glEnable(GL_LIGHTING);
		
		//head!
		glPushMatrix();
			glTranslatef(-0, -0.2, 0);
			glutSolidSphere(0.4, 15, 15);
		glPopMatrix();

		//body!
		glPushMatrix();
			glTranslatef(0, -1.5, 0);
			glScalef(1.0, 2.0, 0.5);
			glutSolidCube(1.0);
		glPopMatrix();
		
		//legs!
		glPushMatrix();
			glTranslatef(-0.3, 1.5 - 5.5, 0);
			glScalef(0.3, 3.0, 0.3);
			glutSolidCube(1.0);
			glTranslatef(0.6/0.3, 0, 0);
			glutSolidCube(1.0);
		glPopMatrix();

		//axes!
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
			float length = 2.0;
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(length, 0, 0);
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, length, 0);
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, -length);
		glEnd();
	glPopMatrix();
	
}

void setLight(float x, float y, float z)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float lightPosition[] = {x, y, z, 1};
	glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
}



void display(void)
{
    // update and render the scene graph
	osg::Camera* currentCam = viewer->getCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	currentCam->setProjectionMatrixAsPerspective(60, aspect, 0.2, 200.0);
	currentCam->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
	gluPerspective(60, aspect, 0.2, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//apply our chosen matrix!	
	KMatrix view = gCamera.getViewMatrix();

	glLoadMatrixf(view.m);

	//use this time to get the head and wand matrices and pass them to our app.  
	//this only works because GLUT uses a single OpenGL context.  if you send matrices to a C6 
	//app while you're drawing, bad things will happen	
	
	//which one should we send?  If we're view-aligning particles, it's useful to send whichever one we're actually using for our camera
	//but if we're using it to track the user's head and interact with it, we should send the one representing the user...the first person view matrix
	

	//here's a cool trick!
	//the head matrix we get from Juggler is actually the INVERSE of the modelview matrix that would be needed
	//for a camera at that same position
	//Right now, we can grab GL's modelview matrix and use that, but matrix inversions are hard
	//Fortunately, since we're not doing any scaling, our modelview matrix is an orthogonal matrix
	//this means that its inverse is the same as its transpose!  so....
	VRBuilderApp::instance().setHeadMatrix(osg::Matrixf(gCamera.getViewMatrix(CameraController::FPS_VIEW).getInverse().m));
	

	//next we'll send the app a wand matrix based on the mouse position

	KMatrix wandMat = gCamera.getWandMatrix(KVec3(-1.0 + 2.0 * gMouseX / screenWidth, -1.0 + 2.0 * gMouseY / screenHeight, -2));
	VRBuilderApp::instance().setWandMatrix(osg::Matrixf(wandMat.m));

	currentCam->setViewMatrix(osg::Matrixf(view.m));
    if (viewer.valid()) viewer->frame();
	
	//go back to our view so we can draw some extras
	glViewport(0, 0, screenWidth, screenHeight);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	osg::Matrixf proj = 	currentCam->getProjectionMatrix();
	glMultMatrixf(proj.ptr());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(view.m);
	setLight(50, 50, 50);
	glEnable(GL_DEPTH_TEST);
	if(gCamera.getViewMode() != CameraController::FPS_VIEW)
		drawTheFPSGuy();
	glDisable(GL_LIGHTING);
	drawC6(false);
	drawStatus();
    // Swap Buffers
    glutSwapBuffers();
}

void reshape( int w, int h )
{
	screenWidth = w;
	screenHeight = h;
	aspect = 1.0 * screenWidth / screenHeight;
	printf("reshape to %i, %i\n", screenWidth, screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
    // update the window dimensions, in case the window has been resized.
    if (window.valid()) 
    {
        window->resized(window->getTraits()->x, window->getTraits()->y, w, h);
        window->getEventQueue()->windowResize(window->getTraits()->x, window->getTraits()->y, w, h );
    }
}

void mousebutton( int button, int state, int x, int y )
{
  	gCamera.mouseClick(button, state, x, y);
	y = screenHeight - y;
	gMouseX = x;
	gMouseY = y;
	if(button == GLUT_RIGHT_BUTTON)
		gRightClick = true;
	else
		gRightClick = false;
}


void mouseMotion(int x, int y)
{
	gCamera.mouseMotion(x, y);
	y = screenHeight - y;
	gMouseX = x;
	gMouseY = y;
}

void mouser(int button, int state, int x, int y)
{
	y = screenHeight - y;
	gMouseX = x;
	gMouseY = y;
	if(button == GLUT_RIGHT_BUTTON)
		gRightClick = true;
	else
		gRightClick = false;

	glutPostRedisplay();
}

void passiveMotion(int x, int y)
{
	gCamera.passiveMouse(x, y);
	y = screenHeight - y;
	gMouseX = x;
	gMouseY = y;
}


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		//handle key input
		case 'q': gCamera.setStrafeLeft(true);	break;
		case 'w': gCamera.setUp(true);	break;
		case 'e': gCamera.setStrafeRight(true);	break;
		case 'a': gCamera.setLeft(true);	break;
		case 's': gCamera.setDown(true);	break;
		case 'd': gCamera.setRight(true);	break;
		case 'z': gCamera.setLower(true);		break;
		case 'x': gCamera.setRaise(true);		break;
	
		case 'c': gShowC6 = !gShowC6; break;
		case ' ':	VRBuilderApp::instance().buttonInput(0, true);	break;		//space bar controls the main wand button
	
		case 'p':	gPaused = !gPaused;	break;		//pause/unpause
		//switch input modes with tab
		case '	':	gCamera.cycleViewMode();	break;
		case 'f':
			if(!gFullScreen)	glutFullScreen();
			else glutReshapeWindow(1024, 768);
			gFullScreen = !gFullScreen;
			break;
		case 27:	exit(1);	break;
		default:
            if (window.valid())
            {
                window->getEventQueue()->keyPress( (osgGA::GUIEventAdapter::KeySymbol) key );
                window->getEventQueue()->keyRelease( (osgGA::GUIEventAdapter::KeySymbol) key );
            }
            break;
    }
	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
	
	}
}

void keySpecial(int key, int x, int y)
{
	switch(key)
	{
		default: break;

	}
}

void timer(int bl)
{
	static int lastTime = glutGet(GLUT_ELAPSED_TIME);
	int thisTime = glutGet(GLUT_ELAPSED_TIME);
	float dt = 0.001 * ((float) thisTime - lastTime);
	lastTime = thisTime;
	gCamera.update(dt);
	
	if(!gPaused)
		VRBuilderApp::instance().update(dt);		//send the timestep to the app class
	glutTimerFunc(0, timer, 0);
	glutPostRedisplay();
}

void keyUpBoard(unsigned char key, int x, int y)
{
	switch(key)
	{
		//handle key input
		case 'q': gCamera.setStrafeLeft(false);	break;
		case 'w': gCamera.setUp(false);	break;
		case 'e': gCamera.setStrafeRight(false);	break;
		case 'a': gCamera.setLeft(false);	break;
		case 's': gCamera.setDown(false);	break;
		case 'd': gCamera.setRight(false);	break;
		case 'z': gCamera.setLower(false);		break;
		case 'x': gCamera.setRaise(false);		break;
		
		case ' ':	VRBuilderApp::instance().buttonInput(0, false);	break;		//space bar controls the main wand button
	}

	glutPostRedisplay();
}

void quitApp()
{
	VRBuilderApp::instance().shutdown();
	if(viewer) viewer = NULL;
}

int main( int argc, char **argv )
{
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA );
    glutInitWindowPosition( 100, 100 );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( argv[0] );
    glutDisplayFunc(display);
    glutReshapeFunc( reshape );
    glutMouseFunc( mousebutton );
    glutMotionFunc( mouseMotion);
    glutPassiveMotionFunc(passiveMotion);
	glutKeyboardFunc( keyboard );
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keySpecial);
	glutKeyboardUpFunc(keyUpBoard);
 
	// Setup glut input
	InteractionManager interaction_manager(InteractionManager::GLUT_INTERFACE);
	Input* keyboard_input = interaction_manager.inputForType(Input::KEYBOARD);
	if (keyboard_input) {
		GlutKeyboardInput* input = dynamic_cast<GlutKeyboardInput*>(keyboard_input);
		glutKeyboardFunc(input->keyboardDown_ptr());
	}
	
	// create the view of the scene.
    viewer = new osgViewer::Viewer;
    window = viewer->setUpViewerAsEmbeddedInWindow(100,100,800,600);
	VRBuilderApp::instance().init();
    viewer->setSceneData(VRBuilderApp::instance().getRoot());
    viewer->addEventHandler(new osgViewer::StatsHandler);
    viewer->realize();
	glutTimerFunc(100, timer, 0);
	atexit(quitApp);
	
    glutMainLoop();
    
    return 0;
}

/*EOF*/
