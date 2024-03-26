cmake_minimum_required(VERSION 3.5)

add_library(glad STATIC glad/glad.h glad/glad.c)
add_library(lib::glad ALIAS glad)

#out variable for parent
set(GLAD_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(GLAD_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib PARENT_SCOPE)
set(GLOBAR_LIB_DIR FALSE)
#set build out files
if(NOT DEFINED LIB_DIR)
    message(STATUS "glad lib place to : ${GLAD_LIB_DIR}")
else()
    set(GLAD_LIB_DIR ${LIB_DIR})
    message(STATUS "glad lib place to : ${LIB_DIR}")
endif()

set_target_properties(glad  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${GLAD_LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${GLAD_LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${GLAD_LIB_DIR})



