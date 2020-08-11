dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(octetos_version, 0.7.0)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=octetos_version
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT



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
AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")

AM_CONDITIONAL(WITH_PORTAGE, test x"$with_portage" = "xyes")
AC_ARG_WITH([portage], AS_HELP_STRING([--with-portage], [Activando soporte para Portage.]))

AM_CONDITIONAL(WITH_PACMAN, test x"$with_pacman" = "xyes")
AC_ARG_WITH([pacman], AS_HELP_STRING([--with-pacman], [Activando soporte para pacman.]))



LT_INIT([win32-dll])


PKG_CHECK_MODULES(OCTETOS_VERSION, [octetos-core octetos-coreutils])




AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
