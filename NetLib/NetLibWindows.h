//
// Created by marmelade on 01/06/23.
//

// DO NOT INCLUDE THIS FILE YOURSELF

#ifndef NETLIB_NETLIBWINDOWS_H
#define NETLIB_NETLIBWINDOWS_H

#include <winsock2.h>

// #pragma comment(lib, "Ws2_32.lib")

enum class Domain {

    IPv4        , // = AF_INET,
    IPv6        , // = AF_INET6,
    PACKET      , // = AF_PACKET,
    BLUETOOTH   , // = AF_BLUETOOTH,
    LOCAL       , // = AF_LOCAL,
    VSOCK       , // = AF_VSOCK,
};

enum class Type {

    PACKET      , // = SOCK_PACKET,
    SEQ_PACKET  , // = SOCK_SEQPACKET,
    RAW         , // = SOCK_RAW,
    RDM         , // = SOCK_RDM,
    TCP         , // = SOCK_STREAM,
    UDP         , // = SOCK_DGRAM,
};

enum class Protocol {

    UNSPEC  = 0,
};

#endif //NETLIB_NETLIBWINDOWS_H
