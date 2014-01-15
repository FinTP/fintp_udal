bin_PROGRAMS = usage_sample

usage_sample_SOURCES = main.cpp
usage_sample_LDFLAGS = @LIBS@ @LDFLAGS@ -L$(FINTP_HOME)/fintp_udal/.libs -lfintp_udal -L$(FINTP_HOME)/fintp_log/.libs -lfintp_log

COMMON_CPPFLAGS = -I$(FINTP_HOME)/fintp_udal/src -I$(FINTP_HOME)/fintp_utils/src -I$(FINTP_HOME)/fintp_log/src @CPPFLAGS@ @BOOST_CPPFLAGS@ @XERCES_CPPFLAGS@ -DDEBUG_ENABLED

if COMP_ODBC
 AM_CPPFLAGS = -DWITH_ODBC $(COMMON_CPPFLAGS)
else
 AM_CPPFLAGS = $(COMMON_CPPFLAGS)
endif

AUTOMAKE_OPTIONS = foreign
