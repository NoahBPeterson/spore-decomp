// Cast (0x007fdcf0): return this for interface 0x0254cc84, otherwise ask the base class (Cast 0x7f9bb0).
#include "game/types.h"

struct Base_7fdcf0 {
    void* Cast(uint32_t typeID) const;   // 0x007f9bb0
};
struct Object_7fdcf0 : Base_7fdcf0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007fdcf0
void* Object_7fdcf0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0254cc84)
        return Base_7fdcf0::Cast(typeID);
    return (void*)this;
}
