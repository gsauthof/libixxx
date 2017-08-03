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

#include "ansi.h"
#include "ixxx.h"

#include <sstream>

using namespace std;

namespace ixxx {

  namespace {
    void throw_errno(Function f)
    {
      int e = errno;
      throw errno_error(f, e);
    }
  }

  namespace ansi {


    int fclose(FILE *stream)
    {
      int r = ::fclose(stream);
      if (r == EOF)
        throw_errno(Function::FCLOSE);
      return r;
    }

    int fflush(FILE *stream)
    {
      int r = ::fflush(stream);
      if (r == EOF)
        throw_errno(Function::FFLUSH);
      return r;
    }

    FILE *fopen(const char *path, const char *mode)
    {
      FILE *f = ::fopen(path, mode);
      if (!f) {
        throw_errno(Function::FOPEN);
      }
      return f;
    }
    FILE *fopen(const std::string &path, const char *mode)
    {
      return ansi::fopen(path.c_str(), mode);
    }

    int fputs(const char *s, FILE *stream)
    {
      int r = ::fputs(s, stream);
      if (r == EOF)
        throw_errno(Function::FPUTS);
      return r;
    }
    int fputs(const std::string &s, FILE *stream)
    {
      return ansi::fputs(s.c_str(), stream);
    }

    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
    {
      size_t r = ::fwrite(ptr, size, nmemb, stream);
      if (r != size*nmemb)
        throw_errno(Function::FWRITE);
      return r;
    }

    char *getenv(const char *name)
    {
      char *r = ::getenv(name);
      if (!r) {
        ostringstream o;
        o << "environment variable " << name << " not defined!";
        throw runtime_error(Function::GETENV, o.str());
      }
      return r;
    }
    char *getenv(const std::string &name)
    {
      return getenv(name.c_str());
    }

    void *malloc(size_t n)
    {
      void *r = ::malloc(n);
      if (!r && n)
        throw_errno(Function::MALLOC);
      return r;
    }

    size_t strftime(char *s, size_t max, const char *format,
        const struct tm *tm)
    {
      size_t r = ::strftime(s, max, format, tm);
      if (!r)
        throw ixxx::runtime_error(Function::STRFTIME,
            "destination buffer too small");
      return r;
    }

    long strtol(const char *nptr, char **endptr, int base)
    {
      errno = 0;
      char *s = 0;
      long r = ::strtol(nptr, &s, base);
      if (errno)
        throw_errno(Function::STRTOL);
      if (s == nptr)
        throw ixxx::runtime_error(Function::STRTOL, "no digits found");
      if (endptr)
        *endptr = s;
      return r;
    }
    int system(const string &command)
    {
      return system(command.c_str());
    }
    int system(const char *command)
    {
      int r = ::system(command);
      if (r == -1)
        throw_errno(Function::SYSTEM);
      if (!command && !r)
        throw runtime_error(Function::SYSTEM, "shell unavailable");
      if (r)
        throw runtime_error(Function::SYSTEM, "child failed");
      return r;
    }

    time_t time(time_t *t)
    {
      time_t r = ::time(t);
      if (r == ((time_t)-1))
        throw_errno(Function::TIME);
      return r;
    }

  }
}
