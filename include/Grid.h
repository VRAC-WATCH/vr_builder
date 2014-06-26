/**
 *  Grid.h
 *  VRBuilder
 *
 *  Created by Bhaskar Bhattacharya on 10/6/14.
 *  Copyright 2014 Iowa State University. All rights reserved.
 */

//OSG HEADERS
#include <osg/Array>

//STL Headers
#include <string>
#include <vector>
using namespace std;

class Grid{

private:
	int _gridsize;
	float _gridblocksize;
	int** _grid;
public:
	Grid(int GridSize = 20 ,float GridBlockSize = 1.0f);
	~Grid();
	void add(osg::Vec3 );

	/** 
	 * Finds the closest grid point and height for the given position. 
	 * This just helps us stick to a grid instead of placing continuously.
	 */
	osg::Vec3 computeNearestGridPoint(osg::Vec3 position);

	int cursor_height(osg::Vec3);

	/** Resets all retained heights back to 0. */
	void reset();	
};
