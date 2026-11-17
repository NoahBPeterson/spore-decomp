// Cast helper (0x00de46c0): ask the object held by a ref (possibly null) for interface 0xf5e905cd (Cast, slot 3).
#include "game/types.h"

struct Object_de46c0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_de46c0 {
    Object_de46c0* mpObject;
};

// @ 0x00de46c0
void* CastTo_de46c0(const Ref_de46c0& ref)
{
    Object_de46c0* p = ref.mpObject;
    return p ? p->Cast(0xf5e905cd) : 0;
}
