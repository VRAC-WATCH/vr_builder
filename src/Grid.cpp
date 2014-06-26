/**
 *  Grid.cpp
 *  VRBuilder
 *
 *  Created by Bhaskar Bhattacharya on 10/6/14.
 *  Copyright 2014 Iowa State University. All rights reserved.
 */
#include "Grid.h"

int _counter = 0;

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
	_counter++;
	std::cout<<"New Number is "<<_counter<<std::endl;
}

osg::Vec3 Grid::computeNearestGridPoint(osg::Vec3 position)
{
	// This is a bit of a hack right now as a quick way to
	// find valid positions of all of the highest points
	// on the grid when passed a point. We need something like
	// this in order to place the cursor with devices like
	// the wand.
	int gridx=(position.x()/_gridblocksize);
	float x_pos = gridx * _gridblocksize + _gridblocksize/2.0;
	int gridy=(position.z()/_gridblocksize);
	float z_pos = gridy * _gridblocksize + _gridblocksize/2.0;
	float height = cursor_height(position) * _gridblocksize + (float)_gridblocksize/2.0;

	return osg::Vec3(x_pos, height, z_pos);
}

int Grid::cursor_height(osg::Vec3 position){
	int gridx=(position.x()/_gridblocksize)+_gridsize/2;
	int gridy=(position.z()/_gridblocksize)+_gridsize/2;
	int height = _grid[gridx][gridy];
	//std::cout << "Height: " << height << std::endl;
	return height;
}

void Grid::reset()
{
	for(int i=0;i<_gridsize;i++)
		for(int j=0;j<_gridsize;j++)
			_grid[i][j] = 0;
}
