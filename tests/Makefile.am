
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir). \
	$(octetos-core_CFLAGS)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(OCTETOS_VERSION_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

check_PROGRAMS = v0
TESTS= $(check_PROGRAMS)


if WITH_PORTAGE
v0_CPPFLAGS = -DPORTAGE
endif
if WITH_PACMAN
v0_CPPFLAGS = -DPACMAN
endif

v0_LDADD = $(CUNIT_LIBS) $(OCTETOS_VERSION_LIBS) $(top_srcdir)/src/libversion.la
v0_CXXFLAGS = -I$(top_srcdir)/src
v0_SOURCES = v0.cc  

 