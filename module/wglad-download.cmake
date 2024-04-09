cmake_minimum_required(VERSION 3.28)

#set glad
if(NOT DEFINED WGLAD_INSTALL_DIR)
set(WGLAD_INSTALL_DIR ${CMAKE_SOURCE_DIR}/External/wglad)
endif()
#check out glad dir
set(GLAD_DOWNLOAD_REQUIRED FALSE)
if(NOT EXISTS ${WGLAD_INSTALL_DIR})
    message(STATUS "downloading... wglad")
    execute_process(
        COMMAND git clone https://github.com/ripcode0/wglad.git ${WGLAD_INSTALL_DIR})
        file(REMOVE_RECURSE ${WGLAD_INSTALL_DIR}/.git)
        file(REMOVE_RECURSE ${WGLAD_INSTALL_DIR}/module)
        file(REMOVE_RECURSE ${WGLAD_INSTALL_DIR}/.gitignore)
else()
    #check out each file
    if(NOT EXISTS ${WGLAD_INSTALL_DIR}/CMakeLists.txt)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(NOT EXISTS ${WGLAD_INSTALL_DIR}/include/wglad/glad.h)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(NOT EXISTS ${WGLAD_INSTALL_DIR}/include/wglad/glad.c)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(GLAD_DOWNLOAD_REQUIRED)
        message(STATUS "downloading... wglad")
        file(REMOVE_RECURSE ${WGLAD_INSTALL_DIR})
        execute_process(
            COMMAND git clone https://github.com/ripcode0/wglad.git ${WGLAD_INSTALL_DIR})
        file(REMOVE_RECURSE ${WGLAD_INSTALL_DIR}/.git)
        file(REMOVE_RECURSE ${WGLAD_INSTALL_DIR}/module)
        file(REMOVE_RECURSE ${WGLAD_INSTALL_DIR}/.gitignore)
    endif()
endif()

add_subdirectory(External/wglad)