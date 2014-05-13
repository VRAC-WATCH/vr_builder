/*
 *  viewerScene.h
 *  vrViewer
 *
 *  Created by WATCH on 8/18/09.
 *  Copyright 2009 Iowa State University. All rights reserved.
 *
 */

#ifndef _ARTCENTERSCENE_H_
#define _ARTCENTERSCENE_H_
#include "dice.h"

#define RAWWIDTH 576
#define RAWHEIGHT 576
#define DATAPATH "../Data/10-14-13/rawfile_3Ball"
#define START_IMAGE 0
#define END_IMAGE 27
#define NO_IMAGES END_IMAGE-START_IMAGE+1
#include<vector>
using namespace std;

class viewerScene
{
protected:
	// Constructor
	viewerScene();
	
public:
	// viewerScene is a singleton instance
	static viewerScene& instance() { static viewerScene scene;  return scene; }
	
	// Setup the scenegraph
	void setMaster(bool isMaster);
	void init();
	
	// Override KVObserver methods
	//void didChangeValueForKey(bool value, aq::String key);
	//void didChangeValueForKey(int value, aq::String key);
	//void didChangeValueForKey(double value, aq::String key);
	
	// Accessor for node matrices
	void setHeadMatrix(osg::Matrixf m);
	void setWandMatrix(osg::Matrixf m);
	void setNavigationMatrix(osg::Matrixf matrix);
	osg::Matrixf getHeadMatrix();
	osg::Matrixf getWandMatrix();
	osg::Matrixf getNavigationMatrix();

	// Accessors for scenegraph nodes
	osg::Group* getRootNode();
	osg::Group* getModels();
	
	// Error checking version of OSG's finddatafile function
	static std::string findDataFile(std::string name);
	
	// Update method called in every juggler latePreFrame and every GLUT display
	void update(double dt);
	
	// Update button info
	void buttonInput(int button, bool pressed);

	//Clear button info
	void clearbuttons();

	//Interaction effects
	void buttoninteraction();
		
private:
	osg::ref_ptr<osg::Group> _rootNode;
	osg::ref_ptr<osg::MatrixTransform> _navTrans;
	osg::ref_ptr<osg::Group> _models;
	osg::ref_ptr<osg::MatrixTransform> _wandTrans;
	osg::Matrixf _wandMatrix;
	osg::Matrixf _headMatrix;
	
	double _totalTime;
	double _step;
	bool _isMaster;

	Dice* _dice;
	vector<bool>buttons;
	bool buttonpressed;
	int frame;
	//double currTime;
};


#endif  // _ARTCENTERSCENE_H_
