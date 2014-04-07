//
//  GameObject.cpp
//  PaddleboatQuest
//
//  Created by Ken Kopecky II on 1/27/14.
//
//



#include "GameObject.h"


using namespace osg;

GameObject::GameObject()
{
	mRoot = new Group();
	mRoot->setName("GameObject Root");
	mPat = new PositionAttitudeTransform();
	mPat->setName("GameObject Pat");
	mRoot->addChild(mPat);
}

GameObject::~GameObject()
{
	//remove the root from everything that contains it
	if(mRoot)
		while(mRoot->getNumParents())
			mRoot->getParent(0)->removeChild(mRoot);

}

Matrixf GameObject::getTransform()
{
	//get our current transform as a matrix
	Matrixf currentXForm;
	Vec3 pos = getPos();
	mPat->getAttitude().get(currentXForm);
	currentXForm.ptr()[12] = pos.x();
	currentXForm.ptr()[13] = pos.y();
	currentXForm.ptr()[14] = pos.z();
	return currentXForm;

}

void GameObject::setTransform(Matrixf m)
{
	mPat->setAttitude(m.getRotate());
	mPat->setPosition(m.getTrans());
	
}

void GameObject::setForward(osg::Vec3 f)
{
	if(f.length() < 0.001)
	{
		printf("attempting to use tiny vector for forward!\n");
		return;
	}
	
	f.normalize();
	Vec3 currentForward = getForward();
	Matrixf m = Matrixf::rotate(currentForward, f);
	setTransform(getTransform() * m);
}

osg::Vec3 GameObject::getForward()
{
	Matrixf x = getTransform();
	return (Vec3(x.ptr()[8], x.ptr()[9], x.ptr()[10])*-1.0);
}
