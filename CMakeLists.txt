cmake_minimum_required(VERSION 3.29)
project(VitalVision)

set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR})

file(GLOB OTHERS CONFIGURE_DEPENDS src/*.h src/main.cpp)
file(GLOB_RECURSE CORE CONFIGURE_DEPENDS src/core/*.h src/core/*.cpp)
#file(GLOB_RECURSE SRC_VULKAN CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/include/vulkan/*.cpp)

add_executable(${PROJECT_NAME} ${OTHERS} ${CORE})

#add_library(VULKAN ${SRC_VULKAN})

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libglog.dll)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/vulkan-1.lib)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 拷贝动态库
file(COPY ${CMAKE_SOURCE_DIR}/lib/glfw3.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/lib/libglog.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})