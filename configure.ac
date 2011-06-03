#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.66])
AC_INIT(vortex, 0.1, emilnorden at yahoo.se)
AC_CONFIG_SRCDIR([src/vortex/resource.cpp])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_CONFIG_HEADER([config.h])
AC_PROG_RANLIB

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

CXXFLAGS="-g"

# Checks for libraries.

# Checks for header files.
AC_PATH_X
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_CONFIG_SUBDIRS([google_test/gtest-1.6.0])
AC_OUTPUT
