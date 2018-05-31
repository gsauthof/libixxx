// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#include "socket.hh"
#include "sys_error.hh"

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

namespace ixxx {

  namespace posix {

    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
    {
      int r = ::accept(sockfd, addr, addrlen);
      if (r == -1)
        throw accept_error(errno);
      return r;
    }

    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    {
      int r = ::bind(sockfd, addr, addrlen);
      if (r == -1)
        throw bind_error(errno);
      return r;
    }

    int listen(int sockfd, int backlog)
    {
      int r = ::listen(sockfd, backlog);
      if (r == -1)
        throw listen_error(errno);
      return r;
    }
    int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
    {
      int r = ::setsockopt(sockfd, level, optname, optval, optlen);
      if (r == -1)
        throw setsockopt_error(errno);
      return r;
    }
    int shutdown(int socket, int how)
    {
      int r = ::shutdown(socket, how);
      if (r == -1)
        throw shutdown_error(errno);
      return r;
    }
    int socket(int domain, int type, int protocol)
    {
      int r = ::socket(domain, type, protocol);
      if (r == -1)
        throw socket_error(errno);
      return r;
    }


  } // posix


} // ixxx
