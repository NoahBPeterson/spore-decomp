// Cast helper (0x00972db0): ask the object held by a ref (possibly null) for interface 0x6ec581fd (Cast, slot 3).
#include "game/types.h"

struct Object_972db0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_972db0 {
    Object_972db0* mpObject;
};

// @ 0x00972db0
void* CastTo_972db0(const Ref_972db0& ref)
{
    Object_972db0* p = ref.mpObject;
    return p ? p->Cast(0x6ec581fd) : 0;
}
