// Cast helper (0x005c2570): ask the object held by a ref (possibly null) for interface 0x8ed27e7a (Cast, slot 3).
#include "game/types.h"

struct Object_5c2570 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_5c2570 {
    Object_5c2570* mpObject;
};

// @ 0x005c2570
void* CastTo_5c2570(const Ref_5c2570& ref)
{
    Object_5c2570* p = ref.mpObject;
    return p ? p->Cast(0x8ed27e7a) : 0;
}
