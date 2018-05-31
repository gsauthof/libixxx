// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#include "linux.hh"
#include "sys_error.hh"

#if defined(__linux__)
#include <sys/prctl.h>
#endif

namespace ixxx {

  namespace linux {

#if defined(__linux__)
    int prctl(int option, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5)
    {
      int r = ::prctl(option, arg2, arg3, arg4, arg5);
      if (r == -1)
        throw prctl_error(errno);
      return r;
    }

#endif

  } // linux
} // ixxx
