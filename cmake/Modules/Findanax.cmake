# define the ANAX_STATIC_LIBRARIES macro if static build was chosen
# note: just set(ANAX_STATIC_LIBRARIES true) before you find_package(anax)
if(ANAX_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

# deduce the libraries suffix from the options
set(FIND_ANAX_LIB_SUFFIX "")
if(ANAX_STATIC_LIBRARIES)
    set(FIND_ANAX_LIB_SUFFIX "${FIND_ANAX_LIB_SUFFIX}_s")
endif()


set(FIND_ANAX_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt)

find_path(ANAX_INCLUDE_DIR anax/anax.hpp PATH_SUFFIXES include PATHS ${FIND_ANAX_PATHS})

# debug
find_library(ANAX_LIBRARY_DEBUG NAMES "anax_d${FIND_ANAX_LIB_SUFFIX}" "libanax_d${FIND_ANAX_LIB_SUFFIX}" PATH_SUFFIXES lib lib64 PATHS ${FIND_ANAX_PATHS})

# release
find_library(ANAX_LIBRARY_RELEASE NAMES "anax${FIND_ANAX_LIB_SUFFIX}" "libanax${FIND_ANAX_LIB_SUFFIX}" PATH_SUFFIXES lib lib64 PATHS ${FIND_ANAX_PATHS})

set(ANAX_LIBRARIES ${ANAX_LIBRARY_DEBUG} ${ANAX_LIBRARY_RELEASE})
set(ANAX_INCLUDE_DIR ${ANAX_INCLUDE_DIR})
