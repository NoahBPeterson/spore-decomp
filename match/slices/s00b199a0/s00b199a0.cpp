// Cast helper (0x00b199a0): ask the object held by a ref (possibly null) for interface 0x017f243b (Cast, slot 3).
#include "game/types.h"

struct Object_b199a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_b199a0 {
    Object_b199a0* mpObject;
};

// @ 0x00b199a0
void* CastTo_b199a0(const Ref_b199a0& ref)
{
    Object_b199a0* p = ref.mpObject;
    return p ? p->Cast(0x017f243b) : 0;
}
