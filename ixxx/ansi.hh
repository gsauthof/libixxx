// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#ifndef IXXX_ANSI_H
#define IXXX_ANSI_H

#include <string>
#include <array>
#include <stdio.h>
#include <time.h>

namespace ixxx {

  namespace ansi {

    void  *calloc(size_t k, size_t n);
    void   fclose(FILE *stream);
    void   fflush(FILE *stream);
    FILE  *fopen (const char *path, const char *mode);
    FILE  *fopen (const std::string &path, const char *mode);
    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    int    fputs(const char *s, FILE *stream);
    int    fputs(const std::string &s, FILE *stream);
    char  *getenv(const char *name);
    char  *getenv(const std::string &name);
    void  *malloc(size_t n);
    void  *realloc(void *p, size_t n);
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
