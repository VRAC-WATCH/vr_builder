// System headers
#include <vector>

// Local headers
#include "Input.h"


class InteractionManager
{
public:
	
	/** Enum for declaring the Interface type. */
	enum InterfaceType {
		GLUT_INTERFACE,
		JUGGLER_INTERFACE
	};
	
	/** Default Constructor - Sets up the glut interface. */
	InteractionManager();
	
	/** Constructor declaring interface. */
	InteractionManager(InterfaceType type);
	
	/** Destructor. */
	~InteractionManager();
	
	/** Accessors for the specified input type. */
	Input* inputForType(Input::InputType type);
	
	/** 
	 * Builds a list of commands that have been executed from any input. 
	 * This needs to be done every frame before trying to use commands.
	 */
	void update();
	
	
protected:
	
	/** Sets up user interaction handlers for Glut. */
	void _setupGlutInputs();
	
	/** Sets up user interaction hanlders for Juggler. */
	void _setupJugglerInputs();
	
	/** iVars. */
	std::vector<Input*>		_inputs;
	InterfaceType			_interfaceType;
};