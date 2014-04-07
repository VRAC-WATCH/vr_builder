# Find the Gadgeteer (libgadget) module from VR Juggler
#
# If found, will define:
#
#  GADGETEER_FOUND
#  GADGETEER_INCLUDE_DIRS
#  GADGETEER_LIBRARIES
#  GADGETEER_DEFINITIONS

find_package( Flagpoll )

set( FIND_PACKAGE_ARGS )

if( Gadgeteer_FIND_REQUIRED )
    list( APPEND FIND_PACKAGE_ARGS REQUIRED )
endif()

if( Gadgeteer_FIND_QUIETLY )
    list( APPEND FIND_PACKAGE_ARGS QUIET )
endif()

if( NOT JACKAL_FOUND )
    find_package( Jackal ${FIND_PACKAGE_ARGS} )
endif()

flagpoll_get_include_dirs( gadgeteer NO_DEPS )
flagpoll_get_library_dirs( gadgeteer NO_DEPS )
flagpoll_get_library_names( gadgeteer NO_DEPS )
flagpoll_get_module_version( gadgeteer NO_DEPS )
flagpoll_get_other_definitions( gadgeteer NO_DEPS )

find_path( GADGETEER_INCLUDE_DIR gadget/gadgetDefines.h
           HINTS ${gadgeteer_FLAGPOLL_INCLUDE_DIRS} )

include( FindPackageHandleStandardArgs )

set( GADGET_FAIL_MESSAGE
     "Could NOT find Gadgeteer. Is the FLAGPOLL_PATH environment variable set?"
     CACHE INTERNAL "" )

if( MSVC )
    set( GADGETEER_LIBRARY_DIRS ${gadgeteer_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( Gadgeteer
                                       REQUIRED_VARS GADGETEER_LIBRARY_DIRS GADGETEER_INCLUDE_DIR
                                       VERSION_VAR gadgeteer_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${GADGET_FAIL_MESSAGE} )
    set( GADGETEER_LIBRARIES )
    mark_as_advanced( GADGETEER_LIBRARY_DIRS )
    link_directories( ${GADGETEER_LIBRARY_DIRS} )
else()
    find_library( GADGETEER_LIBRARY NAMES ${gadgeteer_FLAGPOLL_LIBRARY_NAMES}
                  HINTS ${gadgeteer_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( Gadgeteer
                                       REQUIRED_VARS GADGETEER_LIBRARY GADGETEER_INCLUDE_DIR
                                       VERSION_VAR gadgeteer_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${GADGET_FAIL_MESSAGE} )
    set( GADGETEER_LIBRARIES ${GADGETEER_LIBRARY} ${JACKAL_LIBRARIES} )
    mark_as_advanced( GADGETEER_LIBRARY )
endif()

set( GADGETEER_INCLUDE_DIRS ${GADGETEER_INCLUDE_DIR} ${JACKAL_INCLUDE_DIRS} )

set( GADGETEER_DEFINITIONS ${gadgeteer_FLAGPOLL_OTHER_DEFINITIONS} ${VAPOR_DEFINITIONS} )

mark_as_advanced( GADGETEER_INCLUDE_DIR GADGETEER_DEFINITIONS )
