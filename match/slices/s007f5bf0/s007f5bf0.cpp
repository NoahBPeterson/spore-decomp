// Cast (0x007f5bf0): return this for interface 0x026e0fbc, otherwise ask the base class (Cast 0x951240).
#include "game/types.h"

struct Base_7f5bf0 {
    void* Cast(uint32_t typeID) const;   // 0x00951240
};
struct Object_7f5bf0 : Base_7f5bf0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007f5bf0
void* Object_7f5bf0::Cast(uint32_t typeID) const
{
    if (typeID != 0x026e0fbc)
        return Base_7f5bf0::Cast(typeID);
    return (void*)this;
}
