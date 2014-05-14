# - Config file for the osgWorks package
# It defines the following variables
#  OSGWORKS_INCLUDE_DIRS - include directories for osgWorks
#  OSGWORKS_LIBRARIES    - libraries to link against
#  OSGWORKS_EXECUTABLE   - the bar executable


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was osgWorksConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

# These are IMPORTED targets created by osgWorksLibraryDepends.cmake
set(OSGWORKS_LIBRARIES "osgwTools;osgwQuery;osgwMx;osgwControls" )
set(OSGWORKS_EXECUTABLE test)

# Compute paths
# get_filename_component(OSGWORKS_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${PACKAGE_PREFIX_DIR}/CMakeCache.txt")
    # In build tree
    include("${PACKAGE_PREFIX_DIR}/lib/osgWorksBuildTreeSettings.cmake")
    # Our library dependencies (contains definitions for IMPORTED targets)
    include("${PACKAGE_PREFIX_DIR}/lib/osgWorksLibraryDepends.cmake")
else()
    set_and_check(OSGWORKS_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include")
    # The osgWorks targets file.
    if(EXISTS "${PACKAGE_PREFIX_DIR}/lib/osgworks-targets.cmake")
        include("${PACKAGE_PREFIX_DIR}/lib/osgworks-targets.cmake")
    endif()
endif()

# The location of the UseosgWorks.cmake file.
set(osgWorks_USE_FILE "${PACKAGE_PREFIX_DIR}/lib/UseosgWorks.cmake")
