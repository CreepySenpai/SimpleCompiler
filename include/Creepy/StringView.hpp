#pragma once

#include <cstdint>

namespace Creepy{

    struct StringView{
        char* ptr{nullptr};
        uint32_t count{};
    };
    
}