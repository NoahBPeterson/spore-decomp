// Cast helper (0x00d54710): ask the object held by a ref (possibly null) for interface 0x0436f315 (Cast, slot 2).
#include "game/types.h"

struct Object_d54710 {
    virtual void v0();
    virtual void v1();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_d54710 {
    Object_d54710* mpObject;
};

// @ 0x00d54710
void* CastTo_d54710(const Ref_d54710& ref)
{
    Object_d54710* p = ref.mpObject;
    return p ? p->Cast(0x0436f315) : 0;
}
