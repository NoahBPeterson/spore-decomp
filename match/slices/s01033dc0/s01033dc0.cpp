// Cast (0x01033dc0): return this for interface 0x03cdbbe9, otherwise ask the base class (Cast 0xabe880).
#include "game/types.h"

struct Base_1033dc0 {
    void* Cast(uint32_t typeID) const;   // 0x00abe880
};
struct Object_1033dc0 : Base_1033dc0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x01033dc0
void* Object_1033dc0::Cast(uint32_t typeID) const
{
    if (typeID != 0x03cdbbe9)
        return Base_1033dc0::Cast(typeID);
    return (void*)this;
}
