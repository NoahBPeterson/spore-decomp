// Cast (0x00808570): return this for interface 0x04a61af2, otherwise ask the base class (Cast 0x950eb0).
#include "game/types.h"

struct Base_808570 {
    void* Cast(uint32_t typeID) const;   // 0x00950eb0
};
struct Object_808570 : Base_808570 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00808570
void* Object_808570::Cast(uint32_t typeID) const
{
    if (typeID != 0x04a61af2)
        return Base_808570::Cast(typeID);
    return (void*)this;
}
