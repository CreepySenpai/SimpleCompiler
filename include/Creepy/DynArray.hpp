#pragma once

#include <cstring>
#include <Creepy/Arena.hpp>

namespace Creepy{

    template <typename T>
    struct DynArray{
        static constexpr uint32_t GROW_FACTOR = 2;

        T* element{nullptr};
        uint32_t count{};
        uint32_t capacity{};
    };

    template <typename T>
    constexpr inline DynArray<T> DynArray_Create(Arena& arena, uint32_t capacity){
        T* mem = Arena_AllocArray<T>(arena, capacity);

        return DynArray<T>{
            .element = mem,
            .count = 0,
            .capacity = capacity
        };
    }

    template <typename T>
    constexpr inline void DynArray_Add(DynArray<T>& dynArr, Arena& arena, T ele){
        if(dynArr.count + 1 >= dynArr.capacity){
            // Realloc
            const uint32_t newCapacity = dynArr.capacity * DynArray<T>::GROW_FACTOR;
            T* newMem = Arena_AllocArray<T>(arena, newCapacity);

            std::memcpy(newMem, dynArr.element, sizeof(T) * dynArr.capacity);
            
            dynArr.element = newMem;
            dynArr.capacity = newCapacity;
        }

        dynArr.element[dynArr.count] = ele;
        ++dynArr.count;
    }

    template <typename T>
    constexpr inline void DynArray_Clear(DynArray<T>& dynArr){
        dynArr.count = 0;
        // std::memset(dynArr.element, 0, dynArr.capacity * sizeof(T));
    }
}