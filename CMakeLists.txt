# 标题
cmake_minimum_required(VERSION 4.0.0)
project(LocatedinBackrooms VERSION 0.0.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 查找并载入Cmake预设
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# 添加头文件路径
include_directories("include")

# 添加可执行文件
add_executable(${TARGET} 
                "src/main.cpp")

# 链接库
target_link_libraries(${TARGET}
                    ${SDL2_LIBRARIES}
                    SDL2_image::SDL2_image
                    SDL2_mixer::SDL2_mixer
                    SDL2_ttf::SDL2_ttf)