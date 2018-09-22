// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#ifndef IXXX_POSIX_SOCKET_H
#define IXXX_POSIX_SOCKET_H

#include <sys/types.h>

#if defined(__MINGW32__) || defined(__MINGW64__)
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <sys/socket.h>
#endif

namespace ixxx {
  namespace posix {

    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    int listen(int sockfd, int backlog);
    int setsockopt(int sockfd, int level, int optname, const void *optval,
        socklen_t optlen);
    int shutdown(int socket, int how);
    int socket(int domain, int type, int protocol);

  }
}

#endif // IXXX_POSIX_SOCKET_H
