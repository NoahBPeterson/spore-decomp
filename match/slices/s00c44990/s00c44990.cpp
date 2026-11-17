// Cast (0x00c44990): return this for interface 0x34066a80, otherwise ask the base class (Cast 0xb18460).
#include "game/types.h"

struct Base_c44990 {
    void* Cast(uint32_t typeID) const;   // 0x00b18460
};
struct Object_c44990 : Base_c44990 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c44990
void* Object_c44990::Cast(uint32_t typeID) const
{
    if (typeID != 0x34066a80)
        return Base_c44990::Cast(typeID);
    return (void*)this;
}
