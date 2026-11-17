// Cast (0x00c5af10): return this for interface 0x0397bff2, otherwise ask the base class (Cast 0xc44a00).
#include "game/types.h"

struct Base_c5af10 {
    void* Cast(uint32_t typeID) const;   // 0x00c44a00
};
struct Object_c5af10 : Base_c5af10 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c5af10
void* Object_c5af10::Cast(uint32_t typeID) const
{
    if (typeID != 0x0397bff2)
        return Base_c5af10::Cast(typeID);
    return (void*)this;
}
