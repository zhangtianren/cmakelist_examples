
# 添加源文件列表变量
SET(SRC_LIST applefilesystem.mm
		arraysize.h
		array_view.h
		array_view_unittest.cc
		asyncinvoker-inl.h
		asyncinvoker.cc
		asyncinvoker.h
		asyncpacketsocket.cc
		asyncpacketsocket.h
		asyncresolverinterface.cc
		asyncresolverinterface.h
		asyncsocket.cc
		asyncsocket.h
		asynctcpsocket.cc
		asynctcpsocket.h
		asynctcpsocket_unittest.cc
		asyncudpsocket.cc
		asyncudpsocket.h
		asyncudpsocket_unittest.cc
		atomicops.h
		atomicops_unittest.cc
		base64.cc
		base64.h
		base64_unittest.cc
		basictypes.h
		basictypes_unittest.cc
		bind.h
		bind_unittest.cc
		bitbuffer.cc
		bitbuffer.h
		bitbuffer_unittest.cc
		buffer.h
		bufferqueue.cc
		bufferqueue.h
		bufferqueue_unittest.cc
		buffer_unittest.cc
		BUILD.gn
		bytebuffer.cc
		bytebuffer.h
		bytebuffer_unittest.cc
		byteorder.h
		byteorder_unittest.cc
		callback.h
		callback.h.pump
		callback_unittest.cc
		checks.cc
		checks.h
		constructormagic.h
		copyonwritebuffer.cc
		copyonwritebuffer.h
		copyonwritebuffer_unittest.cc
		cpu_time.cc
		cpu_time.h
		cpu_time_unittest.cc
		crc32.cc
		crc32.h
		crc32_unittest.cc
		criticalsection.cc
		criticalsection.h
		criticalsection_unittest.cc
		cryptstring.cc
		cryptstring.h
		deprecation.h
		DEPS
		dscp.h
		event.cc
		event.h
		event_tracer.cc
		event_tracer.h
		event_tracer_unittest.cc
		event_unittest.cc
		fakeclock.cc
		fakeclock.h
		fakenetwork.h
		fakesslidentity.h
		file.cc
		file.h
		filerotatingstream.cc
		filerotatingstream.h
		filerotatingstream_unittest.cc
		fileutils.cc
		fileutils.h
		fileutils_unittest.cc
		file_posix.cc
		file_unittest.cc
		file_win.cc
		firewallsocketserver.cc
		firewallsocketserver.h
		flags.cc
		flags.h
		format_macros.h
		function_view.h
		function_view_unittest.cc
		gtest_prod_util.h
		gunit.h
		gunit_prod.h
		helpers.cc
		helpers.h
		helpers_unittest.cc
		httpbase.cc
		httpbase.h
		httpbase_unittest.cc
		httpcommon-inl.h
		httpcommon.cc
		httpcommon.h
		httpcommon_unittest.cc
		httpserver.cc
		httpserver.h
		httpserver_unittest.cc
		ifaddrs-android.cc
		ifaddrs-android.h
		ifaddrs_converter.cc
		ifaddrs_converter.h
		ignore_wundef.h
		ipaddress.cc
		ipaddress.h
		ipaddress_unittest.cc
		#java
		json.cc
		json.h
		json_unittest.cc
		keep_ref_until_done.h
		location.cc
		location.h
		logging.cc
		logging.h
		logging_mac.mm
		logging_unittest.cc
		logsinks.cc
		logsinks.h
		maccocoathreadhelper.h
		maccocoathreadhelper.mm
		macifaddrs_converter.cc
		macutils.cc
		macutils.h
		macutils_unittest.cc
		mathutils.h
		md5.cc
		md5.h
		md5digest.cc
		md5digest.h
		md5digest_unittest.cc
		memory_usage.cc
		memory_usage.h
		memory_usage_unittest.cc
		messagedigest.cc
		messagedigest.h
		messagedigest_unittest.cc
		messagehandler.cc
		messagehandler.h
		messagequeue.cc
		messagequeue.h
		messagequeue_unittest.cc
		mod_ops.h
		mod_ops_unittest.cc
		natserver.cc
		natserver.h
		natsocketfactory.cc
		natsocketfactory.h
		nattypes.cc
		nattypes.h
		nat_unittest.cc
		nethelpers.cc
		nethelpers.h
		network.cc
		network.h
		networkmonitor.cc
		networkmonitor.h
		networkroute.h
		network_unittest.cc
		nullsocketserver.cc
		nullsocketserver.h
		nullsocketserver_unittest.cc
		numerics/exp_filter.cc
		numerics/exp_filter.h
		numerics/exp_filter_unittest.cc
		numerics/percentile_filter.h
		numerics/percentile_filter_unittest.cc
		onetimeevent.h
		onetimeevent_unittest.cc
		openssl.h
		openssladapter.cc
		openssladapter.h
		openssldigest.cc
		openssldigest.h
		opensslidentity.cc
		opensslidentity.h
		opensslstreamadapter.cc
		opensslstreamadapter.h
		optional.cc
		optional.h
		optional_unittest.cc
		optionsfile.cc
		optionsfile.h
		optionsfile_unittest.cc
		OWNERS
		pathutils.cc
		pathutils.h
		pathutils_unittest.cc
		physicalsocketserver.cc
		physicalsocketserver.h
		physicalsocketserver_unittest.cc
		platform_file.cc
		platform_file.h
		platform_thread.cc
		platform_thread.h
		platform_thread_types.h
		platform_thread_unittest.cc
		proxyinfo.cc
		proxyinfo.h
		proxyserver.cc
		proxyserver.h
		proxy_unittest.cc
		race_checker.cc
		race_checker.h
		random.cc
		random.h
		random_unittest.cc
		ratelimiter.cc
		ratelimiter.h
		ratelimiter_unittest.cc
		ratetracker.cc
		ratetracker.h
		ratetracker_unittest.cc
		rate_limiter.cc
		rate_limiter.h
		rate_limiter_unittest.cc
		rate_statistics.cc
		rate_statistics.h
		rate_statistics_unittest.cc
		refcount.h
		refcountedobject.h
		refcountedobject_unittest.cc
		rollingaccumulator.h
		rollingaccumulator_unittest.cc
		rtccertificate.cc
		rtccertificate.h
		rtccertificategenerator.cc
		rtccertificategenerator.h
		rtccertificategenerator_unittest.cc
		rtccertificate_unittest.cc
		safe_compare.h
		safe_compare_unittest.cc
		safe_conversions.h
		safe_conversions_impl.h
		sanitizer.h
		scopedptrcollection.h
		scopedptrcollection_unittest.cc
		scoped_autorelease_pool.h
		scoped_autorelease_pool.mm
		scoped_ref_ptr.h
		sequenced_task_checker.h
		sequenced_task_checker_impl.cc
		sequenced_task_checker_impl.h
		sequenced_task_checker_unittest.cc
		sha1.cc
		sha1.h
		sha1digest.cc
		sha1digest.h
		sha1digest_unittest.cc
		sharedexclusivelock.cc
		sharedexclusivelock.h
		sharedexclusivelock_unittest.cc
		signalthread.cc
		signalthread.h
		signalthread_unittest.cc
		sigslot.cc
		sigslot.h
		sigslotrepeater.h
		sigslottester.h
		sigslottester.h.pump
		sigslottester_unittest.cc
		sigslot_unittest.cc
		socket.h
		socketadapters.cc
		socketadapters.h
		socketaddress.cc
		socketaddress.h
		socketaddresspair.cc
		socketaddresspair.h
		socketaddress_unittest.cc
		socketfactory.h
		socketserver.h
		socketstream.cc
		socketstream.h
		socket_unittest.cc
		socket_unittest.h
		ssladapter.cc
		ssladapter.h
		ssladapter_unittest.cc
		sslfingerprint.cc
		sslfingerprint.h
		sslidentity.cc
		sslidentity.h
		sslidentity_unittest.cc
		sslroots.h
		sslstreamadapter.cc
		sslstreamadapter.h
		sslstreamadapter_unittest.cc
		stream.cc
		stream.h
		stream_unittest.cc
		stringencode.cc
		stringencode.h
		stringencode_unittest.cc
		stringutils.cc
		stringutils.h
		stringutils_unittest.cc
		swap_queue.h
		swap_queue_unittest.cc
		task.cc
		task.h
		taskparent.cc
		taskparent.h
		taskrunner.cc
		taskrunner.h
		task_queue.h
		task_queue_gcd.cc
		task_queue_libevent.cc
		task_queue_posix.cc
		task_queue_posix.h
		task_queue_unittest.cc
		task_queue_win.cc
		task_unittest.cc
		template_util.h
		testbase64.h
		testclient.cc
		testclient.h
		testclient_unittest.cc
		testechoserver.h
		testutils.h
		thread.cc
		thread.h
		thread_annotations.h
		thread_annotations_unittest.cc
		thread_checker.h
		thread_checker_impl.cc
		thread_checker_impl.h
		thread_checker_unittest.cc
		thread_unittest.cc
		timedelta.h
		timestampaligner.cc
		timestampaligner.h
		timestampaligner_unittest.cc
		timeutils.cc
		timeutils.h
		timeutils_unittest.cc
		trace_event.h
		transformadapter.cc
		transformadapter.h
		type_traits.h
		unittest_main.cc
		unixfilesystem.cc
		unixfilesystem.h
		virtualsocketserver.cc
		virtualsocketserver.h
		virtualsocket_unittest.cc
		weak_ptr.cc
		weak_ptr.h
		weak_ptr_unittest.cc
		win32.cc
		win32.h
		win32filesystem.cc
		win32filesystem.h
		win32securityerrors.cc
		win32socketinit.cc
		win32socketinit.h
		win32socketserver.cc
		win32socketserver.h
		win32socketserver_unittest.cc
		win32window.cc
		win32window.h
		win32window_unittest.cc
		win32_unittest.cc
		window.h
		winping.cc
		winping.h)