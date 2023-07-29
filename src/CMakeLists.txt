find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED GL Trade Sdl2Application)

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
    Magnum::Trade)    

install(TARGETS ${PROJECT_NAME} DESTINATION ${MAGNUM_BINARY_INSTALL_DIR})

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
