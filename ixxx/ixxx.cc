// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#include "ixxx.h"

#include <sstream>
#include <array>

#include <string.h>
#include <errno.h>

using namespace std;




namespace {

  string mk_errno_msg(int errno_) {
    ostringstream o;
    array<char, 256> buffer = {0};
    const char *x = buffer.data();

    // work around g++ unconditionally defining _GNU_SOURCE
    // https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=485135
    // http://stackoverflow.com/questions/11670581/why-is-gnu-source-defined-by-default-and-how-to-turn-it-off
#ifdef _GNU_SOURCE
    x = ::strerror_r(errno_, buffer.data(), buffer.size());
#else
  #if defined(__MINGW32__) || defined(__MINGW64__)
    // cf. sec_api/string_s.h
    int r = strerror_s(buffer.data(), buffer.size(), errno_);
  #else
    int r = ::strerror_r(errno_, buffer.data(), buffer.size());
  #endif
    (void)r;
#endif
    o << x << " (" << errno_ << ')';
    return o.str();
  }

  template <typename E> const char* enum2str(E e, const char ** argv)
  {
    if (e > E::FIRST_ && e < E::LAST_) {
      unsigned index = static_cast<unsigned>(e);
      return argv[index];
    } else {
      return "?UNK?";
    }
  }


}

namespace ixxx {

  static const char *function_str[] = {
    0,
    "accept",
    "bind",
    "close",
    "closedir",
    "dup",
    "dup2",
    "fclose",
    "fcntl",
    "fdopen",
    "fflush",
    "fileno",
    "fopen",
    "fork",
    "fputs",
    "fstat",
    "fsync",
    "ftruncate",
    "fwrite",
    "getenv",
    "gethostname",
    "gmtime_r",
    "isatty",
    "link",
    "linkat",
    "listen",
    "lseek",
    "malloc",
    "mkdir",
    "mkdirat",
    "mkdtemp",
    "mkstemp",
    "mmap",
    "munmap",
    "nanosleep",
    "open",
    "openat",
    "opendir",
    "prctl",
    "read",
    "readdir",
    "rmdir",
    "setenv",
    "setsockopt",
    "shutdown",
    "sigaction",
    "socket",
    "stat",
    "strftime",
    "strtol",
    "system",
    "time",
    "unlink",
    "unlinkat",
    "waitid",
    "write",
    0
  };
  namespace {
    string mk_fn_msg(Function f)
    {
      return enum2str(f, function_str);
    }
  }
  std::ostream &operator<<(std::ostream &o, Function f)
  {
    o << mk_fn_msg(f);
    return o;
  }

  runtime_error::runtime_error(Function f, const string &msg)
    : std::runtime_error(mk_fn_msg(f) + ": " + msg), function_(f)
  {
  }

  int errno_error::code() const
  {
    return errno_;
  }

  errno_error::errno_error(Function f, int e)
    : runtime_error(f, mk_errno_msg(e)), errno_(e)
  {
  }
  Function runtime_error::function() const
  {
    return function_;
  }


}

