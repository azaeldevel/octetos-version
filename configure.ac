
AC_INIT(octetos_version, 0.20.0-alpha)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11])
AM_SILENT_RULES([yes])

AC_PROG_CXX



LT_INIT

PKG_CHECK_MODULES(OCTETOS_VERSION, [octetos-core])

AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")

AM_CONDITIONAL(WITH_PORTAGE, test x"$with_portage" = "xyes")
AC_ARG_WITH([portage], AS_HELP_STRING([--with-portage], [Activando soporte para Gentoo.]))

AM_CONDITIONAL(WITH_PACMAN, test x"$with_pacman" = "xyes")
AC_ARG_WITH([pacman], AS_HELP_STRING([--with-pacman], [Activando soporte para ArchLinux.]))

AM_CONDITIONAL(WITH_APT, test x"$with_apt" = "xyes")
AC_ARG_WITH([apt], AS_HELP_STRING([--with-apt], [Activando soporte para Debian.]))



PKG_CHECK_MODULES(CUNIT,cunit)



AC_OUTPUT([
Makefile
src/Makefile
src/octetos-version.pc
tests/Makefile
])

