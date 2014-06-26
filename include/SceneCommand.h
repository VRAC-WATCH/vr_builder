//
//  SceneCommand.h
//  VRBuilder
//
//  Created by Trevor Richardson on 4/29/14.
//
//

#ifndef VRBuilder_SceneCommand_h
#define VRBuilder_SceneCommand_h

#include <osg/Array>

typedef osg::Vec3 v3;

/**
 * The SceneCommand structure will be used to communicate
 * any input from the user to the system and eventually
 * to the graphical scene.
 */
//TODO: Add device id so we can easily handle collaboration
//Add device command?
class SceneCommand{
public:
	virtual const char* CommandType(){ return "GENERIC"; }
};

class Add_Block: public SceneCommand{
public:
	const char* CommandType(){ return "ADD_BLOCK"; }
	osg::Vec4		color;
	std::string		textureFileName;
};

class ClearSceneCommand: public SceneCommand{
public:
	const char* CommandType(){ return "CLEAR_SCENE"; }
};

class HeadTrackChangeCommand : public SceneCommand {
public:
	const char* CommandType(){ return "HEAD_TRACK"; }
	osg::Matrix headMatrix;
};

class Mode_Change: public SceneCommand{
public:
	const char* CommandType(){ return "MODE_CHANGE"; }
};

class Move: public SceneCommand{
public:
	const char* CommandType(){ return "MOVE"; }
	osg::Vec3	direction;
};

class Navigation: public SceneCommand{
public:
	const char* CommandType(){ return "NAVIGATION"; }
	osg::Matrix	navMatrixMultiplier;
};

class Throw_Block: public SceneCommand{
public:
	const char* CommandType(){ return "THROW_BLOCK"; }
};

class WandTrackChangeCommand : public SceneCommand {
public:
	const char* CommandType(){ return "WAND_TRACK"; }
	osg::Matrix wandMatrix;
};

#endif
