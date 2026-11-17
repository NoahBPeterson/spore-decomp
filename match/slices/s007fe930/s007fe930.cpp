// Cast (0x007fe930): return this for interface 0x025611e9, otherwise ask the base class (Cast 0x7fa180).
#include "game/types.h"

struct Base_7fe930 {
    void* Cast(uint32_t typeID) const;   // 0x007fa180
};
struct Object_7fe930 : Base_7fe930 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007fe930
void* Object_7fe930::Cast(uint32_t typeID) const
{
    if (typeID != 0x025611e9)
        return Base_7fe930::Cast(typeID);
    return (void*)this;
}
