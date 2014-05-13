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
	_navigation_matrix = new osg::MatrixTransform;

	_root->addChild(_navigation_matrix);
	_navigation_matrix->addChild(_model_matrix);

	_gridsize = GridSize;
	_grid = new int*[_gridsize];
	for(int i=0;i<_gridsize;i++)
		_grid[i]=new int[_gridsize];
}