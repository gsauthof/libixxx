// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#ifndef IXXX_LINUX_HH
#define IXXX_LINUX_HH

namespace ixxx {

  // work-around GCC/Clang that `define linux 1` with -std=gnu++11/14 ...
  #ifdef linux
    #undef linux
  #endif

  namespace linux {

#if defined(__linux__)
    int prctl(int option, unsigned long arg2, unsigned long arg3 = 0,
        unsigned long arg4 = 0, unsigned long arg5 = 0);

#endif

  } // linux
} // ixxx

#endif // IXXX_LINUX_HH

