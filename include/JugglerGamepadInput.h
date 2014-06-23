// Juggler headers
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>

// Local headers
#include "Input.h"
#include "SceneCommand.h"

class JugglerGamepadInput : public Input
{
public:

	/** Default Constructor. */
	JugglerGamepadInput();
	
	/** Destructor. */
	~JugglerGamepadInput();
	
	/** Add any commands we have stored to the list passed in. */
	void populateSceneCommand(std::vector<SceneCommand>& commandList);


protected:

	/** Pulls information from the gadgets. */
	void _updateJugglerInput();

	/** Juggler gadget interface iVars. */
	gadget::DigitalInterface _button[10];
	gadget::AnalogInterface _axis0;
	gadget::AnalogInterface _axis1;
	gadget::AnalogInterface _axis2;
	gadget::AnalogInterface _axis3;
	gadget::AnalogInterface _axis4;
	gadget::AnalogInterface _axis5;
};


