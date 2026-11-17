// Cast helper (0x0081d780): ask the object held by a ref (possibly null) for interface 0xcf428691 (Cast, slot 3).
#include "game/types.h"

struct Object_81d780 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_81d780 {
    Object_81d780* mpObject;
};

// @ 0x0081d780
void* CastTo_81d780(const Ref_81d780& ref)
{
    Object_81d780* p = ref.mpObject;
    return p ? p->Cast(0xcf428691) : 0;
}
