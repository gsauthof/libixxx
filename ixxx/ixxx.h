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

#ifndef IXXX_H
#define IXXX_H

#include <stdexcept>
#include <string>
#include <ostream>


#include <ixxx/ansi.h>
#include <ixxx/posix.h>

// Mac OS X pollutes the global namespace with a FWRITE
// macro ... undeffing it such that we can use it
// as enum value ...
#ifdef FWRITE
  #undef FWRITE
#endif

namespace ixxx {
  
    enum class Function {
      FIRST_,
      CLOSE,
      DUP,
      DUP2,
      FCLOSE,
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
      ISATTY,
      LINK,
      LINKAT,
      LSEEK,
      MALLOC,
      MKDTEMP,
      MKSTEMP,
      MMAP,
      MUNMAP,
      NANOSLEEP,
      OPEN,
      OPENAT,
      READ,
      SETENV,
      SIGACTION,
      STAT,
      TIME,
      UNLINK,
      UNLINKAT,
      WAITID,
      WRITE,
      LAST_
    };
    std::ostream &operator<<(std::ostream &o, Function f);

  class runtime_error : public std::runtime_error {
    private:
        Function function_;
    public:
        runtime_error(Function f, const std::string &msg);
        Function function() const;
  };

  class errno_error : public runtime_error {
    private:
      int errno_ {0};
    public:
        errno_error(Function f, int e);
      int code() const;
  };


}

#endif
