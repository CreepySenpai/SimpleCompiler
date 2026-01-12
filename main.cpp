#include <Creepy/Logger.hpp>
#include <Creepy/Assert.hpp>
#include <Creepy/DynArray.hpp>

int main(){

    uint8_t* buffer = new uint8_t[30 * 4096]{};

    Creepy::Arena arena{
        .mem = buffer,
        .count = 0,
        .capacity = 4096
    };

    Creepy::Arena_Align(arena, 8);

    auto myArr = Creepy::DynArray_Create<int>(arena, 20);

    for(uint32_t i{}; i < myArr.capacity; ++i){
        myArr.element[i] = i;
    }

    for(uint32_t i{}; i < myArr.capacity; ++i){
        ASSERT_MSG(myArr.element[i] != i, "Hum wrong");

        LOG("Ele: {}", myArr.element[i]);
    }

    return 0;
}
