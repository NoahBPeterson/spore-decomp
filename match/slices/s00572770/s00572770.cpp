// Cast helper (0x00572770): ask the object held by a ref (possibly null) for interface 0x050a993c (Cast, slot 3).
#include "game/types.h"

struct Object_572770 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_572770 {
    Object_572770* mpObject;
};

// @ 0x00572770
void* CastTo_572770(const Ref_572770& ref)
{
    Object_572770* p = ref.mpObject;
    return p ? p->Cast(0x050a993c) : 0;
}
