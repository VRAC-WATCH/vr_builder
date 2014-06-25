// Juggler headers
#include <gadget/Type/PositionInterface.h>

// Local headers
#include "Input.h"
#include "SceneCommand.h"

class JugglerHeadTrackInput : public Input
{
public:

	/** Default Constructor. */
	JugglerHeadTrackInput();
	
	/** Destructor. */
	~JugglerHeadTrackInput();
	
	/** Add any commands we have stored to the list passed in. */
	void populateSceneCommand(std::vector<SceneCommand*>& commandList);


protected:

	/** Pulls information from the gadgets. */
	void _updateJugglerInput();

	/** Juggler gadget interface iVars. */
	gadget::PositionInterface  _head;
};


