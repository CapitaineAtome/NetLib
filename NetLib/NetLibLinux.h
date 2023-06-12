//
// Created by marmelade on 01/06/23.
//

// DO NOT INCLUDE THIS FILE YOURSELF

#ifndef NETLIB_NETLIBLINUX_H
#define NETLIB_NETLIBLINUX_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <arpa/inet.h>

#include <netdb.h>

#include <unistd.h>

namespace net {

    enum class Type {

        Packet      = SOCK_PACKET,
        SeqPacket   = SOCK_SEQPACKET,
        Raw         = SOCK_RAW,
        Rdm         = SOCK_RDM,
        TCP         = SOCK_STREAM,
        UDP         = SOCK_DGRAM,
    };

    enum class Family {

        Unspec      = PF_UNSPEC,
        Local       = PF_LOCAL,
        Unix        = PF_UNIX,
        File        = PF_FILE,
        Inet        = PF_INET,
        AX25        = PF_AX25,
        IPX         = PF_IPX,
        AppleTalk   = PF_APPLETALK,
        NetRom      = PF_NETROM,
        Bridge      = PF_BRIDGE,
        ATMPVC      = PF_ATMPVC,
        X25         = PF_X25,
        INET6       = PF_INET6,
        Rose        = PF_ROSE,
        DECnet      = PF_DECnet,
        NetBEUI     = PF_NETBEUI,
        Security    = PF_SECURITY,
        Key         = PF_KEY,
        NetLink     = PF_NETLINK,
        Route       = PF_ROUTE,
        Packet      = PF_PACKET,
        ASH         = PF_ASH,
        EcoNet      = PF_ECONET,
        ATMSVC      = PF_ATMSVC,
        RDS         = PF_RDS,
        SNA         = PF_SNA,
        IRDA        = PF_IRDA,
        PPPOX       = PF_PPPOX,
        WANPipe     = PF_WANPIPE,
        LLC         = PF_LLC,
        IB          = PF_IB,
        MPLS        = PF_MPLS,
        CAN         = PF_CAN,
        TIPC        = PF_TIPC,
        Bluetooth   = PF_BLUETOOTH,
        IUCV        = PF_IUCV,
        RXRPC       = PF_RXRPC,
        ISDN        = PF_ISDN,
        PHONET      = PF_PHONET,
        IEEE802154  = PF_IEEE802154,
        CAIF        = PF_CAIF,
        ALG         = PF_ALG,
        NFC         = PF_NFC,
        VSock       = PF_VSOCK,
        KCM         = PF_KCM,
        QIPCRTR     = PF_QIPCRTR,
        SMC         = PF_SMC,
        XDP         = PF_XDP,
        MCTP        = PF_MCTP,
        MAX         = PF_MAX,
    };
}
#endif //NETLIB_NETLIBLINUX_H
