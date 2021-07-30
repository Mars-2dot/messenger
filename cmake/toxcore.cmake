find_package(Threads REQUIRED)

include(ExternalProject)

set(TMP_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/tmp)
set(STAMP_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/stamp)
set(LOG_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/log)

set(ctoxcore_ROOT ${CMAKE_BINARY_DIR}/3rd/ctoxcore)
set(ctoxcore_INCLUDE_DIR ${ctoxcore_ROOT}/ctoxcore/include)
set(GMOCK_INCLUDE ${ctoxcore_ROOT}/googlemock/include)

set(ctoxcore_INSTALL_CMAKE ${CMAKE_SOURCE_DIR}/dependencies/ctoxcore)
set(ctoxcore_LIB ${ctoxcore_INSTALL_CMAKE}/lib/gtestd.lib)
set(ctoxcore_LIB_MAIN ${ctoxcore_INSTALL_CMAKE}/lib/gtest_maind.lib)
set(GMOCK_LIB ${ctoxcore_INSTALL_CMAKE}/lib/gmockd.lib)
set(GMOCK_LIB_MAIN ${ctoxcore_INSTALL_CMAKE}/lib/gmock_maind.lib)

ExternalProject_Add( ctoxcore
    PREFIX            ${ctoxcore_ROOT}
    DOWNLOAD_DIR      ${ctoxcore_ROOT}
    SOURCE_DIR        ${ctoxcore_ROOT}
    BINARY_DIR        ${ctoxcore_ROOT}
    TMP_DIR           ${TMP_PATH}
    STAMP_DIR         ${STAMP_PATH}
    LOG_DIR 	      ${LOG_PATH}
    GIT_REPOSITORY    https://github.com/google/ctoxcore.git
#    CMAKE_ARGS        "-Dgtest_force_shared_crt=ON"
    BUILD_COMMAND     ${CMAKE_COMMAND} --build ${ctoxcore_ROOT} --config Release
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    BUILD_BYPRODUCTS ${ctoxcore_LIB}
    BUILD_BYPRODUCTS ${ctoxcore_LIB_MAIN}
    BUILD_BYPRODUCTS ${GMOCK_LIB}
    BUILD_BYPRODUCTS ${GMOCK_LIB_MAIN}
  )

file(MAKE_DIRECTORY ${ctoxcore_INCLUDE_DIR})
file(MAKE_DIRECTORY ${GMOCK_INCLUDE})

include_directories(${ctoxcore_INCLUDE_DIR})

#set(ctoxcore_LIBRARY_DEBUG GTest)
#add_library(GTest::gtest UNKNOWN IMPORTED)
#set_property( TARGET GTest::gtest PROPERTY IMPORTED_LOCATION  ${ctoxcore_LIB} )
#set_property( TARGET GTest::gtest PROPERTY INCLUDE_DIRECTORIES  ${ctoxcore_INCLUDE_DIR} )
#set_property( TARGET GTest::gtest PROPERTY IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT} )
#set_property( TARGET GTest::gtest PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${ctoxcore_INCLUDE_DIRS} )
#add_dependencies(GTest::gtest ctoxcore)

#set(ctoxcore_LIBRARY_MAIN_DEBUG GTest_main)
#add_library(GTest::gtest_main UNKNOWN IMPORTED)
#set_property( TARGET GTest::gtest_main PROPERTY IMPORTED_LOCATION  ${ctoxcore_LIB_MAIN} )
#set_property( TARGET GTest::gtest_main PROPERTY INCLUDE_DIRECTORIES  ${ctoxcore_INCLUDE_DIR} )
#set_property( TARGET GTest::gtest_main PROPERTY IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT} )
#set_property( TARGET GTest::gtest_main PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${ctoxcore_INCLUDE_DIRS} )
#add_dependencies(GTest::gtest_main ctoxcore)

#set(GMOCK_LIBRARY_DEBUG GMock)
#add_library(${GMOCK_LIBRARY_DEBUG} UNKNOWN IMPORTED)
#set_property( TARGET ${GMOCK_LIBRARY_DEBUG} PROPERTY IMPORTED_LOCATION  ${GMOCK_LIB} )
#set_property( TARGET ${GMOCK_LIBRARY_DEBUG} PROPERTY INCLUDE_DIRECTORIES  ${ctoxcore_INCLUDE_DIR} )
#set_property( TARGET ${GMOCK_LIBRARY_DEBUG} PROPERTY IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT} )
#set_property( TARGET ${GMOCK_LIBRARY_DEBUG} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${ctoxcore_INCLUDE_DIRS} )
#add_dependencies(${GMOCK_LIBRARY_DEBUG} ctoxcore)

#set(GMOCK_LIBRARY_MAIN_DEBUG GMock_main)
#add_library(${GMOCK_LIBRARY_MAIN_DEBUG} UNKNOWN IMPORTED)
#set_property( TARGET ${GMOCK_LIBRARY_MAIN_DEBUG} PROPERTY IMPORTED_LOCATION  ${GMOCK_LIB_MAIN} )
#set_property( TARGET ${GMOCK_LIBRARY_MAIN_DEBUG} PROPERTY INCLUDE_DIRECTORIES  ${ctoxcore_INCLUDE_DIR} )
#set_property( TARGET ${GMOCK_LIBRARY_MAIN_DEBUG} PROPERTY IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT} )
#set_property( TARGET ${GMOCK_LIBRARY_MAIN_DEBUG} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${ctoxcore_INCLUDE_DIRS} )
#add_dependencies(${GMOCK_LIBRARY_MAIN_DEBUG} ctoxcore)

#set(ctoxcore_INSTALL_CMAKE_INCLUDE ${ctoxcore_INSTALL_CMAKE}/include)
#set(ctoxcore_INSTALL_CMAKE_LIB ${ctoxcore_INSTALL_CMAKE}/lib)
#set(ctoxcore_INSTALL_CMAKE_FIND ${ctoxcore_INSTALL_CMAKE}/lib/cmake)
#set(ctoxcore_INSTALL_CMAKE_PKGCNF ${ctoxcore_INSTALL_CMAKE}/lib/pkgconfig)

#file(MAKE_DIRECTORY ${ctoxcore_INSTALL_CMAKE})
#file(MAKE_DIRECTORY ${ctoxcore_INSTALL_CMAKE_INCLUDE})
#file(MAKE_DIRECTORY ${ctoxcore_INSTALL_CMAKE_LIB})
#file(MAKE_DIRECTORY ${ctoxcore_INSTALL_CMAKE_FIND})
#file(MAKE_DIRECTORY ${ctoxcore_INSTALL_CMAKE_PKGCNF})

#add_custom_command(
#        TARGET ctoxcore POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy_directory
#                ${CMAKE_BINARY_DIR}/3rd/ctoxcore/googletest/include
#                ${ctoxcore_INSTALL_CMAKE}/include)
#add_custom_command(
#        TARGET ctoxcore POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy_directory
#                ${CMAKE_BINARY_DIR}/3rd/ctoxcore/lib
#                ${ctoxcore_INSTALL_CMAKE}/lib)
#add_custom_command(
#        TARGET ctoxcore POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy_directory
#                ${CMAKE_BINARY_DIR}/3rd/ctoxcore/googletest/CMakeFiles/Export/lib/cmake
#                ${ctoxcore_INSTALL_CMAKE}/lib/cmake)
#add_custom_command(
#        TARGET ctoxcore POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_BINARY_DIR}/3rd/ctoxcore/googletest/generated/GTestConfig.cmake
#                ${CMAKE_BINARY_DIR}/3rd/ctoxcore/googletest/generated/GTestConfigVersion.cmake
#                ${ctoxcore_INSTALL_CMAKE}/lib/cmake/GTest)
#add_custom_command(
#        TARGET ctoxcore POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_BINARY_DIR}/3rd/ctoxcore/googletest/generated/gtest.pc
#                ${CMAKE_BINARY_DIR}/3rd/ctoxcore/googletest/generated/gtest_main.pc
#                ${ctoxcore_INSTALL_CMAKE}/lib/pkgconfig)
