// Cast (0x007f3c70): return this for interface 0x9fedbcdb, otherwise ask the base class (Cast 0x95f960).
#include "game/types.h"

struct Base_7f3c70 {
    void* Cast(uint32_t typeID) const;   // 0x0095f960
};
struct Object_7f3c70 : Base_7f3c70 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007f3c70
void* Object_7f3c70::Cast(uint32_t typeID) const
{
    if (typeID == 0x9fedbcdb)
        return (void*)this;
    return Base_7f3c70::Cast(typeID);
}
