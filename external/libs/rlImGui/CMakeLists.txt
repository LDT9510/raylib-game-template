# Created by XReaper

project("rlImGui" LANGUAGES C)

# create static library
add_library(${PROJECT_NAME} STATIC "rlImGui.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib imgui-bundle) # Link cimgui, as it links to ImGui
