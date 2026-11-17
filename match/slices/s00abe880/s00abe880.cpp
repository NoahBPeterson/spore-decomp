// Cast (0x00abe880): return this for interface 0x01141f86, else null.
#include "game/types.h"

struct Object_abe880 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00abe880
void* Object_abe880::Cast(uint32_t typeID) const
{
    return typeID == 0x01141f86 ? (void*)this : 0;
}
