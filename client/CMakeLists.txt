cmake_minimum_required(VERSION 3.5)

project(Client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

set(SOURCE_FILES
        main.cpp
        messenger.cpp
        netcontroller.cpp
    )

set(HEADER_FILES
        netcontroller.h
        messenger.h
        qtincludes.h
    )

set(GUI_FILES
        messenger.ui
    )

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${GUI_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Client
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Client SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Client
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::Network)
