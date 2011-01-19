include_HEADERS = uuuid.h

lib_LTLIBRARIES = libuuuid.la

libuuuid_la_SOURCES = uuuid.h
if WIN32
libuuuid_la_SOURCES += uuuid-win32.c
endif
if LINUX
libuuuid_la_SOURCES += uuuid-linux.c
endif
if FBSD
libuuuid_la_SOURCES += uuuid-fbsd.c
endif

libuuuid_la_CPPFLAGS = $(UUID_CFLAGS)

libuuuid_la_LDFLAGS = -no-undefined
libuuuid_la_LIBADD = $(UUID_LIBS)
