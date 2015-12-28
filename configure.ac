#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tombola], [0.7], [guido.aulisi@gmail.com],, [http://pinguino.linkpc.net])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([main.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LIBTOOL
LT_INIT
PKG_PROG_PKG_CONFIG

# Checks for libraries.
PKG_CHECK_MODULES([gtkmm], [gtkmm-3.0 >= 3.8])
BOOST_REQUIRE([1.53.0])
BOOST_CONVERSION
BOOST_ASIO
BOOST_BIND

# Checks for c++11
AC_LANG_PUSH([C++])
AX_CXX_COMPILE_STDCXX_11([ext],[optional])
AC_LANG_POP([C++])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([socket])

AC_ARG_ENABLE([debug],
	AS_HELP_STRING([--enable-debug], [enable debug]),
	AC_DEFINE([HAVE_DEBUG], [1], [Enable debugging code]))
AC_ARG_ENABLE([remote],
	AS_HELP_STRING([--enable-remote], [enable remote control]),
	AC_DEFINE([HAVE_REMOTE], [1], [Enable remote control]))

AC_CONFIG_FILES([Makefile tombola.spec])
AC_OUTPUT
