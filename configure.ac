AC_PREREQ([2.63])
AC_INIT([udal], [0.0.1])
AC_CONFIG_SRCDIR([src/Database.cpp])
AC_CONFIG_MACRO_DIR([../fintp_utils/m4])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AM_INIT_AUTOMAKE

AC_CHECK_HEADERS([malloc.h stdlib.h string.h sys/param.h sys/timeb.h unistd.h], [], [Cannot build])

AC_CHECK_FUNCS([ftime gethostbyaddr gethostbyname gethostname memset strerror strtol strtoul uname], [], [Cannot build])

ENVIRONMENT

AX_PTHREAD(, [AC_MSG_ERROR([Cannot build without pthread]) ])

AX_BOOST_BASE([1.48.0], , [AC_MSG_ERROR([Cannot build without Boost])])

AX_LIB_XERCES([2.8.0])

AC_ARG_WITH(oracle,
 [AS_HELP_STRING([--with-oracle], [link with Oracle libs (default is no)])],
 [ORACLE=$withval;with_oracle=yes], [with_oracle=no])

if test $with_oracle == yes; then
	AX_LIB_ORACLE_OCI([11.2])
	if test $HAVE_ORACLE_OCI = "no"; then
		AC_MSG_ERROR([Cannot build without OCI])
	fi
fi

UNIXODBC

AM_CONDITIONAL(COMP_ORACLE, test $with_oracle == yes)
AM_CONDITIONAL(COMP_ODBC, test $unixodbc != no)

if test $with_oracle == no && test $unixodbc == no; then
	AC_MSG_ERROR([Cannot build without OCI or UnixODBC support])
fi

AC_CONFIG_FILES([Makefile usage_sample/Makefile])

AC_OUTPUT
