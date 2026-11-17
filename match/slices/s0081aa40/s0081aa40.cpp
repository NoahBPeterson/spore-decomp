// Cast (0x0081aa40): return this for interface 0x04c058cf, otherwise ask the base class (Cast 0x963f30).
#include "game/types.h"

struct Base_81aa40 {
    void* Cast(uint32_t typeID) const;   // 0x00963f30
};
struct Object_81aa40 : Base_81aa40 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0081aa40
void* Object_81aa40::Cast(uint32_t typeID) const
{
    if (typeID != 0x04c058cf)
        return Base_81aa40::Cast(typeID);
    return (void*)this;
}
