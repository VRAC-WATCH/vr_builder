//
//  SceneCommand.h
//  VRBuilder
//
//  Created by Trevor Richardson on 4/29/14.
//
//

#ifndef VRBuilder_SceneCommand_h
#define VRBuilder_SceneCommand_h

// OSG headers
#include <osg/Vec3>

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
		SET_CURSOR_POS
	};
	
	/** Enumeration of game modes possible. */
	enum GameMode {
		CREATION,
		PHYSICS
	};
	
	/** Possible command arguments. */	
	v3				blockSize;
	osg::Vec4 		color;
	CommandType		commandType;
	GameMode		currentGameMode;
	v3				magnitude;
	v3 				position;
	std::string 	textureFileName;
};

#endif
