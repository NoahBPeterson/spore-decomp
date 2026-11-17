// Cast (0x00f25020): return this for interface 0xe742574a, otherwise ask the base class (Cast 0x6abe20).
#include "game/types.h"

struct Base_f25020 {
    void* Cast(uint32_t typeID) const;   // 0x006abe20
};
struct Object_f25020 : Base_f25020 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00f25020
void* Object_f25020::Cast(uint32_t typeID) const
{
    if (typeID == 0xe742574a)
        return (void*)this;
    return Base_f25020::Cast(typeID);
}
