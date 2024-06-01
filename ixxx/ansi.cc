// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#include "ansi.hh"
#include "sys_error.hh"

#include <errno.h>
#include <stdlib.h>

using namespace std;

namespace ixxx {

  namespace ansi {

    void  *calloc(size_t k, size_t n)
    {
        void *r = ::calloc(k, n);
        if (!r && k && n)
            throw calloc_error(errno);
        return r;
    }

    void fclose(FILE *stream)
    {
      int r = ::fclose(stream);
      if (r == EOF)
        throw fclose_error(errno);
    }

    void fflush(FILE *stream)
    {
      int r = ::fflush(stream);
      if (r == EOF)
        throw fflush_error(errno);
    }

    FILE *fopen(const char *path, const char *mode)
    {
      FILE *f = ::fopen(path, mode);
      if (!f) {
        throw fopen_error(errno);
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
        throw fputs_error(errno);
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
        throw fwrite_error(errno);
      return r;
    }

    char *getenv(const char *name)
    {
      char *r = ::getenv(name);
      if (!r)
        throw getenv_error("environment variable not defined");
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
        throw malloc_error(errno);
      return r;
    }

    void  *realloc(void *p, size_t n)
    {
        void *r = ::realloc(p, n);
        if (!r && n)
            throw realloc_error(errno);
        return r;
    }

    void rename(const char *oldpath, const char *newpath)
    {
        int r = ::rename(oldpath, newpath);
        if (r == -1)
            throw rename_error(errno);
    }
    void rename(const std::string &oldpath, const std::string &newpath)
    {
        ixxx::ansi::rename(oldpath.c_str(), newpath.c_str());
    }

    // NB: gcc 13 and earlier warn under -Wformat-nonliteral,
    //     arguably this is a bug, cf. https://gcc.gnu.org/bugzilla/show_bug.cgi?id=39438
    size_t strftime(char *s, size_t max, const char *format, const struct tm *tm)
    {
      size_t r = ::strftime(s, max, format, tm);
      if (!r)
          throw strftime_error(errno, "destination buffer too small");
      return r;
    }

    long strtol(const char *nptr, char **endptr, int base)
    {
      errno = 0;
      char *s = 0;
      long r = ::strtol(nptr, &s, base);
      if (errno)
        throw strtol_error(errno);
      if (s == nptr)
        throw strtol_error(errno, "no digits found");
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
        throw system_error(errno);
      if (!command && !r)
        throw system_error(errno, "shell unavailable");
      return r;
    }

    time_t time(time_t *t)
    {
      time_t r = ::time(t);
      if (r == ((time_t)-1))
        throw time_error(errno);
      return r;
    }

  }
}
