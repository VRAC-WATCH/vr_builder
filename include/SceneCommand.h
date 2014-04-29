//
//  SceneCommand.h
//  VRBuilder
//
//  Created by Trevor Richardson on 4/29/14.
//
//

#ifndef VRBuilder_SceneCommand_h
#define VRBuilder_SceneCommand_h

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
	}
	
	/** Enumeration of game modes possible. */
	enum GameMode {
		CREATION,
		PHYSICS
	}
	
	/** Possible command arguments. */
	v3 position;
	v3 blockSize;
	GameMode currentGameMode;
};

typedef osg::Vec3 v3;

#endif
