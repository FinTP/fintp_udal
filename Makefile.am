ACLOCAL_AMFLAGS = -I ../fintp_utils/m4

if COMP_ORACLE
 OCICPP_FLAGS = -DORA_ONLY @ORACLE_OCI_CFLAGS@
 OCILIB_FLAGS = @ORACLE_OCI_LDFLAGS@ -lclntsh
else
 OCICPP_FLAGS = 
 OCILIB_FLAGS = 
endif

AM_CPPFLAGS = -DUNIX -DDEBUG_ENABLED	\
-I$(FINTP_HOME)/fintp_utils/src	\
-I$(FINTP_HOME)/fintp_log/src	\
@CPPFLAGS@	\
@PTHREAD_CFLAGS@	\
@BOOST_CPPFLAGS@	\
@XERCES_CPPFLAGS@	\
$(OCICPP_FLAGS)

lib_LTLIBRARIES = libfintp_udal.la

AUTOMAKE_OPTIONS = foreign

if COMP_ODBC
 ODBCLIB_FLAGS = -lodbc
 SRCS = $(COMMON_SRCS) \
$(ODBC)
else
 SRCS = $(COMMON_SRCS)
 ODBCLIB_FLAGS = 
endif

if COMP_ORACLE
 libfintp_udal_la_SOURCES = $(SRCS) \
$(Oracle)
else
 libfintp_udal_la_SOURCES = $(SRCS)
endif

libfintp_udal_la_LDFLAGS = @LIBS@ @LDFLAGS@	\
@PTHREAD_LIBS@	\
@BOOST_LDFLAGS@	\
@XERCES_LDFLAGS@ -lxerces-c	\
$(ODBCLIB_FLAGS)	\
$(OCILIB_FLAGS)	\
-L$(FINTP_HOME)/fintp_utils/.libs -lfintp_utils	\
-L$(FINTP_HOME)/fintp_log/.libs -lfintp_log

COMMON_SRCS = src/ConnectionString.cpp	\
src/Database.cpp	\
src/DatabaseProvider.cpp	\
src/DataColumn.cpp	\
src/DataCommand.cpp	\
src/DataParameter.cpp	\
src/DataRow.cpp	\
src/DataSet.cpp

ODBC = src/ODBC/ODBCColumn.cpp	\
src/ODBC/ODBCDatabase.cpp	\
src/ODBC/ODBCDatabaseProvider.cpp	\
src/ODBC/ODBCParameter.cpp	\
$(DB2)	\
$(Informix)	\
$(SqlServer)	\
$(Postgres)

DB2 = src/ODBC/DB2/Db2Database.cpp	\
src/ODBC/DB2/Db2DatabaseProvider.cpp

Informix = src/ODBC/Informix/InformixDatabase.cpp	\
src/ODBC/Informix/InformixDatabaseProvider.cpp

Postgres = src/ODBC/Postgres/PostgresDatabase.cpp	\
src/ODBC/Postgres/PostgresDatabaseProvider.cpp

SqlServer = src/ODBC/SqlServer/SqlServerDatabase.cpp	\
src/ODBC/SqlServer/SqlServerDatabaseProvider.cpp

Oracle = src/Oracle/OracleColumn.cpp	\
src/Oracle/OracleDatabase.cpp	\
src/Oracle/OracleDatabaseProvider.cpp	\
src/Oracle/OracleParameter.cpp

nobase_include_HEADERS = src/ConnectionString.h	\
src/Database.h	\
src/DatabaseProvider.h	\
src/DataColumn.h	\
src/DataCommand.h	\
src/DataParameter.h	\
src/DataRow.h	\
src/DataSet.h	\
src/ODBC/ODBCColumn.h	\
src/ODBC/ODBCDatabase.h	\
src/ODBC/ODBCDatabaseProvider.h	\
src/ODBC/ODBCParameter.h	\
src/ODBC/DB2/Db2Database.h	\
src/ODBC/DB2/Db2DatabaseProvider.h	\
src/ODBC/Informix/InformixDatabase.h	\
src/ODBC/Informix/InformixDatabaseProvider.h	\
src/ODBC/Postgres/PostgresDatabase.h	\
src/ODBC/Postgres/PostgresDatabaseProvider.h	\
src/ODBC/SqlServer/SqlServerDatabase.h	\
src/ODBC/SqlServer/SqlServerDatabaseProvider.h	\
src/Oracle/OracleColumn.h	\
src/Oracle/OracleDatabase.h	\
src/Oracle/OracleDatabaseProvider.h	\
src/Oracle/OracleParameter.h

SUBDIRS = . usage_sample
