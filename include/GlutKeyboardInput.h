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
	typedef void (*func_ptr)(int, int, int);
	func_ptr keyboardDown_ptr();
	func_ptr keyboardnormal_ptr();
	
	
protected:
	
	/** Glut keyboardDownFunc. */
	static void _keyboardDown(int key, int x, int y);
	static void _keyboardnormal(int key, int x, int y);
};


