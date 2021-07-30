########## MACROS ###########################################################################
#############################################################################################

function(conan_message MESSAGE_OUTPUT)
    if(NOT CONAN_CMAKE_SILENT_OUTPUT)
        message(${ARGV${0}})
    endif()
endfunction()


macro(conan_find_apple_frameworks FRAMEWORKS_FOUND FRAMEWORKS FRAMEWORKS_DIRS)
    if(APPLE)
        foreach(_FRAMEWORK ${FRAMEWORKS})
            # https://cmake.org/pipermail/cmake-developers/2017-August/030199.html
            find_library(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND NAME ${_FRAMEWORK} PATHS ${FRAMEWORKS_DIRS} CMAKE_FIND_ROOT_PATH_BOTH)
            if(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND)
                list(APPEND ${FRAMEWORKS_FOUND} ${CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND})
            else()
                message(FATAL_ERROR "Framework library ${_FRAMEWORK} not found in paths: ${FRAMEWORKS_DIRS}")
            endif()
        endforeach()
    endif()
endmacro()


function(conan_package_library_targets libraries package_libdir deps out_libraries out_libraries_target build_type package_name)
    unset(_CONAN_ACTUAL_TARGETS CACHE)
    unset(_CONAN_FOUND_SYSTEM_LIBS CACHE)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAME ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            list(APPEND _out_libraries ${CONAN_FOUND_LIBRARY})
            if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
                # Create a micro-target for each lib/a found
                set(_LIB_NAME CONAN_LIB::${package_name}_${_LIBRARY_NAME}${build_type})
                if(NOT TARGET ${_LIB_NAME})
                    # Create a micro-target for each lib/a found
                    add_library(${_LIB_NAME} UNKNOWN IMPORTED)
                    set_target_properties(${_LIB_NAME} PROPERTIES IMPORTED_LOCATION ${CONAN_FOUND_LIBRARY})
                    set(_CONAN_ACTUAL_TARGETS ${_CONAN_ACTUAL_TARGETS} ${_LIB_NAME})
                else()
                    conan_message(STATUS "Skipping already existing target: ${_LIB_NAME}")
                endif()
                list(APPEND _out_libraries_target ${_LIB_NAME})
            endif()
            conan_message(STATUS "Found: ${CONAN_FOUND_LIBRARY}")
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            list(APPEND _out_libraries_target ${_LIBRARY_NAME})
            list(APPEND _out_libraries ${_LIBRARY_NAME})
            set(_CONAN_FOUND_SYSTEM_LIBS "${_CONAN_FOUND_SYSTEM_LIBS};${_LIBRARY_NAME}")
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()

    if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
        # Add all dependencies to all targets
        string(REPLACE " " ";" deps_list "${deps}")
        foreach(_CONAN_ACTUAL_TARGET ${_CONAN_ACTUAL_TARGETS})
            set_property(TARGET ${_CONAN_ACTUAL_TARGET} PROPERTY INTERFACE_LINK_LIBRARIES "${_CONAN_FOUND_SYSTEM_LIBS};${deps_list}")
        endforeach()
    endif()

    set(${out_libraries} ${_out_libraries} PARENT_SCOPE)
    set(${out_libraries_target} ${_out_libraries_target} PARENT_SCOPE)
endfunction()


########### FOUND PACKAGE ###################################################################
#############################################################################################

include(FindPackageHandleStandardArgs)

conan_message(STATUS "Conan: Using autogenerated FindOpus.cmake")
set(Opus_FOUND 1)
set(Opus_VERSION "1.3.1")

find_package_handle_standard_args(Opus REQUIRED_VARS
                                  Opus_VERSION VERSION_VAR Opus_VERSION)
mark_as_advanced(Opus_FOUND Opus_VERSION)

set(Opus_COMPONENTS Opus::opus)

if(Opus_FIND_COMPONENTS)
    foreach(_FIND_COMPONENT ${Opus_FIND_COMPONENTS})
        list(FIND Opus_COMPONENTS "Opus::${_FIND_COMPONENT}" _index)
        if(${_index} EQUAL -1)
            conan_message(FATAL_ERROR "Conan: Component '${_FIND_COMPONENT}' NOT found in package 'Opus'")
        else()
            conan_message(STATUS "Conan: Component '${_FIND_COMPONENT}' found in package 'Opus'")
        endif()
    endforeach()
endif()

########### VARIABLES #######################################################################
#############################################################################################


set(Opus_INCLUDE_DIRS "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include"
			"C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include/opus")
set(Opus_INCLUDE_DIR "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include;C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include/opus")
set(Opus_INCLUDES "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include"
			"C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include/opus")
set(Opus_RES_DIRS )
set(Opus_DEFINITIONS )
set(Opus_LINKER_FLAGS_LIST
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>"
)
set(Opus_COMPILE_DEFINITIONS )
set(Opus_COMPILE_OPTIONS_LIST "" "")
set(Opus_COMPILE_OPTIONS_C "")
set(Opus_COMPILE_OPTIONS_CXX "")
set(Opus_LIBRARIES_TARGETS "") # Will be filled later, if CMake 3
set(Opus_LIBRARIES "") # Will be filled later
set(Opus_LIBS "") # Same as Opus_LIBRARIES
set(Opus_SYSTEM_LIBS )
set(Opus_FRAMEWORK_DIRS )
set(Opus_FRAMEWORKS )
set(Opus_FRAMEWORKS_FOUND "") # Will be filled later
set(Opus_BUILD_MODULES_PATHS )

conan_find_apple_frameworks(Opus_FRAMEWORKS_FOUND "${Opus_FRAMEWORKS}" "${Opus_FRAMEWORK_DIRS}")

mark_as_advanced(Opus_INCLUDE_DIRS
                 Opus_INCLUDE_DIR
                 Opus_INCLUDES
                 Opus_DEFINITIONS
                 Opus_LINKER_FLAGS_LIST
                 Opus_COMPILE_DEFINITIONS
                 Opus_COMPILE_OPTIONS_LIST
                 Opus_LIBRARIES
                 Opus_LIBS
                 Opus_LIBRARIES_TARGETS)

# Find the real .lib/.a and add them to Opus_LIBS and Opus_LIBRARY_LIST
set(Opus_LIBRARY_LIST opus)
set(Opus_LIB_DIRS "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/lib")

# Gather all the libraries that should be linked to the targets (do not touch existing variables):
set(_Opus_DEPENDENCIES "${Opus_FRAMEWORKS_FOUND} ${Opus_SYSTEM_LIBS} ")

conan_package_library_targets("${Opus_LIBRARY_LIST}"  # libraries
                              "${Opus_LIB_DIRS}"      # package_libdir
                              "${_Opus_DEPENDENCIES}"  # deps
                              Opus_LIBRARIES            # out_libraries
                              Opus_LIBRARIES_TARGETS    # out_libraries_targets
                              ""                          # build_type
                              "Opus")                                      # package_name

set(Opus_LIBS ${Opus_LIBRARIES})

foreach(_FRAMEWORK ${Opus_FRAMEWORKS_FOUND})
    list(APPEND Opus_LIBRARIES_TARGETS ${_FRAMEWORK})
    list(APPEND Opus_LIBRARIES ${_FRAMEWORK})
endforeach()

foreach(_SYSTEM_LIB ${Opus_SYSTEM_LIBS})
    list(APPEND Opus_LIBRARIES_TARGETS ${_SYSTEM_LIB})
    list(APPEND Opus_LIBRARIES ${_SYSTEM_LIB})
endforeach()

# We need to add our requirements too
set(Opus_LIBRARIES_TARGETS "${Opus_LIBRARIES_TARGETS};")
set(Opus_LIBRARIES "${Opus_LIBRARIES};")

set(CMAKE_MODULE_PATH "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/" ${CMAKE_PREFIX_PATH})


########### COMPONENT opus VARIABLES #############################################

set(Opus_opus_INCLUDE_DIRS "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include"
			"C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include/opus")
set(Opus_opus_INCLUDE_DIR "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include;C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include/opus")
set(Opus_opus_INCLUDES "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include"
			"C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include/opus")
set(Opus_opus_LIB_DIRS "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/lib")
set(Opus_opus_RES_DIRS )
set(Opus_opus_DEFINITIONS )
set(Opus_opus_COMPILE_DEFINITIONS )
set(Opus_opus_COMPILE_OPTIONS_C "")
set(Opus_opus_COMPILE_OPTIONS_CXX "")
set(Opus_opus_LIBS opus)
set(Opus_opus_SYSTEM_LIBS )
set(Opus_opus_FRAMEWORK_DIRS )
set(Opus_opus_FRAMEWORKS )
set(Opus_opus_BUILD_MODULES_PATHS )
set(Opus_opus_DEPENDENCIES )
set(Opus_opus_LINKER_FLAGS_LIST
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>"
)


########## FIND PACKAGE DEPENDENCY ##########################################################
#############################################################################################

include(CMakeFindDependencyMacro)


########## FIND LIBRARIES & FRAMEWORKS / DYNAMIC VARS #######################################
#############################################################################################

########## COMPONENT opus FIND LIBRARIES & FRAMEWORKS / DYNAMIC VARS #############

set(Opus_opus_FRAMEWORKS_FOUND "")
conan_find_apple_frameworks(Opus_opus_FRAMEWORKS_FOUND "${Opus_opus_FRAMEWORKS}" "${Opus_opus_FRAMEWORK_DIRS}")

set(Opus_opus_LIB_TARGETS "")
set(Opus_opus_NOT_USED "")
set(Opus_opus_LIBS_FRAMEWORKS_DEPS ${Opus_opus_FRAMEWORKS_FOUND} ${Opus_opus_SYSTEM_LIBS} ${Opus_opus_DEPENDENCIES})
conan_package_library_targets("${Opus_opus_LIBS}"
                              "${Opus_opus_LIB_DIRS}"
                              "${Opus_opus_LIBS_FRAMEWORKS_DEPS}"
                              Opus_opus_NOT_USED
                              Opus_opus_LIB_TARGETS
                              ""
                              "Opus_opus")

set(Opus_opus_LINK_LIBS ${Opus_opus_LIB_TARGETS} ${Opus_opus_LIBS_FRAMEWORKS_DEPS})

set(CMAKE_MODULE_PATH "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "C:/Users/Mars_/.conan/data/opus/1.3.1/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/" ${CMAKE_PREFIX_PATH})


########## TARGETS ##########################################################################
#############################################################################################

########## COMPONENT opus TARGET #################################################

if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
    # Target approach
    if(NOT TARGET Opus::opus)
        add_library(Opus::opus INTERFACE IMPORTED)
        set_target_properties(Opus::opus PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                              "${Opus_opus_INCLUDE_DIRS}")
        set_target_properties(Opus::opus PROPERTIES INTERFACE_LINK_DIRECTORIES
                              "${Opus_opus_LIB_DIRS}")
        set_target_properties(Opus::opus PROPERTIES INTERFACE_LINK_LIBRARIES
                              "${Opus_opus_LINK_LIBS};${Opus_opus_LINKER_FLAGS_LIST}")
        set_target_properties(Opus::opus PROPERTIES INTERFACE_COMPILE_DEFINITIONS
                              "${Opus_opus_COMPILE_DEFINITIONS}")
        set_target_properties(Opus::opus PROPERTIES INTERFACE_COMPILE_OPTIONS
                              "${Opus_opus_COMPILE_OPTIONS_C};${Opus_opus_COMPILE_OPTIONS_CXX}")
    endif()
endif()

########## GLOBAL TARGET ####################################################################

if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
    if(NOT TARGET Opus::Opus)
        add_library(Opus::Opus INTERFACE IMPORTED)
    endif()
    set_property(TARGET Opus::Opus APPEND PROPERTY
                 INTERFACE_LINK_LIBRARIES "${Opus_COMPONENTS}")
endif()

########## BUILD MODULES ####################################################################
#############################################################################################
########## COMPONENT opus BUILD MODULES ##########################################

foreach(_BUILD_MODULE_PATH ${Opus_opus_BUILD_MODULES_PATHS})
    include(${_BUILD_MODULE_PATH})
endforeach()
