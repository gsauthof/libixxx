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
#ifndef IXXX_POSIX_H
#define IXXX_POSIX_H

#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#if !defined(__MINGW32__) && !defined(__MINGW64__)
  #include <sys/wait.h>
#endif
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

namespace ixxx {
  namespace posix {

    int close(int fd);
    int dup(int oldfd);
    int dup2(int oldfd, int newfd);
    int fcntl(int fd, int cmd, int arg1);
    FILE *fdopen(int fd, const char *mode);
    int fileno(FILE *stream);
#if !defined(__MINGW32__) && !defined(__MINGW64__)
    pid_t fork();
#endif
    int fstat(int fd, struct stat *buf);
    int fstat(int fd, struct stat &buf);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    int fsync(int fd);
#endif
    int ftruncate(int fd, off_t length);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    int gethostname(char *name, size_t len);
#endif
    struct tm *gmtime_r(const time_t *timep, struct tm *result);
    int isatty(int fd);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    int link(const char *oldpath, const char *newpath);
    int link(const std::string &oldpath, const std::string &newpath);
#endif
    // Solaris 10 and Mac OS X don't not have linkat()
#if defined(__sun) || (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    int linkat(int olddirfd, const char *oldpath, int newdirfd,
        const char *newpath, int flags);
    int linkat(int olddirfd, const std::string &oldpath, int newdirfd,
        const std::string &newpath, int flags);
#endif
    off_t lseek(int fd, off_t offset, int whence);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    char *mkdtemp(char *template_string);
#endif
    int mkstemp(char *tmplate);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void *mmap(void *addr, size_t length, int prot, int flags,
        int fd, off_t offset);
    int munmap(void *addr, size_t length);
#endif
    int nanosleep(const struct timespec *req, struct timespec *rem);
    int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);
    int open(const std::string &pathname, int flags);
    int open(const std::string &pathname, int flags, mode_t mode);
    // Mac OS X doesn't have openat
#if (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    int openat(int dirfd, const char *pathname, int flags);
    int openat(int dirfd, const char *pathname, int flags, mode_t mode);
    int openat(int dirfd, const std::string &pathname, int flags);
    int openat(int dirfd, const std::string &pathname, int flags, mode_t mode);
#endif
    ssize_t read(int fd, void *buf, size_t count);
    void   setenv(const char *name, const char *value, bool overwrite);
    void   setenv(const std::string &name, const std::string &value,
        bool overwrite);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    int sigaction(int signum, const struct sigaction *act,
                                    struct sigaction *oldact);
#endif
    int stat(const char *pathname, struct stat *buf);
    int stat(const std::string &pathname, struct stat *buf);
    int unlink(const char *pathname);
    int unlink(const std::string &pathname);
#if (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    int unlinkat(int dirfd, const char *pathname, int flags);
    int unlinkat(int dirfd, const std::string &pathname, int flags);
#endif
#if !defined(__MINGW32__) && !defined(__MINGW64__)
    int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
#endif
    ssize_t write(int fd, const void *buf, size_t count);
  }
}

#endif
