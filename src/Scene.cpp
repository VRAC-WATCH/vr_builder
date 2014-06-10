//
//  Scene.cpp
//  VRBuilder
//
//  Created by Bhaskar Bhattacharya on 5/13/14.
//
//

#include "Scene.h"

Scene::Scene(){

	/*Initialize the scene graph*/
	_root = new osg::Group;
	_model_matrix = new osg::MatrixTransform;
	_navigation_matrix = new osg::MatrixTransform;

	_root->addChild(_navigation_matrix);
	_navigation_matrix->addChild(_model_matrix);
	
	_root->getOrCreateStateSet()->setMode(GL_NORMALIZE, true);
	_lightsource = new osg::LightSource;
	_navigation_matrix->addChild(_lightsource.get());
	osg::Light* light = _lightsource->getLight();
	light->setDiffuse(osg::Vec4(0.7f, 0.7f, 0.7f, 1.0f));
	light->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAmbient(osg::Vec4(0.05f, 0.05f, 0.05f, 1.0f));
	light->setPosition(osg::Vec4(0.0f, 100.0f, 0.0f, 0.0f));

	//add floor with configuration
	//_model_matrix->addChild(createFloor(_gridsize*_gridblocksize,_gridsize*_gridblocksize,osg::Vec3(0,0,0)));
}

Scene::~Scene(){
	_root->removeChildren(0,_root->getNumChildren());
}

void Scene::set_navigation_matrix(osg::Matrix mat){
	_navigation_matrix->setMatrix(mat);
}

void Scene::add(osg::Node* node){
	_model_matrix->addChild(node);
}



//void Scene::moveHead(v3 direction)
//{
//	std::cout << "Moving the head" << std::endl;
//	osg::MatrixTransform* head_mt = _navigation_matrix.get();
//	head_mt->postMult(osg::Matrix::translate(direction));
//}