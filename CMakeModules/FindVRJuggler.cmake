# Find VR Juggler
#
# If found, will define:
#
#  VRJUGGLER_FOUND
#  VRJUGGLER_INCLUDE_DIRS
#  VRJUGGLER_LIBRARIES
#  VRJUGGLER_DEFINITIONS

find_package( Flagpoll )

set( FIND_PACKAGE_ARGS )

if( VRJuggler_FIND_REQUIRED )
    list( APPEND FIND_PACKAGE_ARGS REQUIRED )
endif()

if( VRJuggler_FIND_QUIETLY )
    list( APPEND FIND_PACKAGE_ARGS QUIET )
endif()

find_package( Vapor ${FIND_PACKAGE_ARGS} )
find_package( Jackal ${FIND_PACKAGE_ARGS} )
find_package( Sonix ${FIND_PACKAGE_ARGS} )
find_package( Gadgeteer ${FIND_PACKAGE_ARGS} )
find_package( Boost COMPONENTS program_options ${FIND_PACKAGE_ARGS} )
find_package( GMTL ${FIND_PACKAGE_ARGS} )

flagpoll_get_include_dirs( vrjuggler NO_DEPS )
flagpoll_get_library_dirs( vrjuggler NO_DEPS )
flagpoll_get_library_names( vrjuggler NO_DEPS )
flagpoll_get_module_version( vrjuggler NO_DEPS )
flagpoll_get_other_definitions( vrjuggler NO_DEPS )

find_path( VRJUGGLER_INCLUDE_DIR vrj/vrjDefines.h
           HINTS ${vrjuggler_FLAGPOLL_INCLUDE_DIRS} )

include( FindPackageHandleStandardArgs )

set( VRJUGGLER_FAIL_MESSAGE
     "Could NOT find VRJuggler. Is the FLAGPOLL_PATH environment variable set?"
     CACHE INTERNAL "" )

if( MSVC )
    set( VRJUGGLER_LIBRARY_DIRS ${vrjuggler_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( VRJuggler
                                       REQUIRED_VARS VRJUGGLER_LIBRARY_DIRS VRJUGGLER_INCLUDE_DIR
                                       VERSION_VAR vrjuggler_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${VRJUGGLER_FAIL_MESSAGE} )
    set( VRJUGGLER_LIBRARIES )
    mark_as_advanced( VRJUGGLER_LIBRARY_DIRS )
    link_directories( ${VRJUGGLER_LIBRARY_DIRS} )
else()
    find_library( VRJUGGLER_LIBRARY NAMES ${vrjuggler_FLAGPOLL_LIBRARY_NAMES}
                  HINTS ${vrjuggler_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( VRJuggler
                                       REQUIRED_VARS VRJUGGLER_LIBRARY VRJUGGLER_INCLUDE_DIR
                                       VERSION_VAR vrjuggler_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${VRJUGGLER_FAIL_MESSAGE} )
    set( VRJUGGLER_LIBRARIES ${VRJUGGLER_LIBRARY}
                             ${VAPOR_LIBRARIES}
                             ${JACKAL_LIBRARY}
                             ${SONIX_LIBRARY}
                             ${GADGETEER_LIBRARY}
                             ${Boost_PROGRAM_OPTIONS_LIBRARY} )
    mark_as_advanced( VRJUGGLER_LIBRARY )
endif()

set( VRJUGGLER_INCLUDE_DIRS ${VRJUGGLER_INCLUDE_DIR}
                            ${VAPOR_INCLUDE_DIRS}
                            ${JACKAL_INCLUDE_DIR}
                            ${SONIX_INCLUDE_DIR}
                            ${GADGETEER_INCLUDE_DIR}
                            ${GMTL_INCLUDE_DIR} )

set( VRJUGGLER_DEFINITIONS ${vrjuggler_FLAGPOLL_OTHER_DEFINITIONS} ${VAPOR_DEFINITIONS} )

mark_as_advanced( VRJUGGLER_INCLUDE_DIR VRJUGGLER_DEFINITIONS )
