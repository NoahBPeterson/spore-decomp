// Cast (0x00c3f190): return this for interface 0x02e71a5a, otherwise ask the base class (Cast 0xc6f6e0).
#include "game/types.h"

struct Base_c3f190 {
    void* Cast(uint32_t typeID) const;   // 0x00c6f6e0
};
struct Object_c3f190 : Base_c3f190 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c3f190
void* Object_c3f190::Cast(uint32_t typeID) const
{
    if (typeID == 0x02e71a5a)
        return (void*)this;
    return Base_c3f190::Cast(typeID);
}
