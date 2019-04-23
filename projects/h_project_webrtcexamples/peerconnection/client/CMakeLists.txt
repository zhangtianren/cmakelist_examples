# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.7)                      

# 项目名称
PROJECT(h_project_webrtcpeerconnection)

# 添加源文件列表变量
SET(SRC_LIST main.cc
	data_socket.h
	data_socket.cc
	peer_channel.h
	peer_channel.cc
	utils.h
	utils.cc
	depend/typedefs.h
	depend/checks.h
	depend/checks.cc
	depend/stringencode.h
	depend/stringencode.cc
	depend/stringutils.h
	depend/stringutils.cc
	depend/safe_compare.h)

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(h_webrtcpeerconnection ${SRC_LIST})
