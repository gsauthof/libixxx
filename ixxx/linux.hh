// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#ifndef IXXX_LINUX_HH
#define IXXX_LINUX_HH

struct epoll_event;
struct itimerspec;

namespace ixxx {

  // work-around GCC/Clang that `define linux 1` with -std=gnu++11/14 ...
  #ifdef linux
    #undef linux
  #endif

  namespace linux {

#if defined(__linux__)

      int epoll_create1(int flags);
      void epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
      int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

    int prctl(int option, unsigned long arg2, unsigned long arg3 = 0,
        unsigned long arg4 = 0, unsigned long arg5 = 0);

      int timerfd_create(int clockid, int flags);
      void timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value);

#endif

  } // linux
} // ixxx

#endif // IXXX_LINUX_HH

