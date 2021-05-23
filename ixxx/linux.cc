// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#include "linux.hh"
#include "sys_error.hh"

#if defined(__linux__)
#include <sys/prctl.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>
#endif

#include <unistd.h>
#include <sys/syscall.h>

#include <errno.h>

namespace ixxx {

  namespace linux {

#if defined(__linux__)

    int epoll_create1(int flags)
    {
      int r = ::epoll_create1(flags);
      if (r == -1)
        throw epoll_create1_error(errno);
      return r;
    }
    void epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
    {
      int r = ::epoll_ctl(epfd, op, fd, event);
      if (r == -1)
        throw epoll_ctl_error(errno);
    }
    int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)
    {
      int r = ::epoll_wait(epfd, events, maxevents, timeout);
      if (r == -1)
        throw epoll_wait_error(errno);
      return r;
    }

    int eventfd(unsigned initval, int flags)
    {
        int r = ::eventfd(initval, flags);
        if (r == -1)
            throw eventfd_error(errno);
        return r;
    }

    int prctl(int option, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5)
    {
      int r = ::prctl(option, arg2, arg3, arg4, arg5);
      if (r == -1)
        throw prctl_error(errno);
      return r;
    }

    int signalfd(int fd, const sigset_t *mask, int flags)
    {
        int r = ::signalfd(fd, mask, flags);
        if (r == -1)
            throw signalfd_error(errno);
        return r;
    }

    int timerfd_create(int clockid, int flags)
    {
      int r = ::timerfd_create(clockid, flags);
      if (r == -1)
        throw timerfd_create_error(errno);
      return r;
    }
    void timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value)
    {
      int r = ::timerfd_settime(fd, flags, new_value, old_value);
      if (r == -1)
        throw timerfd_settime_error(errno);
    }

      void io_setup(unsigned nr_events, io_context_t *ctx)
      {
          int r = ::syscall(SYS_io_setup, nr_events, ctx);
          if (r == -1)
              throw io_setup_error(errno);
      }
      void io_destroy(io_context_t ctx)
      {
          int r = ::syscall(SYS_io_destroy, ctx);
          if (r == -1)
              throw io_destroy_error(errno);
      }
      int io_submit(io_context_t ctx, long nr, struct iocb **iocbpp)
      {
          int r = ::syscall(SYS_io_submit, ctx, nr, iocbpp);
          if (r == -1)
              throw io_submit_error(errno);
          return r;
      }
      int io_getevents(io_context_t ctx, long min_nr, long nr,
              struct io_event *events, struct timespec *timeout)
      {
          int r = ::syscall(SYS_io_getevents, ctx, min_nr, nr, events, timeout);
          if (r == -1)
              throw io_getevents_error(errno);
          return r;
      }


#endif

  } // linux
} // ixxx
