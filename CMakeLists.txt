cmake_minimum_required(VERSION 3.4)
set(PROJECT_NAME mg-ball)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

# Add Corrade as a subproject
add_subdirectory(libs/corrade EXCLUDE_FROM_ALL)

# Add Magnum as a subproject, enable Sdl2Application
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/libs/SDL2-2.0.10 ${CMAKE_PREFIX_PATH})
set(MAGNUM_WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
set(MAGNUM_WITH_TGAIMPORTER ON CACHE BOOL "" FORCE)
set(MAGNUM_WITH_PNGIMPORTER ON CACHE BOOL "" FORCE)
add_subdirectory(libs/magnum EXCLUDE_FROM_ALL)

set(MAGNUM_WITH_PNGIMPORTER ON CACHE BOOL "" FORCE)
add_subdirectory(libs/magnum-plugins EXCLUDE_FROM_ALL)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)
set(MAGNUM_WITH_IMGUI ON CACHE BOOL "" FORCE)
add_subdirectory(libs/magnum-integration EXCLUDE_FROM_ALL)

# fine packages
find_package(MagnumIntegration REQUIRED ImGui)
find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED GL Trade Sdl2Application)

add_subdirectory(src)

add_dependencies(${PROJECT_NAME} Magnum::TgaImporter)
add_dependencies(${PROJECT_NAME} MagnumPlugins::PngImporter)
