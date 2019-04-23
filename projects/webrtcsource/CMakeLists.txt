add_subdirectory(api)
add_subdirectory(audio)
add_subdirectory(base)
add_subdirectory(call)
add_subdirectory(p2p)
add_subdirectory(system_wrappers)

# 添加源文件列表变量
SET(SRC_LIST call.h
		common_types.cc
		common_types.h
		config.cc
		config.h
		no_op_function.cc
		typedefs.h
		video_decoder.h
		video_encoder.h
		video_frame.h
		video_receive_stream.h
		video_send_stream.h)