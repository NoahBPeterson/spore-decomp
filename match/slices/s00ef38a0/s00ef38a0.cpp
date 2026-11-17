// Cast helper (0x00ef38a0): ask the object held by a ref (possibly null) for interface 0x0106f146 (Cast, slot 3).
#include "game/types.h"

struct Object_ef38a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_ef38a0 {
    Object_ef38a0* mpObject;
};

// @ 0x00ef38a0
void* CastTo_ef38a0(const Ref_ef38a0& ref)
{
    Object_ef38a0* p = ref.mpObject;
    return p ? p->Cast(0x0106f146) : 0;
}
