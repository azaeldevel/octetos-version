
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir). \
	$(octetos-core_CFLAGS)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(OCTETOS_VERSION_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

noinst_PROGRAMS = v0

v0_LDADD = $(CUNIT_LIBS) $(OCTETOS_VERSION_LIBS)
v0_CXXFLAGS = -I$(top_srcdir)/src
v0_SOURCES = v0.cc $(top_srcdir)/src/version.cc $(top_srcdir)/src/Portage.cc