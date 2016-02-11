Thin C++ wrapper around POSIX/Ansi-C/Unix/Linux functions.

Main rationale behind this is to simplify writing robust system code that does
not miss checking any error condition.

2014-02-01, Georg Sauthoff <mail@georg.so>

[![Build Status](https://travis-ci.org/gsauthof/libixxx.svg?branch=master)](https://travis-ci.org/gsauthof/libixxx)

## Design

- All errors are reported via exceptions
- Overloads are provided for directly supplying string arguments as `std::string`
- Functions are added as needed

## Example

    #include <iostream>
    #include <ixxx/ixxx.h>

    using namespace ixxx;

    int main(int argc, char **argv)
    {
      if (argc<2) { cerr << "Missing argument\n"; return 1; }
      try {
        posix::unlink(argv[1]);
      } catch (const ixxx::runtime_error &e) {
        cerr << "Error: " << e.what() << '\n';
      }
      return 0;
    }

## Compile

    $ mkdir build
    $ cd build
    $ cmake ../CMakeLists.txt ..

This creates the library and also the unittests. Execute the unittests via:

    $ ./ut

## Licence

2-clause BSD
