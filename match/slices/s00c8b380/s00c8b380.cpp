// Cast (0x00c8b380): return this for interface 0x0355c8df, otherwise ask the base class (Cast 0xb18460).
#include "game/types.h"

struct Base_c8b380 {
    void* Cast(uint32_t typeID) const;   // 0x00b18460
};
struct Object_c8b380 : Base_c8b380 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c8b380
void* Object_c8b380::Cast(uint32_t typeID) const
{
    if (typeID == 0x0355c8df)
        return (void*)this;
    return Base_c8b380::Cast(typeID);
}
