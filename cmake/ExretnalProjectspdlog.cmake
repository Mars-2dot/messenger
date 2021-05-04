find_package(Threads REQUIRED)
include(ExternalProject)

set(TMP_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/tmp)
set(STAMP_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/stamp)
set(LOG_PATH ${CMAKE_BINARY_DIR}/3rd/external_files/log)

set(SPDLOG_URL https://github.com/gabime/spdlog.git)

set(SPDLOG_ROOT ${CMAKE_BINARY_DIR}/3rd/spdlog)
set(SPDLOG_LIB_PATH ${SPDLOG_ROOT}/spdlogd.lib)
set(SPDLOG_INCLUDE_DIRS ${SPDLOG_ROOT}/include)
set(SPDLOG_INSTALL_CMAKE ${CMAKE_BINARY_DIR}/dependencies/spdlog)

ExternalProject_Add(spdlog
    PREFIX            ${SPDLOG_ROOT}
    DOWNLOAD_DIR      ${SPDLOG_ROOT}
    SOURCE_DIR        ${SPDLOG_ROOT}
    BINARY_DIR        ${SPDLOG_ROOT}
    INSTALL_DIR       ${SPDLOG_INSTALL_CMAKE}
    TMP_DIR           ${TMP_PATH}
    STAMP_DIR         ${STAMP_PATH}
    LOG_DIR 	      ${LOG_PATH}
    GIT_REPOSITORY    ${SPDLOG_URL}
    GIT_TAG           v1.8.5
    INSTALL_COMMAND ""
    BUILD_COMMAND     ${CMAKE_COMMAND} --build ${SPDLOG_ROOT} --config Release
    BUILD_BYPRODUCTS  ${SPDLOG_LIB_PATH}
)

file(MAKE_DIRECTORY ${SPDLOG_INSTALL_CMAKE})

if(UNIX)
        set(SPDLOG_LIBRARY_PATH ${SPDLOG_ROOT}/lib/spdlog.a)
else ()
        set(SPDLOG_LIBRARY_PATH ${SPDLOG_LIB_PATH})
endif ()

include_directories(${SPDLOG_INCLUDE_DIRS})

link_directories(${SPDLOG_ROOT}/Debug)

add_library(spdlog::spdlog UNKNOWN IMPORTED)
set_target_properties(spdlog::spdlog PROPERTIES
    "IMPORTED_LOCATION" "${SPDLOG_LIB_PATH}"
    "INCLUDE_DIRECTORIES" "${SPDLOG_INCLUDE_DIRS}"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
add_dependencies(spdlog::spdlog spdlog)

add_custom_command(
        TARGET spdlog POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${SPDLOG_INCLUDE_DIRS}
                ${SPDLOG_INSTALL_CMAKE}/include)
add_custom_command(
        TARGET spdlog POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/3rd/spdlog/spdlogd.lib
                ${SPDLOG_INSTALL_CMAKE}/lib/spdlogd.lib)
add_custom_command(
        TARGET spdlog POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_BINARY_DIR}/3rd/spdlog/CMakeFiles/Export/lib/
                ${SPDLOG_INSTALL_CMAKE}/lib)
add_custom_command(
        TARGET spdlog POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/3rd/spdlog/spdlogConfig.cmake
                ${CMAKE_BINARY_DIR}/3rd/spdlog/spdlogConfigVersion.cmake
                ${CMAKE_BINARY_DIR}/dependencies/spdlog/lib/cmake/spdlog)
add_custom_command(
        TARGET spdlog POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/3rd/spdlog/spdlog.pc
                ${SPDLOG_INSTALL_CMAKE}/lib/pkgconfig)
