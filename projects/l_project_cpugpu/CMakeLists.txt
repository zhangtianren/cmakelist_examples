# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.7)                      


#set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang")
#set(CMAKE_CXX_FLAGS "-std=c++11")


# 项目名称
PROJECT(l_project_cpugpu)

# SET(SRC_LIST main_test.cpp)
# 添加源文件列表变量
SET(SRC_LIST main.cpp
            picture.h
            picture.cpp
            pictureex.h
            pictureex.cpp)

set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")

MESSAGE(STATUS "Build Type:"${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(l_cpugpu ${SRC_LIST})

