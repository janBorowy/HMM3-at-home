cmake_minimum_required(VERSION 3.14)
project(HMM3-clone)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

file(GLOB src_FILES src/*.cc)
include_directories(src)
include_directories(src/engine_core)
add_executable(HMM3-clone src/main.cc ${src_FILES} ${src_engine_core_FILES} ${src_component_FILES})

file(GLOB imgui_SOURCE_FILES extern/imgui/*.cpp)
set(imgui_BACKEND extern/imgui/backends/imgui_impl_sdl2.cpp
    extern/imgui/backends/imgui_impl_sdlrenderer2.cpp)
include_directories(extern/imgui)
include_directories(extern/imgui/backends)
add_library(imgui ${imgui_SOURCE_FILES} ${imgui_BACKEND})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(HMM3-clone imgui SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

list(REMOVE_ITEM src_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc")

# compiles tests
add_executable(test test/main.cc ${src_FILES})
target_link_libraries(test imgui SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)