#pragma once

#include <cstdint>
#include <memory>

namespace Creepy {
    struct Arena{
        void* mem{nullptr};
        uint64_t count{};
        uint64_t capacity{};
    };

    template <typename T>
    constexpr inline T* Arena_Alloc(Arena& arena){
        if(arena.count + sizeof(T) >= arena.capacity){
            // asm("int3");
            return nullptr;
        }
        
        T* obj = std::start_lifetime_as<T>(static_cast<uint8_t*>(arena.mem) + arena.count);
        arena.count += sizeof(T);

        return obj;
    }

    template <typename T>
    constexpr inline T* Arena_AllocArray(Arena& arena, uint32_t count){
        if(arena.count + (sizeof(T) * count) >= arena.capacity){
            // asm("int3");
            return nullptr;
        }

        T*obj = std::start_lifetime_as_array<T>(static_cast<uint8_t*>(arena.mem) + arena.count, count);

        arena.count += (sizeof(T) * count);

        return obj;
    }

    constexpr inline void Arena_Align(Arena& arena, uint64_t alignSize){
        const uint64_t remain = alignSize - (reinterpret_cast<uint64_t>(arena.mem) % alignSize);

        if(remain == 0){
            return;
        }

        if(arena.count + remain >= arena.capacity){
            // TODO: Some error agnostic
        }

        arena.count += remain;
    }
}