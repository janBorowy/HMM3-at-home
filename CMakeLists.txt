cmake_minimum_required(VERSION 3.14)
project(HMM3-at-home)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

file(GLOB src_FILES src/*.cc)
include_directories(src)
include_directories(src/engine_core)
add_executable(HMM3-at-home src/main.cc ${src_FILES} ${src_engine_core_FILES} ${src_component_FILES})

file(GLOB imgui_SOURCE_FILES extern/imgui/*.cpp)
set(imgui_BACKEND extern/imgui/backends/imgui_impl_sdl2.cpp
    extern/imgui/backends/imgui_impl_sdlrenderer2.cpp)
include_directories(extern/imgui)
include_directories(extern/imgui/backends)
add_library(imgui ${imgui_SOURCE_FILES} ${imgui_BACKEND})

Include(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(HMM3-at-home imgui ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

list(REMOVE_ITEM src_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc")

# compiles tests
add_executable(test test/main.cc ${src_FILES})
target_link_libraries(test imgui ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# images
add_custom_target(make-images-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory images)
file(GLOB images images/*)
foreach(file ${images})
    get_filename_component(filename ${file} NAME)
    configure_file(${file} images/${filename} COPYONLY)
endforeach()

# resources
add_custom_target(make-resources-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory resources)
file(GLOB resources resources/*)
foreach(file ${resources})
    get_filename_component(filename ${file} NAME)
    configure_file(${file} resources/${filename} COPYONLY)
endforeach()
