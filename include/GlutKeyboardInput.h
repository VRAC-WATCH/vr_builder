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
	void populateSceneCommand(std::vector<SceneCommand*>& commandList);
	
	/** Accessors for glut function pointers. */
	typedef void (*special_func_ptr)(int, int, int);
	special_func_ptr keyboardSpecial_ptr();
	typedef void (*normal_func_ptr)(unsigned char, int, int);
	normal_func_ptr keyboardNormal_ptr();
	
	
protected:
	
	/** Glut keyboardDownFunc. */
	static void _keyboardSpecial(int key, int x, int y);
	static void _keyboardNormal(unsigned char key, int x, int y);
};


