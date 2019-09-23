# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.7)                      

# 项目名称
PROJECT(k_project_searchandsort)

# 添加源文件列表变量
SET(SRC_LIST main.cpp
    sort.h
    sort.cpp
    search.h
    search.cpp
    util.h
    util.cpp
    test_sort.cpp
    test_search.cpp)

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(k_sort ${SRC_LIST})
