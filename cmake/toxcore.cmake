find_package(Threads REQUIRED)

include( ExternalProject )

set( TOXCORE_GIT "https://github.com/TokTok/c-toxcore.git" )

set(TMP_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/tmp)
set(STAMP_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/stamp)
set(LOG_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/log)

set( TOXCORE_ROOT ${CMAKE_BINARY_DIR}/3rd/TOXCORE )
set( TOXCORE_INSTALL ${CMAKE_SOURCE_DIR}/dependencies/TOXCORE )
set( TOXCORE_LIB_DIRS ${boost_INSTALL}/lib )
set( Boost_INCLUDE_DIR ${TOXCORE_INSTALL}/include/TOXCORE)
#set( TOXCORE_PO_PATH ${TOXCORE_LIB_DIRS}/libboost_program_options-vc${MSVC_TOOLSET_VERSION}-mt-gd-x64-1_77.lib)
#set( TOXCORE_FS_PATH ${TOXCORE_LIB_DIRS}/libboost_filesystem-vc${MSVC_TOOLSET_VERSION}-mt-gd-x64-1_77.lib )

file(MAKE_DIRECTORY ${Boost_INCLUDE_DIR}/TOXCORE/filesystem)
file(MAKE_DIRECTORY ${TOXCORE_LIB_DIRS})

ExternalProject_Add( external_TOXCORE
        PREFIX 	       ${TOXCORE_ROOT}
        TMP_DIR        ${TMP_PATH}
        STAMP_DIR      ${STAMP_PATH}
        LOG_DIR        ${LOG_PATH}
        GIT_REPOSITORY ${TOXCORE_git}
#        GIT_TAG 	TOXCORE-1.75.0
#        GIT_SUBMODULES	""
#        GIT_SUBMODULES_RECURSE ON
#        GIT_SHALLOW ON
        GIT_PROGRESS ON
#        BUILD_IN_SOURCE 1
        DOWNLOAD_DIR  ${CMAKE_BINARY_DIR}/3rd/TOXCORE
        SOURCE_DIR    ${CMAKE_BINARY_DIR}/3rd/TOXCORE
        CONFIGURE_COMMAND ""
        BUILD_COMMAND conan install .
#             b2 toolset=msvc address-model=64 link=static variant=debug threading=multi install --prefix=${TOXCORE_INSTALL}
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
#        BUILD_BYPRODUCTS ${TOXCORE_PO_PATH}
#        BUILD_BYPRODUCTS ${TOXCORE_FS_PATH}
#        BUILD_BYPRODUCTS ${Boost_INCLUDE_DIR}/TOXCORE/filesystem/fstream.hpp
#        BUILD_BYPRODUCTS ${Boost_INCLUDE_DIR}/TOXCORE/program_options.hpp
        )
