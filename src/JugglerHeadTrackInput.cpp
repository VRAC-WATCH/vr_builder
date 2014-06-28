// System headers
#include <iostream>

// Local headers
#include "JugglerHeadTrackInput.h"
#include "SceneCommand.h"

JugglerHeadTrackInput::JugglerHeadTrackInput() : Input(Input::HEAD_TRACK)
{
	std::cout << "JugglerHeadTrackInput Constructor" << std::endl;

	// Initialize the head track gadget interface
	_head.init("VJHead");

	wantCursor = false;
}

JugglerHeadTrackInput::~JugglerHeadTrackInput()
{
	std::cout << "JugglerHeadTrackInput Destructor" << std::endl;
}

void JugglerHeadTrackInput::populateSceneCommand(std::vector<SceneCommand*>& commandList)
{
	_updateJugglerInput();

	for(int i=0;i<_sceneCommandList.size();i++){
		_sceneCommandList[i]->id = getID();
	}

	// Append all of our latest scene commands to the list requested then clear it
	commandList.insert(commandList.end(),
					   _sceneCommandList.begin(), _sceneCommandList.end());
	_sceneCommandList.clear();
}

void JugglerHeadTrackInput::_updateJugglerInput()
{
	// Grab the head matrix every frame from the device
	osg::Matrixf head_matrix(_head->getData().mData);
	
	// Build a command and at it to the list
	HeadTrackChangeCommand* head_track_change = new HeadTrackChangeCommand;
	head_track_change->headMatrix = head_matrix;
	_sceneCommandList.push_back(head_track_change);
}

