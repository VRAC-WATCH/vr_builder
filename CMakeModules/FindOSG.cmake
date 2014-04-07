##################################################################################
#
# This module defines:
#
# - OSG_DIR (where the OSG installation was installed)
# - OSG_LIBRARIES (where to find the libraries)
# - OSG_FOUND (whether the headers and libraries were found)
# - OSG_INCLUDE_DIR (where to find the headers)
#
# Created by Robert Osfield.
# Updated for VIPRE by Christian Noon.
#
##################################################################################

FIND_PATH (OSG_INCLUDE_DIR osg/Node
    ${OSG_DIR}/include
    $ENV{OSG_DIR}/include
    $ENV{OSG_DIR}
    $ENV{OSGDIR}/include
    $ENV{OSGDIR}
    $ENV{OSG_ROOT}/include
    NO_DEFAULT_PATH
)

#FIND_PATH (OSG_INCLUDE_DIR osg/Node)

MACRO (FIND_OSG_LIBRARY MYLIBRARY MYLIBRARYNAME)

    FIND_LIBRARY ("${MYLIBRARY}_DEBUG"
        NAMES "${MYLIBRARYNAME}d"
        PATHS
        ${OSG_DIR}/lib/Debug
        ${OSG_DIR}/lib64/Debug
        ${OSG_DIR}/lib
        ${OSG_DIR}/lib64
        $ENV{OSG_DIR}/lib/debug
        $ENV{OSG_DIR}/lib64/debug
        $ENV{OSG_DIR}/lib
        $ENV{OSG_DIR}/lib64
        $ENV{OSG_DIR}
        $ENV{OSGDIR}/lib
        $ENV{OSGDIR}/lib64
        $ENV{OSGDIR}
        $ENV{OSG_ROOT}/lib
        $ENV{OSG_ROOT}/lib64
        NO_DEFAULT_PATH
    )

    FIND_LIBRARY ("${MYLIBRARY}_DEBUG"
        NAMES "${MYLIBRARYNAME}d"
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/local/lib64
        /usr/lib
        /usr/lib64
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/lib
        /usr/freeware/lib64
    )

    FIND_LIBRARY (${MYLIBRARY}
        NAMES "${MYLIBRARYNAME}"
        PATHS
        ${OSG_DIR}/lib/Release
        ${OSG_DIR}/lib64/Release
        ${OSG_DIR}/lib
        ${OSG_DIR}/lib64
        $ENV{OSG_DIR}/lib/Release
        $ENV{OSG_DIR}/lib64/Release
        $ENV{OSG_DIR}/lib
        $ENV{OSG_DIR}/lib64
        $ENV{OSG_DIR}
        $ENV{OSGDIR}/lib
        $ENV{OSGDIR}/lib64
        $ENV{OSGDIR}
        $ENV{OSG_ROOT}/lib
        $ENV{OSG_ROOT}/lib64
        NO_DEFAULT_PATH
    )

    FIND_LIBRARY (${MYLIBRARY}
        NAMES "${MYLIBRARYNAME}"
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/local/lib64
        /usr/lib
        /usr/lib64
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/lib
        /usr/freeware/lib64
    )

	# Set the debug version to the release if the debug couldn't be found
    IF (NOT ${MYLIBRARY}_DEBUG)
        IF (${MYLIBRARY})
            SET (${MYLIBRARY}_DEBUG ${${MYLIBRARY}})
        ENDIF ()
    ENDIF ()

	# Bake both debug and release into the same variable
    SET (${MYLIBRARY} optimized ${${MYLIBRARY}} debug ${${MYLIBRARY}_DEBUG})

ENDMACRO (FIND_OSG_LIBRARY LIBRARY LIBRARYNAME)

# Go fetch all the libraries we need
FIND_OSG_LIBRARY (OSG_OpenThreads_LIBRARY OpenThreads)
FIND_OSG_LIBRARY (OSG_osg_LIBRARY osg)
FIND_OSG_LIBRARY (OSG_osgDB_LIBRARY osgDB)
FIND_OSG_LIBRARY (OSG_osgGA_LIBRARY osgGA)
FIND_OSG_LIBRARY (OSG_osgText_LIBRARY osgText)
FIND_OSG_LIBRARY (OSG_osgUtil_LIBRARY osgUtil)
FIND_OSG_LIBRARY (OSG_osgViewer_LIBRARY osgViewer)
FIND_OSG_LIBRARY (OSG_osgQt_LIBRARY osgQt)

# Build the OSG_LIBRARIES variable
SET (OSG_FOUND "NO")
IF (OSG_OpenThreads_LIBRARY
    AND OSG_osg_LIBRARY
    AND OSG_osgDB_LIBRARY
    AND OSG_osgGA_LIBRARY
    AND OSG_osgText_LIBRARY
    AND OSG_osgUtil_LIBRARY
    AND OSG_osgViewer_LIBRARY)

    SET (OSG_FOUND "YES")
    SET (OSG_LIBRARIES
        ${OSG_OpenThreads_LIBRARY}
        ${OSG_osg_LIBRARY}
        ${OSG_osgDB_LIBRARY}
        ${OSG_osgGA_LIBRARY}
        ${OSG_osgText_LIBRARY}
        ${OSG_osgUtil_LIBRARY}
        ${OSG_osgViewer_LIBRARY}
    )

ENDIF ()

# Add the ability to just set the OSG_DIR and let CMake figure the rest out
IF (NOT OSG_FOUND)
	SET (OSG_DIR "" CACHE PATH "Root of OSG installation tree (optional).")
ENDIF ()