// Cast (0x00c7cca0): return this for interface 0x02a8fe3c, otherwise ask the base class (Cast 0xc3f850).
#include "game/types.h"

struct Base_c7cca0 {
    void* Cast(uint32_t typeID) const;   // 0x00c3f850
};
struct Object_c7cca0 : Base_c7cca0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c7cca0
void* Object_c7cca0::Cast(uint32_t typeID) const
{
    if (typeID != 0x02a8fe3c)
        return Base_c7cca0::Cast(typeID);
    return (void*)this;
}
