//
//  sceneMgr.h
//  VRBuilder
//
//  Created by Frederick Thompson on 4/25/14.
//
//

#ifndef __VRBuilder__sceneMgr__
#define __VRBuilder__sceneMgr__

#include <iostream>
#include "SceneCommand.h"
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/io_utils>
#include <osg/Texture2D>

//Own the scene
//Use the builder - send updates
//Take commands from App manager
    //initialize default scene
    //interaction command update
//Update scene - send updates from builder
//Get information from the scene


class sceneManager
{
    //private members
    
public:
    
    //reads in an input from the Application Manager
    void listenAppManger(const struct SceneCommand&);
    
    //sends an update from builder to the scene
    std::string builderToScene(void);//using strings for now
    
    //listens to the scene
    void listenScene( std::string );//using strings for now
    
    //An instance of some data from the scene
    void sceneInstance(void);
    
    //Intended to store the location of the blocks in the scene in progress
    //may end up moving somewhere else
    void storeBock(const struct SceneCommand&)
};

#endif /* defined(__VRBuilder__sceneMgr__) */
