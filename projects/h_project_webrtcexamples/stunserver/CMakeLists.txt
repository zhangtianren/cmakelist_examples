# 版本限定
CMAKE_MINIMUM_REQUIRED(VERSION 2.7)                      

add_definitions("-DWEBRTC_WIN")
add_definitions("-DUNICODE")
include_directories("D:/my_setup/openssl-1.1.1/win32-release/include") 
link_directories("D:/my_setup/openssl-1.1.1/win32-release/lib") 
link_libraries("libssl.lib" "libcrypto.lib")

# 项目名称
PROJECT(h_webrtcexample_stunserver)

# 添加源文件列表变量
SET(SRC_LIST stunserver_main.cc
		../../webrtcsource/p2p/base/stun.h
		../../webrtcsource/p2p/base/stun.cc
		../../webrtcsource/p2p/base/stunserver.h
		../../webrtcsource/p2p/base/stunserver.cc
		#../../webrtcsource/p2p/base/stunrequest.h
		#../../webrtcsource/p2p/base/stunrequest.cc
		#../../webrtcsource/p2p/base/stunport.h
		#../../webrtcsource/p2p/base/stunport.cc
		../../webrtcsource/base/cryptstring.h
		../../webrtcsource/base/cryptstring.cc
		../../webrtcsource/base/stringencode.h
		../../webrtcsource/base/stringencode.cc
		../../webrtcsource/base/stringutils.h
		../../webrtcsource/base/stringutils.cc
		../../webrtcsource/base/asyncresolverinterface.h
		../../webrtcsource/base/asyncresolverinterface.cc
		../../webrtcsource/base/thread.h
		../../webrtcsource/base/thread.cc
		../../webrtcsource/base/signalthread.h
		../../webrtcsource/base/signalthread.cc
		../../webrtcsource/base/sigslot.h
		../../webrtcsource/base/sigslot.cc
		../../webrtcsource/base/checks.h
		../../webrtcsource/base/checks.cc
		../../webrtcsource/base/event.h
		../../webrtcsource/base/event.cc
		../../webrtcsource/base/byteorder.h
		../../webrtcsource/base/win32.h
		../../webrtcsource/base/win32.cc
		../../webrtcsource/base/winping.h
		../../webrtcsource/base/winping.cc
		../../webrtcsource/base/win32socketinit.h
		../../webrtcsource/base/win32socketinit.cc
		../../webrtcsource/base/win32socketserver.h
		../../webrtcsource/base/win32socketserver.cc
		../../webrtcsource/base/win32window.h
		../../webrtcsource/base/win32window.cc
		../../webrtcsource/base/win32securityerrors.cc
		../../webrtcsource/base/crc32.h
		../../webrtcsource/base/crc32.cc
		../../webrtcsource/base/base64.h
		../../webrtcsource/base/base64.cc
		../../webrtcsource/base/location.h
		../../webrtcsource/base/location.cc
		../../webrtcsource/base/messagequeue.h
		../../webrtcsource/base/messagequeue.cc
		../../webrtcsource/base/messagehandler.h
		../../webrtcsource/base/messagehandler.cc
		../../webrtcsource/base/messagedigest.h
		../../webrtcsource/base/messagedigest.cc
		../../webrtcsource/base/criticalsection.h
		../../webrtcsource/base/criticalsection.cc
		../../webrtcsource/base/logging.h
		../../webrtcsource/base/logging.cc
		../../webrtcsource/base/event_tracer.h
		../../webrtcsource/base/event_tracer.cc
		../../webrtcsource/base/sharedexclusivelock.h
		../../webrtcsource/base/sharedexclusivelock.cc
		../../webrtcsource/base/nethelpers.h
		../../webrtcsource/base/nethelpers.cc
		../../webrtcsource/base/ipaddress.h
		../../webrtcsource/base/ipaddress.cc
		../../webrtcsource/base/socket.h
		../../webrtcsource/base/socketadapters.h
		../../webrtcsource/base/socketadapters.cc
		../../webrtcsource/base/socketaddresspair.h
		../../webrtcsource/base/socketaddresspair.cc
		../../webrtcsource/base/socketaddress.h
		../../webrtcsource/base/socketaddress.cc
		../../webrtcsource/base/socketfactory.h
		../../webrtcsource/base/socketserver.h
		../../webrtcsource/base/physicalsocketserver.h
		../../webrtcsource/base/physicalsocketserver.cc
		../../webrtcsource/base/socketstream.h
		../../webrtcsource/base/socketstream.cc
		../../webrtcsource/base/stream.h
		../../webrtcsource/base/stream.cc
		../../webrtcsource/base/httpbase.h
		../../webrtcsource/base/httpbase.cc
		../../webrtcsource/base/httpcommon.h
		../../webrtcsource/base/httpcommon.cc
		../../webrtcsource/base/httpcommon-inl.h
		../../webrtcsource/base/httpserver.h
		../../webrtcsource/base/httpserver.cc
		../../webrtcsource/base/bytebuffer.h
		../../webrtcsource/base/bytebuffer.cc
		../../webrtcsource/base/timeutils.h
		../../webrtcsource/base/timeutils.cc
		../../webrtcsource/base/nullsocketserver.h
		../../webrtcsource/base/nullsocketserver.cc
		../../webrtcsource/base/platform_thread.h
		../../webrtcsource/base/platform_thread.cc
		../../webrtcsource/base/openssldigest.h
		../../webrtcsource/base/openssldigest.cc
		../../webrtcsource/base/asyncsocket.h
		../../webrtcsource/base/asyncsocket.cc
		../../webrtcsource/base/asynctcpsocket.h
		../../webrtcsource/base/asynctcpsocket.cc
		../../webrtcsource/base/asyncudpsocket.h
		../../webrtcsource/base/asyncudpsocket.cc
		../../webrtcsource/base/thread_checker.h
		../../webrtcsource/base/thread_checker_impl.h
		../../webrtcsource/base/thread_checker_impl.cc
		../../webrtcsource/base/asyncpacketsocket.h
		../../webrtcsource/base/asyncpacketsocket.cc)

# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 生成可执行文件
ADD_EXECUTABLE(h_webrtcexample_stunserver ${SRC_LIST})
