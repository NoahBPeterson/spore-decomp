// Cast (0x00bccaf0): return this for interface 0x0ff10521, otherwise ask the base class (Cast 0xbcc500).
#include "game/types.h"

struct Base_bccaf0 {
    void* Cast(uint32_t typeID) const;   // 0x00bcc500
};
struct Object_bccaf0 : Base_bccaf0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bccaf0
void* Object_bccaf0::Cast(uint32_t typeID) const
{
    if (typeID == 0x0ff10521)
        return (void*)this;
    return Base_bccaf0::Cast(typeID);
}
