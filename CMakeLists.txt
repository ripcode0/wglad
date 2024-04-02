cmake_minimum_required(VERSION 3.28)

project(wglad-0.1 LANGUAGES C VERSION 0.1)

set(EXPORT_NAME wglad-config)

add_subdirectory(wglad)

install(EXPORT ${EXPORT_NAME}
    NAMESPACE opengl
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}
)




