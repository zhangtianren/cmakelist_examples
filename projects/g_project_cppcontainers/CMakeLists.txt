# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)                      

# 项目名称
PROJECT(g_project_cppcontainers)

# 添加源文件列表变量
SET(SRC_LIST main.cpp
		stl_headers.h
		sort.cpp
		stl_array.cpp
		stl_deque.cpp
		stl_list.cpp
		stl_map.cpp
		stl_queue.cpp
		stl_set.cpp
		stl_stack.cpp
		stl_vector.cpp)

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(g_cppcontainers ${SRC_LIST})
