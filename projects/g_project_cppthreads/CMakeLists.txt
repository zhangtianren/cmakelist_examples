# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)                      

# 项目名称
PROJECT(g_project_cppthreads)

# 添加源文件列表变量
SET(SRC_LIST main.cpp
			cppthread_header.h
			cppthreads_1_newthread.cpp 
			cppthreads_2_threadmanage.cpp
			cppthreads_3_mutexlock.cpp
			cppthreads_4_concurrent.cpp
			cppthreads_5_stragate.cpp
			cppthreads_6_posix.cpp)

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(g_cppthreads ${SRC_LIST})
