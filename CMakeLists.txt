cmake_minimum_required(VERSION 3.28)

project(wglad-0.1 LANGUAGES C VERSION 0.1)

add_library(wglad STATIC ./include/wglad/wglad.cpp  ./include/wglad/glad.c)
add_library(lib::wglad ALIAS wglad)

#out variable for parent
set(GLAD_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLAD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
if(NOT PROJECT_IS_TOP_LEVEL)
    set(GLAD_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
    set(GLAD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib PARENT_SCOPE)
endif()
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



