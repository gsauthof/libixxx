// Copyright (c) 2018, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#ifndef IXXX_SYS_ERROR_HH
#define IXXX_SYS_ERROR_HH

#include <exception>
#include <memory>
#include <string>

namespace ixxx {

    enum class Function : int;


    // optimized for catcher doesn't need to call what() (good case),
    // i.e. the what() message is computed lazily
    class sys_error : public std::exception
    {
        public:
            enum Code_Type { ERRNO, GAI };
            sys_error(int code, const char *literal = nullptr, Code_Type type = ERRNO);
            sys_error(const char *literal = nullptr);
            sys_error(const sys_error &o);
            sys_error &operator=(const sys_error &o);
            const char *what() const noexcept override;
            int code() const;
            const char* literal() const;

            virtual Function function() const = 0;
            virtual const char* name() const = 0;
        private:
            int errno_;
            unsigned type_;
            const char *literal_;
            mutable std::unique_ptr<std::string> what_;
    };

    // Mac OS X pollutes the global namespace with a FWRITE
    // macro ... undeffing it such that we can use it
    // as enum value ...
#ifdef FWRITE
#undef FWRITE
#endif


    // Autogenerated by mk_boilerplate.py - begin
    enum class Function {
        ACCEPT,
        BIND,
        CALLOC,
        CLOCK_GETTIME,
        CLOSE,
        CLOSEDIR,
        CONNECT,
        DUP,
        DUP2,
        EPOLL_CREATE1,
        EPOLL_CTL,
        EPOLL_WAIT,
        EXECV,
        EXECVP,
        EXECVPE,
        EVENTFD,
        FCLOSE,
        FCNTL,
        FDOPEN,
        FFLUSH,
        FILENO,
        FOPEN,
        FORK,
        FPUTS,
        FSTAT,
        FSTATAT,
        FSYNC,
        FTRUNCATE,
        FWRITE,
        GETADDRINFO,
        GETENV,
        GETHOSTNAME,
        GETLINE,
        GETPWNAM_R,
        GETPWUID_R,
        GETSOCKOPT,
        GMTIME_R,
        IF_NAMETOINDEX,
        ISATTY,
        LINK,
        LINKAT,
        LISTEN,
        LOCALTIME_R,
        LSEEK,
        LSTAT,
        MALLOC,
        MKDIR,
        MKDIRAT,
        MKDTEMP,
        MKSTEMP,
        MMAP,
        MSYNC,
        MUNMAP,
        NANOSLEEP,
        OPEN,
        OPENAT,
        OPENDIR,
        PIPE,
        POLL,
        POSIX_FALLOCATE,
        PRCTL,
        PTHREAD_ATTR_DESTROY,
        PTHREAD_ATTR_INIT,
        PTHREAD_ATTR_SETAFFINITY_NP,
        PTHREAD_ATTR_SETINHERITSCHED,
        PTHREAD_ATTR_SETSCHEDPARAM,
        PTHREAD_ATTR_SETSCHEDPOLICY,
        PTHREAD_CREATE,
        PTHREAD_JOIN,
        READ,
        READDIR,
        READLINK,
        READLINKAT,
        REALLOC,
        RENAME,
        RENAMEAT,
        RMDIR,
        SETENV,
        SETSOCKOPT,
        SHUTDOWN,
        SIGACTION,
        SIGNALFD,
        SIGPROCMASK,
        SOCKET,
        SPAWN,
        SPAWN_FILE_ACTIONS_ADDCLOSE,
        SPAWN_FILE_ACTIONS_ADDDUP2,
        SPAWN_FILE_ACTIONS_ADDOPEN,
        SPAWN_FILE_ACTIONS_DESTROY,
        SPAWN_FILE_ACTIONS_INIT,
        SPAWNP,
        STAT,
        STRFTIME,
        STRTOL,
        SYSCONF,
        TRUNCATE,
        SYSTEM,
        TIME,
        TIMERFD_CREATE,
        TIMERFD_SETTIME,
        UNLINK,
        UNLINKAT,
        WAITID,
        WRITE
    };
    class accept_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class bind_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class calloc_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class clock_gettime_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class close_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class closedir_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class connect_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class dup_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class dup2_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class epoll_create1_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class posix_fallocate_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class epoll_ctl_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class epoll_wait_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class execv_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class execvp_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class execvpe_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class eventfd_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fclose_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fcntl_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fdopen_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fflush_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fileno_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fopen_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fork_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fputs_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fstat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fstatat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fsync_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class ftruncate_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class fwrite_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class getaddrinfo_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class getenv_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class gethostname_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class getline_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class getpwnam_r_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class getpwuid_r_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class getsockopt_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class gmtime_r_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class if_nametoindex_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class isatty_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class link_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class linkat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class listen_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class localtime_r_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class lseek_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class lstat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class malloc_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class mkdir_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class mkdirat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class mkdtemp_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class mkstemp_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class mmap_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class msync_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class munmap_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class nanosleep_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class open_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class openat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class opendir_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pipe_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class poll_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class prctl_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pthread_attr_destroy_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pthread_attr_init_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pthread_attr_setaffinity_np_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pthread_attr_setinheritsched_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pthread_attr_setschedparam_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pthread_attr_setschedpolicy_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pthread_create_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class pthread_join_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class read_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class readdir_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class readlink_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class readlinkat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class realloc_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class rename_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class renameat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class rmdir_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class setenv_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class setsockopt_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class shutdown_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class sigaction_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class signalfd_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class sigprocmask_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class socket_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class spawn_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class spawn_file_actions_addclose_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class spawn_file_actions_adddup2_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class spawn_file_actions_addopen_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class spawn_file_actions_destroy_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class spawn_file_actions_init_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class spawnp_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class stat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class strftime_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class strtol_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class sysconf_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class truncate_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class system_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class time_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class timerfd_create_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class timerfd_settime_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class unlink_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class unlinkat_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class waitid_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    class write_error : public sys_error {
        public:
            using sys_error::sys_error;
            Function function() const override;
            const char* name() const override;
    };
    // Autogenerated by mk_boilerplate.py - end

} // ixxx

#endif // IXXX_SYS_ERROR_HH
