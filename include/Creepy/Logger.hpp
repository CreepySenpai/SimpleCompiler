#pragma once

#include <print>

namespace Creepy{

#ifdef CREEPY_ENABLE_LOGGER
    #define LOG(fmt, ...) std::println(fmt, ##__VA_ARGS__)
#else
    #define LOG(fmt, ...)
#endif

}