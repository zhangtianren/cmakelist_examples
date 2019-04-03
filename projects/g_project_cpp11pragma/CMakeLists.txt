# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)                      

# 项目名称
PROJECT(g_project_cpp11pragma)

# 添加源文件列表变量
SET(SRC_LIST main.cpp
			cpp11_header.h
			cpp11_1_auto_nullptr_for.cpp 
			cpp11_2_stl.cpp
			cpp11_3_concurrent.cpp
			cpp11_4_sharedptr.cpp
			cpp11_5_stdfunclamda.cpp)

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(g_cpp11pragma ${SRC_LIST})
