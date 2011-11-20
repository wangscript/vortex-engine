
SOURCES =		main.cpp /
			src/concurrent_queue.cpp /
			src/content.cpp /
			src/io.cpp /
			src/jobmanager.cpp /
			src/memory_tests.cpp /
			src/rendermanager_tests.cpp /
			src/root.cpp /
			src/vector3_tests.cpp

# Automake says to use AM_CPPFLAGS instead of CPPFLAGS, but using AM_CPPFLAGS doesnt seem to have an effect.
CPPFLAGS = -I/usr/include -I../google_test/gtest-1.6.0/include/ -I../src/ -msse3 -mssse3 -O0

bin_PROGRAMS = vortextest
vortextest_SOURCES = $(SOURCES)
vortextest_CPPFLAGS = $(CPPFLAGS)
vortextest_LDADD = ../google_test/gtest-1.6.0/lib/libgtest.la

# lib_LIBRARIES = libvortex.a
# libvortex_a_SOURCES = $(SOURCES)
# libvortex_a_CPPFLAGS = $(CPPFLAGS)

# noinst_LIBRARIES = libvortex-tool.a
# libvortex_tool_a_SOURCES = $(SOURCES)
# libvortex_tool_a_CPPFLAGS = $(CPPFLAGS) -DVTX_TOOL_BUILD
