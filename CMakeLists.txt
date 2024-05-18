cmake_minimum_required(VERSION 3.28)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(NOT HAS_PARENT)
    project(wglad VERSION 1.0.0 LANGUAGES C CXX)
endif()

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(WGLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(wglad_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(NOT wglad_LIB_DIR)
    set(wglad_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()

#is top root directory?
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(WGLAD_EXPORT "set export variables for external jroject" OFF)
else()
    option(WGLAD_EXPORT "set export variables for external jroject" ON)
endif()

set(wglad_srcs 
    ${wglad_INC_DIR}/wglad/wglad.h 
    ${wglad_INC_DIR}/wglad/wglad.cpp
    ${wglad_INC_DIR}/wglad/glad.h
    ${wglad_INC_DIR}/wglad/glad.c
)

add_library(wglad STATIC ${wglad_srcs})
add_library(lib::wglad ALIAS wglad)

if(WGLAD_EXPORT)
    set(wglad_LIBRARIES wglad PARENT_SCOPE)
    set(wglad_INC_DIR ${wglad_INC_DIR} PARENT_SCOPE)
    set(wglad_LIB_DIR ${wglad_LIB_DIR} PARENT_SCOPE)
endif()

message(STATUS "GLAD_INC_DIR : ${wglad_INC_DIR}")
message(STATUS "GLAD_LIB_DIR : ${wglad_LIB_DIR}")

set_target_properties(wglad  PROPERTIES
    INCLUDE_DIRECTORIES ${wglad_INC_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${wglad_LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${wglad_LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${wglad_LIB_DIR})


#install
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
endif()

install(
    TARGETS wglad
    INCLUDES DESTINATION include
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ 
    DESTINATION include FILES_MATCHING PATTERN "*.h")

#add_custom_target(installing COMMAND ${CMAKE_COMMAND} -E --install --prefix installed)