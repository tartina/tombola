ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = tombola
tombola_SOURCES = main.cc window.cc window.h about.cc about.h bingo.h bingo.cc remote.h remote.cc callback.h

tombola_CPPFLAGS=$(gtkmm_CFLAGS)
tombola_CXXFLAGS=-Wall
tombola_LDADD=$(gtkmm_LIBS) $(BOOST_SYSTEM_LIBS)

icon48dir = $(datadir)/icons/hicolor/48x48/apps
dist_icon48_DATA = icons/48/tombola.png

icon128dir = $(datadir)/icons/hicolor/128x128/apps
dist_icon128_DATA = icons/128/tombola.png

desktopdir = $(datadir)/applications
dist_desktop_DATA = tombola.desktop
