cmake_minimum_required(VERSION 3.17)
project(VulkanTriangle)
set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Stb REQUIRED)
find_package(FFMPEG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${FFMPEG_LIBRARY_DIRS})

target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw ${FFMPEG_LIBRARIES})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders-bin/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)


add_executable(readVideoInfo ffmpegusages/read_video_info.cpp)
target_include_directories(readVideoInfo PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(readVideoInfo PRIVATE ${FFMPEG_LIBRARY_DIRS})

target_link_libraries(readVideoInfo ${FFMPEG_LIBRARIES})