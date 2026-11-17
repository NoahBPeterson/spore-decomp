// Cast (0x00c748b0): return this for interface 0x02dd8c33, otherwise ask the base class (Cast 0xc68f30).
#include "game/types.h"

struct Base_c748b0 {
    void* Cast(uint32_t typeID) const;   // 0x00c68f30
};
struct Object_c748b0 : Base_c748b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c748b0
void* Object_c748b0::Cast(uint32_t typeID) const
{
    if (typeID == 0x02dd8c33)
        return (void*)this;
    return Base_c748b0::Cast(typeID);
}
