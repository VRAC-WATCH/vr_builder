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
	osg::Matrix mat = _navigation_matrix->getMatrix();
	_root->addChild(_navigation_matrix);
	_navigation_matrix->addChild(_model_matrix);
	
	_root->getOrCreateStateSet()->setMode(GL_NORMALIZE, true);
	_lightsource = new osg::LightSource;
	_navigation_matrix->addChild(_lightsource.get());
	osg::Light* light = _lightsource->getLight();
	light->setDiffuse(osg::Vec4(0.7f, 0.7f, 0.7f, 1.0f));
	light->setSpecular(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAmbient(osg::Vec4(0.4f, 0.4f, 0.4f, 1.0f));
	light->setPosition(osg::Vec4(500.0f, 500.0f, 500.0f, 0.0f));

	projno=0;
	rebuilt = true;
	//add floor with configuration
	//_model_matrix->addChild(createFloor(_gridsize*_gridblocksize,_gridsize*_gridblocksize,osg::Vec3(0,0,0)));
}

Scene::~Scene(){
	_root->removeChildren(0,_root->getNumChildren());
}

void Scene::add(osg::Node* node){		
	_model_matrix->addChild(node);
}

void Scene::clear()
{
	// Clear out the old model scene
	bool removed = _navigation_matrix->removeChild(_model_matrix);	
	if (!removed) {
		std::cout << "Scene::clear() - Unable to properly clear model matrix." << std::endl;
		return;
	}

	_model_matrix = new osg::MatrixTransform;
	_navigation_matrix->addChild(_model_matrix);
}

void Scene::set_navigation_matrix(osg::Matrix mat){
	_navigation_matrix->setMatrix(mat);
}

void Scene::rebuild(){
	if(rebuilt)
		return;
	int num2remove = _model_matrix->getNumChildren() - projno;
	if(num2remove)
		_model_matrix->removeChildren(projno,num2remove);
	rebuilt = true;
}

void Scene::physicsmode(){
	if(rebuilt)
		projno = _model_matrix->getNumChildren();
	rebuilt = false;
}

//void Scene::moveHead(v3 direction)
//{
//	std::cout << "Moving the head" << std::endl;
//	osg::MatrixTransform* head_mt = _navigation_matrix.get();
//	head_mt->postMult(osg::Matrix::translate(direction));
//}
