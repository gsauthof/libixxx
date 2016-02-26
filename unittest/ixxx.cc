// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

/* {{{ 2-clause BSD

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

}}} */

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include <ixxx/ixxx.h>

#include <errno.h>
#include <string.h>

#include <array>
#include <fstream>
using namespace std;
using namespace ixxx;

BOOST_AUTO_TEST_SUITE( ixxx )

  BOOST_AUTO_TEST_SUITE( ansi )

    BOOST_AUTO_TEST_CASE( basic )
    {
      string filename("tmp/basic");
      fs::create_directory("tmp");
      fs::remove(filename);
      BOOST_CHECK_EQUAL(fs::exists(filename), false);
      int fd = posix::open(filename, O_CREAT | O_WRONLY, 0666);
      posix::close(fd);
      BOOST_CHECK_EQUAL(fs::exists(filename), true);
    }

    BOOST_AUTO_TEST_CASE( except )
    {
      string filename("tmp/except");
      fs::create_directory("tmp");
      fs::remove(filename);
      BOOST_CHECK_EQUAL(fs::exists(filename), false);
      bool caught = false;
      try {
        int fd = posix::open(filename, O_WRONLY, 0666);
        posix::close(fd);
        // This does not catch the exception on gcc/clang
        // } catch (const errno_error &e) {
      } catch (const ::errno_error &e) {
        caught = true;
        BOOST_CHECK_EQUAL(e.code(), ENOENT);
      }
      BOOST_CHECK_EQUAL(fs::exists(filename), false);
      BOOST_CHECK_EQUAL(caught, true);
    }

    BOOST_AUTO_TEST_CASE( except2 )
    {
      string filename("tmp/except2");
      fs::create_directory("tmp");
      fs::remove(filename);
      BOOST_CHECK_EQUAL(fs::exists(filename), false);
      bool caught = false;
      try {
        int fd = posix::open(filename, O_WRONLY, 0666);
        posix::close(fd);
      } catch (const errno_error &e) {
        caught = true;
        BOOST_CHECK_EQUAL(e.code(), ENOENT);
        BOOST_CHECK(e.function() == Function::OPEN);
      }
      BOOST_CHECK_EQUAL(fs::exists(filename), false);
      BOOST_CHECK_EQUAL(caught, true);
    }

    BOOST_AUTO_TEST_CASE( env )
    {
      string s(ansi::getenv("PATH"));
      BOOST_CHECK_EQUAL(s.empty(), false);
    }
    BOOST_AUTO_TEST_CASE( noenv )
    {
      bool caught = false;
      try {
        string s(ansi::getenv("DOESNOTEXISTNOTEXIST"));
      } catch (runtime_error &e) {
        caught = true;
        BOOST_CHECK_EQUAL(e.function(), Function::GETENV);
      }
      BOOST_CHECK_EQUAL(caught, true);
    }

  BOOST_AUTO_TEST_SUITE_END()

  BOOST_AUTO_TEST_SUITE( posix )

#if !defined(__MINGW32__) && !defined(__MINGW64__)
    BOOST_AUTO_TEST_CASE( exception_errno_message )
    {
      string message;
      bool caught = false;
      try {
        try {
          siginfo_t info = {0};
          posix::waitid(P_PID, 0, &info, WEXITED);
        } catch (const exception &e) {
          message = e.what();
          throw;
        }
      } catch (const ixxx::errno_error &e) {
#if (defined(__APPLE__) && defined(__MACH__))
        BOOST_CHECK_EQUAL(e.code(), ECHILD);
#else
        BOOST_CHECK_EQUAL(e.code(), EINVAL);
#endif
        BOOST_CHECK_EQUAL(e.function(), ixxx::Function::WAITID);
        caught = true;
      }
      ostringstream o;
#if (defined(__APPLE__) && defined(__MACH__))
      o << "waitid: " << strerror(ECHILD) << " (" << ECHILD << ')';
#else
      o << "waitid: " << strerror(EINVAL) << " (" << EINVAL << ')';
#endif
      //BOOST_CHECK_EQUAL(message, "waitid: Invalid argument (22)");
      BOOST_CHECK_EQUAL(message, o.str());
      BOOST_CHECK_EQUAL(caught, true);
    }
#endif

    BOOST_AUTO_TEST_CASE( open_exception_errno_message )
    {
      string message;
      bool caught = false;
      try {
        try {
          posix::open("does_not_exist_23_42", O_RDWR);
        } catch (const exception &e) {
          message = e.what();
          throw;
        }
      } catch (const ixxx::errno_error &e) {
        BOOST_CHECK_EQUAL(e.code(), ENOENT);
        BOOST_CHECK_EQUAL(e.function(), ixxx::Function::OPEN);
        caught = true;
      }
      ostringstream o;
      o << "open: " << strerror(ENOENT) << " (" << ENOENT << ')';
      //BOOST_CHECK_EQUAL(message, "waitid: Invalid argument (22)");
      BOOST_CHECK_EQUAL(message, o.str());
      BOOST_CHECK_EQUAL(caught, true);
    }

    BOOST_AUTO_TEST_CASE(open_newlines)
    {
      int fd = posix::open("newlines", O_CREAT | O_WRONLY, 0666);
      const char inp1[] = "Hello\n";
      posix::write(fd, inp1, sizeof(inp1)-1);
      const char inp2[] = "World\n";
      posix::write(fd, inp2, sizeof(inp2)-1);
      posix::close(fd);
      BOOST_CHECK_EQUAL(boost::filesystem::file_size("newlines"),
          12u);
    }

  BOOST_AUTO_TEST_SUITE_END()

  BOOST_AUTO_TEST_SUITE(shared)

    BOOST_AUTO_TEST_CASE(enums)
    {
      {
        ostringstream o;
        o << ixxx::Function::CLOSE;
        BOOST_CHECK_EQUAL(o.str(), "close");
      }
      {
        ostringstream o;
        o << ixxx::Function::WRITE;
        BOOST_CHECK_EQUAL(o.str(), "write");
      }
      {
        ostringstream o;
        o << ixxx::Function::ISATTY;
        BOOST_CHECK_EQUAL(o.str(), "isatty");
      }
    }

    BOOST_AUTO_TEST_CASE(end_markers)
    {
      {
        ostringstream o;
        o << ixxx::Function::FIRST_;
        BOOST_CHECK_EQUAL(o.str(), "?UNK?");
      }
      {
        ostringstream o;
        o << ixxx::Function::LAST_;
        BOOST_CHECK_EQUAL(o.str(), "?UNK?");
      }
    }

  BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

