# Find the Sonix (libsonix) module from VR Juggler
#
# If found, will define:
#
#  SONIX_FOUND
#  SONIX_INCLUDE_DIRS
#  SONIX_LIBRARIES
#  SONIX_DEFINITIONS

find_package( Flagpoll )

set( FIND_PACKAGE_ARGS )

if( Sonix_FIND_REQUIRED )
    list( APPEND FIND_PACKAGE_ARGS REQUIRED )
endif()

if( Sonix_FIND_QUIETLY )
    list( APPEND FIND_PACKAGE_ARGS QUIET )
endif()

if( NOT VAPOR_FOUND )
    find_package( Vapor ${FIND_PACKAGE_ARGS} )
endif()

flagpoll_get_include_dirs( sonix NO_DEPS )
flagpoll_get_library_dirs( sonix NO_DEPS )
flagpoll_get_library_names( sonix NO_DEPS )
flagpoll_get_module_version( sonix NO_DEPS )
flagpoll_get_other_definitions( sonix NO_DEPS )

find_path( SONIX_INCLUDE_DIR snx/sonix.h
           HINTS ${sonix_FLAGPOLL_INCLUDE_DIRS} )

include( FindPackageHandleStandardArgs )

set( SONIX_FAIL_MESSAGE
     "Could NOT find Sonix. Is the FLAGPOLL_PATH environment variable set?"
     CACHE INTERNAL "" )

if( MSVC )
    set( SONIX_LIBRARY_DIRS ${sonix_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( Sonix
                                       REQUIRED_VARS SONIX_LIBRARY_DIRS SONIX_INCLUDE_DIR
                                       VERSION_VAR sonix_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${SONIX_FAIL_MESSAGE} )
    set( SONIX_LIBRARIES )
    mark_as_advanced( SONIX_LIBRARY_DIRS )
    link_directories( ${SONIX_LIBRARY_DIRS} )
else()
    find_library( SONIX_LIBRARY NAMES ${sonix_FLAGPOLL_LIBRARY_NAMES}
                  HINTS ${sonix_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( Sonix
                                       REQUIRED_VARS SONIX_LIBRARY SONIX_INCLUDE_DIR
                                       VERSION_VAR sonix_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${SONIX_FAIL_MESSAGE} )
    set( SONIX_LIBRARIES ${SONIX_LIBRARY} ${VAPOR_LIBRARIES} )
    mark_as_advanced( SONIX_LIBRARY )
endif()

set( SONIX_INCLUDE_DIRS ${SONIX_INCLUDE_DIR} ${VAPOR_INCLUDE_DIRS} )
set( SONIX_DEFINITIONS ${sonix_FLAGPOLL_OTHER_DEFINITIONS} ${VAPOR_DEFINITIONS} )

mark_as_advanced( SONIX_INCLUDE_DIR SONIX_DEFINITIONS )
