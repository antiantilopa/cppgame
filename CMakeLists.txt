cmake_minimum_required(VERSION 3.20)
project(cppgame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/libraries)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/main.cpp
    src/cppgame/*.cpp
    src/cppgame/*.c
)

add_executable(cppgame ${SOURCES})

target_include_directories(cppgame PRIVATE ${LIB_DIR}/include)

target_link_libraries(cppgame PRIVATE
    opengl32
    gdi32
    user32
    kernel32
    ole32
    mmdevapi
    winmm
)

if(MSVC)
    target_link_libraries(cppgame PRIVATE ${LIB_DIR}/lib/glfw3.lib)
else()
    target_link_libraries(cppgame PRIVATE ${LIB_DIR}/lib/libglfw3.a)
endif()