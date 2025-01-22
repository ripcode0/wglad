cmake_minimum_required(VERSION 3.22)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(wglad_standalone TRUE)
else()
    set(wglad_standalone FALSE)
endif()

if(wglad_standalone)
    project(wglad VERSION 1.0.0 LANGUAGES C CXX)
endif()

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(wglad_srcs 
    ${CMAKE_CURRENT_SOURCE_DIR}/srcs/wglad/wglad.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/srcs/wglad/wglad.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/srcs/wglad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/srcs/wglad/glad.c
)
include(GNUInstallDirs)

add_library(wglad STATIC ${wglad_srcs})
add_library(wglad::wglad ALIAS wglad)

target_include_directories(wglad
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/srcs>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/wglad>
)

#install
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(install_dir ${CMAKE_CURRENT_BINARY_DIR}/install)
    set(CMAKE_INSTALL_PREFIX "${install_dir}" CACHE PATH "defualt install path" FORCE)
endif()


#installation
install(CODE "message(STATUS \"install wglad configuration : $<CONFIG> ${CMAKE_INSTALL_PREFIX}\")")
install(
    TARGETS wglad
    EXPORT wglad-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(config_location share/wglad)

install(
    DIRECTORY srcs/ 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/wglad
    FILES_MATCHING PATTERN *.h)

install(EXPORT wglad-targets
    FILE wglad-targets.cmake
    NAMESPACE wglad::
    DESTINATION ${config_location}
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/module/wglad-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/wglad-config.cmake
    INSTALL_DESTINATION ${config_location}
)

install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/wglad-config.cmake
    DESTINATION ${config_location}
)
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_CONFIGURATION_TYPES MATCHES "Debug")
    message("-- [wglad] build type    : Debug ${CMAKE_CONFIGURATION_TYPES}")
endif()

if(BUILD_EXAMPLE)
    add_subdirectory(examples)
endif()