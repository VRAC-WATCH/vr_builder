/**
 *  Grid.cpp
 *  VRBuilder
 *
 *  Created by Bhaskar Bhattacharya on 10/6/14.
 *  Copyright 2014 Iowa State University. All rights reserved.
 */
#include "Grid.h"

Grid::Grid(int GridSize,float GridBlockSize){
	_gridsize = GridSize;
	_gridblocksize = GridBlockSize;
	_grid = new int*[_gridsize];
	for(int i=0;i<_gridsize;i++){
		_grid[i] = new int[_gridsize];
		for(int j=0;j<_gridsize;j++)
			_grid[i][j] = 0;
	}
}

Grid::~Grid(){
	for(int i=0;i<_gridsize;i++)
		delete _grid[i];
	delete _grid;
}

void Grid::add(osg::Vec3 position){
	int gridx=(position.x()/_gridblocksize)+_gridsize/2;
	int gridy=(position.z()/_gridblocksize)+_gridsize/2;
	_grid[gridx][gridy]++;
}

int Grid::cursor_height(osg::Vec3 position){
	int gridx=(position.x()/_gridblocksize)+_gridsize/2;
	int gridy=(position.z()/_gridblocksize)+_gridsize/2;
	return (_grid[gridx][gridy]);
}