
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

corrade_add_resource(APP_RESOURCES ../resources/resources.conf)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(${PROJECT_NAME} WIN32
    ${SOURCES}
    ${APP_RESOURCES})
    
target_link_libraries(${PROJECT_NAME} PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::Shaders
    Magnum::Trade
    MagnumIntegration::ImGui)    

target_precompile_headers(${PROJECT_NAME} PRIVATE
    <array>
    <cassert>
    <cstdint>
    <fstream>
    <functional>
    <iostream>
    <queue>
    <random>
    <source_location>
    <span>
    <string>
    <utility>
    <vector>
    
    <Corrade/Containers/Optional.h>
    <Corrade/Containers/Pointer.h>
    <Corrade/Containers/StringView.h>
    <Corrade/PluginManager/Manager.h>
    <Corrade/Utility/Resource.h>
    <Magnum/GL/AbstractShaderProgram.h>
    <Magnum/GL/Buffer.h>
    <Magnum/GL/Mesh.h>
    <Magnum/GL/Texture.h>
    <Magnum/GL/TextureFormat.h>
    <Magnum/ImageView.h>
    <Magnum/Magnum.h>
    <Magnum/Math/Matrix3.h>
    <Magnum/Math/Matrix4.h>
    <Magnum/Trade/AbstractImporter.h>
    <Magnum/Trade/ImageData.h>
    
    <imgui.h>
)
 
install(TARGETS ${PROJECT_NAME} DESTINATION ${MAGNUM_BINARY_INSTALL_DIR})

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
