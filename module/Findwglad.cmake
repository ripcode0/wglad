get_filename_component(root_dir ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

set(wglad_ROOT_DIR ${root_dir})

message(STATUS "Root Dir : ${root_dir}")

find_path(
    wglad_INCLUDE_DIR
    NAMES wglad.h
    HINTS ${wglad_ROOT_DIR}/include/wglad
)

message("inc dir : ${wglad_INCLUDE_DIR}")
