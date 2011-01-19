AC_PREREQ(2.59)

AC_INIT([libuuuid], [0.0.1], [jan.palus@gmail.com])
AC_CONFIG_AUX_DIR([scripts])

AM_INIT_AUTOMAKE([foreign])
LT_INIT

AC_PROG_CC
AC_HEADER_STDC

case $host in
	*mingw*)
	uuid_impl=win32
	;;
	*linux*)
	PKG_CHECK_MODULES([UUID],[uuid])
	uuid_impl=linux
	;;
        *solaris*)
        AC_CHECK_HEADER([uuid/uuid.h],[],[AC_MSG_ERROR([No <uuid/uuid.h> header found])])
        AC_CHECK_LIB([uuid],[uuid_generate],[],[AC_MSG_ERROR([No suitable -luuid found])])
        uuid_impl=linux
	;;
	*freebsd*)
	uuid_impl=fbsd
	;;
	*)
	AC_MSG_ERROR([No supported UUID implementation found])
esac

AM_CONDITIONAL([WIN32],[test x$uuid_impl = xwin32])
AM_CONDITIONAL([LINUX],[test x$uuid_impl = xlinux])
AM_CONDITIONAL([FBSD],[test x$uuid_impl = xfbsd])

AC_CONFIG_FILES([\
		 Makefile \
		 uuuid.pc \
		 src/Makefile
		 ])
AC_OUTPUT
