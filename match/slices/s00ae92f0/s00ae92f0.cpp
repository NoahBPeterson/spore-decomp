// Cast (0x00ae92f0): return this when the type ID is one of 0x0179c807, 0x037abb49, else null.
#include "game/types.h"

struct Object_ae92f0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ae92f0
void* Object_ae92f0::Cast(uint32_t typeID) const
{
    if (typeID == 0x0179c807)
        return (void*)this;
    return typeID == 0x037abb49 ? (void*)this : 0;
}
