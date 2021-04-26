// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#include "socket.hh"
#include "sys_error.hh"

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>

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

    int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    {
      int r = ::connect(sockfd, addr, addrlen);
      if (r == -1)
        throw connect_error(errno);
      return r;
    }

    void getaddrinfo(const char *node, const char *service,
                     const struct addrinfo *hints,
                     struct addrinfo **res)
    {
        int r = ::getaddrinfo(node, service, hints, res);
        if (r)
            throw getaddrinfo_error(r, nullptr, sys_error::GAI);
    }

    int getsockopt(int fd, int level, int optname, void *val, socklen_t *len)
    {
        int r = ::getsockopt(fd, level, optname, val, len);
        if (r == -1)
            throw getsockopt_error(errno);
        return r;
    }

    unsigned if_nametoindex(const char *ifname)
    {
        unsigned r = ::if_nametoindex(ifname);
        if (!r)
            throw if_nametoindex_error(errno);
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
#if defined(__MINGW32__) || defined(__MINGW64__)
      int r = ::setsockopt(sockfd, level, optname,
              static_cast<const char*>(optval), optlen);
#else
      int r = ::setsockopt(sockfd, level, optname, optval, optlen);
#endif
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
