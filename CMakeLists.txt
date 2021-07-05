cmake_minimum_required(VERSION 3.5)

project(ToxLite VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Sql REQUIRED)

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
    sodium
    toxcore
    spdlog
    /usr/local/lib/
    )

set_target_properties(ToxLite PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ToxLite)
endif()
