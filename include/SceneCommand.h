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
//struct SceneCommand {
//	
//	/** Enumeration of commands possible from the user. */
//	enum CommandType {
//		ADD_BLOCK,
//		MODE_CHANGE,
//		MOVE,
//		THROW_BLOCK,
//		NAVIGATION
//	};
//	
//	/** Enumeration of game modes possible. */
//	enum GameMode {
//		CREATION,
//		PHYSICS
//	};
//	
//	/** Possible command arguments. */
//	osg::Vec4		color;
//	CommandType		commandType;
//	GameMode		currentGameMode;
//	osg::Vec3		direction;
//	v3				position;
//	std::string		textureFileName;
//	osg::Matrix		navigationMatrix;
//};

class SceneCommand{
public:
	virtual const char* CommandType()=0;
};

class Add_Block: public SceneCommand{
public:
	const char* CommandType(){ return "ADD_BLOCK"; }
	osg::Vec4		color;
	std::string		textureFileName;
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

class Throw_Block: public SceneCommand{
public:
	const char* CommandType(){ return "THROW_BLOCK"; }
};

class Navigation: public SceneCommand{
public:
	const char* CommandType(){ return "NAVIGATION"; }
	osg::Matrix		navigationMatrix;
};

#endif
