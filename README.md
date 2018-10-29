Thin C++ wrapper around POSIX/Ansi-C/Unix/Linux functions.

Main rationale behind this is to simplify writing robust system code that does
not miss checking any error condition.

2014-2018, Georg Sauthoff <mail@georg.so>, BSD-2-Clause

[![Build Status](https://travis-ci.org/gsauthof/libixxx.svg?branch=master)](https://travis-ci.org/gsauthof/libixxx)

## Design

- All errors are reported via exceptions.
- Return type is changed to `void` if the function just
  returns error codes.
- Overloads are provided for some STL objects (e.g.
  `std::string`) where it makes sense.
- Functions are added as needed.
- The headers are also usable in a mingw environment (under
  Windows), i.e.  some functions unavailable in mingw are
  disabled by the pre-processor and where it makes sense and
  (without too much pain) a thin compatibility wrapper is
  provided (cf. e.g. `fsync()`).

## Example

    #include <iostream>
    #include <ixxx/ixxx.hh>

    using namespace ixxx;
    using namespace std;

    int main(int argc, char **argv)
    {
        if (argc<2) { cerr << "Missing argument\n"; return 1; }
        try {
            posix::unlink(argv[1]);
        } catch (const ixxx::sys_error& e) {
            cerr << "Error: " << e.what() << '\n';
        }
        return 0;
    }

## Compile

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

This creates the library and also the unittests. Execute the unittests via:

    $ ./ut

## Licence

2-clause BSD
