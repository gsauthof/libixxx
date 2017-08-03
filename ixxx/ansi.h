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

#ifndef IXXX_ANSI_H
#define IXXX_ANSI_H

#include <string>
#include <array>
#include <stdio.h>
#include <time.h>

namespace ixxx {

  namespace ansi {

    int    fclose(FILE *stream);
    int    fflush(FILE *stream);
    FILE  *fopen (const char *path, const char *mode);
    FILE  *fopen (const std::string &path, const char *mode);
    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    int    fputs(const char *s, FILE *stream);
    int    fputs(const std::string &s, FILE *stream);
    char  *getenv(const char *name);
    char  *getenv(const std::string &name);
    void  *malloc(size_t n);
    size_t strftime(char *s, size_t max, const char *format,
        const struct tm *tm);
    template <size_t U>
    size_t strftime(std::array<char, U> &s, const char *format,
        const struct tm *tm)
    {
      return ixxx::ansi::strftime(s.data(), s.size(), format, tm);
    }
    long   strtol(const char *nptr, char **endptr, int base);
    int    system(const char *command);
    int    system(const std::string &command);
    time_t time  (time_t *t = nullptr);

  }

}

#endif
