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

#include "socket.hh"
#include "ixxx.h"

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

namespace ixxx {

  namespace {
    void throw_errno(Function f)
    {
      int e = errno;
      throw errno_error(f, e);
    }
  }

  namespace posix {

    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
    {
      int r = ::accept(sockfd, addr, addrlen);
      if (r == -1)
        throw_errno(Function::ACCEPT);
      return r;
    }

    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    {
      int r = ::bind(sockfd, addr, addrlen);
      if (r == -1)
        throw_errno(Function::BIND);
      return r;
    }

    int listen(int sockfd, int backlog)
    {
      int r = ::listen(sockfd, backlog);
      if (r == -1)
        throw_errno(Function::LISTEN);
      return r;
    }
    int setsockopt(int sockfd, int level, int optname,
                              const void *optval, socklen_t optlen)
    {
      int r = ::setsockopt(sockfd, level, optname, optval, optlen);
      if (r == -1)
        throw_errno(Function::SETSOCKOPT);
      return r;
    }
    int shutdown(int socket, int how)
    {
      int r = ::shutdown(socket, how);
      if (r == -1)
        throw_errno(Function::SHUTDOWN);
      return r;
    }
    int socket(int domain, int type, int protocol)
    {
      int r = ::socket(domain, type, protocol);
      if (r == -1)
        throw_errno(Function::SOCKET);
      return r;
    }


  } // posix


} // ixxx
