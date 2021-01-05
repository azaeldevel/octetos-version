

AC_INIT(octetos_version, 0.20.0-alpha)
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


LT_INIT


PKG_CHECK_MODULES(OCTETOS_VERSION, [octetos-core octetos-coreutils])


AM_CONDITIONAL(WITH_PORTAGE, test x"$with_portage" = "xyes")
AC_ARG_WITH([portage], AS_HELP_STRING([--with-portage], [Activando soporte para Gentoo.]))

AM_CONDITIONAL(WITH_PACMAN, test x"$with_pacman" = "xyes")
AC_ARG_WITH([pacman], AS_HELP_STRING([--with-pacman], [Activando soporte para ArchLinux.]))

AM_CONDITIONAL(WITH_APT, test x"$with_apt" = "xyes")
AC_ARG_WITH([apt], AS_HELP_STRING([--with-apt], [Activando soporte para Debian.]))


AM_CONDITIONAL(WITH_TESTS, test x"$with_tests" = "xyes")
AC_ARG_WITH([tests], AS_HELP_STRING([--with-tests], [Compilando con soporte para Tests]))
if test "x$with_tests" = "xyes"; then 
	PKG_CHECK_MODULES(CUNIT,cunit)
fi



AC_OUTPUT([
Makefile
src/Makefile
src/octetos-version.pc
tests/Makefile
])

