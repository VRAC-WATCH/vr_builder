#ifndef DP3DJUGGLERH
#define DP3DJUGGLERH

#include <vrj/Draw/OGL/GlApp.h>
#include <vrj/Draw/OSG/OsgApp.h>


// OSG
#include <osg/Matrix>
#include <osg/Transform>
#include <osg/MatrixTransform>



class JugglerInterface : public vrj::OsgApp
{
  public:
    JugglerInterface(vrj::Kernel* kern, int & argc, char** argv);
    virtual ~JugglerInterface();

    virtual void init();
    virtual void initScene();
    virtual void preFrame();
    virtual void latePreFrame();
	virtual void draw();
    void bufferPreDraw();

    virtual osg::Group* getScene();

//	void configSceneView(osgUtil::SceneView* newSceneViewer);

  private:
	osg::ref_ptr<osg::Group> _rootNode;
	gadget::PositionInterface  mWand;    /**< Positional interface for Wand position */
	gadget::PositionInterface  mHead;    /**< Positional interface for Head position */
	gadget::DigitalInterface   mButton[6]; /**< Digital interface for button 0 */
	osg::ref_ptr<osg::FrameStamp> _frameStamp;
};

#endif
