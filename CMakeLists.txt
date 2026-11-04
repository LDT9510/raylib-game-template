cmake_minimum_required(VERSION 3.23)
project("raylib-game-template" C)

# set the CMake modules path, required to import using " include(...)"
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include("Config")
include("dependencies/raylib")
include("dependencies/rlImGui")
include("dependencies/imgui-bundle")
include("SymlinkContent")

project("raylib-game" C CXX)  # needs CXX because of imgui

add_executable(${PROJECT_NAME} "src/main.c")

set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 11)
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD_REQUIRED ON)
set_target_properties(${PROJECT_NAME} PROPERTIES C_EXTENSIONS OFF)

# default to desktop, override on toolchain identification
set(RAYLIB_PLATFORM "Desktop")

# this is set by the included Windows toolchain
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /nologo /W4 /WX)
else ()
    # should cover both GCC and CLANG
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -W -Werror -pedantic-errors)
endif ()

# this is set by the Emscripten toolchain
if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PRIVATE
            -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sGL_ENABLE_GET_PROC_ADDRESS=1)
    set(RAYLIB_PLATFORM "Web")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WEB)

    # for wasm, contents are embedded in a .data file:
    # --preload-file will add the path as a base, so should be imported as /<file>
    target_link_options(${PROJECT_NAME} PRIVATE --preload-file ${PROJECT_ROOT_DIR}/contents@contents)
else ()
    # on desktop, add symlink to contents
    symlink_content(${PROJECT_NAME} contents)
endif ()

# configure external dependencies
configure_external_raylib(${PROJECT_NAME} ${RAYLIB_PLATFORM})
configure_external_rlImGui(${PROJECT_NAME})
configure_external_imgui_bundle(${PROJECT_NAME})

copy_compilation_database()

# configure thirdparty include directory
target_include_thirdparty(${PROJECT_NAME})

