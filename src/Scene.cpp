//
//  Scene.cpp
//  VRBuilder
//
//  Created by Bhaskar Bhattacharya on 5/13/14.
//
//

#include "Scene.h"

Scene::Scene(int GridSize){
	_root = new osg::Group;
	_model_matrix = new osg::MatrixTransform;
	_cursor_matrix = new osg::MatrixTransform;
	_navigation_matrix = new osg::MatrixTransform;

	_root->addChild(_navigation_matrix);
	_navigation_matrix->addChild(_model_matrix);
	_navigation_matrix->addChild(_cursor_matrix);

	_gridsize = GridSize;
	_grid = new int*[_gridsize];
	for(int i=0;i<_gridsize;i++)
		_grid[i]=new int[_gridsize];
}

void Scene::set_navigation_matrix(osg::Matrix mat){
	_navigation_matrix->setMatrix(mat);
}

void Scene::set_cursor(osg::Node* node){
	_cursor_matrix->addChild(node);
}

void Scene::set_cursor_position(osg::Matrix pos){
	_cursor_matrix->setMatrix(pos);
}

int Scene::add_model_node(osg::Node* model){
	_model_matrix->addChild(model);

	return 1;
}

void Scene::remove_model_node(int id){

}

void Scene::update(double){

}