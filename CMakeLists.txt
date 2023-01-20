cmake_minimum_required(VERSION 3.17)
project(VulkanApplication)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

add_executable(VulkanApplication main.cpp)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} Vulkan::Vulkan)