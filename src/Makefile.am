AUTOMAKE_OPTIONS=foreign 1.4


bin_PROGRAMS = version
lib_LTLIBRARIES = libversion.la


version_CFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS)
version_SOURCES = \
	main.cc \
	version.cc
if WITH_PORTAGE
version_SOURCES += Portage.cc
endif
if WITH_PACMAN
version_SOURCES += Pacman.cc
endif
if WITH_APT
version_SOURCES += Apt.cc
endif
version_LDFLAGS =
version_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS)
if WITH_PORTAGE
version_CPPFLAGS = -DPORTAGE
endif
if WITH_PACMAN
version_CPPFLAGS = -DPACMAN
endif
if WITH_APT
version_CPPFLAGS = -DAPT
endif




if WITH_PORTAGE
libversion_la_CPPFLAGS = -DPORTAGE
endif
if WITH_PACMAN
libversion_la_CPPFLAGS = -DPACMAN
endif
if WITH_APT
libversion_la_CPPFLAGS = -DAPT
endif
libversion_la_CXXFLAGS = -fPIC



libversion_la_LIBADD = 
libversion_la_SOURCES = libversion.cc




octetos_version_includedir = $(includedir)/octetos/version
octetos_version_include_HEADERS = version.hh
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-version.pc
EXTRA_DIST = octetos-version.pc.in