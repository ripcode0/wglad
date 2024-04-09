cmake_minimum_required(VERSION 3.28)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(NOT HAS_PARENT)
    project(wglad VERSION 0.1)
endif()

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


set(WGLAD_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(WGLAD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(WGLAD_NAME wglad)

if(HAS_PARENT)
#output variables
set(WGLAD_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(WGLAD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib PARENT_SCOPE)
set(WGLAD_NAME ${WGLAD_NAME} PARENT_SCOPE)
endif()

set(SRCS 
    ${WGLAD_INC_DIR}/wglad/wglad.h 
    ${WGLAD_INC_DIR}/wglad/wglad.cpp
    ${WGLAD_INC_DIR}/wglad/glad.h
    ${WGLAD_INC_DIR}/wglad/glad.c
)
add_library(wglad STATIC ${SRCS})
add_library(lib::wglad ALIAS wglad)

#out variable for parent


#set build out files
if(DEFINED LIB_DIR)
    set(WGLAD_LIB_DIR ${LIB_DIR})
    set(WGLAD_LIB_DIR ${LIB_DIR} PARENT_SCOPE)
endif()

message(STATUS "GLAD_INC_DIR : ${WGLAD_INC_DIR}")
message(STATUS "GLAD_LIB_DIR : ${WGLAD_LIB_DIR}")

set_target_properties(wglad  PROPERTIES
    INCLUDE_DIRECTORIES ${WGLAD_INC_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${WGLAD_LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${WGLAD_LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${WGLAD_LIB_DIR})



