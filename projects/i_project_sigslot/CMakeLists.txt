# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.7)                      

add_definitions("-DWEBRTC_WIN")

# 项目名称
PROJECT(i_project_sigslot)

# 添加源文件列表变量
SET(SRC_LIST main.cpp 
		sigslot.h 
		#sigslot.cc 
		sigslot_cpp.h 
		sigslot_cpp.cpp
		testsigslot.cpp 
		testsigslot.h)

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(i_sigslot ${SRC_LIST})
