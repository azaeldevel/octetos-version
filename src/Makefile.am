
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

version_SOURCES = \
	main.cc \
	version.cc
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
