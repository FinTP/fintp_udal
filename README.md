fintp_udal
==========

Uniform database access library for **FinTP**

Requirements
------------
- Boost
- Xerces-C
- pthread
- UnixODBC (only for Unix-like systems)
- Oracle Instant Client
- **fintp_utils**
- **fintp_log**

Build instructions
------------------
- On Unix-like systems, **fintp_udal** uses the GNU Build System (Autotools) so we first need to generate the configuration script using:


        autoreconf -fi
Now we must run: 

        ./configure [--with-oracle=yes/no][without-unixodbc]
        make
By default, **fintp_udal** is built with UnixODBC support and no Oracle Instant Client support.
- For Windows, a Visual Studio 2010 solution is provided.

License
-------
- [GPLv3](http://www.gnu.org/licenses/gpl-3.0.html)

