// Cast (0x00765aa0): return this for interface 0x2f4e681c, otherwise ask the base class (Cast 0x6abe20).
#include "game/types.h"

struct Base_765aa0 {
    void* Cast(uint32_t typeID) const;   // 0x006abe20
};
struct Object_765aa0 : Base_765aa0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00765aa0
void* Object_765aa0::Cast(uint32_t typeID) const
{
    if (typeID == 0x2f4e681c)
        return (void*)this;
    return Base_765aa0::Cast(typeID);
}
