/**
 *  GridElement.cpp
 *  SOMVIZ
 *
 *  Created by Trevor Richardson on 10/4/13.
 *  Copyright 2013 Iowa State University. All rights reserved.
 */

// Bump headers
#include <bump/Log.h>

// OSG headers
#include <osg/CullFace>

// Local headers
#include "common/Settings.h"
#include "ui/ModelNode.h"
#include "ui/GeodeVisitor.h"
#include "ui/GridElement.h"
#include "ui/VertexPoller.h"

static const bump::String PRINTOUT_PREFIX = "GridElement : ";


#ifdef __APPLE__
#pragma mark -
#pragma mark Initialization
#endif

GridElement::GridElement(bump::String nodeID)
{
    bumpINFO_P(PRINTOUT_PREFIX, "Constructor called");
	
	_nodeID = nodeID;
	
	_initializeLabel();
	_setupMaterial();
}

GridElement::GridElement(ModelNode* modelNode, bump::String nodeID)
{
	bumpINFO_P(PRINTOUT_PREFIX, "Constructor called");
	
	_nodeID = nodeID;
	
	attachModel(modelNode);
	_initializeLabel();
	_setupMaterial();
}

GridElement::~GridElement()
{
    bumpINFO_P(PRINTOUT_PREFIX, "Destructor called");
}

void GridElement::_initializeLabel()
{
	// Allocate and add to node element as child
	bump::String fonts_path = SETTINGS()->fontsDirectoryPath();
	bump::String font(fonts_path + "inconsolata.ttf");
	osg::ref_ptr<osgText::Font> boldFont = osgText::readFontFile(font.toStdString());
	_label = new osgText::Text;
	_label->setAlignment(osgText::TextBase::CENTER_CENTER);
	_label->setCharacterSize(17.0f);
	_label->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
	_labelGeode = new osg::Geode;
	_labelGeode->addDrawable(_label);
	_label->setColor(v4(0,0,0,1));
	addChild(_labelGeode);
	
	// Override stateset of parent
	_labelGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::PROTECTED|osg::StateAttribute::OFF);
}

void GridElement::_setupMaterial()
{
	// Cull backfaces to get rid of an odd poly effect on the node model with blending
	osg::ref_ptr<osg::CullFace> cull = new osg::CullFace;
	cull->setMode(osg::CullFace::BACK);
	_stateSet->setAttributeAndModes(cull, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);
}

void GridElement::attachModel(ModelNode *modelNode)
{
	_modelNode = modelNode;
	addChild(_modelNode);
}

void GridElement::highlight()
{
	v4 color(1.0, 1.0, 1.0, 1.0);
	_material->setAmbient(osg::Material::FRONT_AND_BACK, color);
	_material->setDiffuse(osg::Material::FRONT_AND_BACK, color);
	_stateset->setAttributeAndModes(_material,
									osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
}

void GridElement::setTransparent(float value)
{
	v4 color(_color[0], _color[1], _color[2], value);
	_material->setAmbient(osg::Material::FRONT_AND_BACK, color);
	_material->setDiffuse(osg::Material::FRONT_AND_BACK, color);
	_stateset->setAttributeAndModes(_material,
									osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
}

void GridElement::setColor(const v4 color)
{
	_color = color;
	
	if (_modelNode)
	{
		// Update the material colors
		_material->setAmbient(osg::Material::FRONT_AND_BACK, color);
		_material->setDiffuse(osg::Material::FRONT_AND_BACK, color);
		_stateset->setAttributeAndModes(_material,
										osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
	}
}

void GridElement::setLabel(const bump::String label)
{
	_label->setText(label.toStdString());
	
	// Place into the center of the model if there is one.
	// Set at positive depth if there was a _modelNode attached.
	// This allows us to set the text above the model.
	if (_modelNode) {
		bb neuron_bound = VertexPoller::getBoundingBox(_modelNode, true);
		float offset_x = (neuron_bound.xMax()-neuron_bound.xMin()) / 2.0;
		float offset_y = (neuron_bound.yMax()-neuron_bound.yMin()) / 2.0;
		float offset_z = (neuron_bound.zMax() - neuron_bound.zMin()) + 1;
		_label->setPosition(v3(offset_x, offset_y, offset_z));
	}
}

void GridElement::setSelected(bool isSelected)
{
	_isSelected = isSelected;
	
	// Reset to the original color
	if (!isSelected) {
		setColor(_color);
	}
}