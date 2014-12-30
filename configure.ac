#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tombola], [0.1], [guido.aulisi@gmail.com],, [http://pinguino.linkpc.net])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([main.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
PKG_PROG_PKG_CONFIG

# Checks for libraries.
PKG_CHECK_MODULES([gtkmm], [gtkmm-3.0 >= 3.8])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_ARG_ENABLE([debug],
	AS_HELP_STRING([--enable-debug], [enable debug]),
	AC_DEFINE([HAVE_DEBUG], [1], [Enable debugging code]))

AC_CONFIG_FILES([Makefile])
AC_OUTPUT