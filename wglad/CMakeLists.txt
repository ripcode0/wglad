cmake_minimum_required(VERSION 3.15)

#local variable
set(LOCAL_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(wglad STATIC ./wglad/wglad.cpp  ./wglad/glad.c)
add_library(lib::wglad ALIAS wglad)


target_include_directories(
    wglad 
    PUBLIC
    $<BUILD_INTERFACE:${LOCAL_INC_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/wglad>)



install(TARGETS wglad
    EXPORT         ${EXPORT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

