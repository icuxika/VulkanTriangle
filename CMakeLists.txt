cmake_minimum_required(VERSION 3.17)
project(VulkanApplication)
set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(VulkanApplication main.cpp)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)