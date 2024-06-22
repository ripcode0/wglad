cmake_minimum_required(VERSION 3.22.0)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "c:/deps/shared/wglad/cmake")

project(findmodule LANGUAGES C CXX)

#LIST(APPEND ${CMAKE_MODULE_PATH} "c:/deps/shared/wglad/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "c:/deps/shared/wglad/cmake")

foreach(dir ${CMAKE_MODULE_PATH})
    message("--- ${dir} ---")
    if(EXISTS ${dir})
    message("--- ${dir} alive---")
    endif()
endforeach()


find_package(wglad REQUIRED)

if(NOT wglad_FOUND)
    message(STATUS "failed to find wglad")
endif()

add_executable(findmodule main.cpp)