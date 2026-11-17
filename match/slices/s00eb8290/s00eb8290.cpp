// Cast (0x00eb8290): return this for interface 0x66bf88e2, otherwise ask the base class (Cast 0x657340).
#include "game/types.h"

struct Base_eb8290 {
    void* Cast(uint32_t typeID) const;   // 0x00657340
};
struct Object_eb8290 : Base_eb8290 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00eb8290
void* Object_eb8290::Cast(uint32_t typeID) const
{
    if (typeID == 0x66bf88e2)
        return (void*)this;
    return Base_eb8290::Cast(typeID);
}
