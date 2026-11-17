// Cast helper (0x00da8280): ask the object held by a ref (possibly null) for interface 0x4f396a66 (Cast, slot 5).
#include "game/types.h"

struct Object_da8280 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_da8280 {
    Object_da8280* mpObject;
};

// @ 0x00da8280
void* CastTo_da8280(const Ref_da8280& ref)
{
    Object_da8280* p = ref.mpObject;
    return p ? p->Cast(0x4f396a66) : 0;
}
