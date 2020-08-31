AUTOMAKE_OPTIONS=foreign 1.4

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir). \
	$(octetos-core_CFLAGS)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(OCTETOS_VERSION_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g 

bin_PROGRAMS = version
lib_LTLIBRARIES = libversion.la


version_CFLAGS =-I$(OCTETOS_VERSION_CFLAGS)
version_SOURCES = \
	main.cc \
	version.cc
if WITH_PORTAGE
version_SOURCES += Portage.cc
endif
if WITH_PACMAN
version_SOURCES += Pacman.cc
endif
version_LDFLAGS =
version_LDADD = $(OCTETOS_VERSION_LIBS)
if WITH_PORTAGE
version_CPPFLAGS = -DPORTAGE
endif
if WITH_PACMAN
version_CPPFLAGS = -DPACMAN
endif
if NATIVE_WIN32
version_LDFLAGS += -mwindows 
endif


libversion_la_CFLAGS = -fPIC
libversion_la_CPPFLAGS = -fPIC
if WITH_PORTAGE
libversion_la_CPPFLAGS = -DPORTAGE
endif
if WITH_PACMAN
libversion_la_CPPFLAGS = -DPACMAN
endif
libversion_la_CXXFLAGS = -fPIC
libversion_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
libversion_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
libversion_la_LDFLAGS += -export-dynamic
endif
libversion_la_LIBADD = 
libversion_la_SOURCES = libversion.cc



libshmem_la_SOURCES = dummy.c
libshmem_la_CFLAGS = -fPIC

octetos_version_includedir = $(includedir)/octetos/version
octetos_version_include_HEADERS = version.hh
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-version.pc
EXTRA_DIST = octetos-version.pc.in