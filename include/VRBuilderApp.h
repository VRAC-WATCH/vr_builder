/*
 *  VRBuilderApp.h
 *  Hybrid OSG Template
 *
 *  Created by Kenneth Kopecky on 8/15/09.
 *  Updated by Trevor Richardson on 4/4/2014.
 *
 */

#ifndef VR_BUILDER_APP_H
#define VR_BUILDER_APP_H

// OSG headers
#include <osg/Group>
#include <osg/Geode>
#include <osg/LightSource>
#include <osg/MatrixTransform>

#include "SceneManager.h"
#include "InteractionManager.h"

/** Class description here. */
class VRBuilderApp{
	
public:
	
	enum ButtonState {OFF, ON, TOGGLE_OFF, TOGGLE_ON};		//the four possible states of your standard button
	static VRBuilderApp& instance()	{static VRBuilderApp a;  return a;}				//singleton instance
	void init();
	void setHeadMatrix(osg::Matrixf m);
	void setWandMatrix(osg::Matrixf m);
	void setNavigationMatrix(osg::Matrixf matrix);
	osg::Matrixf getHeadMatrix()		{return mHeadMatrix;}
	osg::Matrixf getWandMatrix()		{return mWandMatrix;}
	osg::Matrixf getNavigationMatrix()	{return mNavigation->getMatrix();}
	void update(float dt);										//timestep update
	osg::Group* getRoot() {return mRoot.get();}			//get our root scene node
	osg::Group* getModelGroup()	{return mModelGroup.get();}
	void buttonInput(unsigned int button, bool pressed);

	void setIsMaster(bool m)	{mIsMaster = m;}
	bool isMaster()				{return mIsMaster;}
	void drawStatus();									//draw run-time info, like frame rate, on the head node
	void handleArguments(int* argc, char** argv);		//process command line arguments
	void shutdown();									//clean up before exiting
	
	
protected:

	//put very little in the constructor so we don't risk a recurisive call
	VRBuilderApp()
	{
		mIsMaster = true; mTargetTime = 0; mTotalTime = 0; mTimeStep = 0.01;
	}
	
	//update our calculated frame rate
	void updateFrameRate(float dt);

	osg::ref_ptr<osg::Group> mRoot;								//root of our scenegraph
	osg::ref_ptr<osg::MatrixTransform> mNavigation;				//navigation matrix
	osg::ref_ptr<osg::Group> mModelGroup;						//this is where we put things into the app!
	osg::Matrixf mWandMatrix;
	osg::Matrixf mHeadMatrix;
	osg::ref_ptr<osg::LightSource> mLightSource;
	void deToggleButtons();									//remove toggle status from our buttons after each frame to prevent events from happening repeatedly
	static const int NUMBUTTONS = 6;
	
	int mButtons[NUMBUTTONS];

	osg::MatrixTransform* mWandXForm;
	SceneManager* _scenemanager;

	//timekeeping
	float mTargetTime;
	float mTotalTime;
	float mTimeStep;
	float mAvgFrameRate;

	//needed for clusteredness
	bool mIsMaster;										//is this the master node of the cluster?

	/** TODO: Change when we add the AppManager. */
	InteractionManager* interaction_manager;

public:
	Input* pass_keyboard_input();
};

#endif /** End of VR_BUILDER_APP_H. */

