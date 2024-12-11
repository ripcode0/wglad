if(WIN32)
    message("-- [wglad] configuration win32")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message("-- [wglad] cpp compiler ${CMAKE_CXX_COMPILER_ID}")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    endif()
endif()

add_executable(exec exec_win32.cpp)

target_link_libraries(exec PRIVATE wglad::wglad opengl32 gdi32)

if(MINGW)
    message("-- [wglad] mingw ... ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    target_compile_options(exec PRIVATE )

endif()