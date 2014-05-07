// Local headers
#include "Input.h"
#include "SceneCommand.h"

class KeyboardInput : public Input
{
public:

	/** Default Constructor. */
	KeyboardInput();
	
	/** Destructor. */
	~KeyboardInput();
	
	/** Add any commands we have stored to the list passed in. */
	void populateSceneCommand(std::vector<SceneCommand>& commandList);
	
	typedef void (*func_ptr)(unsigned char, int, int);
	
	void update();
	static void keyboardDown(unsigned char key, int x, int y);
	static void keyboardUp(unsigned char key, int x, int y);
	
	func_ptr keyboardDown_ptr();
	func_ptr keyboardUp_ptr();
};


