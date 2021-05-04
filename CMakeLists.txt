cmake_minimum_required(VERSION 3.5)

project(Messenger LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Sql REQUIRED)
find_package(spdlog PATHS ${CMAKE_BINARY_DIR}/dependencies/spdlog/lib/cmake/spdlog)

if(spdlog_FOUND)
    message("***Logger found***")
else()
    message("***Logger not found***")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ExretnalProjectspdlog.cmake)
endif()

#set(PROJECT_SOURCES
#        main.cpp
#        messenger.cpp
#        messenger.h
#        messenger.ui
#)

set(SOURCE_FILES
        main.cpp
        diskapi.cpp
        messenger.cpp
        node.cpp
        database.cpp
        netcontroller.cpp
    )

set(HEADER_FILES
        netcontroller.h
        diskapi.h
        node.h
        messenger.h
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
    qt_add_executable(Messenger
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Messenger SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Messenger
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Messenger PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Sql spdlog::spdlog)
