
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


if WITH_GENTOO
v0_CPPFLAGS = -DGENTOO
endif
if WITH_ARCH
v0_CPPFLAGS = -DARCH
endif
v0_LDADD = $(CUNIT_LIBS) $(OCTETOS_VERSION_LIBS)
v0_CXXFLAGS = -I$(top_srcdir)/src
v0_SOURCES = v0.cc $(top_srcdir)/src/version.cc 
if WITH_GENTOO
v0_SOURCES += $(top_srcdir)/src/Portage.cc
endif
if WITH_ARCH
v0_SOURCES += $(top_srcdir)/src/Pacman.cc
endif
 