/*
 *  Builder.cpp
 *
 *	Created by Bhaskar Bhattacharya on 5/1/2014.
 *  Copyright 2014 Iowa State University. All rights reserved.
 *
 */

#include "Builder.h"

//function to create the Geode
osg::Transform* osgBox( osg::Vec3 blocksize, osg::Vec4 color = osg::Vec4( 1.0, 1.0, 1.0, 1.0) )
{
	osg::Box* box = new osg::Box();
    box->setHalfLengths( blocksize/2.0 );	

    osg::ShapeDrawable* shape = new osg::ShapeDrawable( box );
    shape->setColor( color );
    osg::Geode* geode = new osg::Geode();
    geode->addDrawable( shape );

	// Build the border
	osg::ref_ptr<osg::Geode> border_geode(new osg::Geode);
	osg::ref_ptr<osg::Geometry> border_geom(new osg::Geometry);
	osg::ref_ptr<osg::Vec3Array> border_verts(new osg::Vec3Array);

	// Bottom
    border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, -blocksize.y()/2.0, -blocksize.z()/2.0) );
    border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, -blocksize.y()/2.0, blocksize.z()/2.0) );
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, -blocksize.y()/2.0, blocksize.z()/2.0) );
    border_verts->push_back( osg::Vec3(blocksize.x()/2.0, -blocksize.y()/2.0, blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(blocksize.x()/2.0, -blocksize.y()/2.0, blocksize.z()/2.0));
    border_verts->push_back( osg::Vec3(blocksize.x()/2.0, -blocksize.y()/2.0, -blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(blocksize.x()/2.0, -blocksize.y()/2.0, -blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, -blocksize.y()/2.0, -blocksize.z()/2.0));

	// Top
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, blocksize.y()/2.0, -blocksize.z()/2.0));
    border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, blocksize.y()/2.0, blocksize.z()/2.0) );
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, blocksize.y()/2.0, blocksize.z()/2.0) );
    border_verts->push_back( osg::Vec3(blocksize.x()/2.0, blocksize.y()/2.0, blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(blocksize.x()/2.0, blocksize.y()/2.0, blocksize.z()/2.0));
    border_verts->push_back( osg::Vec3(blocksize.x()/2.0, blocksize.y()/2.0, -blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(blocksize.x()/2.0, blocksize.y()/2.0, -blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, blocksize.y()/2.0, -blocksize.z()/2.0));

	// Sides
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, -blocksize.y()/2.0, -blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, blocksize.y()/2.0, -blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, -blocksize.y()/2.0, blocksize.z()/2.0) );
	border_verts->push_back( osg::Vec3(-blocksize.x()/2.0, blocksize.y()/2.0, blocksize.z()/2.0) );
	border_verts->push_back( osg::Vec3(blocksize.x()/2.0, -blocksize.y()/2.0, blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(blocksize.x()/2.0, blocksize.y()/2.0, blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(blocksize.x()/2.0, -blocksize.y()/2.0, -blocksize.z()/2.0));
	border_verts->push_back( osg::Vec3(blocksize.x()/2.0, blocksize.y()/2.0, -blocksize.z()/2.0));

	// Attach to geometry
	osg::ref_ptr<osg::Vec4Array> color_array = new osg::Vec4Array;
	color_array->push_back(osg::Vec4(0.3,0.3,0.3,1.0));
	border_geom->setVertexArray(border_verts.get());
	border_geom->setColorArray(color_array.get());
	border_geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	border_geom->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,24));
	border_geode->addDrawable(border_geom);

	// StateSet
	osg::StateSet* border_ss = border_geode->getOrCreateStateSet();
	osg::ref_ptr<osg::LineWidth> line_width(new osg::LineWidth());
	line_width->setWidth(1.0f);
	border_ss->setAttributeAndModes(line_width,osg::StateAttribute::ON);
	border_ss->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
	border_ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::MatrixTransform* mt = new osg::MatrixTransform();
    mt->addChild(geode);
	mt->addChild(border_geode);
	
	// Add support for transparency
	osg::ref_ptr<osg::StateSet> ss = mt->getOrCreateStateSet();
	//ss->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    return( mt );
}

Builder::Builder(){

}

void Builder::init(){

}

void Builder::setColor(osg::Node*& node,osg::Vec4 color=osg::Vec4(0,1,0,1)){
	osg::ShapeDrawable* shape= dynamic_cast<osg::ShapeDrawable*>(node->asTransform()->getChild(0)->asGeode()->getDrawable(0));
	shape->setColor(color);
}

void Builder::setTexture(osg::Node*& node, std::string textureFileName=""){
	if(textureFileName.length()==0)
		return;
	//Check for valid texture and load it
	osg::Texture2D* texture = new osg::Texture2D;
	texture->setDataVariance(osg::Object::DYNAMIC); 
	osg::Image* image = osgDB::readImageFile(textureFileName);
	if (!image)
	{
		std::cout << " couldn't find texture setting default color" << std::endl;
		setColor(node);
		return;
	}
	texture->setImage(image);

	osg::StateSet* ss=node->asTransform()->getChild(0)->asGeode()->getOrCreateStateSet();
	ss->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
	node->asTransform()->getChild(0)->asGeode()->setStateSet(ss);
	return;
}
osg::MatrixTransform* Builder::makeBlock(Add_Block sc)
{
	osg::MatrixTransform* root = new osg::MatrixTransform;
	osg::Node* node = osgBox(osg::Vec3(1,1,1));
	if( node == NULL )
	{
		osg::notify( osg::FATAL ) << "Node generation failed" << std::endl;
		exit( 0 );
	}
	setColor(node,sc.color);	
	setTexture(node,sc.textureFileName);

	root->addChild( node );
	return( root );
}

osg::Node* Builder::createBlock(Add_Block sc){ 
	return makeBlock(sc);
}

osg::Node* Builder::createFloor( float w, float h, const osg::Vec3& center, int _gridsize, float _gridblocksize)
{
	float ground_size = (_gridsize+0.5) * _gridblocksize;
    osg::Transform* ground = osgBox(osg::Vec3(ground_size, .05, ground_size), osg::Vec4(1,1,1,0.7));

	// Make the ground transparent
	osg::ref_ptr<osg::StateSet> ground_ss = ground->getOrCreateStateSet();
	ground_ss->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	ground_ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	ground_ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	//Draw Grid lines
	osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array;
	osg::ref_ptr<osg::Geometry> lines =  new osg::Geometry; 
	int count=0;
	for(double i=-(_gridsize+1)/2*_gridblocksize;i<=(_gridsize+1)/2*_gridblocksize;i+=_gridblocksize,count+=2){
		osg::Vec3 sp(i,0.05,-(_gridsize+1)/2*_gridblocksize); 
		osg::Vec3 ep(i,0.05,(_gridsize+1)/2*_gridblocksize);
		points->push_back(sp);
		points->push_back(ep);
		osg::DrawElementsUInt* line =  new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
		line->push_back(count);
		line->push_back(count+1);
		lines->addPrimitiveSet(line);
	}
	for(double i=-(_gridsize+1)/2*_gridblocksize;i<=(_gridsize+1)/2*_gridblocksize;i+=_gridblocksize,count+=2){
		osg::Vec3 sp(-(_gridsize+1)/2*_gridblocksize,0.05,i); 
		osg::Vec3 ep((_gridsize+1)/2*_gridblocksize,0.05,i);
		points->push_back(sp);
		points->push_back(ep);
		osg::DrawElementsUInt* line =  new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
		line->push_back(count);
		line->push_back(count+1);
		lines->addPrimitiveSet(line);
	}
	
	osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array; 
	color->push_back(osg::Vec4(0.0,0.0,0.0,0.2)); 
	lines->setVertexArray(points); 
	lines->setColorArray(color); 
	lines->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(lines);

	ground->addChild(geode);

	osg::MatrixTransform* mt = ground->asMatrixTransform();
	osg::Matrix mat;
	mat.setTrans(0.0,-20.0, 0.0);
	mt->setMatrix(mat);
	//mt->setPosition();

    return( ground );
}

osg::Node* Builder::createProjectile(){
	osg::Vec3 initialposition(0,0,0);	
	osg::MatrixTransform* root = new osg::MatrixTransform;
	
	osg::Sphere* ball = new osg::Sphere();
    ball->setRadius(0.1);

    osg::ShapeDrawable* shape = new osg::ShapeDrawable( ball );
    shape->setColor( osg::Vec4( 1., 1., 0., 1. ) );
    osg::Geode* geode = new osg::Geode();
    geode->addDrawable( shape );

    osg::MatrixTransform* mt = new osg::MatrixTransform();
    mt->addChild( geode );
	root->addChild(mt);
	
    return( root );
}
