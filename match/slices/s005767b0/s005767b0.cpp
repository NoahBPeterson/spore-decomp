// Cast helper (0x005767b0): ask the object held by a ref (possibly null) for interface 0x72d44e3a (Cast, slot 3).
#include "game/types.h"

struct Object_5767b0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_5767b0 {
    Object_5767b0* mpObject;
};

// @ 0x005767b0
void* CastTo_5767b0(const Ref_5767b0& ref)
{
    Object_5767b0* p = ref.mpObject;
    return p ? p->Cast(0x72d44e3a) : 0;
}
