// Cast (0x00c2e3a0): return this for interface 0x14066ce5, otherwise ask the base class (Cast 0xc44990).
#include "game/types.h"

struct Base_c2e3a0 {
    void* Cast(uint32_t typeID) const;   // 0x00c44990
};
struct Object_c2e3a0 : Base_c2e3a0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c2e3a0
void* Object_c2e3a0::Cast(uint32_t typeID) const
{
    if (typeID != 0x14066ce5)
        return Base_c2e3a0::Cast(typeID);
    return (void*)this;
}
