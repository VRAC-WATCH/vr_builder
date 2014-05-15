/*
 *  precompiled_header.h
 *
 *  Created by Brandon Newendorp on 10/6/09.
 *  Copyright 2010 Iowa State University. All rights reserved.
 *
 */

// Put all C++ headers inside the __cplusplus guard
#ifdef __cplusplus

// Common C++ includes
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

// OSG pch
#include <osg/AutoTransform>
#include <osg/BlendFunc>
#include <osg/BoundingBox>
#include <osg/Camera>
#include <osg/CameraView>
#include <osg/ClipNode>
#include <osg/ClipPlane>
#include <osg/CullFace>
#include <osg/Depth>
#include <osg/DrawPixels>
#include <osg/Drawable>
#include <osg/GL>
#include <osg/GL2Extensions>
#include <osg/GLExtensions>
#include <osg/GLU>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/GraphicsContext>
#include <osg/Group>
#include <osg/Light>
#include <osg/LightModel>
#include <osg/LightSource>
#include <osg/LineSegment>
#include <osg/LineWidth>
#include <osg/Math>
#include <osg/Material>
#include <osg/Matrix>
#include <osg/Matrixd>
#include <osg/Matrixf>
#include <osg/MatrixTransform>
#include <osg/Multisample>
#include <osg/Node>
#include <osg/NodeCallback>
#include <osg/NodeVisitor>
#include <osg/Object>
#include <osg/Point>
#include <osg/PointSprite>
#include <osg/PolygonMode>
#include <osg/PolygonOffset>
#include <osg/PositionAttitudeTransform>
#include <osg/Quat>
#include <osg/Referenced>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/State>
#include <osg/StateAttribute>
#include <osg/StateSet>
#include <osg/Switch>
#include <osg/Transform>
#include <osg/Vec3>
#include <osg/Vec3b>
#include <osg/Vec3d>
#include <osg/Vec3f>
#include <osg/Vec3s>
#include <osg/Vec4>
#include <osg/Vec4b>
#include <osg/Vec4d>
#include <osg/Vec4f>
#include <osg/Vec4s>
#include <osg/Viewport>
#include <osg/ref_ptr>

#include <osgDB/FileUtils>
#include <osgDB/ReadFile>

#include <osgViewer/Export>
#include <osgViewer/Version>
#include <osgViewer/Viewer>

#include <osgText/Font>
#include <osgText/Font3D>
#include <osgText/String>
#include <osgText/Text>
#include <osgText/TextBase>

#include <osgUtil/DelaunayTriangulator>
#include <osgUtil/Optimizer>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

// Boost includes
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

// VPR includes
#include <vpr/IO/ObjectReader.h>
#include <vpr/IO/ObjectWriter.h>
#include <vpr/IO/SerializableObject.h>
#include <vpr/IO/Socket/InetAddr.h>
#include <vpr/IO/Socket/SocketStream.h>
#include <vpr/IO/TimeoutException.h>
#include <vpr/Sync/Guard.h>
#include <vpr/Sync/Mutex.h>
#include <vpr/Thread/Thread.h>
#include <vpr/Util/Debug.h>
#include <vpr/Util/Singleton.h>

// Add some nifty pre defs
#define NO_CONSTRAINT_STRING " No constraints"

#endif
