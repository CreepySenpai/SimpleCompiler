#pragma once

#include <Creepy/Logger.hpp>

namespace Creepy{

#ifdef CREEPY_ENABLE_ASSERT

    #define ASSERT(cond)                                                \
        if(!(cond)){                                                    \
            LOG("Assertion failed at: {}:{}", __FILE__, __LINE__);      \
            std::abort();                                               \
        }


    #define ASSERT_MSG(cond, msg, ...)                                                           \
        if(!(cond)){                                                                        \
            LOG("Assertion failed at: {}:{} with msg {}", __FILE__, __LINE__, std::format(msg, ##__VA_ARGS__));         \
            std::abort();                                                                   \
        }

#else

    #define ASSERT(cond)

    #define ASSERT_MSG(cond, msg, ...)

#endif

}