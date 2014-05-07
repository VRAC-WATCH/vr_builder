/*
 *  VRBuilderApp.cpp
 *  Hybrid OSG Template
 *
 *  Created by Kenneth Kopecky on 8/15/09.
 *  Updated by Trevor Richardson on 4/4/2014.
 *
 */
#include <stdlib.h>
// GL headers
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#include <glut.h>
#endif

// OSG headers
#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/FileUtils>

// Local headers
#include "VRBuilderApp.h"
#include "XML/XML.h"
#include "Util.h"
#include "Builder.h"

void VRBuilderApp::init()
{
	PROFILER.init();		//init profiling
//	__FUNCTION_HEADER__

	//set up our OSGDB search paths
	osgDB::getDataFilePathList().push_back("data");
	osgDB::getDataFilePathList().push_back("data/models");
	osgDB::getDataFilePathList().push_back("data/shaders");
	
	mTotalTime = 0;
	mRoot = new osg::Group;
	mNavigation = new osg::MatrixTransform;
	mRoot->addChild(mNavigation.get());
	mRoot->getOrCreateStateSet()->setMode(GL_NORMALIZE, true);
	mLightSource = new osg::LightSource;
	mNavigation->addChild(mLightSource.get());
	mAvgFrameRate = 30;
	mModelGroup = new osg::Group;
	mNavigation->addChild(mModelGroup.get());

	osg::Light* light = mLightSource->getLight();
	light->setDiffuse(osg::Vec4(0.7f, 0.7f, 0.7f, 1.0f));
	light->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAmbient(osg::Vec4(0.05f, 0.05f, 0.05f, 1.0f));
	light->setPosition(osg::Vec4(100.0f, 100.0f, 100.0f, 0.0f));

	mWandXForm = new osg::MatrixTransform;
	mModelGroup->addChild(mWandXForm);

	//Added to test
	Builder::instance().init();
	mRoot->addChild(Builder::instance().createFloor(20,20,osg::Vec3(0,0,0)));
	SceneCommand scenecommand;
	scenecommand.blockSize=osg::Vec3(1,1,1);
	scenecommand.color=osg::Vec4(1,0,0,1);
	scenecommand.position=osg::Vec3(0,5,-7.5);
	scenecommand.command=SceneCommand::CommandType::ADD_BLOCK;
	scenecommand.textureFileName="../resources/Metalic_texture.bmp";
	mRoot->addChild(Builder::instance().createBlock(scenecommand));
}


void VRBuilderApp::buttonInput(unsigned int button, bool pressed)
{
//	__FUNCTION_HEADER__
	if(button < NUMBUTTONS)
	{
		mButtons[button] = pressed ? TOGGLE_ON : TOGGLE_OFF;
	}

}

void VRBuilderApp::update(float dt)
{
	//__FUNCTION_HEADER__ is for built-in, low-overhead time profiling
	//profile results are printed to the console when the app exits

//	__FUNCTION_HEADER__

	mTargetTime += dt;
	while(mTotalTime < mTargetTime)
	{
		mTotalTime += mTimeStep;
		//process navigation, etc
		if(mButtons[0] == ON)
		{
			osg::Vec3 direction(mWandMatrix.ptr()[8], mWandMatrix.ptr()[9],mWandMatrix.ptr()[10]);
			mNavigation->setMatrix(mNavigation->getMatrix() * osg::Matrix::translate(direction * dt * 4.0));
		}
		//process shooting
		if(mButtons[1] == ON){
			std::cout<<"Button 1 Pressed"<<std::endl;
			mRoot->addChild(Builder::instance().throwProjectile(osg::Vec3(0,1,0),osg::Vec3(0,0,-0.5)));
			mButtons[1] = OFF;
		}
		deToggleButtons();			//it's important that this be called every frame
	}
	Builder::instance().update(dt);
//	PROFILER.endCycle();		//needed for time profiling
}

void VRBuilderApp::deToggleButtons()
{
	//remove any toggleness from the buttons.  this is important if we want to attach events to the moment a button is pressed
	for(int i = 0; i < NUMBUTTONS; i++)
		if(mButtons[i] == TOGGLE_ON)	mButtons[i] = ON;
		else if(mButtons[i] == TOGGLE_OFF) mButtons[i] = OFF;
}

//transform the head and wand matrix into navigation space (optional, depends on how you're using them)
void VRBuilderApp::setHeadMatrix(osg::Matrixf mat)
{
	mHeadMatrix = mat*mNavigation->getInverseMatrix();
}

void VRBuilderApp::setWandMatrix(osg::Matrixf mat)
{
	mWandMatrix = mat*mNavigation->getInverseMatrix();
	mWandXForm->setMatrix(osg::Matrixf::scale(0.25, 0.125, 1.0)*mWandMatrix);
}

void drawStringOnScreen(int x, int y, const char* format, ...)
{
	char stringData[2024];
	//va_list args;
	//va_start(args, format);
	//vsnprintf(stringData, 2024, format, args);
	
	//find the viewport size so we can properly size everything
	int vport[4];
	glGetIntegerv(GL_VIEWPORT, vport);
	int screenWidth = vport[2];
	int screenHeight = vport[3];
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			glOrtho(0, screenWidth, 0, screenHeight, -1, 1);

			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glRasterPos3i(x, screenHeight - y, 0);
			
			for(int i=0; i<2024 && stringData[i] != 0; i++ )
			{
				glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, stringData[i] );
			}
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


}


void VRBuilderApp::drawStatus()
{	
	if(!mIsMaster) return;		//only the master node draws stats, or cluster nodes could break
//	__FUNCTION_HEADER__
#ifdef USE_VRJ
	int argc = 3;
	//pass fake args to GLUT so it uses the right display
	char* argv[] = {(char*)"SampleApp", (char*)"-display", (char*)":0.0"};
	static bool once = true;
	if(once)
	{
		std::cout << "initing glut..." << std::endl;
		glutInit(&argc, argv);
		once = false;
	}

#endif
	glColor3f(1, 1, 1);
	int rowHeight = 20;
	int row = 2;

	drawStringOnScreen(20, rowHeight*row++, "Frame Rate:  %.2f", mAvgFrameRate);
	drawStringOnScreen(20, rowHeight * row++, "Buttons:  %i, %i, %i, %i, %i, %i", mButtons[0], mButtons[1], mButtons[2], mButtons[3], mButtons[4], mButtons[5]);
	drawStringOnScreen(20, rowHeight * row++, "Head at:  %.2f, %.2f, %.2f", mHeadMatrix.ptr()[12], mHeadMatrix.ptr()[13], mHeadMatrix.ptr()[14]);
	drawStringOnScreen(20, rowHeight * row++, "Wand at:  %.2f, %.2f, %.2f", mWandMatrix.ptr()[12], mWandMatrix.ptr()[13], mWandMatrix.ptr()[14]);

}

void VRBuilderApp::updateFrameRate(float dt)
{
	if(dt > 0 && dt < 0.05)		//don't update our framerate for crazy-ass timesteps
	{
		static float tSinceUpdate = 0.0;
		static int framesSinceUpdate = 0;
		tSinceUpdate += dt;
		framesSinceUpdate++;
		if(tSinceUpdate > 0.5 && framesSinceUpdate > 5)		//update every half second or so
		{
			float newAvg = (float)framesSinceUpdate / tSinceUpdate;
			mAvgFrameRate += (newAvg - mAvgFrameRate) * 0.5;
			tSinceUpdate = 0;
			framesSinceUpdate = 0;
		}
	}
}

void VRBuilderApp::handleArguments(int* argc, char **argv)
{
	int num = 1;		//like the 'i' below, but doesn't change when an arg is handled and is used for clear output in this function
	for(int i = 1; i < *argc; i++)
	{
		std::string arg(argv[i]);

		bool handled = false;
//		if(XML::CICompare(arg, "--vrjslave"))
//		{
//			mIsMaster = false;
////			handled = true;
//		}
//		else if(XML::CICompare(arg, "--vrjmaster"))
//		{
//			mIsMaster = true;
////			handled = true;
//		}

		printf("Arg %i:  %s (%s)\n", num++, arg.c_str(), handled ? "Handled" : "Not Handled");
		
		//pull it out of the list if we handled the argument
		if(handled)
		{
			for(int j = i; j < *argc-1; j++)
			{
				argv[j] = argv[j+1];
			}
			i--;			//and go back an index so we'll look at the next argument
			(*argc)--;		//and decrement the number of args
		}
	}

}

void VRBuilderApp::shutdown()
{
	//print out our profiler summary and important errors
	std::string prof = PROFILER.getSummary();
	printf("Final Profiler Summary:  \n%s\n", prof.c_str());
//	Util::printErrors();
}

