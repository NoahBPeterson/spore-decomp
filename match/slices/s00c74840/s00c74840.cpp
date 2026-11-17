// Cast (0x00c74840): return this for interface 0x04e3faaf, otherwise ask the base class (Cast 0xc68f30).
#include "game/types.h"

struct Base_c74840 {
    void* Cast(uint32_t typeID) const;   // 0x00c68f30
};
struct Object_c74840 : Base_c74840 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c74840
void* Object_c74840::Cast(uint32_t typeID) const
{
    if (typeID == 0x04e3faaf)
        return (void*)this;
    return Base_c74840::Cast(typeID);
}
