//
//  Input.h
//  VRBuilder
//
//  Created by Trevor Richardson on 5/6/14.
//
//

#ifndef __VRBuilder__Input__
#define __VRBuilder__Input__

// Local headers
#include "SceneCommand.h"


class Input
{
public:
	
	/** Enum for declaring input types. */
	enum InputType {
		KEYBOARD,
		GAMEPAD,
		MOUSE,
		WAND,
		OTHER = 0
	};
	
	/** 
	 * Default Constructor. 
	 * Any derived classes should call this constructor to initialize the type.
	 */
	Input(InputType type);
	
	/** Destructor. */
	virtual ~Input();
	
	/** Populates the commandList with any addition input since the last update. */
	virtual void populateSceneCommand(std::vector<SceneCommand*>& commandList) = 0;
	
	/** Accessor for the input type of the current input. */
	inline const InputType inputType() { return _inputType; }


protected:
	
	/** Protected iVars. */
	std::vector<SceneCommand*>	_sceneCommandList;
	
	
private:
	
	/** Private iVars. */
	InputType					_inputType;
};

#endif /* defined(__VRBuilder__Input__) */
