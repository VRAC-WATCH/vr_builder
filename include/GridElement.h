/**
 *  GridElement.h
 *  SOMVIZ
 *
 *  Created by Trevor Richardson on 10/4/13.
 *  Copyright 2013 Iowa State University. All rights reserved.
 */

#ifndef GRID_ELEMENT_H
#define GRID_ELEMENT_H

// Bump headers
#include <bump/String.h>

// OSG headers
#include <osg/Geode>
#include <osgText/Text>

// Local headers
#include "ui/BaseNode.h"

// Forward declaration
class ModelNode;

/** 
 * The GridElement class is used as the graphical display
 * of each grid element.
 */
class GridElement : public BaseNode
{
public:
    
    /** Default Constructor. */
    GridElement(bump::String nodeID = "");
	
	/** Constructor taking weak ref to a default GridElement geometry. */
    GridElement(ModelNode* node, bump::String nodeID = "");
	
    /** Destructor. */
    ~GridElement();
	
	/** Sets the model geometry for this GridElement. */
	void attachModel(ModelNode* modelNode);
	
	/** Highlights the node. */
	void highlight();
	
	/** Override the BaseNode node type. */
	inline const char* nodeType() const { return "GridElement"; }
	
	/** Set the nodes color decoration. */
	void setColor(const v4 color);
	inline const v4 color() const { return _color; }
	
	/** Sets the transparency level of the node. */
	void setTransparent(float value);
	
	/** Set the nodes color decoration. */
	void setId(const bump::String id) { _nodeID = id; }
	inline const bump::String& id() const { return _nodeID; }
	
	/** Set the nodes text label. */
	void setLabel(const bump::String label);
	inline const bump::String label() const { return _label->getText().createUTF8EncodedString(); }
	
	/** Override the setSelected method to handle decorating the element. */
	virtual void setSelected(bool isSelected);
	
protected:
	
	/** Sets up the textual label for the element. */
	void _initializeLabel();
	
	/** Sets up the material of the element. */
	void _setupMaterial();
	
	/** iVars. */
	v4								_color;
	bump::String					_nodeID;
	osg::ref_ptr<osgText::Text>		_label;
	osg::ref_ptr<osg::Geode>		_labelGeode;
	ModelNode*						_modelNode;
};

#endif  // End of GRID_ELEMENT_H
