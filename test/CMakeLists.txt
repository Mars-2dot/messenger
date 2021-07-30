cmake_minimum_required(VERSION 3.5)

project(ToxLite VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

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

include(cmake/ExternalProjectGtests.cmake)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Sql REQUIRED)
find_package(libsodium)
find_package(spdlog)
find_package(pthreads4w)
find_package(fmt)
find_package(Opus)
find_package(libvpx)
find_package(OpenSSL)

include_directories(${CMAKE_BINARY_DIR}/3rd/TOXCORE)
include_directories(G:/code/c-toxcore)

#link_directories(G:/code/c-toxcore/build/Release)

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
