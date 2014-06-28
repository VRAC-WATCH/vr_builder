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
		HEAD_TRACK,
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
	
	/** Accessor for the input to be able to control the  cursor */
	bool wantCursor;

	/**Set the ID of the Input */
	void setID(int inputid){_id = inputid;}

	/**Get the ID of the Input */
	int getID(){return _id;}

protected:
	
	/** Protected iVars. */
	std::vector<SceneCommand*>	_sceneCommandList;
	
	
private:
	
	/** Private iVars. */
	InputType					_inputType;
	int 						_id;
};

#endif /* defined(__VRBuilder__Input__) */
