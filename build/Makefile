#
#	Makefile
#   vrViewer
#
#	Created by Iowa State University on 08/18/09.
#	Copyright 2009 Iowa State University. All rights reserved.
#	
#

# Set the shell to sh
SHELL = /bin/sh

# Specify the precompiled header
precompiled_header = osg.h.gch

# Specify the objects to be generated from source files
objects =	AppManager.o\
			Builder.o\
			Cursor.o\
			GlutKeyboardInput.o\
			Grid.o\
			Input.o\
			InteractionManager.o\
			JugglerGamepadInput.o\
			JugglerHeadTrackInput.o\
			JugglerInterface.o \
			JugglerWandInput.o\
			mainJuggler.o\
			Physics.o\
			Scene.o\
			SceneManager.o
			#VRBuilderApp.o
			

# Specify the application binary
application = vrBuilderApp

# Set the source directory
src_dir = ../src

# Setup the targets
all: $(precompiled_header) $(objects) $(application)

# Setup the VR-Juggler environment variables
# - Adds values to EXTRA_INCLUDES and EXTRA_LIBS
DZR_BASE_DIR = /home/vr/apps/watch-libs/rhel6/doozer-2.1.6/share/Doozer
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk

# Setup the OSG and FMOD includes and libs
EXTRA_INCLUDES += -I$(OSG_HOME)/include $(VRJ_CXX_FLAGS) -I$(src_dir)
EXTRA_INCLUDES += -I/home/vr/apps/watch-libs/rhel6/gmtl-0.6.1/include/gmtl-0.6.1
EXTRA_INCLUDES += -I$(OSGBULLET_ROOT)/include
EXTRA_INCLUDES += -I$(OSGWORKS_ROOT)/include
EXTRA_INCLUDES += -I$(BULLET_ROOT)/include/bullet
EXTRA_INCLUDES += -I../include
EXTRA_LIBS += -L$(OSG_HOME)/lib64 -lOpenThreads -losgAnimation -losgDB -losgFX -losgGA -losgManipulator -losgParticle -losgShadow -losgSim -losg -losgTerrain -losgText -losgUtil -losgViewer -losgVolume -losgWidget
EXTRA_LIBS += -L$(BULLET_ROOT)/lib -lBulletCollision -lBulletDynamics -lBulletSoftBody -LinearMath
EXTRA_LIBS += -L$(OSGWORKS_ROOT)/lib64 -losgwControls -losgwMx -losgwTools -losgwQuery
EXTRA_LIBS += -L$(OSGBULLET_ROOT)/lib -losgbCollision -losgbDynamics -losgbInteraction
EXTRA_LIBS += -lglut

# Generate the gch for the precompiled header
$(precompiled_header): $(src_dir)/osg.h
	g++ $(EXTRA_INCLUDES) -c $<

# Generate all the object files for all the source files
$(objects): %.o: $(src_dir)/%.cpp
ifeq ($(DEBUG),true)
	g++ -Og -include $(src_dir)/osg.h $(EXTRA_INCLUDES) -c $< -o $@
else
	g++ -include $(src_dir)/osg.h $(EXTRA_INCLUDES) -c $< -o $@
endif

# Link the application together
$(application): $(objects)
ifeq ($(DEBUG),true)
	g++ -Og $(objects) $(EXTRA_LIBS) $(LIBS) -o $@ 
else
	g++ $(objects) $(EXTRA_LIBS) $(LIBS) -o $@ 
endif

# Methods for cleanup
# - Use clean_all when you need to regenerate the gch for the pre-compiled header
clean:
	rm -f *.o *core core.*
	rm -rf ./ii_files
	rm -f $(application)

clean_all:
	rm -f osg.h.gch *.o *core core.*
	rm -rf ./ii_files
	rm -f $(application)


