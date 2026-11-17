// Cast (0x00ef3880): return this for interface 0xfcb7f2be, otherwise ask the base class (Cast 0x657340).
#include "game/types.h"

struct Base_ef3880 {
    void* Cast(uint32_t typeID) const;   // 0x00657340
};
struct Object_ef3880 : Base_ef3880 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ef3880
void* Object_ef3880::Cast(uint32_t typeID) const
{
    if (typeID == 0xfcb7f2be)
        return (void*)this;
    return Base_ef3880::Cast(typeID);
}
