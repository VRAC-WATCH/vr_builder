// Local headers
#include "Input.h"
#include "SceneCommand.h"

class GlutKeyboardInput : public Input
{
public:

	/** Default Constructor. */
	GlutKeyboardInput();
	
	/** Destructor. */
	~GlutKeyboardInput();
	
	/** Add any commands we have stored to the list passed in. */
	void populateSceneCommand(std::vector<SceneCommand>& commandList);
	
	/** Accessors for glut function pointers. */
	typedef void (*func_ptr)(unsigned char, int, int);
	func_ptr keyboardDown_ptr();
	func_ptr keyboardUp_ptr();
	
protected:
	
	/** Glut keyboardDownFunc. */
	static void _keyboardDown(unsigned char key, int x, int y);
	
	/** Glut keyboardUpFunc. */
	static void _keyboardUp(unsigned char key, int x, int y);
};


