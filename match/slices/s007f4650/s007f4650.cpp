// Cast (0x007f4650): return this for interface 0x1382be3e, otherwise ask the base class (Cast 0x989210).
#include "game/types.h"

struct Base_7f4650 {
    void* Cast(uint32_t typeID) const;   // 0x00989210
};
struct Object_7f4650 : Base_7f4650 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007f4650
void* Object_7f4650::Cast(uint32_t typeID) const
{
    if (typeID == 0x1382be3e)
        return (void*)this;
    return Base_7f4650::Cast(typeID);
}
