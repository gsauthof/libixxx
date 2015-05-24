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

#include "posix.h"
#include "ixxx.h"

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

namespace ixxx {

  namespace {
    void throw_errno(Function f)
    {
      int e = errno;
      throw errno_error(f, e);
    }
  }

  namespace posix {

    int dup(int oldfd)
    {
      int r = ::dup(oldfd);
      if (r == -1)
        throw_errno(Function::DUP);
      return r;
    }

    int fileno(FILE *stream)
    {
      int r = ::fileno(stream);
      if (r == -1)
        throw_errno(Function::FILENO);
      return r;
    }

    FILE *fdopen(int fd, const char *mode)
    {
      FILE *r = ::fdopen(fd, mode);
      if (!r)
        throw_errno(Function::FDOPEN);
      return r;
    }

    pid_t fork()
    {
      pid_t r = ::fork();
      if (r == -1)
        throw_errno(Function::FORK);
      return r;
    }

    int open(const char *pathname, int flags)
    {
      int r = ::open(pathname, flags);
      if (r == -1)
        throw_errno(Function::OPEN);
      return r;
    }
    int open(const string &pathname, int flags)
    {
      return posix::open(pathname.c_str(), flags);
    }
    int open(const char *pathname, int flags, mode_t mode)
    {
      int r = ::open(pathname, flags, mode);
      if (r == -1)
        throw_errno(Function::OPEN);
      return r;
    }
    int open(const string &pathname, int flags, mode_t mode)
    {
      return posix::open(pathname.c_str(), flags, mode);
    }
    int openat(int dirfd, const char *pathname, int flags)
    {
      int r = ::openat(dirfd, pathname, flags);
      if (r == -1)
        throw_errno(Function::OPENAT);
      return r;
    }
    int openat(int dirfd, const char *pathname, int flags, mode_t mode)
    {
      int r = ::openat(dirfd, pathname, flags, mode);
      if (r == -1)
        throw_errno(Function::OPENAT);
      return r;
    }
    int openat(int dirfd, const std::string &pathname, int flags)
    {
      return openat(dirfd, pathname, flags);
    }
    int openat(int dirfd, const std::string &pathname, int flags, mode_t mode)
    {
      return openat(dirfd, pathname, flags, mode);
    }
    int close(int fd)
    {
      int r = ::close(fd);
      if (r == -1)
        throw_errno(Function::CLOSE);
      return r;
    }
    int fsync(int fd)
    {
      int r = ::fsync(fd);
      if (r == -1)
        throw_errno(Function::FSYNC);
      return r;
    }
    int ftruncate(int fd, off_t length)
    {
      int r = ::ftruncate(fd, length);
      if (r == -1)
        throw_errno(Function::FTRUNCATE);
      return r;
    }
    int gethostname(char *name, size_t len)
    {
      int r = ::gethostname(name, len);
      if (r == -1)
        throw_errno(Function::GETHOSTNAME);
      return r;
    }
    int link(const char *oldpath, const char *newpath)
    {
      int r = ::link(oldpath, newpath);
      if (r == -1)
        throw_errno(Function::LINK);
      return r;
    }
    int link(const std::string &oldpath, const std::string &newpath)
    {
      return link(oldpath.c_str(), newpath.c_str());
    }
    // Solaris 10 does not have linkat()
#if defined(__sun)
#else
    int linkat(int olddirfd, const char *oldpath,
        int newdirfd, const char *newpath, int flags)
    {
      int r = ::linkat(olddirfd, oldpath, newdirfd, newpath, flags);
      if (r == -1)
        throw_errno(Function::LINKAT);
      return r;
    }
    int linkat(int olddirfd, const std::string &oldpath,
        int newdirfd, const std::string &newpath, int flags)
    {
      return linkat(olddirfd, oldpath.c_str(), newdirfd, newpath.c_str(), flags);
    }
#endif
    int unlink(const char *pathname)
    {
      int r = ::unlink(pathname);
      if (r == -1)
        throw_errno(Function::UNLINK);
      return r;
    }
    int unlink(const std::string &pathname)
    {
      return unlink(pathname.c_str());
    }
    int unlinkat(int dirfd, const char *pathname, int flags)
    {
      int r = ::unlinkat(dirfd, pathname, flags);
      if (r == -1)
        throw_errno(Function::UNLINKAT);
      return r;
    }
    int unlinkat(int dirfd, const std::string &pathname, int flags)
    {
      return unlinkat(dirfd, pathname.c_str(), flags);
    }

    int isatty(int fd)
    {
      int r = ::isatty(fd);
      if (r == -1)
        throw_errno(Function::ISATTY);
      return r;
    }

    int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options)
    {
      int r = ::waitid(idtype, id, infop, options);
      if (r == -1)
        throw_errno(Function::WAITID);
      return r;
    }
    ssize_t write(int fd, const void *buf, size_t count)
    {
      int r = ::write(fd, buf, count);
      if (r == -1)
        throw_errno(Function::WRITE);
      return r;
    }
    int nanosleep(const struct timespec *req, struct timespec *rem)
    {
      int r = ::nanosleep(req, rem);
      if (r == -1)
        throw_errno(Function::NANOSLEEP);
      return r;
    }

  }

}
