find_package(Threads REQUIRED)

include( ExternalProject )

set( TOXCORE_GIT "https://github.com/TokTok/c-toxcore.git" )

set(TMP_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/tmp)
set(STAMP_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/stamp)
set(LOG_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/log)

set( TOXCORE_ROOT ${CMAKE_BINARY_DIR}/3rd/TOXCORE )
set(TOXCORE_LIB  ${TOXCORE_ROOT}/Debug)
set( TOXCORE_INSTALL ${CMAKE_SOURCE_DIR}/dependencies/TOXCORE )
set( TOXCORE_LIB_DIRS ${TOXCORE_INSTALL}/lib )
set( TOXCORE_INCLUDE_DIR ${TOXCORE_INSTALL}/include/TOXCORE)
#set( TOXCORE_PO_PATH ${TOXCORE_LIB_DIRS}/libTOXCORE_program_options-vc${MSVC_TOOLSET_VERSION}-mt-gd-x64-1_77.lib)
#set( TOXCORE_FS_PATH ${TOXCORE_LIB_DIRS}/libTOXCORE_filesystem-vc${MSVC_TOOLSET_VERSION}-mt-gd-x64-1_77.lib )

file(MAKE_DIRECTORY ${TOXCORE_INCLUDE_DIR}/TOXCORE/filesystem)
file(MAKE_DIRECTORY ${TOXCORE_LIB_DIRS})
include_directories(${TOXCORE_ROOT})

 ExternalProject_Add( external_TOXCORE
        PREFIX 	       ${TOXCORE_ROOT}
        TMP_DIR        ${TMP_PATH}
        STAMP_DIR      ${STAMP_PATH}
        LOG_DIR        ${LOG_PATH}
        GIT_REPOSITORY ${TOXCORE_git}
        GIT_PROGRESS ON
        DOWNLOAD_DIR  ${CMAKE_BINARY_DIR}/3rd/TOXCORE
        SOURCE_DIR    ${CMAKE_BINARY_DIR}/3rd/TOXCORE
        BINARY_DIR    ${CMAKE_BINARY_DIR}/3rd/TOXCORE
#        CONFIGURE_COMMAND ""
#        BUILD_COMMAND ""
#        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
        BUILD_BYPRODUCTS ${TOXCORE_LIB}
        BUILD_BYPRODUCTS ${TOXCORE_LIB}/toxcore/tox.h
#        BUILD_BYPRODUCTS ${TOXCORE_FS_PATH}
#        BUILD_BYPRODUCTS ${TOXCORE_INCLUDE_DIR}/TOXCORE/filesystem/fstream.hpp
#        BUILD_BYPRODUCTS ${TOXCORE_INCLUDE_DIR}/TOXCORE/program_options.hpp
        )
    add_custom_target(${external_TOXCORE} COMMAND "conan install ."
        WORKING_DIRECTORY ${TOXCORE_ROOT})
