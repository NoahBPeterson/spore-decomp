// Cast (0x00941f60): return this for interface 0xae9cb0f9, else null.
#include "game/types.h"

struct Object_941f60 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00941f60
void* Object_941f60::Cast(uint32_t typeID) const
{
    return typeID == 0xae9cb0f9 ? (void*)this : 0;
}
