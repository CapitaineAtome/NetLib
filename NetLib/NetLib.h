//
// Created by marmelade on 01/06/23.
//

#ifndef NETLIB_NETLIB_H
#define NETLIB_NETLIB_H

#include <expected>
#include <cstdint>

#define unused(arg) (void)arg

namespace net {

    enum class [[nodiscard("Error returned should not be ignored")]] Error : uint8_t {
        Success = 0,
        Error,
        Open,
        Bind,
        Listen,
        Accept,
        Connect,
        Send,
        Recv,
    };

    using bool_err = std::expected<bool, enum Error>;
    using uint_err = std::expected<unsigned int, enum Error>;
    using int_err = std::expected<int, enum Error>;

}

#if defined(__linux__)

#include "NetLibLinux.h"

#elif defined(WIN32) || defined(WIN64)

#include "NetLibWindows.h"

#endif // SYSTEM

#endif // NETLIB_NETLIB_H
