// Cast (0x00807f10): return this for interface 0x03ec2e62, otherwise ask the base class (Cast 0x950eb0).
#include "game/types.h"

struct Base_807f10 {
    void* Cast(uint32_t typeID) const;   // 0x00950eb0
};
struct Object_807f10 : Base_807f10 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00807f10
void* Object_807f10::Cast(uint32_t typeID) const
{
    if (typeID == 0x03ec2e62)
        return (void*)this;
    return Base_807f10::Cast(typeID);
}
