cmake_minimum_required(VERSION 3.5)

project(Server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Sql REQUIRED)

find_package(spdlog PATHS ${CMAKE_BINARY_DIR}/dependencies/spdlog/lib/cmake/spdlog)

if(spdlog_FOUND)
    message("***Logger found***")
else()
    message("***Logger not found***")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ExretnalProjectspdlog.cmake)
endif()

set(SOURCE_FILES
        main.cpp
        database.cpp
        server.cpp
    )

set(HEADER_FILES
        server.h
        database.h
        qtincludes.h
    )

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Server
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Server SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Server
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Server PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Sql spdlog::spdlog)
