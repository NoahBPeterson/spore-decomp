// Cast helper (0x005767d0): ask the object held by a ref (possibly null) for interface 0x03a3aa3a (Cast, slot 3).
#include "game/types.h"

struct Object_5767d0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_5767d0 {
    Object_5767d0* mpObject;
};

// @ 0x005767d0
void* CastTo_5767d0(const Ref_5767d0& ref)
{
    Object_5767d0* p = ref.mpObject;
    return p ? p->Cast(0x03a3aa3a) : 0;
}
