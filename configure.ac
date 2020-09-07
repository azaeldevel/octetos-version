dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(octetos_version, 0.17.0-alpha)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11])
AM_SILENT_RULES([yes])

AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
#IT_PROG_INTLTOOL([0.35.0])

#GETTEXT_PACKAGE=octetos_version
#AC_SUBST(GETTEXT_PACKAGE)
#AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
#AM_GLIB_GNU_GETTEXT



dnl ***************************************************************************
dnl Check for Windows
dnl ***************************************************************************
AC_CANONICAL_HOST

case $host_os in
  *mingw*)
    platform_win32=yes
    native_win32=yes
    ;;
  pw32* | *cygwin*)
    platform_win32=yes
    native_win32=no
    ;;
  *)
    platform_win32=no
    native_win32=no
    ;;
esac



PKG_CHECK_MODULES(OCTETOS_VERSION, [octetos-core octetos-coreutils])

AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")

AM_CONDITIONAL(WITH_GENTOO, test x"$with_gentoo" = "xyes")
AC_ARG_WITH([gentoo], AS_HELP_STRING([--with-gentoo], [Activando soporte para Gentoo.]))

AM_CONDITIONAL(WITH_ARCH, test x"$with_arch" = "xyes")
AC_ARG_WITH([arch], AS_HELP_STRING([--with-arch], [Activando soporte para ArchLinux.]))



LT_INIT([win32-dll])


PKG_CHECK_MODULES(CUNIT,cunit)



AC_OUTPUT([
Makefile
src/Makefile
src/octetos-version.pc
tests/Makefile
])

