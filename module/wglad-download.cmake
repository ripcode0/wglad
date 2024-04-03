cmake_minimum_required(VERSION 3.28)

#set glad
set(INSTALL_GLAD_DIR ${CMAKE_SOURCE_DIR}/External/glad)

#check out glad dir
set(GLAD_DOWNLOAD_REQUIRED FALSE)
if(NOT EXISTS ${INSTALL_GLAD_DIR})
    message(STATUS "download glad")
    execute_process(
        COMMAND git clone https://github.com/ripcode0/wglad.git ${INSTALL_GLAD_DIR})
        file(REMOVE_RECURSE ${INSTALL_GLAD_DIR}/.git)
else()
    #check out each file
    if(NOT EXISTS ${INSTALL_GLAD_DIR}/CMakeLists.txt)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(NOT EXISTS ${INSTALL_GLAD_DIR}/include/glad.h)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(NOT EXISTS ${INSTALL_GLAD_DIR}/include/glad.c)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(GLAD_DOWNLOAD_REQUIRED)
        message(STATUS "download glad")
        file(REMOVE_RECURSE ${INSTALL_GLAD_DIR})
        execute_process(
            COMMAND git clone https://github.com/ripcode0/wglad.git ${INSTALL_GLAD_DIR})
        file(REMOVE_RECURSE ${INSTALL_GLAD_DIR}/.git)
    endif()
endif()

add_subdirectory(External/glad)