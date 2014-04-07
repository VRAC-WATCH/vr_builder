//
//  GameObject.h
//  PaddleboatQuest
//
//  Created by Ken Kopecky II on 1/27/14.
//
//

#ifndef __PaddleboatQuest__GameObject__
#define __PaddleboatQuest__GameObject__

#include <osg/PositionAttitudeTransform>
#include <iostream>


//the base class for things that are in the game

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();					//destroy and remove all traces from the scenegraph

	//timestep update.  return false if this needs to be deleted and removed
	virtual bool update(float dt){return true;}
	
	//the root is a group, but it also contains a positionAttitudeTransform
	//just in case certain objects want to position things globally
	//in general, load models and put them in the pat.
	virtual osg::Group* getRoot()	{return mRoot;}
	
	
	//-----------some handy setters, getters, etceters
	//set/get position
	virtual osg::Vec3 getPos()	{return mPat->getPosition();}
	virtual void setPos(osg::Vec3 p)		{mPat->setPosition(p);}
	
	//set/get transform by matrix
	virtual osg::Matrixf getTransform();
	virtual void setTransform(osg::Matrixf mat);
	
	//set/get rotation by quat
	virtual osg::Quat getQuat()	{return mPat->getAttitude();}
	virtual void setQuat(osg::Quat q)	{mPat->setAttitude(q);}
	
	//----------other directioneering things
	
	//forward is the NEGATIVE Z-AXIS!
	//aim the front of this guy forward, attempting to preserve the other axes
	virtual void setForward(osg::Vec3 f);
	virtual osg::Vec3 getForward();
	
protected:
	osg::ref_ptr<osg::Group>						mRoot;
	osg::ref_ptr<osg::PositionAttitudeTransform>	mPat;		//used for positioning/orienting
};



#endif /* defined(__PaddleboatQuest__GameObject__) */
