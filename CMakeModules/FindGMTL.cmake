# Find the Generic Math Template Library (GMTL)
#
# If found, will define:
#
#  GMTL_FOUND
#  GMTL_INCLUDE_DIRS

find_package( Flagpoll )

flagpoll_get_include_dirs( gmtl NO_DEPS )
flagpoll_get_module_version( gmtl NO_DEPS )

find_path( GMTL_INCLUDE_DIR gmtl/gmtl.h
           HINTS ${gmtl_FLAGPOLL_INCLUDE_DIRS} )

set( GMTL_INCLUDE_DIRS ${GMTL_INCLUDE_DIR} )

include( FindPackageHandleStandardArgs )

set( GMTL_FAIL_MESSAGE
     "Could NOT find GMTL. Is the FLAGPOLL_PATH environment variable set?"
     CACHE INTERNAL "" )

find_package_handle_standard_args( GMTL
                                   REQUIRED_VARS GMTL_INCLUDE_DIR
                                   VERSION_VAR gmtl_FLAGPOLL_MODULE_VERSION
                                   FAIL_MESSAGE ${GMTL_FAIL_MESSAGE} )

mark_as_advanced( GMTL_INCLUDE_DIR )
