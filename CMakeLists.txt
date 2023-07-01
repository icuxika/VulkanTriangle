cmake_minimum_required(VERSION 3.17)
project(VulkanTriangle)
set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders-bin/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)