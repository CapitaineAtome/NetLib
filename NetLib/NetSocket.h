//
// Created by marmelade on 01/06/23.
//

#ifndef NETLIB_NETSOCKET_H
#define NETLIB_NETSOCKET_H

#include <utility>
#include <string>
#include <variant>
#include <cstring>

#include "NetLib.h"

namespace net {

#if defined(WIN32) || defined(WIN64)

    net::Error init_wsa_socket(unsigned int minor = 2, unsigned int major = 2) {

        WSADATA wsaData;
        int iResult;

        if(WSAStartup(MAKEWORD(static_cast<int>(major), static_cast<int>(minor), &wsaData) != NO_ERROR) {

            return Error::Error
        }

        if (LOBYTE(wsaData.wVersion) != minor || HIBYTE(wsaData.wVersion) != major)
        {
            deinit_wsa_socket();

            return Error::Error;
        }

        return Error::Success;
    }

    net::Error deinit_wsa_socket() {

        WSACleanup();
    }

#endif

    struct sockaddr_in operator""__ipv4(const char * buffer, const size_t len) {

        unused(len);

        struct sockaddr_in sa{};

        inet_pton(AF_INET, buffer, &(sa.sin_addr));

        return sa;
    }

    struct sockaddr_in6 operator""__ipv6(const char * buffer, const size_t len) {

        unused(len);

        struct sockaddr_in6 sa6{};

        inet_pton(AF_INET6, buffer, &(sa6.sin6_addr));

        return sa6;
    }

    class Socket {
    public:

        Socket() : m_sock{} {}

        Socket(const std::string node, const std::string service, const enum Type type, const enum Family family, int flags = AI_PASSIVE) : Socket() {

            Open(node, service, type, family, flags);
        }

        ~Socket() {

            Close();
        }

        [[nodiscard]] bool IsValid() const noexcept {

            return m_sock != -1;
        }

        std::expected<int, enum Error> Open(const std::string node, const std::string service, const enum Type type, const enum Family family, int flags = AI_PASSIVE) noexcept {

            struct addrinfo hints{};
            struct addrinfo *res{};
            struct addrinfo *curr{};

            hints.ai_family = std::to_underlying(family);   // IPv4 or IPv6
            hints.ai_socktype = std::to_underlying(type);
            hints.ai_flags = flags;

            if( int status = getaddrinfo(node.c_str(), service.c_str(), &hints, &res); status != 0) {

                return std::unexpected(Error::Error);
            }

            for(curr = res; curr != nullptr; curr = curr->ai_next) {

                if(int sock = socket(curr->ai_family, curr->ai_socktype, curr->ai_protocol); sock != -1) {

                    m_sock = sock;
                    m_sa_len = curr->ai_addrlen;
                    memcpy(&m_sa, curr->ai_addr, m_sa_len);
                    break;
                }
            }

            freeaddrinfo(res);

            if(m_sock == -1) {

                return std::unexpected(Error::Open);
            }

            return false;
        }

        void Close(int how = 2) noexcept {

            // close(m_sock);
            shutdown(m_sock, how);
            m_sock = -1;
        }

        std::expected<int, Error> Bind() {

            if(bind(m_sock, &m_sa, m_sa_len)) {

                return std::unexpected(Error::Bind);
            }

            return 0;
        }

        std::expected<int, Error> Listen(const unsigned int backlog) {

            if(listen(m_sock, static_cast<int>(backlog)) == -1) {

                return std::unexpected(Error::Listen);
            }

            return 0;
        }

        std::expected<Socket, Error> Accept() {

            Socket sock{{}, {}, sizeof(struct sockaddr)};

            sock.m_sock = accept(m_sock, &sock.m_sa, &sock.m_sa_len);

            if(m_sock == -1) {

                return std::unexpected(Error::Accept);
            }

            return sock;
        }

        std::expected<int, Error> Connect() {

            if(connect(m_sock, &m_sa, m_sa_len) == -1) {

                return std::unexpected(Error::Connect);
            }

            return 0;
        }

        template<typename T>
        std::expected<unsigned int, enum Error> Send(const T &data, const int flags) const noexcept {

            int bytes_send = send(m_sock, &data, sizeof(data), flags);

            if(bytes_send == -1) {

                return std::unexpected(Error::Send);
            }

            return static_cast<unsigned int>(bytes_send);
        }

        template<typename T, const size_t length>
        std::expected<unsigned int, enum Error> Send(const T (&data)[length], const int flags) const noexcept {

            int bytes_send = send(m_sock, data, sizeof(T) * length, flags);

            if(bytes_send == -1) {

                return std::unexpected(Error::Send);
            }

            return bytes_send;
        }

        template<typename T>
        std::expected<unsigned int, enum Error> Send(const T * const data, const int flags) const noexcept {

            int bytes_send = send(m_sock, data, sizeof(T), flags);

            if(bytes_send == -1) {

                return std::unexpected(Error::Send);
            }

            return bytes_send;
        }

        template<typename T>
        std::expected<unsigned int, enum Error> Recv(T &data, const int flags) {

            int bytes_recv = recv(m_sock, &data, sizeof(data), flags);

            if(bytes_recv == -1) {

                return std::unexpected(Error::Recv);
            }

            return static_cast<unsigned int>(bytes_recv);
        }

        template<typename T, const size_t length>
        std::expected<unsigned int, enum Error> Recv(T (&data)[length], const int flags) const noexcept {

            int bytes_recv = recv(m_sock, data, sizeof(T) * length, flags);

            if(bytes_recv == -1) {

                return std::unexpected(Error::Send);
            }

            return bytes_recv;
        }

        template<typename T>
        std::expected<unsigned int, enum Error> Recv(T * const data, const int flags) const noexcept {

            int bytes_recv = recv(m_sock, data, sizeof(T), flags);

            if(bytes_recv == -1) {

                return std::unexpected(Error::Send);
            }

            return bytes_recv;
        }

        [[nodiscard]] std::expected<bool, Error> SetNonBlocking(const bool enable) const noexcept {

            if(ioctl(m_sock, FIONBIO, &enable) == -1) {

                return std::unexpected(Error::Error);
            }

            return enable;
        }

    private:
        Socket(const int sock, struct sockaddr sa, socklen_t sa_len) : m_sa{sa}, m_sock{sock}, m_sa_len{sa_len} {}

    protected:
        struct sockaddr m_sa;
        socklen_t m_sa_len;
        int m_sock{-1};

    };
}

#endif //NETLIB_NETSOCKET_H
