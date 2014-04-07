#include "JugglerInterface.h"
#include "PaddleApp.h"


JugglerInterface::JugglerInterface(vrj::Kernel* kern, int& argc, char** argv) : vrj::OsgApp(kern)
{
	
}

JugglerInterface::~JugglerInterface()
{

}

void JugglerInterface::init()
{
	mHead.init("VJHead");		
	mWand.init("VJWand");

	mButton[0].init("VJButton0");
	mButton[1].init("VJButton1");
	mButton[2].init("VJButton2");
	mButton[3].init("VJButton3");
	mButton[4].init("VJButton4");
	mButton[5].init("VJButton5");
	 vrj::OsgApp::init();

}

void JugglerInterface::initScene()
{
	printf("______initing scene_____\n");
	 PaddleApp::instance().init();
	 _rootNode = PaddleApp::instance().getRoot();
}

void JugglerInterface::preFrame()
{	
	//trigger handling
	
	//if(mButton1->getData() == gadget::Digital::TOGGLE_ON)
		//ShaderManager::instance().reloadShaders();
	
	
	//printf("preframe end\n");
}

void JugglerInterface::latePreFrame()
{
	//printf("preframe begin\n");
	static double tLast = mHead->getTimeStamp().secd();
	double tNow = mHead->getTimeStamp().secd();
	double dt = tNow - tLast;
	tLast = tNow;
	
	//pass changes in button state on to the app
	for(int i = 0; i < 6; i++)
	{
		if(mButton[i]->getData() == gadget::Digital::TOGGLE_ON)
			PaddleApp::instance().buttonInput(i, true);
		else if(mButton[i]->getData() == gadget::Digital::TOGGLE_OFF)
			PaddleApp::instance().buttonInput(i, false);
	}

	PaddleApp::instance().update(dt);
	//attach the wand's matrix to the paint sprayer
	osg::Matrixf wandMatrix(mWand->getData().mData);
	PaddleApp::instance().setWandMatrix(wandMatrix);
	osg::Matrixf headMatrix	(mHead->getData().mData);
	PaddleApp::instance().setHeadMatrix(headMatrix);

}

void JugglerInterface::bufferPreDraw()
{
	glClearColor(0.5, 0.5, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	
	const osg::FrameStamp* frameStamp = (*sceneViewer)->getFrameStamp();
}

osg::Group* JugglerInterface::getScene()
{
	return _rootNode.get();
}

/*
// Override OsgApp::configSceneView to add FrameStamp to SceneView.
// This helps animations and shaders work properly in OSG.
void JugglerInterface::configSceneView(osgUtil::SceneView* newSceneViewer)
{
	 newSceneViewer->setDefaults();
  	 // newSceneViewer->setClearColor(osg::Vec4(0.7f, 0.7f, 0.8f, 0.0f));
	 
	 // Needed for stereo to work.
	 newSceneViewer->setDrawBufferValue(GL_NONE);

	 _frameStamp = new osg::FrameStamp;
	 newSceneViewer->setFrameStamp(_frameStamp.get());
}
*/

void JugglerInterface::draw()
{
	//printf("Begin draw\n");
	OsgApp::draw();
	//printf("end draw\n");

}
