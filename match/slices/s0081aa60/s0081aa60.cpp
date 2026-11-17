// Cast (0x0081aa60): return this for interface 0x04c6ec97, otherwise ask the base class (Cast 0x963f30).
#include "game/types.h"

struct Base_81aa60 {
    void* Cast(uint32_t typeID) const;   // 0x00963f30
};
struct Object_81aa60 : Base_81aa60 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0081aa60
void* Object_81aa60::Cast(uint32_t typeID) const
{
    if (typeID != 0x04c6ec97)
        return Base_81aa60::Cast(typeID);
    return (void*)this;
}
