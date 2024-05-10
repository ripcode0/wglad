cmake_minimum_required(VERSION 3.28)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(NOT HAS_PARENT)
    project(wglad VERSION 0.1)
endif()

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


set(wglad_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(wglad_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(wglad_NAME wglad)

if(HAS_PARENT)
#output variables
set(wglad_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(wglad_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib PARENT_SCOPE)
set(wglad_NAME ${wglad_NAME} PARENT_SCOPE)
endif()

set(SRCS 
    ${wglad_INC_DIR}/wglad/wglad.h 
    ${wglad_INC_DIR}/wglad/wglad.cpp
    ${wglad_INC_DIR}/wglad/glad.h
    ${wglad_INC_DIR}/wglad/glad.c
)
add_library(wglad STATIC ${SRCS})
add_library(lib::wglad ALIAS wglad)

#out variable for parent


#set build out files
if(DEFINED LIB_DIR)
    set(wglad_LIB_DIR ${LIB_DIR})
    set(wglad_LIB_DIR ${LIB_DIR} PARENT_SCOPE)
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

install(TARGETS wglad
    INCLUDES DESTINATION include
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION dll
)

install(DIRECTORY include/ 
    DESTINATION include FILES_MATCHING PATTERN "*.h")

add_custom_target(installing COMMAND ${CMAKE_COMMAND} -E --install --prefix installed)