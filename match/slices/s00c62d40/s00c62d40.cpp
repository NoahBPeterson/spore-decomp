// Cast (0x00c62d40): return this for interface 0x0330fc43, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c62d40 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c62d40 : Base_c62d40 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c62d40
void* Object_c62d40::Cast(uint32_t typeID) const
{
    if (typeID != 0x0330fc43)
        return Base_c62d40::Cast(typeID);
    return (void*)this;
}
