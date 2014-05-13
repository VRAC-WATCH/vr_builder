/*
 *  JugglerInterface.h
 *  vrViewer
 *
 *  Created by WATCH on 8/18/09.
 *  Copyright 2009 Iowa State University All rights reserved.
 *
 */

#ifndef _JUGGLERINTERFACE_H_
#define _JUGGLERINTERFACE_H_

#include <vrj/vrjConfig.h>
#include <vrj/Draw/OSG/App.h>
#include <vrj/Draw/OpenGL/App.h>
#include <vrj/Draw/OpenGL/ContextData.h>
#include <plugins/ApplicationDataManager/UserData.h>

#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>

#include <gmtl/Vec.h>
#include <gmtl/Coord.h>
#include <gmtl/Xforms.h>
#include <gmtl/Math.h>
#include <gmtl/Matrix.h>
#include <gmtl/Point.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/VecOps.h>
#include <gmtl/Xforms.h>
#include <gmtl/Output.h>
#include <gmtl/Generate.h>

// Local headers
#include "VRBuilderApp.h"
#include "nav.h"
#include "myType.h"

// Cluster data object to check for the master
extern cluster::UserData< vpr::SerializableObjectMixin<myType> > mMyData;

// Forward declarations
class AppManager;

class JugglerInterface : public vrj::osg::App
{
	enum NAVIGATION_TYPE
	{
		WAND = 0,
		GAMEPAD = 1,
		WAND_AND_GAMEPAD = 2
	};

public:
	// Constructor/Destructor
    JugglerInterface(vrj::Kernel* kern, int & argc, char** argv, AppManager* appMan);
    virtual ~JugglerInterface();

	// Juggler draw loop methods
    virtual void init();
    virtual void initScene();
    virtual void preFrame();
    virtual void latePreFrame();
	virtual void draw();
    void bufferPreDraw();

	// Override OsgApp::configSceneView to add FrameStamp to SceneView.
	// This helps animations and shaders work properly in OSG.
	void configSceneView(osgUtil::SceneView* newSceneViewer);
	
	virtual osg::Group* getScene();

protected:
	
	/** Weak ref of application manager so that we can update it every frame. */
	AppManager*	_appManager;

  private:

	osg::ref_ptr<osg::FrameStamp> _frameStamp;
	gadget::PositionInterface  _wand;    /**< Positional interface for Wand position */
	gadget::PositionInterface  _head;    /**< Positional interface for Head position */
	
	// Controls the gamepad navigation calculations
	OsgNavigator _osgNavigator;
	
	// Gamepad digital interface
	gadget::DigitalInterface _button[10];
	
	// Gamepad analog interface	
	gadget::AnalogInterface _axis0;
	gadget::AnalogInterface _axis1;
	gadget::AnalogInterface _axis2;
	gadget::AnalogInterface _axis3;
	gadget::AnalogInterface _axis4;
	gadget::AnalogInterface _axis5;

	// Wand digital interface
	gadget::DigitalInterface _wandButtons[6];
	float _wandNavSpeed;
	bool _wandIsFlying;
	
	// Time variables
	bool	_initialTimeIsSet;
	double	_totalTime;
	double	_initialTime;
	double	_timeDelta;
	double	_navDeltaTime;
	double	_previousFrameTime;
	int		_frameCount;
	float 	_fadeInTime;
	float 	_fadeOutTime;	

	// Controls the navigation type
	NAVIGATION_TYPE _navType;

};

#endif
