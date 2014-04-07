# Find the Jackal (libjccl) module from VR Juggler
#
# If found, will define:
#
#  JACKAL_FOUND
#  JACKAL_INCLUDE_DIRS
#  JACKAL_LIBRARIES
#  JACKAL_DEFINITIONS

find_package( Flagpoll )

set( FIND_PACKAGE_ARGS )

if( Jackal_FIND_REQUIRED )
    list( APPEND FIND_PACKAGE_ARGS REQUIRED )
endif()

if( Jackal_FIND_QUIETLY )
    list( APPEND FIND_PACKAGE_ARGS QUIET )
endif()

if( NOT VAPOR_FOUND )
    find_package( Vapor ${FIND_PACKAGE_ARGS} )
endif()

flagpoll_get_include_dirs( jccl NO_DEPS )
flagpoll_get_library_dirs( jccl NO_DEPS )
flagpoll_get_library_names( jccl NO_DEPS )
flagpoll_get_module_version( jccl NO_DEPS )
flagpoll_get_other_definitions( jccl NO_DEPS )

find_path( JACKAL_INCLUDE_DIR jccl/jcclDefines.h
           HINTS ${jccl_FLAGPOLL_INCLUDE_DIRS} )

include( FindPackageHandleStandardArgs )

set( JACKAL_FAIL_MESSAGE
     "Could NOT find Jackal. Is the FLAGPOLL_PATH environment variable set?"
     CACHE INTERNAL "" )

if( MSVC )
    set( JACKAL_LIBRARY_DIRS ${jccl_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( Jackal
                                       REQUIRED_VARS JACKAL_LIBRARY_DIRS JACKAL_INCLUDE_DIR
                                       VERSION_VAR jccl_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${JACKAL_FAIL_MESSAGE} )
    set( JACKAL_LIBRARIES )
    mark_as_advanced( JACKAL_LIBRARY_DIRS )
    link_directories( ${JACKAL_LIBRARY_DIRS} )
else()
    find_library( JACKAL_LIBRARY NAMES ${jccl_FLAGPOLL_LIBRARY_NAMES}
                  HINTS ${jccl_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( Jackal
                                       REQUIRED_VARS JACKAL_LIBRARY JACKAL_INCLUDE_DIR
                                       VERSION_VAR jccl_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${JACKAL_FAIL_MESSAGE} )
    set( JACKAL_LIBRARIES ${JACKAL_LIBRARY} ${VAPOR_LIBRARIES} )
    mark_as_advanced( JACKAL_LIBRARY )
endif()

set( JACKAL_INCLUDE_DIRS ${JACKAL_INCLUDE_DIR} ${VAPOR_INCLUDE_DIRS} )
set( JACKAL_DEFINITIONS ${jccl_FLAGPOLL_OTHER_DEFINITIONS} ${VAPOR_DEFINITIONS} )

mark_as_advanced( JACKAL_INCLUDE_DIR JACKAL_DEFINITIONS )
