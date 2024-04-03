cmake_minimum_required(VERSION 3.28)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(NOT HAS_PARENT)
    project(wglad VERSION 0.1)
endif()

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


set(GLAD_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLAD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if(HAS_PARENT)
message(STATUS "this is subdirectory")
set(GLAD_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(GLAD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib PARENT_SCOPE)
endif()

set(SRCS 
    ${GLAD_INC_DIR}/wglad/wglad.h 
    ${GLAD_INC_DIR}/wglad/wglad.cpp
    ${GLAD_INC_DIR}/wglad/glad.h
    ${GLAD_INC_DIR}/wglad/glad.c
)
add_library(wglad STATIC ${SRCS})
add_library(lib::wglad ALIAS wglad)

#out variable for parent


#set build out files
if(DEFINED LIB_DIR)
    message(STATUS "glob on")
    set(GLAD_LIB_DIR ${LIB_DIR})
    set(GLAD_LIB_DIR ${LIB_DIR} PARENT_SCOPE)
endif()

message(STATUS "GLAD_INC_DIR : ${GLAD_INC_DIR}")
message(STATUS "GLAD_LIB_DIR : ${GLAD_LIB_DIR}")

set_target_properties(wglad  PROPERTIES
    INCLUDE_DIRECTORIES ${GLAD_INC_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${GLAD_LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${GLAD_LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${GLAD_LIB_DIR})



