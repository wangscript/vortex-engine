#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.66])
AC_INIT(vortex-engine, 0.1a, emilnorden at yahoo dot se)
AC_CONFIG_SRCDIR([src/core/standardallocator.cpp])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER([config.h])
# AC_CONFIG_FILES([Makefile src/Makefile])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_PATH_X
AC_CHECK_HEADERS([stdint.h stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset pow sqrt])

# AC_CONFIG_FILES([Makefile
#                 src/Makefile
#                 vortex_unittest/Makefile
#                 vortex_unittest/src/Makefile])
AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_CONFIG_SUBDIRS([google_test/gtest-1.6.0])
AC_OUTPUT
