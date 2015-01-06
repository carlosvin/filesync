dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.64)
AC_INIT(filesync, 1.0)
AC_PROG_CC
AC_CONFIG_MACRO_DIR(m4)

AC_CANONICAL_SYSTEM

dnl Initialize automake
AM_INIT_AUTOMAKE

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

# Checks for programs.
AC_LANG([C++])
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext])


dnl Initialize Libtool
LT_INIT


dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_CONFIG_FILES(Makefile
                exampleProgram/Makefile
                libFileSync/Makefile
                include/Makefile)
AC_OUTPUT