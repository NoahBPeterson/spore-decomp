// Cast (0x00ff3b10): return this for interface 0x9073163b, otherwise ask the base class (Cast 0xc86fc0).
#include "game/types.h"

struct Base_ff3b10 {
    void* Cast(uint32_t typeID) const;   // 0x00c86fc0
};
struct Object_ff3b10 : Base_ff3b10 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ff3b10
void* Object_ff3b10::Cast(uint32_t typeID) const
{
    if (typeID != 0x9073163b)
        return Base_ff3b10::Cast(typeID);
    return (void*)this;
}
