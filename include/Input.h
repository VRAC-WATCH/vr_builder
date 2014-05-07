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
	
	/** Default Constructor. */
	Input();
	
	/** Destructor. */
	virtual ~Input();
	
	/** Populates the commandList with any addition input since the last update. */
	virtual void populateSceneCommand(std::vector<SceneCommand>& commandList) = 0;

protected:
	
	/** iVars. */
	std::vector<SceneCommand>	_sceneCommandList;
};

#endif /* defined(__VRBuilder__Input__) */
