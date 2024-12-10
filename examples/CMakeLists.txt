if(WIN32)
    message("-- [wglad] configuration win32")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message("-- [wglad] cpp compiler ${CMAKE_CXX_COMPILER_ID}")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    endif()
endif()

add_executable(exec EXCLUDE_FROM_ALL exec_win32.cpp)

target_link_libraries(exec PRIVATE lib::wglad)