#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "wglad::wglad" for configuration "Debug"
set_property(TARGET wglad::wglad APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(wglad::wglad PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/wglad.lib"
  )

list(APPEND _cmake_import_check_targets wglad::wglad )
list(APPEND _cmake_import_check_files_for_wglad::wglad "${_IMPORT_PREFIX}/lib/wglad.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
