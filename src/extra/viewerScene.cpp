/*
 *  viewerScene.cpp
 *  vrViewer
 *
 *  Created by WATCH on 8/18/09.
 *  Copyright 2009 Iowa State University. All rights reserved.
 *
 */

#include "viewerScene.h"

extern float _navSpeed;
extern float _rotSpeed;

viewerScene::viewerScene()
{
	// Create the device and network input controllers
	//_deviceInputController = new DeviceInputController();

	// Initialize the audio manager and audio flags
	_isMaster = false;
	_totalTime = 0.0;
	_wandTrans = new osg::MatrixTransform;
	buttons.resize(15);
	clearbuttons();
	buttonpressed=false;
	_rootNode = new osg::Group;
	_dice = new Dice;
}

void viewerScene::setMaster(bool isMaster)
{
	_isMaster = isMaster;
}

void viewerScene::init()
{	
	
	_navTrans = new osg::MatrixTransform;
	// Setup the scenegraph hierarchy
	_rootNode->addChild(_navTrans.get());
	_navTrans->addChild(_dice->getRoot());
	frame=0;
	//currTime=0;
}

/*
void viewerScene::didChangeValueForKey(double value, aq::String key)
{
	if (key == "Update_Wand_Matrix")
	{
		osg::Vec3 direction(_wandMatrix.ptr()[8], _wandMatrix.ptr()[9],_wandMatrix.ptr()[10]);
		_navTrans->setMatrix(_navTrans->getMatrix() * osg::Matrix::translate(direction * value * 40.0));
	}
	else if (key == "Decrease_Nav_Speed")
	{
		if (_navSpeed > 0.02)
			_navSpeed -= 0.05;
		if (_rotSpeed < 200)
			_rotSpeed += 5;
	}
	else if (key == "Increase_Nav_Speed")
	{
		_navSpeed += 0.05;
		if (_rotSpeed >= 10)
		_rotSpeed -= 5;
	}
}
*/

void viewerScene::setHeadMatrix(osg::Matrixf mat)
{
	// Transform the head and wand matrix into navigation 
	// space (optional, depends on how you're using them)
	_headMatrix = mat * _navTrans->getInverseMatrix();
}

void viewerScene::setWandMatrix(osg::Matrixf mat)
{
	_wandMatrix = mat * _navTrans->getInverseMatrix();
	_wandTrans->setMatrix(osg::Matrixf::scale(0.25, 0.125, 1.0) * _wandMatrix);
}

osg::Matrixf viewerScene::getHeadMatrix()
{
	return _headMatrix;
}
osg::Matrixf viewerScene::getWandMatrix()
{
	return _wandMatrix;
}

void viewerScene::setNavigationMatrix(osg::Matrixf matrix)
{
	_navTrans->setMatrix(matrix);
}

osg::Matrixf viewerScene::getNavigationMatrix()
{
	return _navTrans->getMatrix();
}

osg::Group* viewerScene::getRootNode()
{
	return _rootNode.get();
}

osg::Group* viewerScene::getModels()
{
	return _models.get();
}

void viewerScene::clearbuttons(){
	for(int i=0;i<15;i++)
		buttons[i]=false;
}

void viewerScene::buttonInput(int button, bool pressed)
{
	//_deviceInputController->buttonInput(button, pressed);
	buttons[button]=pressed;
	//if(pressed==true)
		//std::cout<<"Button "<<button<<" pressed"<<std::endl;
}

void viewerScene::buttoninteraction(){
	if(buttons[1])
		_dice->buttonpress(1);
	if(buttons[3])
		_dice->buttonpress(3);
	clearbuttons();

}

void viewerScene::update(double dt)
{
	buttoninteraction();
	_dice->update(dt);
	_totalTime += dt;
}
