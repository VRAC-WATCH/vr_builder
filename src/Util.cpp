
/*
 *  Util.cpp
 *
 *  Created by Kenneth Kopecky on 5/22/13.
 *  Copyright 2013 Iowa State University. All rights reserved.
 *
 */

// OSG Headers
#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/FileUtils>
//#include <osgDB/ReadFile>
#include <osg/Material>

// STL Headers
#include <stdio.h>

// Project Headers
#include "Util.h"

using namespace osg;
namespace  Util
{

std::vector<std::string> _loggedErrors;

void printNodeHierarchy(osg::Node* node)
{
	if(!node)
	{
		printf("%s:  null node supplied!\n", __FUNCTION__);
		return;
	}
	std::string name = node->getName();
	static int recursion = 0;
	int maxRecursion = 10;
	
	if(recursion >= maxRecursion)
	{
		
		return;
	}
	recursion++;

	//append dashes to the name to show the hierarchical structure
	for(int i = 0; i < recursion - 1; i++)
		printf("-");
	printf("%s: %s", name.c_str(), node->className());
	
	//if we're not going to dive into this node, show its child count
	if(recursion >= maxRecursion)
	{
		if(node->asGroup())
		{
			int chillun = node->asGroup()->getNumChildren();		
		
			printf("--->%i children", chillun);
		}
	}
	printf("\n");
	
	//for geodes, show the drawables
	if(std::string("Geode") == node->className())
	{
		osg::Geode* gio = (osg::Geode*)(node);
		for (unsigned int j = 0; j < gio->getNumDrawables(); ++j)
		{
			for(int i = 0; i < recursion; i++)
				printf("-");
			
			osg::Drawable* drawable = gio->getDrawable(j);
			// Cast the drawable to a geometry object.
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(drawable);
			const osg::Vec3Array* verts = (const osg::Vec3Array*)(geom->getVertexArray());
			if(verts != NULL)
			printf("-Geometry--%i vertices\n", (int)verts->size());
		}
	}
	
	//if this isn't a group, grab its bounding box and return it
	if(!node->asGroup() || recursion >= maxRecursion)
	{ 
		recursion--;
		return;
	}
	//otherwise dive in, child by child
	else
	{
		int kids = node->asGroup()->getNumChildren();
		
		for(int i = 0; i < kids; i++)
		{
			printNodeHierarchy(node->asGroup()->getChild(i));
		}
	}
	recursion--;
	return;
}

osg::Node* findNodeWithName(osg::Group* group, std::string nameToFind)
{
	if(!group)
	{
		printf("%s:  null node supplied!\n", __FUNCTION__);
		return NULL;
	}
	
	std::string name = group->getName();
	if(name == nameToFind) return group;		//is this it?  then return it!
	
	//otherwise, dive in and look in our children
	int kids = group->getNumChildren();
	
	for(int i = 0; i < kids; i++)
	{
		osg::Group* g = group->getChild(i)->asGroup();
		if(g)
		{
			osg::Node* n = findNodeWithName(g, nameToFind);
			if(n) return n;
		}
	}
	return NULL;		//if we're here, we failed to find it ):  
}

void logError(const char* format, ...)
{
	char stringData[2024];
	va_list args;
	va_start(args, format);
	vsnprintf(stringData, 2024, format, args);
	int length = strlen(stringData);
	
	//remove \n's from the string cuz we're adding our own
	if(length > 0 && stringData[length-1] == '\n')
		stringData[length-1] = 0;


	printf("Error:  %s\n", stringData);
		
	_loggedErrors.push_back(stringData);
}

void printErrors()
{
	//let us know if there were no errors, just to be sure
	if(!_loggedErrors.size())
	{
		std::cout << "---No Problems Reported---" << std::endl;
		return;
	}
	
	
	//otherwise print out each error that we got
	std::cout << "-------------Runtime Errors and Warnings-------------" << std::endl;
	for(size_t i = 0; i < _loggedErrors.size(); i++)
	{
		std::cout << _loggedErrors[i] << std::endl;
	}
	
}

std::string findDataFile(std::string name)
{
	std::string found = osgDB::findDataFile(name);
//	if(found == "")
//		Util::logError("Couldn't find the file %s", name.c_str());
	return found;
}

MatrixTransform* loadModel(std::string name, float scale, float rotX, float rotY, float rotZ, osg::Vec3 translate)
{
//	Node* n = osgDB::readNodeFile(findDataFile(name));
//	if(!n) return NULL;
//
//	MatrixTransform* m = new MatrixTransform();
//	m->addChild(n);
//	
//	Matrix mat = Matrix::scale(scale, scale, scale);
//	mat = mat * Matrix::rotate(rotX / 57.296, Vec3(1, 0, 0));
//	mat = mat * Matrix::rotate(rotY / 57.296, Vec3(0, 1, 0));
//	mat = mat * Matrix::rotate(rotZ / 57.296, Vec3(0, 0, 1));
//	mat = mat * Matrix::translate(translate);
//	m->setMatrix(mat);
//	return m;
}

void setTint(osg::Node* node, Vec4 color)
{
	if(!node)
	{
//		printf("%s:  null node supplied!\n", __FUNCTION__);
		return;
	}
	
	//look for materials in the node and use that if they're there
	StateSet* ss = node->getStateSet();
	if(ss)
	{
		printf("found a stateset\n");
		osg::Material* m = (osg::Material*)(ss->getAttribute(osg::StateAttribute::MATERIAL));
		if(m)
		{
			Vec4 current = m->getDiffuse(Material::FRONT);
			printf("found a material:  %.2f, %.2f, %.2f\n", current.x(), current.y(), current.z());
			m->setDiffuse(osg::Material::FRONT_AND_BACK, color);
		}
	}
	
	//for geodes, go into the drawables
	if(std::string("Geode") == node->className())
	{
		osg::Geode* gio = (osg::Geode*)(node);
		for (unsigned int j = 0; j < gio->getNumDrawables(); ++j)
		{
			
			osg::Drawable* drawable = gio->getDrawable(j);

			// Cast the drawable to a geometry object.
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(drawable);
			if(geom)
			{
				
				//and stick in a new color array containing our single color
				Vec4Array* colors = new Vec4Array();
				colors->push_back(color);
				geom->setColorArray(colors);
				
				//this tells the geometry to use only one element of the array for all the color
				geom->setColorBinding(Geometry::BIND_OVERALL);
				geom->dirtyDisplayList();

				
				
			}
		}
	}
	
	//otherwise dive in, child by child
	else if(node->asGroup())
	{
		int kids = node->asGroup()->getNumChildren();
		
		for(int i = 0; i < kids; i++)
		{
			setTint(node->asGroup()->getChild(i), color);
		}
	}

	return;
}


}

ScopedBlock::ScopedBlock(std::string name)
{
	mBlockName = name;
	PROFILER.beginBlock(mBlockName); 
//	printf("begin %s\n", mBlockName.c_str());			
}

ScopedBlock::~ScopedBlock()
{
	PROFILER.endBlock(mBlockName);
//	printf("end %s\n", mBlockName.c_str());
}


