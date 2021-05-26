// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#include "posix.hh"
#include "sys_error.hh"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#if (defined(__MINGW32__) || defined(__MINGW64__))
    #include <windows.h>
#else
    #include <sys/mman.h>
#endif
#include <signal.h>
#include <pwd.h>

#include "ansi.hh"

using namespace std;

namespace ixxx {

  namespace posix {

    void clock_gettime(clockid_t clk_id, struct timespec *tp)
    {
      int r = ::clock_gettime(clk_id, tp);
      if (r == -1)
        throw clock_gettime_error(errno);
    }

    void close(int fd)
    {
      int r = ::close(fd);
      if (r == -1)
        throw close_error(errno);
    }
    void closedir(DIR *dirp)
    {
      int r = ::closedir(dirp);
      if (r == -1)
        throw closedir_error(errno);
    }
    int dup(int oldfd)
    {
      int r = ::dup(oldfd);
      if (r == -1)
        throw dup_error(errno);
      return r;
    }
    int dup2(int oldfd, int newfd)
    {
      int r = ::dup2(oldfd, newfd);
      if (r == -1)
        throw dup2_error(errno);
      return r;
    }
#if !defined(__MINGW32__) && !defined(__MINGW64__)

    void execv(const char *path, char *const *argv)
    {
        int r = ::execv(path, argv);
        if (r == -1)
            throw execv_error(errno);
    }
    void execvp(const char *file, char *const *argv)
    {
        int r = ::execvp(file, argv);
        if (r == -1)
            throw execvp_error(errno);
    }
    void execvp(const std::string &file, char *const *argv)
    {
        execvp(file.c_str(), argv);
    }
#ifdef _GNU_SOURCE
    void execvpe(const char *file, char *const *argv,
            char *const *envp)
    {
        int r = ::execvpe(file, argv, envp);
        if (r == -1)
            throw execvpe_error(errno);
    }
#endif

    int fcntl(int fd, int cmd, int arg1)
    {
      int r = ::fcntl(fd, cmd, arg1);
      if (r == -1)
        throw fcntl_error(errno);
      return r;
    }
#endif

    int fileno(FILE *stream)
    {
      int r = ::fileno(stream);
      if (r == -1)
        throw fileno_error(errno);
      return r;
    }

    FILE *fdopen(int fd, const char *mode)
    {
      FILE *r = ::fdopen(fd, mode);
      if (!r)
        throw fdopen_error(errno);
      return r;
    }

#if !defined(__MINGW32__) && !defined(__MINGW64__)
    pid_t fork()
    {
      pid_t r = ::fork();
      if (r == -1)
        throw fork_error(errno);
      return r;
    }
#endif

    void fstat(int fd, struct stat *buf)
    {
      int r = ::fstat(fd, buf);
      if (r == -1)
        throw fstat_error(errno);
    }
    void fstat(int fd, struct stat &buf)
    {
      ixxx::posix::fstat(fd, &buf);
    }
    void fstatat(int dirfd, const char *pathname, struct stat *statbuf, int flags)
    {
        int r = ::fstatat(dirfd, pathname, statbuf, flags);
        if (r == -1)
            throw fstat_error(errno);
    }
    void fstatat(int dirfd, const std::string &pathname, struct stat *statbuf, int flags)
    {
        ixxx::posix::fstatat(dirfd, pathname.c_str(), statbuf, flags);
    }
    void fsync(int fd)
    {
#if (defined(__MINGW32__) || defined(__MINGW64__))
        HANDLE h = reinterpret_cast<HANDLE>(_get_osfhandle(fd));
        if (h == INVALID_HANDLE_VALUE)
            throw fsync_error("invalid handle - _get_osfhandle()");
        auto r = FlushFileBuffers(h);
        if (!r)
            throw fsync_error("FlushFileBuffers failed");
#else
      int r = ::fsync(fd);
      if (r == -1)
        throw fsync_error(errno);
#endif
    }
    void ftruncate(int fd, off_t length)
    {
      int r = ::ftruncate(fd, length);
      if (r == -1)
        throw ftruncate_error(errno);
    }

#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void gethostname(char *name, size_t len)
    {
      int r = ::gethostname(name, len);
      if (r == -1)
        throw gethostname_error(errno);
    }
#endif

#if _POSIX_C_SOURCE >= 200809L
    ssize_t getline(char **line, size_t *n, FILE *f)
    {
        errno = 0;
        ssize_t r = ::getline(line, n, f);
        if (r == -1 && errno)
            throw getline_error(errno);
        return r;
    }
#endif
    void getpwnam_r(const char *name, struct passwd *pwd,
            char *buf, size_t buflen, struct passwd **result)
    {
        int r = ::getpwnam_r(name, pwd, buf, buflen, result);
        if (r)
            throw getpwnam_r_error(r);
    }
    void getpwuid_r(uid_t uid, struct passwd *pwd,
            char *buf, size_t buflen, struct passwd **result)
    {
        int r = ::getpwuid_r(uid, pwd, buf, buflen, result);
        if (r)
            throw getpwuid_r_error(r);
    }

    struct tm *gmtime_r(const time_t *timep, struct tm *result)
    {
      struct tm *r = ::gmtime_r(timep, result);
      if (!r)
        throw gmtime_r_error(errno, "Year doesn't fit into integer");
      return r;
    }
    int isatty(int fd)
    {
      int r = ::isatty(fd);
      if (r == -1)
        throw isatty_error(errno);
      return r;
    }

#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void link(const char *oldpath, const char *newpath)
    {
      int r = ::link(oldpath, newpath);
      if (r == -1)
        throw link_error(errno);
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
    void linkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags)
    {
      int r = ::linkat(olddirfd, oldpath, newdirfd, newpath, flags);
      if (r == -1)
        throw linkat_error(errno);
    }
    void linkat(int olddirfd, const std::string &oldpath, int newdirfd, const std::string &newpath, int flags)
    {
      linkat(olddirfd, oldpath.c_str(), newdirfd, newpath.c_str(), flags);
    }
#endif

    void localtime_r(const time_t *timep, struct tm *result)
    {
        struct tm *r = ::localtime_r(timep, result);
        if (!r)
            throw localtime_r_error(errno);
    }

    off_t lseek(int fd, off_t offset, int whence)
    {
      off_t r = ::lseek(fd, offset, whence);
      if (r == -1)
        throw lseek_error(errno);
      return r;
    }
#if !defined(__MINGW32__) && !defined(__MINGW64__)
    void lstat(const char *pathname, struct stat *buf)
    {
        int r = ::lstat(pathname, buf);
        if (r == -1)
            throw lstat_error(errno);
    }
    void lstat(const std::string &pathname, struct stat *buf)
    {
        ixxx::posix::lstat(pathname.c_str(), buf);
    }
#endif

    void mkdir(const char *pathname, mode_t mode)
    {
#if (defined(__MINGW32__) || defined(__MINGW64__))
      int r = ::mkdir(pathname);
#else
      int r = ::mkdir(pathname, mode);
#endif
      if (r == -1)
        throw mkdir_error(errno);
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
        throw mkdirat_error(errno);
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
        throw mkdtemp_error(errno);
      return r;
    }
#endif

    int mkstemp(char *tmplate)
    {
      int r = ::mkstemp(tmplate);
      if (r == -1)
        throw mkstemp_error(errno);
      return r;
    }

#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
    {
      void *r = ::mmap(addr, length, prot, flags, fd, offset);
      if (r == MAP_FAILED)
        throw mmap_error(errno);
      return r;
    }
    void msync(void *addr, size_t length, int flags)
    {
        int r = ::msync(addr, length, flags);
        if (r == -1)
            throw msync_error(errno);
    }
    void munmap(void *addr, size_t length)
    {
      int r = ::munmap(addr, length);
      if (r == -1)
        throw munmap_error(errno);
    }
#endif
    void nanosleep(const struct timespec *req, struct timespec *rem)
    {
      int r = ::nanosleep(req, rem);
      if (r == -1)
        throw nanosleep_error(errno);
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
        throw open_error(errno);
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
        throw open_error(errno);
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
        throw openat_error(errno);
      return r;
    }
    int openat(int dirfd, const char *pathname, int flags, mode_t mode)
    {
      int r = ::openat(dirfd, pathname, flags, mode);
      if (r == -1)
        throw openat_error(errno);
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

    DIR *opendir(const char *name)
    {
      DIR *r = ::opendir(name);
      if (!r)
        throw opendir_error(errno);
      return r;
    }
    DIR *opendir(const std::string &name)
    {
      return opendir(name.c_str());
    }

    void pipe(int pipefd[2])
    {
#if defined(__MINGW32__) || defined(__MINGW64__)
        int r = ::_pipe(pipefd, 4*1024, _O_BINARY);
#else
        int r = ::pipe(pipefd);
#endif
        if (r == -1)
            throw pipe_error(errno);
    }

    int poll(struct pollfd *fds, nfds_t nfds, int timeout)
    {
        int r = ::poll(fds, nfds, timeout);
        if (r == -1)
            throw poll_error(errno);
        return r;
    }

    ssize_t pread(int fd, void *buf, size_t count, off_t offset)
    {
        ssize_t r = ::pread(fd, buf, count, offset);
        if (r == -1)
            throw pread_error(errno);
        return r;
    }
    ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset)
    {
        ssize_t r = ::pwrite(fd, buf, count, offset);
        if (r == -1)
            throw pwrite_error(errno);
        return r;
    }

#if (defined(__APPLE__) && defined(__MACH__))
#else
    void posix_fallocate(int fd, off_t offset, off_t len)
    {
        int r = ::posix_fallocate(fd, offset, len);
        if (r)
            throw posix_fallocate_error(r);
    }
#endif

    ssize_t read(int fd, void *buf, size_t count)
    {
      int r = ::read(fd, buf, count);
      if (r == -1)
        throw read_error(errno);
      return r;
    }
    struct dirent *readdir(DIR *dirp)
    {
      errno = 0;
      struct dirent *r = ::readdir(dirp);
      if (errno)
        throw readdir_error(errno);
      return r;
    }

#if !defined(__MINGW32__) && !defined(__MINGW64__)
    size_t readlink(const char *pathname, char *buf, size_t n)
    {
        ssize_t r = ::readlink(pathname, buf, n);
        if (r == -1)
            throw readlink_error(errno);
        return r;
    }
#endif

#if _POSIX_C_SOURCE >= 200809L
    size_t readlinkat(int dirfd, const char *pathname, char *buf, size_t n)
    {
        ssize_t r = ::readlinkat(dirfd, pathname, buf, n);
        if (r == -1)
            throw readlinkat_error(errno);
        return r;
    }
#endif

    void renameat(int olddirfd, const char *oldpath,
            int newdirfd, const char *newpath)
    {
        int r = ::renameat(olddirfd, oldpath, newdirfd, newpath);
        if (r == -1)
            throw renameat_error(errno);
    }
    void renameat(int olddirfd, const std::string &oldpath,
            int newdirfd, const std::string &newpath)
    {
        ixxx::posix::renameat(olddirfd, oldpath.c_str(),
                newdirfd, newpath.c_str());
    }

    void rmdir(const char *pathname)
    {
      int r = ::rmdir(pathname);
      if (r == -1)
        throw rmdir_error(errno);
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
        throw setenv_error(errno);
    }
    void setenv(const std::string &name, const std::string &value, bool overwrite)
    {
      setenv(name.c_str(), value.c_str(), overwrite);
    }
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
    {
      int r = ::sigaction(signum, act, oldact);
      if (r == -1)
        throw sigaction_error(errno);
    }
    void sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
    {
        int r = ::sigprocmask(how, set, oldset);
        if (r == -1)
            throw sigprocmask_error(errno);
    }

    void spawn(pid_t *pid, const char *path,
            const posix_spawn_file_actions_t *file_actions,
            const posix_spawnattr_t *attrp,
            char *const *argv, char *const *envp)
    {
        int r = ::posix_spawn(pid, path, file_actions,
                attrp,
                argv, envp);
        if (r)
            throw spawn_error(r);
    }
    void spawnp(pid_t *pid, const char *file,
            const posix_spawn_file_actions_t *file_actions,
            const posix_spawnattr_t *attrp,
            char *const *argv, char *const *envp)
    {
        int r = ::posix_spawnp(pid, file, file_actions,
                attrp,
                argv, envp);
        if (r)
            throw spawnp_error(r);
    }
    void spawn_file_actions_init(posix_spawn_file_actions_t *as)
    {
        int r = ::posix_spawn_file_actions_init(as);
        if (r)
            throw spawn_file_actions_init_error(r);
    }
    void spawn_file_actions_destroy(posix_spawn_file_actions_t *as)
    {
        int r = ::posix_spawn_file_actions_destroy(as);
        if (r)
            throw spawn_file_actions_destroy_error(r);
    }
    void spawn_file_actions_addopen(posix_spawn_file_actions_t *as,
            int fd, const char *path, int flags, mode_t mode)
    {
        int r = ::posix_spawn_file_actions_addopen(as, fd, path, flags, mode);
        if (r)
            throw spawn_file_actions_addopen_error(r);
    }
    void spawn_file_actions_addclose(posix_spawn_file_actions_t *as, int fd)
    {
        int r = ::posix_spawn_file_actions_addclose(as, fd);
        if (r)
            throw spawn_file_actions_addclose_error(r);
    }
    void spawn_file_actions_adddup2(posix_spawn_file_actions_t *as,
            int oldfd, int newfd)
    {
        int r = ::posix_spawn_file_actions_adddup2(as, oldfd, newfd);
        if (r)
            throw spawn_file_actions_adddup2_error(r);
    }

#endif

    void stat(const char *pathname, struct stat *buf)
    {
      int r = ::stat(pathname, buf);
      if (r == -1)
        throw stat_error(errno);
    }
    void stat(const std::string &pathname, struct stat *buf)
    {
      ixxx::posix::stat(pathname.c_str(), buf);
    }

    long sysconf(int name)
    {
        errno = 0;
        long r = ::sysconf(name);
        if (r == -1)
            throw stat_error(errno);
        return r;
    }

    void truncate(const char *path, off_t length)
    {
        int r = ::truncate(path, length);
        if (r == -1)
            throw truncate_error(errno);
    }
    void truncate(const std::string &path, off_t length)
    {
        ixxx::posix::truncate(path.c_str(), length);
    }

    void unlink(const char *pathname)
    {
      int r = ::unlink(pathname);
      if (r == -1)
        throw unlink_error(errno);
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
        throw unlinkat_error(errno);
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
        throw waitid_error(errno);
    }
#endif
    ssize_t write(int fd, const void *buf, size_t count)
    {
      int r = ::write(fd, buf, count);
      if (r == -1)
        throw write_error(errno);
      return r;
    }


  }

}
