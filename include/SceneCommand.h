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
struct SceneCommand {
	
	/** Enumeration of commands possible from the user. */
	enum CommandType {
		ADD_BLOCK,
		MODE_CHANGE,
		MOVE,
		NAVIGATION,
		THROW_BLOCK
	};
	
	/** Enumeration of game modes possible. */
	enum GameMode {
		CREATION,
		PHYSICS
	};
	
	/** Possible command arguments. */
	float			joystickAxisValues[6];
	osg::Vec4		color;
	CommandType		commandType;
	GameMode		currentGameMode;
	osg::Vec3		direction;
	v3				position;	
	std::string		textureFileName;
};

#endif
