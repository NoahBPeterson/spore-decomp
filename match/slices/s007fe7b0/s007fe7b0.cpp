// Cast (0x007fe7b0): return this for interface 0x0255e38d, otherwise ask the base class (Cast 0x7fa180).
#include "game/types.h"

struct Base_7fe7b0 {
    void* Cast(uint32_t typeID) const;   // 0x007fa180
};
struct Object_7fe7b0 : Base_7fe7b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007fe7b0
void* Object_7fe7b0::Cast(uint32_t typeID) const
{
    if (typeID != 0x0255e38d)
        return Base_7fe7b0::Cast(typeID);
    return (void*)this;
}
