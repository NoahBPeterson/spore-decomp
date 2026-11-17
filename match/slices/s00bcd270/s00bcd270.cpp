// Cast (0x00bcd270): return this for interface 0x070704db, otherwise ask the base class (Cast 0xbcc500).
#include "game/types.h"

struct Base_bcd270 {
    void* Cast(uint32_t typeID) const;   // 0x00bcc500
};
struct Object_bcd270 : Base_bcd270 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bcd270
void* Object_bcd270::Cast(uint32_t typeID) const
{
    if (typeID == 0x070704db)
        return (void*)this;
    return Base_bcd270::Cast(typeID);
}
