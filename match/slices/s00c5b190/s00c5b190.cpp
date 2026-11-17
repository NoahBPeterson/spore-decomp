// Cast (0x00c5b190): return this for interface 0x03960c0a, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c5b190 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c5b190 : Base_c5b190 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c5b190
void* Object_c5b190::Cast(uint32_t typeID) const
{
    if (typeID != 0x03960c0a)
        return Base_c5b190::Cast(typeID);
    return (void*)this;
}
