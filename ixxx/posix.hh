// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#ifndef IXXX_POSIX_H
#define IXXX_POSIX_H

#include <array>
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#if !defined(__MINGW32__) && !defined(__MINGW64__)
    #include <sys/wait.h>
    #include <spawn.h>
#endif
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

namespace ixxx {
  namespace posix {

    void close(int fd);
    void closedir(DIR *dirp);
    int dup(int oldfd);
    int dup2(int oldfd, int newfd);
#if !defined(__MINGW32__) && !defined(__MINGW64__)

    void execv(const char *path, char *const *argv);
    void execvp(const char *file, char *const *argv);
    void execvp(const std::string &file, char *const *argv);
#ifdef _GNU_SOURCE
    void execvpe(const char *file, char *const *argv,
            char *const *envp);
#endif

    int fcntl(int fd, int cmd, int arg1);
#endif
    FILE *fdopen(int fd, const char *mode);
    int fileno(FILE *stream);
#if !defined(__MINGW32__) && !defined(__MINGW64__)
    pid_t fork();
#endif
    void fstat(int fd, struct stat *buf);
    void fstat(int fd, struct stat &buf);
    void fsync(int fd);
    void ftruncate(int fd, off_t length);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void gethostname(char *name, size_t len);
#endif

#if _POSIX_C_SOURCE >= 200809L
    ssize_t getline(char **line, size_t *n, FILE *f);
#endif

    struct tm *gmtime_r(const time_t *timep, struct tm *result);
    int isatty(int fd);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void link(const char *oldpath, const char *newpath);
    void link(const std::string &oldpath, const std::string &newpath);
#endif
    // Solaris 10 and Mac OS X don't have linkat()
#if defined(__sun) || (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void linkat(int olddirfd, const char *oldpath, int newdirfd,
        const char *newpath, int flags);
    void linkat(int olddirfd, const std::string &oldpath, int newdirfd,
        const std::string &newpath, int flags);
#endif
    off_t lseek(int fd, off_t offset, int whence);
#if !defined(__MINGW32__) && !defined(__MINGW64__)
    void lstat(const char *pathname, struct stat *buf);
    void lstat(const std::string &pathname, struct stat *buf);
#endif
    void mkdir(const char *pathname, mode_t mode);
    void mkdir(const std::string &pathname, mode_t mode);
#if defined(__sun) || (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void mkdirat(int dirfd, const char *pathname, mode_t mode);
    void mkdirat(int dirfd, const std::string &pathname, mode_t mode);
#endif
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    char *mkdtemp(char *template_string);
#endif
    int mkstemp(char *tmplate);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void *mmap(void *addr, size_t length, int prot, int flags,
        int fd, off_t offset);
    void msync(void *addr, size_t length, int flags);
    void munmap(void *addr, size_t length);
#endif
    void nanosleep(const struct timespec *req, struct timespec *rem);
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
    DIR *opendir(const char *name);
    DIR *opendir(const std::string &name);

    void pipe(int pipefd[2]);

    ssize_t read(int fd, void *buf, size_t count);
    struct dirent *readdir(DIR *dirp);
    ssize_t readlink(const char *pathname, char *buf, size_t n);
    ssize_t readlink(const char *pathname, std::array<char, 4096> &buf);
    ssize_t readlink(const std::string &pathname, std::array<char, 4096> &buf);
#if _POSIX_C_SOURCE >= 200809L
    ssize_t readlinkat(int dirfd, const char *pathname, char *buf, size_t n);
    ssize_t readlinkat(int dirfd, const char *pathname, std::array<char, 4096> &buf);
    ssize_t readlinkat(int dirfd, const std::string &pathname,
            std::array<char, 4096> &buf);
#endif
    void rmdir(const char *pathname);
    void rmdir(const std::string &pathname);
    void setenv(const char *name, const char *value, bool overwrite);
    void setenv(const std::string &name, const std::string &value,
        bool overwrite);
#if (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void sigaction(int signum, const struct sigaction *act,
                                    struct sigaction *oldact);

    void spawn(pid_t *pid, const char *path,
            const posix_spawn_file_actions_t *file_actions,
            const posix_spawnattr_t *attrp,
            char *const *argv, char *const *envp);
    void spawnp(pid_t *pid, const char *file,
            const posix_spawn_file_actions_t *file_actions,
            const posix_spawnattr_t *attrp,
            char *const *argv, char *const *envp);
    void spawn_file_actions_init(posix_spawn_file_actions_t *as);
    void spawn_file_actions_destroy(posix_spawn_file_actions_t *as);
    void spawn_file_actions_addopen(posix_spawn_file_actions_t *as,
            int fd, const char *path, int flags, mode_t mode);
    void spawn_file_actions_addclose(posix_spawn_file_actions_t *as, int fd);
    void spawn_file_actions_adddup2(posix_spawn_file_actions_t *as,
            int oldfd, int newfd);
#endif

    void stat(const char *pathname, struct stat *buf);
    void stat(const std::string &pathname, struct stat *buf);
    void unlink(const char *pathname);
    void unlink(const std::string &pathname);
#if (defined(__APPLE__) && defined(__MACH__))
#elif (defined(__MINGW32__) || defined(__MINGW64__))
#else
    void unlinkat(int dirfd, const char *pathname, int flags);
    void unlinkat(int dirfd, const std::string &pathname, int flags);
#endif
#if !defined(__MINGW32__) && !defined(__MINGW64__)
    void waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
#endif
    ssize_t write(int fd, const void *buf, size_t count);
  }
}

#endif
