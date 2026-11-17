// Cast (0x00cb3ab0): return this for interface 0x024270c6, otherwise ask the base class (Cast 0xcb3a40).
#include "game/types.h"

struct Base_cb3ab0 {
    void* Cast(uint32_t typeID) const;   // 0x00cb3a40
};
struct Object_cb3ab0 : Base_cb3ab0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00cb3ab0
void* Object_cb3ab0::Cast(uint32_t typeID) const
{
    if (typeID == 0x024270c6)
        return (void*)this;
    return Base_cb3ab0::Cast(typeID);
}
