
SOURCES =	../include/platform/vtx_atomic.h \
			../include/platform/vtx_defineconfig.h \
			../include/platform/vtx_filestream.h \
			../include/platform/vtx_filesystem.h \
			../include/platform/vtx_iostream.h \
			../include/platform/vtx_platform.h \
			../include/platform/vtx_signal.h \
			../include/platform/vtx_thread.h \
			../include/platform/vtx_timer.h \
			../include/core/vtx_assertions.h \
			../include/core/vtx_concurrent_queue.h \
			../include/core/vtx_double_stack_allocator.h \
			../include/core/vtx_eventoutput.h \
			../include/core/vtx_math.h \
			../include/core/vtx_stack_allocator.h \
			../include/core/vtx_types.h \
			../include/core/vtx_util.h \
			../include/vortex/vtx_clock.h \
			../include/vortex/vtx_dx10render.h \
			../include/vortex/vtx_job.h \
			../include/vortex/vtx_manager.h \
			../include/vortex/vtx_openglrender.h \
			../include/vortex/vtx_render.h \
			../include/vortex/vtx_renderinternal.h \
			../include/vortex/vtx_resource.h \
			../include/vortex/vtx_simulation.h \
			../include/vortex/vtx_vortexbase.h \
			../include/vortex/vtx_vortex.h \
			../include/vortex/vtx_window.h \
			platform/file.cpp \
			platform/filestream.cpp \
			platform/filesystem.cpp \
			platform/iostream.cpp \
			platform/signal.cpp \
			platform/thread.cpp \
			platform/timer.cpp \
			core/assertions.cpp \
			core/concurrent_queue.cpp \
			core/eventoutput.cpp \
			core/math.cpp \
			core/matrix.cpp \
			core/stack_allocator.cpp \
			core/util.cpp \
			core/vector2.cpp \
			core/vector3.cpp \
			core/vector4.cpp \
			vortex/clock.cpp \
			vortex/dx10render.cpp \
			vortex/job.cpp \
			vortex/openglrender.cpp \
			vortex/render.cpp \
			vortex/rendercreationparams.cpp \
			vortex/renderinternal.cpp \
			vortex/resource.cpp \
			vortex/simulation.cpp \
			vortex/vortex_root.cpp \
			vortex/window.cpp \
			vortex/windowcreationparams.cpp
CPPFLAGS = -I../include -I/usr/include -msse3 -O0

lib_LIBRARIES = libvortex.a
libvortex_a_SOURCES = $(SOURCES)
libvortex_a_CPPFLAGS = $(CPPFLAGS)

noinst_LIBRARIES = libvortex-tool.a
libvortex_tool_a_SOURCES = $(SOURCES)
libvortex_tool_a_CPPFLAGS = $(CPPFLAGS) -DVTX_TOOL_BUILD
