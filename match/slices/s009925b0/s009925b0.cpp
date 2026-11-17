// Cast (0x009925b0): return this for interface 0x8fb339cd, otherwise ask the base class (Cast 0x95f960).
#include "game/types.h"

struct Base_9925b0 {
    void* Cast(uint32_t typeID) const;   // 0x0095f960
};
struct Object_9925b0 : Base_9925b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x009925b0
void* Object_9925b0::Cast(uint32_t typeID) const
{
    if (typeID == 0x8fb339cd)
        return (void*)this;
    return Base_9925b0::Cast(typeID);
}
