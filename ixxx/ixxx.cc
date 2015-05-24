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

#include "ixxx.h"

#include <stdexcept>
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
    int r = ::strerror_r(errno_, buffer.data(), buffer.size());
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
    "close",
    "dup",
    "fclose",
    "fdopen",
    "fflush",
    "fileno",
    "fopen",
    "fork",
    "fsync",
    "ftruncate",
    "fwrite",
    "getenv",
    "gethostname",
    "isatty",
    "link",
    "linkat",
    "nanosleep",
    "open",
    "openat",
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

