// Cast (0x00700380): return this for interface 0x00e6bce5, otherwise ask the base class (Cast 0x6abe20).
#include "game/types.h"

struct Base_700380 {
    void* Cast(uint32_t typeID) const;   // 0x006abe20
};
struct Object_700380 : Base_700380 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00700380
void* Object_700380::Cast(uint32_t typeID) const
{
    if (typeID == 0x00e6bce5)
        return (void*)this;
    return Base_700380::Cast(typeID);
}
