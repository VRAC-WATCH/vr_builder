/*
 *  GridStructure2D.cpp
 *
 *	Created by Trevor Richardson on 9/27/2013.
 *  Copyright 2013 Iowa State University. All rights reserved.
 *
 */

// Bump headers
#include <bump/Log.h>

// Local headers
#include "ui/GridStructure2D.h"
#include "ui/ModelNode.h"
#include "ui/VertexPoller.h"


static const bump::String PRINTOUT_PREFIX = "GridStructure2D :";

#ifdef __APPLE__
#pragma mark -
#pragma mark Initialization
#endif

GridStructure2D::GridStructure2D()
{
	// Setup all the common BaseNode properties
	BaseNode::initialize();
	
	// Create a two-dimensional grid of objects
	_alternateRowSpacingPercentage = 0.0;
	_gridWidth = 10;
	_gridHeight = 10;
	_horizontalSpacing = 200.0;
	_verticalSpacing = 200.0;
	
	// Default will be to space the models using their bounding box
	_isSpacingAutomated = false;
	
	buildGrid();
}

GridStructure2D::GridStructure2D(const unsigned int& gridWidth, const unsigned int& gridHeight,
								 const float& horizontalSpacing, const float& verticalSpacing,
								 const float& alternateRowSpacingPercentage,
								 const bool& automateSpacing,
								 const osg::ref_ptr<ModelNode> model)
{
	// Setup all the common BaseNode properties
	BaseNode::initialize();
	
	// Create a two-dimensional grid of objects
	_alternateRowSpacingPercentage = alternateRowSpacingPercentage;
	_elementModel = model;
	_gridWidth = gridWidth;
	_gridHeight = gridHeight;
	_horizontalSpacing = horizontalSpacing;
	_verticalSpacing = verticalSpacing;
	
	// Default will be to space the models using their bounding box
	_isSpacingAutomated = automateSpacing;
	
	buildGrid();
}

GridStructure2D::~GridStructure2D()
{
	bumpDEBUG_P(PRINTOUT_PREFIX, "Destructor Called");
}

void GridStructure2D::buildGrid()
{
	// Make sure there is a model actually loaded
	if (_isSpacingAutomated && !_elementModel.valid())
	{
		bumpWARNING_P(PRINTOUT_PREFIX, "Must have model loaded for automated spacing..");
		_isSpacingAutomated = false;
	}
	else if (_isSpacingAutomated)
	{
		bb model_bounds = VertexPoller::getBoundingBox(_elementModel);
		_verticalSpacing = model_bounds.yMax() - model_bounds.yMin();
		_horizontalSpacing = model_bounds.xMax() - model_bounds.xMin();
	}
		
	// Build and place each neuron into a 2d grid structure
	for (unsigned int i=_gridHeight; i>0; --i)
	{
		float vertical_position = _verticalSpacing * i;
		
		for (unsigned int j=0; j<_gridWidth; ++j)
		{
			float horizontal_position = _horizontalSpacing * j;
			
			// Offset alternate rows by the set amount (default=0)
			if (!(i % 2))
				horizontal_position += _alternateRowSpacingPercentage * _horizontalSpacing;
			
			// Build the transform to place the neuron
			osg::Matrix matrix;
			matrix.setTrans(osg::Vec3f(horizontal_position, vertical_position, 0.0));
			
			// Add the neuron to the scene
			osg::ref_ptr<GridElement> element = new GridElement(_elementModel);
			element->setMatrix(matrix);
			_elements.push_back(element);
			addChild(element);
		}
	}
}


#ifdef __APPLE__
#pragma mark -
#pragma mark Accessor Methods
#endif

void GridStructure2D::setAutomatedSpacing(bool isAutomated)
{
	_isSpacingAutomated = isAutomated;
	if (_isSpacingAutomated && !_elementModel.valid())
	{
		bumpWARNING_P(PRINTOUT_PREFIX, "Must have model loaded for automated spacing.. Returning");
		_isSpacingAutomated = false;
	}
}

void GridStructure2D::setGridColor(v4 color)
{
	for (unsigned int i=0; i<_elements.size(); ++i)
	{
		_elements.at(i)->setColor(color);
	}
}

void GridStructure2D::setElementColors(std::vector<v4> colors)
{
	if (colors.size() != _elements.size()) {
		bumpDEBUG_P(PRINTOUT_PREFIX, "Size of color vector does not match node count.. Returning");
		return;
	}
	
	for (unsigned int i=0; i<_elements.size(); ++i) {
		_elements.at(i)->setColor(colors[i]);
	}
}

void GridStructure2D::setElementIds(std::vector<bump::String> ids)
{
	if (ids.size() != _elements.size()) {
		bumpDEBUG_P(PRINTOUT_PREFIX, "Size of id vector does not match node count.. Returning");
		return;
	}
	
	for (unsigned int i=0; i<_elements.size(); ++i) {
		_elements.at(i)->setId(ids[i]);
	}
}

void GridStructure2D::setTextLabels(std::vector<bump::String> labels)
{
	if (labels.size() != _elements.size()) {
		bumpDEBUG_P(PRINTOUT_PREFIX, "Size of label vector does not match node count.. Returning");
		return;
	}
	
	for (unsigned int i=0; i<_elements.size(); ++i) {
		_elements.at(i)->setLabel(labels[i]);
	}
}