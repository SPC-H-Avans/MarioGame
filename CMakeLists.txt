cmake_minimum_required(VERSION 3.23)
project(platformer-game)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_LIBS_DIR ${PROJECT_SOURCE_DIR}/libs)

# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(vcpkg_install_deps.cmake)
vcpkg_install_deps(MANIFEST_ROOT ${PROJECT_LIBS_DIR}/PlatformerEngine)

include_directories(${PROJECT_NAME} ${PROJECT_LIBS_DIR}/PlatformerEngine/includes/spic-prj-api)

if (NOT DEFINED BINARY_RESOURCES_FOLDER)
    set(BINARY_RESOURCES_FOLDER resources)
endif ()

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_RESOURCES_FOLDER})


add_subdirectory(${PROJECT_LIBS_DIR}/PlatformerEngine)
file(GLOB_RECURSE SOURCE src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
add_dependencies(${PROJECT_NAME} copy_assets)
target_link_libraries(${PROJECT_NAME} PRIVATE platformer-engine)