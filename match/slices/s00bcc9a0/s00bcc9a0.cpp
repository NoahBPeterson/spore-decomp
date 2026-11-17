// Cast (0x00bcc9a0): return this for interface 0x0ecade42, otherwise ask the base class (Cast 0xbcc500).
#include "game/types.h"

struct Base_bcc9a0 {
    void* Cast(uint32_t typeID) const;   // 0x00bcc500
};
struct Object_bcc9a0 : Base_bcc9a0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bcc9a0
void* Object_bcc9a0::Cast(uint32_t typeID) const
{
    if (typeID == 0x0ecade42)
        return (void*)this;
    return Base_bcc9a0::Cast(typeID);
}
