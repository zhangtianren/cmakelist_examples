# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)                      

# 项目名称
PROJECT(j_project_datastructure)

# 添加源文件列表变量
SET(SRC_LIST main.cpp
			test.h
			list_test.h
			list_test.cpp
			stack_test.h
			stack_test.cpp
			queue_test.h
			queue_test.cpp
			tree_test.h
			tree_test.cpp
			list.h
			list.cpp
			stack.h
			stack.cpp
			queue.h
			queue.cpp
			tree.h
			tree.cpp
			)

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(j_datastructure ${SRC_LIST})
