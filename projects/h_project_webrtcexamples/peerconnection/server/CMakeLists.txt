# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.7)                      

# 项目名称
PROJECT(h_project_webrtcpeerconnection)

#INCLUDE_DIRECTORIES("../../../webrtcsource/base") 
#INCLUDE_DIRECTORIES("../../../webrtcsource") 

# 添加源文件列表变量
SET(SRC_LIST main.cc
	data_socket.h
	data_socket.cc
	peer_channel.h
	peer_channel.cc
	utils.h
	utils.cc
	../../../webrtcsource/base/stringencode.cc
	../../../webrtcsource/base/stringencode.h
	../../../webrtcsource/base/stringutils.cc
	../../../webrtcsource/base/stringutils.h
	../../../webrtcsource/base/checks.cc
	../../../webrtcsource/base/checks.h
	../../../webrtcsource/typedefs.h)


# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(h_webrtcexample_peerconnectionsvr ${SRC_LIST})
