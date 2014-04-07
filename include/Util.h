
/*
 *  Util.h
 *
 *  Created by Kenneth Kopecky on 5/22/13.
 *  Copyright 2013 Iowa State University. All rights reserved.
 *
 */

#ifndef __UTIL__
#define __UTIL__

#include <iostream>
#include <osg/MatrixTransform>
#include "quickprof.h"

//for tracking crashes when we don't have an easily accessible stacktrace
//uncomment this line for tons of info to be dumped into the console and/or log file
//#define TraceLine(s) std::cout << "[" << __FILE__ << ":" << __LINE__ << "]" << s << std::endl;
#define TraceLine(s) 



//			For profiling, put __FUNCTION_HEADER__ at the top of major functions
//			This can be called dozens of times per frame without any real overhead
//			but void calling it, say, 50,000 times per second.  That'll slow us down
//			You can also use __FUNCTION_HEADER2__(functionName) if the functio name isn't specific enough
//			finally, you can do ScopedBlock(name) inside {} to time individual parts of functions easily

#define __FUNCTION_HEADER__ ScopedBlock __SCOPER__(__FUNCTION__);  
#define __FUNCTION_HEADER2__(name) ScopedBlock __SCOPER__(std::string(__FUNCTION__)+name);  


//starts a block and then stops it when it goes out of scope
//useful for profiling individual functions
	class ScopedBlock
	{
	public:
		ScopedBlock(std::string name);
		~ScopedBlock();
		std::string mBlockName;
	};



//some utility functions!  We'll add more as we need them
namespace Util
{
	//error reporting function.  Re-prints important messages when the program is about to shut down
	//use this from anywhere in the program for when something happens that needs attention
	void logError(const char* format, ...);
	
	void printNodeHierarchy(osg::Node* n);							//for looking at a node's structure within your app

	osg::Node* findNodeWithName(osg::Group* g, std::string name);	//find a node in this group with the given name

	std::string findDataFile(std::string name);						//error reporting version of OSG"s finddatafile function
	
	//this loads a model with the given name, and scales, rotates, and translates it (in the order of the arguments) to a useable state
	//handy for importing downloaded models which are usually way way way too big
	//(rotations are in degrees!)
	osg::MatrixTransform*		loadModel(std::string name, float scale, float rotX = 0, float rotY = 0, float rotZ = 0, osg::Vec3 translate = osg::Vec3());

	//print out logged errors.  This is usually called right before the program exits
	void printErrors();
	
	/*//replace all colors in this node with the specified one
	//useful for if a model loads up grey
	//or for tinting/darkening models
	void setTint(osg::Node* n, osg::Vec4 color);
	*/

};
#endif /* defined(__OSGSample__Util__) */

