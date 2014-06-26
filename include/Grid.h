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
	/** Private Variables*/
	int _gridsize;
	float _gridblocksize;
	int** _grid;
public:
	/** Constructor with default grid information*/
	Grid(int GridSize = 20 ,float GridBlockSize = 1.0f);
	~Grid();

	/** Add to grid using absolute positions*/
	void add(osg::Vec3 absposition);

	/** Return the cursor height for proper visualization*/
	int cursor_height(osg::Vec3 absposition);

	/** Resets all retained heights back to 0. */
	void reset();	
};
