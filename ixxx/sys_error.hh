// Copyright (c) 2018, Georg Sauthoff <mail@georg.so>

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

#ifndef IXXX_SYS_ERROR_HH
#define IXXX_SYS_ERROR_HH

#include <exception>
#include <memory>

namespace ixxx {

    enum class Function : int;

    // optimized for catcher doesn't need to call what() (good case),
    // i.e. the what() message is computed lazily
    class sys_error : public std::exception
    {
        public:
            sys_error(int code, const char *literal = nullptr);
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
        CLOSE,
        CLOSEDIR,
        DUP,
        DUP2,
        FCLOSE,
        FCNTL,
        FDOPEN,
        FFLUSH,
        FILENO,
        FOPEN,
        FORK,
        FPUTS,
        FSTAT,
        FSYNC,
        FTRUNCATE,
        FWRITE,
        GETENV,
        GETHOSTNAME,
        GMTIME_R,
        ISATTY,
        LINK,
        LINKAT,
        LISTEN,
        LSEEK,
        MALLOC,
        MKDIR,
        MKDIRAT,
        MKDTEMP,
        MKSTEMP,
        MMAP,
        MUNMAP,
        NANOSLEEP,
        OPEN,
        OPENAT,
        OPENDIR,
        PRCTL,
        READ,
        READDIR,
        RMDIR,
        SETENV,
        SETSOCKOPT,
        SHUTDOWN,
        SIGACTION,
        SOCKET,
        STAT,
        STRFTIME,
        STRTOL,
        SYSTEM,
        TIME,
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
    class gmtime_r_error : public sys_error {
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
    class lseek_error : public sys_error {
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
    class prctl_error : public sys_error {
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
    class socket_error : public sys_error {
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
