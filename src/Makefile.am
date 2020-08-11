
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(OCTETOS_VERSION_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = version

version_SOURCES = \
	main.cc \
	version.cc

version_LDFLAGS = 

version_LDADD = $(OCTETOS_VERSION_LIBS) 

if WITH_PORTAGE
version_CPPFLAGS = -DPORTAGE
endif

if NATIVE_WIN32
version_LDFLAGS += -mwindows 
endif
