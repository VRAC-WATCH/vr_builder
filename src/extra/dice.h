#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>

#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbDynamics/RigidBody.h>
#include <osgbCollision/Utils.h>

#include <btBulletDynamicsCommon.h>

#include <string>
#include <osg/io_utils>

class Dice{
	osg::PositionAttitudeTransform* root;
	double prevSimTime;
	btDynamicsWorld* bulletWorld;
	osgbDynamics::MotionState* _motion;
	float _lastX, _lastY;

public:
	Dice();
	osg::PositionAttitudeTransform* getRoot(){return root;}
	void update(double);
	void buttonpress(int);
};

/* \cond */
class ShakeManipulator : public osgGA::GUIEventHandler
{
public:
    ShakeManipulator( osgbDynamics::MotionState* motion )
      : _motion( motion )
    {}

    bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& )
    {
        switch( ea.getEventType() )
        {
            case osgGA::GUIEventAdapter::KEYUP:
            {
                if (ea.getKey()==osgGA::GUIEventAdapter::KEY_Space)
                {
                    btTransform trans; trans.setIdentity();
                    _motion->setWorldTransform( trans );

                    return true;
                }

                return false;
            }

            case osgGA::GUIEventAdapter::PUSH:
            {
                _lastX = ea.getXnormalized();
                _lastY = ea.getYnormalized();

                btTransform world;
                _motion->getWorldTransform( world );
                btVector3 o = world.getOrigin();
                o[ 2 ] = 0.25;
                world.setOrigin( o );
                _motion->setWorldTransform( world );

                return true;
            }
            case osgGA::GUIEventAdapter::DRAG:
            {
                btVector3 move;
                move[ 0 ] = _lastX - ea.getXnormalized();
                move[ 1 ] = ea.getYnormalized() - _lastY;
                move[ 2 ] = 0.;
                move *= 10.;
                btTransform moveTrans; moveTrans.setIdentity();
                moveTrans.setOrigin( move );
                btTransform world;
                _motion->getWorldTransform( world );
                btTransform netTrans = moveTrans * world;
                btVector3 o = netTrans.getOrigin();
                o[ 2 ] = 0.;
                netTrans.setOrigin( o );

                _motion->setWorldTransform( netTrans );

                _lastX = ea.getXnormalized();
                _lastY = ea.getYnormalized();

                return true;
            }
            default:
            break;
        }
        return false;
    }

protected:
    osgbDynamics::MotionState* _motion;
    float _lastX, _lastY;
};
/* \endcond */
