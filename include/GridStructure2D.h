/*
 *  Group.h
 *
 *	Created by Trevor Richardson on 9/27/2013.
 *  Copyright 2013 Iowa State University. All rights reserved.
 *
 */

#ifndef GRID_STRUCTURE_2D_H
#define GRID_STRUCTURE_2D_H

// Local headers
#include "ui/BaseNode.h"
#include "ui/GridElement.h"
#include "ui/Group.h"
#include "ui/ModelNode.h"


/** A group base node which can contains other groups and parts. */
class GridStructure2D : public Group
{
public:

	/** Constructor. */
	GridStructure2D();
	
	/** Constructor with manual setup. */
	GridStructure2D(const unsigned int& gridWidth, const unsigned int& gridHeight,
					const float& horizontalSpacing, const float& verticalSpacing,
					const float& alternateRowSpacingPercentage=0.0, const bool& automateSpacing=false,
					const osg::ref_ptr<ModelNode> model=NULL);
		
	/** Destructor. */
	~GridStructure2D();

	/** Intializes the grid structure. */
	void buildGrid();
	
	/** Override the BaseNode node type. */
	inline const char* nodeType() const { return "GridStructure2D"; }
	
	/** 
	 * Accessor for whether to automate the spacing of the grid
	 * using the model's bounds
	 */
	void setAutomatedSpacing(bool isAutomated);
	
	/** Set a single color for each grid element. */
	void setGridColor(v4 color);
	
	/** Set a separate color for each grid element. */
	void setElementColors(std::vector<v4> colors);
	
	/** Set a separate id for each grid element. */
	void setElementIds(std::vector<bump::String> nodeIds);
	
	/** Set the name of the grid. */
	inline void setId(const bump::String& id) { _gridId = id; }
	inline const bump::String& id() const { return _gridId; }
	
	/** Set the text label for each grid element. */
	void setTextLabels(std::vector<bump::String> labels);
	
	/** Accessor for the total number of elements in the grid. */
	inline const int elementCount() const { return _elements.size(); }
	
	/** Accessor for the grid element objects. */
	inline std::vector<osg::ref_ptr<GridElement> > elements() { return _elements; }
	
	
protected:
	
	/** Grid iVars. */
	float						_alternateRowSpacingPercentage;
	unsigned int				_gridHeight;
	unsigned int				_gridWidth;
	float						_horizontalSpacing;
	bool						_isSpacingAutomated;
	float						_verticalSpacing;
	
	/** General iVars. */
	osg::ref_ptr<ModelNode>						_elementModel;
	std::vector<osg::ref_ptr<GridElement> >		_elements;
	bump::String								_gridId;
};

#endif	// End of GRID_STRUCTURE_2D_H
