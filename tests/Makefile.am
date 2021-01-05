

bin_PROGRAMS = v0


if WITH_PORTAGE
v0_CPPFLAGS = -DPORTAGE
endif
if WITH_PACMAN
v0_CPPFLAGS = -DPACMAN
endif

v0_LDADD = $(CUNIT_LIBS) $(top_srcdir)/src/libversion.la
v0_CXXFLAGS = -I$(top_srcdir)/src
v0_SOURCES = v0.cc  

 