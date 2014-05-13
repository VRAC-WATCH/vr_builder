CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (VRBuilder)


################################################################################
# Set the desired build type.
#
#	- DEBUG_BUILD turns on console and sets the Log level to DEBUG_LVL
#	- RELEASE_BUILD turns on the console and sets the Log level to WARNING_LVL
#	- DEPLOYMENT_BUILD turns off the console and sets the Log level to ERROR_LVL
#
################################################################################
SET (BUILD_TYPE "DEBUG_BUILD")

# Handle specifics for each build type
IF (${BUILD_TYPE} STREQUAL "RELEASE_BUILD")
	ADD_DEFINITIONS(-DRELEASE_BUILD)
ELSEIF(${BUILD_TYPE} STREQUAL "DEPLOYMENT_BUILD")
	ADD_DEFINITIONS(-DDEPLOYMENT_BUILD)
	# Specify that we are building a non-console app
	IF(WIN32)
		SET(REQUIRE_WINMAIN_FLAG 1)
	ENDIF(WIN32)
ELSE()
	ADD_DEFINITIONS(-DDEBUG_BUILD)
ENDIF()

################################################################################
# Add OS specific paths for finding dependencies to the project
################################################################################
IF(WIN32)
	SET(CMAKE_PREFIX_PATH "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/x64")
	SET(OSG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/win/osg-3.2.1-rc)
	SET(GLUT_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps/win/glut-3.7)
ELSEIF(APPLE)
	SET(CMAKE_XCODE_ATTRIBUTE_SDKROOT macosx10.9)
	SET(CMAKE_XCODE_ATTRIBUTE_ARCHS "$(ARCHS_STANDARD_64_BIT)")
	SET(OSG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/mac/osg-3.1.9)
ELSE(WIN32)
	# Linux specific commands
	SET(OSG_DIR /home/vr/Applications/watch-libs/rhel6/openscenegraph-3.0.1)
ENDIF(WIN32)



################################################################################
# Set the dependency paths not set with the FindPackage command
################################################################################
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

# Find OpenGL
FIND_PACKAGE(OpenGL REQUIRED)
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${OPENGL_INCLUDE_DIR})
FIND_PACKAGE(GLUT REQUIRED)
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${GLUT_INCLUDE_DIR})

# Find the OpenSceneGraph Libs	
FIND_PACKAGE(OpenSceneGraph REQUIRED osgAnimation osgDB osgFX osgGA osgManipulator osgParticle osgPresentation osgShadow osgSim osgTerrain osgText osgUtil osgViewer osgVolume osgWidget)
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${OSG_INCLUDE_DIR})


################################################################################
# Sets the variables for the source and header files to use in the program
################################################################################
# Common
SET(COMMON_SOURCES ) 	#src/common/Settings.cpp)				
SET(COMMON_HEADERS )	#include/common/Enums.h
# 					include/common/Settings.h
# 					include/common/UIState.h)

# Core
SET(CORE_SOURCES 	src/mainGLUT.cpp
					src/Input.cpp
					src/InteractionManager.cpp
					src/GlutKeyboardInput.cpp
					src/VRBuilderApp.cpp
					src/AppManager.cpp
					src/Scene.cpp)				
SET(CORE_HEADERS 	include/Input.h
					include/VRBuilderApp.h
					include/GlutKeyboardInput.h
					include/InteractionManager.h
					include/AppManager.h
					include/Scene.h)
											 
 # UI
SET(UI_SOURCES 	src/VRBuilderApp.cpp
				src/SceneMgr.cpp)
				# src/GridElement.cpp
				# src/GridStructure2D.cpp
				# src/Scenegraph.cpp)
SET(UI_HEADERS 	include/CameraController.h
				include/SceneMgr.h
				# include/GridElement.h
				# include/GridStructure2D.h
				# include/Scenegraph.h
				include/VRBuilderApp.h)

# Wrap all source and header files into single var
SET(VR_BUILDER_SOURCES 	${COMMON_SOURCES}
						${CORE_SOURCES} 
						${UI_SOURCES})
SET(VR_BUILDER_HEADERS	${COMMON_HEADERS}
						${CORE_HEADERS} 
						${UI_HEADERS})


################################################################################
# Header search paths for the project
# These should not have to be changed, make changes above to
# in the OS specific area to add includes and other settings
################################################################################
INCLUDE_DIRECTORIES(${CMAKE_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include
					${CMAKE_BINARY_DIR})
SET(CMAKE_XCODE_ATTRIBUTE_USER_HEADER_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include)

################################################################################
# Put the source files into folders for the Xcode project. Done for cleaness only.
################################################################################

# Setup the common source and header files
SOURCE_GROUP("src\\common" FILES ${COMMON_SOURCES} ${COMMON_HEADERS})

# Setup the core source and header files
SOURCE_GROUP("src\\core" FILES ${CORE_SOURCES} ${CORE_HEADERS})

# Setup the input/output source and header files
SOURCE_GROUP("src\\io" FILES ${IO_SOURCES} ${IO_HEADERS})

# Setup UI group file structure
SOURCE_GROUP("src\\ui" FILES ${UI_HEADERS} ${UI_SOURCES})

		
################################################################################
# This is the place to add any source files to the project
# Headers, cpp files, etc. 
# For a mac app bundle, add MACOSX_BUNDLE between the project name and
# the source files being added to the project
################################################################################
IF(APPLE)
	SET(MACOSX_BUNDLE_ICON_FILE "") # example: somviz_icon_mac.icns
	SET(ICON_FILE )#${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/${MACOSX_BUNDLE_ICON_FILE})
	ADD_EXECUTABLE(VR_BUILDER MACOSX_BUNDLE ${VR_BUILDER_HEADERS}
											${VR_BUILDER_SOURCES} 
											${ICON_FILE})
	SET_SOURCE_FILES_PROPERTIES(
		${FONTS}
		${MODELS}
		${ICON_FILE}
		PROPERTIES
		MACOSX_PACKAGE_LOCATION Resources
	)
ELSE(APPLE)
	ADD_EXECUTABLE(VR_BUILDER	${VR_BUILDER_HEADERS}
								${VR_BUILDER_SOURCES})
ENDIF(APPLE)

################################################################################
# Need to add the bump/String header to all the files to fix a weird linker error
# this will need to be investigated and fixed in the future.
################################################################################
IF (WIN32)
	SET_TARGET_PROPERTIES(VR_BUILDER PROPERTIES COMPILE_FLAGS "/MP")
ENDIF()

################################################################################
# Set all lib files or frameworks here that you want to link to
# the project.
################################################################################
SET(LINK_LIBRARIES 	${Boost_LIBRARIES}
					${OPENGL_LIBRARIES}
					${GLUT_LIBRARIES}
					${OPENSCENEGRAPH_LIBRARIES})
					#${VRJUGGLER-OPENGL_LIBRARIES})

################################################################################
# Updates the starting point in the program to WinMain instead of main
# if we are only wanting the application and no cmd line
################################################################################
IF(REQUIRE_WINMAIN_FLAG)
	IF(MSVC)
		SET_TARGET_PROPERTIES(VR_BUILDER PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
		GET_TARGET_PROPERTY(FLAGS VR_BUILDER COMPILE_FLAGS)
		SET_TARGET_PROPERTIES(VR_BUILDER PROPERTIES COMPILE_FLAGS "${FLAGS} \"/GL\" \"/Ox\" \"/Ot\"")
	ENDIF()
ENDIF()
			
################################################################################
# This actually links the libs and frameworks to the project
################################################################################		
TARGET_LINK_LIBRARIES(VR_BUILDER ${LINK_LIBRARIES})
