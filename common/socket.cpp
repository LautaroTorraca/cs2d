#include "socket.h"

#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include <arpa/inet.h>
#include <linux/soundcard.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "liberror.h"
#include "resolver.h"

#define STREAM_SEND_CLOSED 0x01
#define STREAM_RECV_CLOSED 0x02
#define STREAM_BOTH_CLOSED 0x03
#define STREAM_BOTH_OPEN 0x00

Socket::Socket(const char* hostname, const char* servname) {
    Resolver resolver(hostname, servname, false);

    int s = -1;
    int fd = -1;
    this->closed = true;
    this->stream_status = STREAM_BOTH_CLOSED;

    while (resolver.has_next()) {
        struct addrinfo* addr = resolver.next();

        if (fd != -1)
            ::close(fd);

        fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (fd == -1) {
            continue;
        }

        s = connect(fd, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        this->closed = false;
        this->stream_status = STREAM_BOTH_OPEN;
        this->skt = fd;
        return;
    }

    int saved_errno = errno;

    if (fd != -1)
        ::close(fd);

    throw LibError(saved_errno, "socket construction failed (connect to %s:%s)",
                   (hostname ? hostname : ""), (servname ? servname : ""));
}

Socket::Socket(const char* servname) {
    Resolver resolver(nullptr, servname, true);

    int s = -1;
    int fd = -1;
    this->closed = true;
    this->stream_status = STREAM_BOTH_CLOSED;

    while (resolver.has_next()) {
        struct addrinfo* addr = resolver.next();

        if (fd != -1)
            ::close(fd);

        fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (fd == -1) {
            continue;
        }

        int optval = 1;
        s = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (s == -1) {
            continue;
        }

        s = bind(fd, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        s = listen(fd, 20);
        if (s == -1) {
            continue;
        }

        this->closed = false;
        this->stream_status = STREAM_BOTH_OPEN;
        this->skt = fd;
        return;
    }

    int saved_errno = errno;

    if (fd != -1)
        ::close(fd);

    throw LibError(saved_errno, "socket construction failed (listen on %s)",
                   (servname ? servname : ""));
}

Socket::Socket(Socket&& other) {
    this->skt = other.skt;
    this->closed = other.closed;
    this->stream_status = other.stream_status;

    other.skt = -1;
    other.closed = true;
    other.stream_status = STREAM_BOTH_CLOSED;
}

Socket& Socket::operator=(Socket&& other) {
    if (this == &other)
        return *this;

    if (!this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }

    this->skt = other.skt;
    this->closed = other.closed;
    this->stream_status = other.stream_status;

    other.skt = -1;
    other.closed = true;
    other.stream_status = STREAM_BOTH_CLOSED;

    return *this;
}

int Socket::recvsome(void* data, unsigned int sz) {
    chk_skt_or_fail();
    int s = recv(this->skt, reinterpret_cast<char*>(data), sz, 0);
    if (s == 0) {
        stream_status |= STREAM_RECV_CLOSED;
        return 0;
    } else if (s == -1) {
        throw LibError(errno, "socket recv failed");
    }
    return s;
}

int Socket::sendsome(const void* data, unsigned int sz) {
    chk_skt_or_fail();
    int s = send(this->skt, reinterpret_cast<const char*>(data), sz, MSG_NOSIGNAL);
    if (s == -1) {
        if (errno == EPIPE) {
            stream_status |= STREAM_SEND_CLOSED;
            return 0;
        }
        throw LibError(errno, "socket send failed");
    } else if (s == 0) {
        stream_status |= STREAM_SEND_CLOSED;
        return 0;
    }
    return s;
}

int Socket::recvall(void* data, unsigned int sz) {
    unsigned int received = 0;
    while (received < sz) {
        int s = recvsome(reinterpret_cast<char*>(data) + received, sz - received);
        if (s <= 0) {
            assert(s == 0);
            if (received)
                throw LibError(EPIPE, "socket received only %d of %d bytes", received, sz);
            else
                return 0;
        }
        received += s;
    }
    return sz;
}

int Socket::sendall(const void* data, unsigned int sz) {
    unsigned int sent = 0;
    while (sent < sz) {
        int s = sendsome(reinterpret_cast<const char*>(data) + sent, sz - sent);
        if (s <= 0) {
            assert(s == 0);
            if (sent)
                throw LibError(EPIPE, "socket sent only %d of %d bytes", sent, sz);
            else
                return 0;
        }
        sent += s;
    }
    return sz;
}

Socket::Socket(int skt) {
    this->skt = skt;
    this->closed = false;
    this->stream_status = STREAM_BOTH_OPEN;
}

Socket Socket::accept() {
    chk_skt_or_fail();
    int peer_skt = ::accept(this->skt, nullptr, nullptr);
    if (peer_skt == -1)
        throw LibError(errno, "socket accept failed");
    return Socket(peer_skt);
}

void Socket::shutdown(int how) {
    chk_skt_or_fail();
    if (::shutdown(this->skt, how) == -1) {
        throw LibError(errno, "socket shutdown failed");
    }
    switch (how) {
        case 0:
            stream_status |= STREAM_RECV_CLOSED;
            break;
        case 1:
            stream_status |= STREAM_SEND_CLOSED;
            break;
        case 2:
            stream_status |= STREAM_BOTH_CLOSED;
            break;
        default:
            throw std::runtime_error("Unknown shutdown value");
    }
}

bool Socket::is_stream_send_closed() const { return stream_status & STREAM_SEND_CLOSED; }

bool Socket::is_stream_recv_closed() const { return stream_status & STREAM_RECV_CLOSED; }


bool Socket::is_closed() const { return this->closed; }

int Socket::close() {
    chk_skt_or_fail();
    this->closed = true;
    this->stream_status = STREAM_BOTH_CLOSED;
    return ::close(this->skt);
}

Socket::~Socket() {
    if (!this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }
}

void Socket::chk_skt_or_fail() const {
    if (skt == -1) {
        throw std::runtime_error("socket with invalid file descriptor (-1), perhaps you are using "
                                 "a *previously moved* socket (and therefore invalid).");
    }
}
