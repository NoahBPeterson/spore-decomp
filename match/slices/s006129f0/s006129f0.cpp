// Cast (0x006129f0): return this for interface 0xaaff1cde, otherwise ask the base class (Cast 0x6abe20).
#include "game/types.h"

struct Base_6129f0 {
    void* Cast(uint32_t typeID) const;   // 0x006abe20
};
struct Object_6129f0 : Base_6129f0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006129f0
void* Object_6129f0::Cast(uint32_t typeID) const
{
    if (typeID == 0xaaff1cde)
        return (void*)this;
    return Base_6129f0::Cast(typeID);
}
