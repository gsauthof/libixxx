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
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#if !defined(__MINGW32__) && !defined(__MINGW64__)
  #include <sys/mman.h>
#endif
#include <signal.h>

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

    void close(int fd)
    {
      int r = ::close(fd);
      if (r == -1)
        throw_errno(Function::CLOSE);
    }
    int dup(int oldfd)
    {
      int r = ::dup(oldfd);
      if (r == -1)
        throw_errno(Function::DUP);
      return r;
    }
    int dup2(int oldfd, int newfd)
    {
      int r = ::dup2(oldfd, newfd);
      if (r == -1)
        throw_errno(Function::DUP2);
      return r;
    }
    int fcntl(int fd, int cmd, int arg1)
    {
      int r = ::fcntl(fd, cmd, arg1);
      if (r == -1)
        throw_errno(Function::FCNTL);
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

#if !defined(__MINGW32__) && !defined(__MINGW64__)
    pid_t fork()
    {
      pid_t r = ::fork();
      if (r == -1)
        throw_errno(Function::FORK);
      return r;
    }
#endif

    void fstat(int fd, struct stat *buf)
    {
      int r = ::fstat(fd, buf);
      if (r == -1)
        throw_errno(Function::FSTAT);
    }
    void fstat(int fd, struct stat &buf)
    {
      ixxx::posix::fstat(fd, &buf);
    }
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void fsync(int fd)
    {
      int r = ::fsync(fd);
      if (r == -1)
        throw_errno(Function::FSYNC);
    }
#endif
    void ftruncate(int fd, off_t length)
    {
      int r = ::ftruncate(fd, length);
      if (r == -1)
        throw_errno(Function::FTRUNCATE);
    }

#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void gethostname(char *name, size_t len)
    {
      int r = ::gethostname(name, len);
      if (r == -1)
        throw_errno(Function::GETHOSTNAME);
    }
#endif

    struct tm *gmtime_r(const time_t *timep, struct tm *result)
    {
      struct tm *r = ::gmtime_r(timep, result);
      if (!r)
        throw ixxx::runtime_error(Function::GMTIME_R,
            "Year doesn't fit into integer");
      return r;
    }
    int isatty(int fd)
    {
      int r = ::isatty(fd);
      if (r == -1)
        throw_errno(Function::ISATTY);
      return r;
    }

#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void link(const char *oldpath, const char *newpath)
    {
      int r = ::link(oldpath, newpath);
      if (r == -1)
        throw_errno(Function::LINK);
    }
    void link(const std::string &oldpath, const std::string &newpath)
    {
      link(oldpath.c_str(), newpath.c_str());
    }
#endif
    // Solaris 10 does not have linkat()
#if defined(__sun) || (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void linkat(int olddirfd, const char *oldpath,
        int newdirfd, const char *newpath, int flags)
    {
      int r = ::linkat(olddirfd, oldpath, newdirfd, newpath, flags);
      if (r == -1)
        throw_errno(Function::LINKAT);
    }
    void linkat(int olddirfd, const std::string &oldpath,
        int newdirfd, const std::string &newpath, int flags)
    {
      linkat(olddirfd, oldpath.c_str(), newdirfd, newpath.c_str(), flags);
    }
#endif

    off_t lseek(int fd, off_t offset, int whence)
    {
      off_t r = ::lseek(fd, offset, whence);
      if (r == -1)
        throw_errno(Function::LSEEK);
      return r;
    }
    void mkdir(const char *pathname, mode_t mode)
    {
      int r = ::mkdir(pathname, mode);
      if (r == -1)
        throw_errno(Function::MKDIR);
    }
    void mkdir(const std::string &pathname, mode_t mode)
    {
      mkdir(pathname.c_str(), mode);
    }
#if defined(__sun) || (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void mkdirat(int dirfd, const char *pathname, mode_t mode)
    {
      int r = ::mkdirat(dirfd, pathname, mode);
      if (r == -1)
        throw_errno(Function::MKDIRAT);
    }
    void mkdirat(int dirfd, const std::string &pathname, mode_t mode)
    {
      mkdirat(dirfd, pathname.c_str(), mode);
    }
#endif

#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    char *mkdtemp(char *template_string)
    {
      char *r = ::mkdtemp(template_string);
      if (!r)
        throw_errno(Function::MKDTEMP);
      return r;
    }
#endif

    void mkstemp(char *tmplate)
    {
      int r = ::mkstemp(tmplate);
      if (r == -1)
        throw_errno(Function::MKSTEMP);
    }

#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void *mmap(void *addr, size_t length, int prot, int flags,
        int fd, off_t offset)
    {
      void *r = ::mmap(addr, length, prot, flags, fd, offset);
      if (r == MAP_FAILED)
        throw_errno(Function::MMAP);
      return r;
    }
    void munmap(void *addr, size_t length)
    {
      int r = ::munmap(addr, length);
      if (r == -1)
        throw_errno(Function::MUNMAP);
    }
#endif
    void nanosleep(const struct timespec *req, struct timespec *rem)
    {
      int r = ::nanosleep(req, rem);
      if (r == -1)
        throw_errno(Function::NANOSLEEP);
    }

    int open(const char *pathname, int flags)
    {
      int r = ::open(pathname, flags
#if (defined(__MINGW32__) || defined(__MINGW64__))
          // without that, windows opens it in 'text mode',
          // i.e. it converts \n to \r\n on write()s ...
          // (similar to fopen() without the "b")
          | _O_BINARY
#endif
          );
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
      int r = ::open(pathname, flags
#if (defined(__MINGW32__) || defined(__MINGW64__))
          | _O_BINARY
#endif
          , mode);
      if (r == -1)
        throw_errno(Function::OPEN);
      return r;
    }
    int open(const string &pathname, int flags, mode_t mode)
    {
      return posix::open(pathname.c_str(), flags, mode);
    }
#if (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
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
      return openat(dirfd, pathname.c_str(), flags);
    }
    int openat(int dirfd, const std::string &pathname, int flags, mode_t mode)
    {
      return openat(dirfd, pathname.c_str(), flags, mode);
    }
#endif

    ssize_t read(int fd, void *buf, size_t count)
    {
      int r = ::read(fd, buf, count);
      if (r == -1)
        throw_errno(Function::READ);
      return r;
    }

    void rmdir(const char *pathname)
    {
      int r = ::rmdir(pathname);
      if (r == -1)
        throw_errno(Function::RMDIR);
    }
    void rmdir(const std::string &pathname)
    {
      rmdir(pathname.c_str());
    }

    void setenv(const char *name, const char *value, bool overwrite)
    {
#if (defined(__MINGW32__) || defined(__MINGW64__))
      if (!overwrite && ::getenv(name))
        return;
      size_t a = strlen(name);
      size_t b = strlen(value);
      size_t n = a  + 1 +  b + 1;
      char *s = static_cast<char*>(ixxx::ansi::malloc(n));
      mempcpy(mempcpy(mempcpy(s, name, a), "=", 1), value, b);
      s[n-1] = 0;
      int r = ::putenv(s);
#else
      int r = ::setenv(name, value, overwrite);
#endif
      if (r == -1)
        throw_errno(Function::SETENV);
    }
    void setenv(const std::string &name, const std::string &value,
        bool overwrite)
    {
      setenv(name.c_str(), value.c_str(), overwrite);
    }
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void sigaction(int signum, const struct sigaction *act,
                                    struct sigaction *oldact)
    {
      int r = ::sigaction(signum, act, oldact);
      if (r == -1)
        throw_errno(Function::SIGACTION);
    }
#endif
    void stat(const char *pathname, struct stat *buf)
    {
      int r = ::stat(pathname, buf);
      if (r == -1)
        throw_errno(Function::STAT);
    }
    void stat(const std::string &pathname, struct stat *buf)
    {
      ixxx::posix::stat(pathname.c_str(), buf);
    }

    void unlink(const char *pathname)
    {
      int r = ::unlink(pathname);
      if (r == -1)
        throw_errno(Function::UNLINK);
    }
    void unlink(const std::string &pathname)
    {
      unlink(pathname.c_str());
    }
#if (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void unlinkat(int dirfd, const char *pathname, int flags)
    {
      int r = ::unlinkat(dirfd, pathname, flags);
      if (r == -1)
        throw_errno(Function::UNLINKAT);
    }
    void unlinkat(int dirfd, const std::string &pathname, int flags)
    {
      unlinkat(dirfd, pathname.c_str(), flags);
    }
#endif


#if !defined(__MINGW32__) && !defined(__MINGW64__)
    void waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options)
    {
      int r = ::waitid(idtype, id, infop, options);
      if (r == -1)
        throw_errno(Function::WAITID);
    }
#endif
    ssize_t write(int fd, const void *buf, size_t count)
    {
      int r = ::write(fd, buf, count);
      if (r == -1)
        throw_errno(Function::WRITE);
      return r;
    }


  }

}
