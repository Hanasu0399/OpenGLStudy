cmake_minimum_required(VERSION 3.16)
project(MyOpenGLApp)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/glfw-3.4.bin.WIN64")
include_directories(${GLFW_ROOT}/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

if(MINGW)
    link_directories(${GLFW_ROOT}/lib-mingw-w64)
else()
    link_directories(${GLFW_ROOT}/lib-vc2022)
endif()

add_executable(${PROJECT_NAME} Lesson1.cpp glad.c)

target_link_libraries(${PROJECT_NAME} 
    glfw3
    opengl32
    gdi32
    user32
    shell32
)
