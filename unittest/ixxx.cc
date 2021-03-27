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

#include <ixxx/ixxx.hh>
#include <ixxx/socket.hh>
#include <ixxx/pthread.hh>

#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>

#include <array>
#include <fstream>
using namespace std;
using namespace ixxx;


static void *sleep_thread_main(void *x)
{
    struct timespec ts { .tv_nsec = 100000000 };
    ixxx::posix::nanosleep(&ts, nullptr);

    size_t a = (size_t)x;

    return (void*)(a+2);
}

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
      } catch (const sys_error &e) {
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
      } catch (const sys_error &e) {
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
      } catch (getenv_error &e) {
        caught = true;
        BOOST_CHECK(e.function() == Function::GETENV);
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
      } catch (const ixxx::sys_error &e) {
#if (defined(__APPLE__) && defined(__MACH__))
        BOOST_CHECK_EQUAL(e.code(), ECHILD);
#else
        BOOST_CHECK_EQUAL(e.code(), EINVAL);
#endif
        BOOST_CHECK(e.function() == ixxx::Function::WAITID);
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
      } catch (const ixxx::open_error &e) {
        BOOST_CHECK_EQUAL(e.code(), ENOENT);
        BOOST_CHECK(e.function() == ixxx::Function::OPEN);
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
      string filename("tmp/newlines");
      fs::create_directory("tmp");
      fs::remove(filename);

      int fd = posix::open(filename.c_str(), O_CREAT | O_WRONLY, 0666);
      const char inp1[] = "Hello\n";
      posix::write(fd, inp1, sizeof(inp1)-1);
      const char inp2[] = "World\n";
      posix::write(fd, inp2, sizeof(inp2)-1);
      posix::close(fd);
      BOOST_CHECK_EQUAL(boost::filesystem::file_size(filename), 12u);
    }

    BOOST_AUTO_TEST_CASE(getsetenv)
    {
      ixxx::posix::setenv("FOO23", "42", true);
      BOOST_CHECK_EQUAL(ixxx::ansi::getenv("FOO23"), string("42"));
      ixxx::posix::setenv("FOO23", "xyz", true);
      BOOST_CHECK_EQUAL(ixxx::ansi::getenv("FOO23"), string("xyz"));
    }

    BOOST_AUTO_TEST_CASE(some_fsync)
    {
      string filename("tmp/fsync");
      fs::create_directory("tmp");
      fs::remove(filename);
      int fd = posix::open(filename, O_CREAT | O_WRONLY, 0666);
      posix::fsync(fd);
      posix::close(fd);
    }


  BOOST_AUTO_TEST_SUITE_END() // posix

  BOOST_AUTO_TEST_SUITE(mixed)

    BOOST_AUTO_TEST_CASE(imf_fixdate)
    {
      static const char fmt[] = "%a, %d %b %Y %H:%M:%S GMT";
      time_t now = 0;
      if (now  == time_t(-1))
        now = ixxx::ansi::time();
      else
        now = 1501746457;
      struct tm tm;
      ixxx::posix::gmtime_r(&now, &tm);
      array<char, 30> a;
      ixxx::ansi::strftime(a, fmt, &tm);
      BOOST_CHECK_EQUAL(string(a.data()), "Thu, 03 Aug 2017 07:47:37 GMT");
      a[0] = 0;
      ixxx::ansi::strftime(a.data(), a.size(), fmt, &tm);
      BOOST_CHECK_EQUAL(string(a.data()), "Thu, 03 Aug 2017 07:47:37 GMT");
    }
  BOOST_AUTO_TEST_SUITE_END()


  BOOST_AUTO_TEST_SUITE(socket)

    BOOST_AUTO_TEST_CASE(gai_foo)
    {
        struct addrinfo hints = {
            .ai_family   = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM
        };
        struct addrinfo *res = 0;
        BOOST_CHECK_EXCEPTION(ixxx::posix::getaddrinfo("example.invalid", "123", &hints, &res),
                ixxx::sys_error,
                [](const sys_error &e) { return !!strstr(e.what(), "not known"); }
                );

    }

  BOOST_AUTO_TEST_SUITE_END()

  BOOST_AUTO_TEST_SUITE(thread)

    BOOST_AUTO_TEST_CASE(pthread_basic)
    {
        pthread_t thread_id;
        ixxx::posix::pthread_create(&thread_id, nullptr, sleep_thread_main, (void*)21);
        void *r = 0;
        ixxx::posix::pthread_join(thread_id, &r);
        size_t x = 0;
        memcpy(&x, &r, sizeof x);
        BOOST_CHECK_EQUAL(x, 23);

    }

  BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

