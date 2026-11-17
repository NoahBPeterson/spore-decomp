// Cast (0x00bcc830): return this for interface 0x1007ae63, otherwise ask the base class (Cast 0xbcc500).
#include "game/types.h"

struct Base_bcc830 {
    void* Cast(uint32_t typeID) const;   // 0x00bcc500
};
struct Object_bcc830 : Base_bcc830 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bcc830
void* Object_bcc830::Cast(uint32_t typeID) const
{
    if (typeID == 0x1007ae63)
        return (void*)this;
    return Base_bcc830::Cast(typeID);
}
