# Find the Vapor (libvpr) module from VR Juggler
#
# If found, will define:
#
#  VAPOR_FOUND
#  VAPOR_INCLUDE_DIRS
#  VAPOR_LIBRARIES
#  VAPOR_DEFINITIONS

find_package( Flagpoll )

set( FIND_PACKAGE_ARGS )

if( Vapor_FIND_REQUIRED )
    list( APPEND FIND_PACKAGE_ARGS REQUIRED )
endif()

if( Vapor_FIND_QUIETLY )
    list( APPEND FIND_PACKAGE_ARGS QUIET )
endif()

find_package( CppDOM ${FIND_PACKAGE_ARGS} )

set( VPR_BOOST_COMPONENTS filesystem signals system )

if( WIN32 )
    list( APPEND VPR_BOOST_COMPONENTS date_time )
endif()

find_package( Boost COMPONENTS ${VPR_BOOST_COMPONENTS} ${FIND_PACKAGE_ARGS} )

flagpoll_get_include_dirs( vpr NO_DEPS )
flagpoll_get_library_dirs( vpr NO_DEPS )
flagpoll_get_library_names( vpr NO_DEPS )
flagpoll_get_module_version( vpr NO_DEPS )
flagpoll_get_other_definitions( vpr NO_DEPS )

find_path( VAPOR_INCLUDE_DIR vpr/vpr.h
           HINTS ${vpr_FLAGPOLL_INCLUDE_DIRS} )

include( FindPackageHandleStandardArgs )

set( VAPOR_FAIL_MESSAGE
     "Could NOT find Vapor. Is the FLAGPOLL_PATH environment variable set?"
     CACHE INTERNAL "" )

if( MSVC )
    set( VAPOR_LIBRARY_DIRS ${vpr_FLAGPOLL_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS} )
    find_package_handle_standard_args( Vapor
                                       REQUIRED_VARS VAPOR_LIBRARY_DIRS VAPOR_INCLUDE_DIR
                                       VERSION_VAR vpr_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${VAPOR_FAIL_MESSAGE} )
    set( VAPOR_LIBRARIES )
    mark_as_advanced( VAPOR_LIBRARY_DIRS )
    link_directories( ${VAPOR_LIBRARY_DIRS} )
else()
    find_library( VAPOR_LIBRARY NAMES ${vpr_FLAGPOLL_LIBRARY_NAMES}
                  HINTS ${vpr_FLAGPOLL_LIBRARY_DIRS} )
    find_package_handle_standard_args( Vapor
                                       REQUIRED_VARS VAPOR_LIBRARY VAPOR_INCLUDE_DIR
                                       VERSION_VAR vpr_FLAGPOLL_MODULE_VERSION
                                       FAIL_MESSAGE ${VAPOR_FAIL_MESSAGE} )
    set( VAPOR_LIBRARIES ${VAPOR_LIBRARY}
                         ${CPPDOM_LIBRARIES}
		                 ${Boost_LIBRARIES} )
    mark_as_advanced( VAPOR_LIBRARY )
endif()

set( VAPOR_INCLUDE_DIRS ${VAPOR_INCLUDE_DIR}
                        ${CPPDOM_INCLUDE_DIR}
                        ${Boost_INCLUDE_DIR} )

set( VAPOR_DEFINITIONS ${vpr_FLAGPOLL_OTHER_DEFINITIONS} )

mark_as_advanced( VAPOR_INCLUDE_DIR VAPOR_DEFINITIONS )
