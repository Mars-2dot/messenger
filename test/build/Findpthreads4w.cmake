

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


include(FindPackageHandleStandardArgs)

conan_message(STATUS "Conan: Using autogenerated Findpthreads4w.cmake")
# Global approach
set(pthreads4w_FOUND 1)
set(pthreads4w_VERSION "3.0.0")

find_package_handle_standard_args(pthreads4w REQUIRED_VARS
                                  pthreads4w_VERSION VERSION_VAR pthreads4w_VERSION)
mark_as_advanced(pthreads4w_FOUND pthreads4w_VERSION)


set(pthreads4w_INCLUDE_DIRS "C:/Users/Mars_/.conan/data/pthreads4w/3.0.0/_/_/package/671a50ef335d046615bfef14f33142d9ea0021e2/include")
set(pthreads4w_INCLUDE_DIR "C:/Users/Mars_/.conan/data/pthreads4w/3.0.0/_/_/package/671a50ef335d046615bfef14f33142d9ea0021e2/include")
set(pthreads4w_INCLUDES "C:/Users/Mars_/.conan/data/pthreads4w/3.0.0/_/_/package/671a50ef335d046615bfef14f33142d9ea0021e2/include")
set(pthreads4w_RES_DIRS )
set(pthreads4w_DEFINITIONS "-D__PTW32_CLEANUP_C"
			"-D__PTW32_STATIC_LIB")
set(pthreads4w_LINKER_FLAGS_LIST
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>"
)
set(pthreads4w_COMPILE_DEFINITIONS "__PTW32_CLEANUP_C"
			"__PTW32_STATIC_LIB")
set(pthreads4w_COMPILE_OPTIONS_LIST "" "")
set(pthreads4w_COMPILE_OPTIONS_C "")
set(pthreads4w_COMPILE_OPTIONS_CXX "")
set(pthreads4w_LIBRARIES_TARGETS "") # Will be filled later, if CMake 3
set(pthreads4w_LIBRARIES "") # Will be filled later
set(pthreads4w_LIBS "") # Same as pthreads4w_LIBRARIES
set(pthreads4w_SYSTEM_LIBS )
set(pthreads4w_FRAMEWORK_DIRS )
set(pthreads4w_FRAMEWORKS )
set(pthreads4w_FRAMEWORKS_FOUND "") # Will be filled later
set(pthreads4w_BUILD_MODULES_PATHS )

conan_find_apple_frameworks(pthreads4w_FRAMEWORKS_FOUND "${pthreads4w_FRAMEWORKS}" "${pthreads4w_FRAMEWORK_DIRS}")

mark_as_advanced(pthreads4w_INCLUDE_DIRS
                 pthreads4w_INCLUDE_DIR
                 pthreads4w_INCLUDES
                 pthreads4w_DEFINITIONS
                 pthreads4w_LINKER_FLAGS_LIST
                 pthreads4w_COMPILE_DEFINITIONS
                 pthreads4w_COMPILE_OPTIONS_LIST
                 pthreads4w_LIBRARIES
                 pthreads4w_LIBS
                 pthreads4w_LIBRARIES_TARGETS)

# Find the real .lib/.a and add them to pthreads4w_LIBS and pthreads4w_LIBRARY_LIST
set(pthreads4w_LIBRARY_LIST libpthreadVC3)
set(pthreads4w_LIB_DIRS "C:/Users/Mars_/.conan/data/pthreads4w/3.0.0/_/_/package/671a50ef335d046615bfef14f33142d9ea0021e2/lib")

# Gather all the libraries that should be linked to the targets (do not touch existing variables):
set(_pthreads4w_DEPENDENCIES "${pthreads4w_FRAMEWORKS_FOUND} ${pthreads4w_SYSTEM_LIBS} ")

conan_package_library_targets("${pthreads4w_LIBRARY_LIST}"  # libraries
                              "${pthreads4w_LIB_DIRS}"      # package_libdir
                              "${_pthreads4w_DEPENDENCIES}"  # deps
                              pthreads4w_LIBRARIES            # out_libraries
                              pthreads4w_LIBRARIES_TARGETS    # out_libraries_targets
                              ""                          # build_type
                              "pthreads4w")                                      # package_name

set(pthreads4w_LIBS ${pthreads4w_LIBRARIES})

foreach(_FRAMEWORK ${pthreads4w_FRAMEWORKS_FOUND})
    list(APPEND pthreads4w_LIBRARIES_TARGETS ${_FRAMEWORK})
    list(APPEND pthreads4w_LIBRARIES ${_FRAMEWORK})
endforeach()

foreach(_SYSTEM_LIB ${pthreads4w_SYSTEM_LIBS})
    list(APPEND pthreads4w_LIBRARIES_TARGETS ${_SYSTEM_LIB})
    list(APPEND pthreads4w_LIBRARIES ${_SYSTEM_LIB})
endforeach()

# We need to add our requirements too
set(pthreads4w_LIBRARIES_TARGETS "${pthreads4w_LIBRARIES_TARGETS};")
set(pthreads4w_LIBRARIES "${pthreads4w_LIBRARIES};")

set(CMAKE_MODULE_PATH "C:/Users/Mars_/.conan/data/pthreads4w/3.0.0/_/_/package/671a50ef335d046615bfef14f33142d9ea0021e2/" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "C:/Users/Mars_/.conan/data/pthreads4w/3.0.0/_/_/package/671a50ef335d046615bfef14f33142d9ea0021e2/" ${CMAKE_PREFIX_PATH})

if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
    # Target approach
    if(NOT TARGET pthreads4w::pthreads4w)
        add_library(pthreads4w::pthreads4w INTERFACE IMPORTED)
        if(pthreads4w_INCLUDE_DIRS)
            set_target_properties(pthreads4w::pthreads4w PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                  "${pthreads4w_INCLUDE_DIRS}")
        endif()
        set_property(TARGET pthreads4w::pthreads4w PROPERTY INTERFACE_LINK_LIBRARIES
                     "${pthreads4w_LIBRARIES_TARGETS};${pthreads4w_LINKER_FLAGS_LIST}")
        set_property(TARGET pthreads4w::pthreads4w PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     ${pthreads4w_COMPILE_DEFINITIONS})
        set_property(TARGET pthreads4w::pthreads4w PROPERTY INTERFACE_COMPILE_OPTIONS
                     "${pthreads4w_COMPILE_OPTIONS_LIST}")
        
    endif()
endif()

foreach(_BUILD_MODULE_PATH ${pthreads4w_BUILD_MODULES_PATHS})
    include(${_BUILD_MODULE_PATH})
endforeach()
