cmake_minimum_required(VERSION 4.2)
project(imgui-bundle C CXX)

# add source code
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC .)

