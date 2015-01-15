#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libFileSyncFtp.la

#######################################
# Build information for each library

# Sources for libFileSync
libFileSyncFtp_la_SOURCES = FtpFilesystem.cpp FtpFilesystem.h

# Linker options libTestProgram
# libFileSyncFtp_la_LDFLAGS = -L$(top_srcdir)/poco-1.6.0/lib/Linux/x86_64 -lPocoNet
libFileSyncFtp_LDADD = -L$(top_srcdir)/poco-1.6.0/lib/Linux/x86_64 -lPocoNet

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libFileSyncFtp_la_CPPFLAGS = -fPIC -I$(top_srcdir)/include -I$(top_srcdir)/poco-1.6.0/Net/include -I$(top_srcdir)/poco-1.6.0/Foundation/include

# libFileSyncFtp_LDFLAGS = -all-static -Wl,-Bdynamic,-L./poco-1.6.0/lib,-lshared,-Bstatic

