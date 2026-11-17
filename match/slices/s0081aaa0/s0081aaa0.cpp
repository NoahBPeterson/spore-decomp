// Cast (0x0081aaa0): return this for interface 0x04c058d5, otherwise ask the base class (Cast 0x963f30).
#include "game/types.h"

struct Base_81aaa0 {
    void* Cast(uint32_t typeID) const;   // 0x00963f30
};
struct Object_81aaa0 : Base_81aaa0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0081aaa0
void* Object_81aaa0::Cast(uint32_t typeID) const
{
    if (typeID != 0x04c058d5)
        return Base_81aaa0::Cast(typeID);
    return (void*)this;
}
