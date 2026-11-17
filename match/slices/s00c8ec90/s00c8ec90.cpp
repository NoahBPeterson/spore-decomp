// Cast helper (0x00c8ec90): ask the object held by a ref (possibly null) for interface 0x03a25119 (Cast, slot 3).
#include "game/types.h"

struct Object_c8ec90 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_c8ec90 {
    Object_c8ec90* mpObject;
};

// @ 0x00c8ec90
void* CastTo_c8ec90(const Ref_c8ec90& ref)
{
    Object_c8ec90* p = ref.mpObject;
    return p ? p->Cast(0x03a25119) : 0;
}
