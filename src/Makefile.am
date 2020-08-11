## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(OCTETOS_VERSION_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = octetos_version

octetos_version_SOURCES = \
	main.cc \
	version.cc

octetos_version_LDFLAGS = 

octetos_version_LDADD = $(OCTETOS_VERSION_LIBS) 

if WITH_PORTAGE
octetos_version_CPPFLAGS = -DPORTAGE
endif

if NATIVE_WIN32
octetos_version_LDFLAGS += -mwindows 
endif
