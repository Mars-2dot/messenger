cmake_minimum_required(VERSION 3.5)

project(ToxLite VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES
    libsodium/1.0.18
    pthreads4w/3.0.0
    opus/1.3.1
    libvpx/1.9.0
    spdlog/1.8.5
    openssl/1.1.1k
    GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conan-center
                    SETTINGS ${settings})

include(cmake/toxcore.cmake)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Sql REQUIRED)
#find_package(spdlog PATHS ${CMAKE_BINARY_DIR} REQUIRED)
#find_package(toxcore  REQUIRED)
include_directories(${CMAKE_BINARY_DIR}/Findlibsodium.cmake)
include_directories(${LIBSODIUM_INCLUDES})
include_directories(C:/.conan/c8a6ec/1/include)

set(SOURCE_FILES
        main.cpp
        core.cpp
        convertstring.cpp
        database.cpp
        messenger.cpp
    )

set(HEADER_FILES
        messenger.h
        core.h
        convertstring.h
        database.h
        qtincludes.h
    )

set(GUI_FILES
        messenger.ui
        resources.qrc
    )

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${GUI_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ToxLite
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ToxLite SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ToxLite
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ToxLite PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Sql
    ${libsodium_LIBRARIES}
    C:/.conan/c8a6ec/1/lib/libsodium.lib
    ${external_TOXCORE}
    )

set_target_properties(ToxLite PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ToxLite)
endif()
