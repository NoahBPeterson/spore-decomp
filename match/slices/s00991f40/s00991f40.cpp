// Cast (0x00991f40): return this for interface 0x02955717, otherwise ask the base class (Cast 0x95f960).
#include "game/types.h"

struct Base_991f40 {
    void* Cast(uint32_t typeID) const;   // 0x0095f960
};
struct Object_991f40 : Base_991f40 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00991f40
void* Object_991f40::Cast(uint32_t typeID) const
{
    if (typeID == 0x02955717)
        return (void*)this;
    return Base_991f40::Cast(typeID);
}
