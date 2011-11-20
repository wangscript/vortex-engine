
SOURCES =		concurrency/vtx_concurrent_queue.h \
			concurrency/vtx_job.h \
			concurrency/vtx_jobmanager.h \
			concurrency/vtx_jobprocessor.h \
			concurrency/vtx_signal.h \
			concurrency/vtx_thread.h \
			content/vtx_contentpackage.h \
			content/vtx_resource.h \
			core/vtx_allocator.h \
			core/vtx_assertions.h \
			core/vtx_atomic.h \
			core/vtx_buildconfig.h \
			core/vtx_camera.h \
			core/vtx_clock.h \
			core/vtx_double_stack_allocator.h \
			core/vtx_eventoutput.h \
			core/vtx_math.h \
			core/vtx_matrix4x4.h \
			core/vtx_nativewindow.h \
			core/vtx_platform.h \
			core/vtx_simulationmanager.h \
			core/vtx_stack_allocator.h \
			core/vtx_timer.h \
			core/vtx_types.h \
			core/vtx_util.h \
			core/vtx_vector2.h \
			core/vtx_vector3.h \
			core/vtx_vector4.h \
			core/vtx_vortexbase.h \
			core/vtx_vortex.h \
			core/vtx_window.h \
			graphics/vtx_d3d10vertexbuffer.h \
			graphics/vtx_dx10render.h \
			graphics/vtx_openglrender.h \
			graphics/vtx_renderapi.h \
			graphics/vtx_rendercreationparams.h \
			graphics/vtx_rendermanager.h \
			graphics/vtx_texture.h \
			graphics/vtx_vbuffer.h \
			graphics/vtx_vertexposnormtex.h \
			io/vtx_filestream.h \
			io/vtx_filesystem.h \
			io/vtx_iostream.h \
			text/vtx_stringutil.h \
			text/utf8.h \
			text/utf8/checked.h \
			text/utf8/core.h \
			text/utf8/unchecked.h \
			concurrency/job.cpp \
			concurrency/jobmanager.cpp \
			concurrency/jobprocessor.cpp \
			concurrency/signal.cpp \
			concurrency/thread.cpp \
			content/contentpackage.cpp \
			content/resource.cpp \
			core/assertions.cpp \
			core/camera3d.cpp \
			core/clock.cpp \
			core/concurrent_queue.cpp \
			core/eventoutput.cpp \
			core/math.cpp \
			core/matrix.cpp \
			core/simulationmanager.cpp \
			core/stack_allocator.cpp \
			core/timer.cpp \
			core/util.cpp \
			core/vector2.cpp \
			core/vector3.cpp \
			core/vector4.cpp \
			core/vortex_root.cpp \
			core/window.cpp \
			core/windowcreationparams.cpp \
			graphics/dx10render.cpp \
			graphics/openglrender.cpp \
			graphics/render.cpp \
			graphics/rendercreationparams.cpp \
			graphics/renderinternal.cpp \
			io/file.cpp \
			io/filestream.cpp \
			io/filesystem.cpp \
			io/iostream.cpp \
			text/stringutil.cpp

# Automake says to use AM_CPPFLAGS instead of CPPFLAGS, but using AM_CPPFLAGS doesnt seem to have an effect.
CPPFLAGS = -I/usr/include -msse3 -mssse3 -O0

lib_LIBRARIES = libvortex.a
libvortex_a_SOURCES = $(SOURCES)
libvortex_a_CPPFLAGS = $(CPPFLAGS)

noinst_LIBRARIES = libvortex-tool.a
libvortex_tool_a_SOURCES = $(SOURCES)
libvortex_tool_a_CPPFLAGS = $(CPPFLAGS) -DVTX_TOOL_BUILD
