/*
 *  Builder.cpp
 *
 *	Created by Bhaskar Bhattacharya on 5/1/2014.
 *  Copyright 2014 Iowa State University. All rights reserved.
 *
 */

#include "Builder.h"

//function to create the Geode
osg::Transform* osgBox( osg::Vec3 blocksize )
{
	osg::Box* box = new osg::Box();
    box->setHalfLengths( blocksize/2 );

    osg::ShapeDrawable* shape = new osg::ShapeDrawable( box );
    shape->setColor( osg::Vec4( 1., 1., 1., 1. ) );
    osg::Geode* geode = new osg::Geode();
    geode->addDrawable( shape );

    osg::MatrixTransform* mt = new osg::MatrixTransform();
    mt->addChild( geode );

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
    osg::Transform* ground = osgBox(osg::Vec3(ground_size, .05, ground_size));

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
	color->push_back(osg::Vec4(1.0,0.0,0.0,1.0)); 
	lines->setVertexArray(points); 
	lines->setColorArray(color); 
	lines->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f,1.0f,0.0f));
	lines->setNormalArray(normals);
	lines->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(lines);

	ground->addChild(geode);

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
