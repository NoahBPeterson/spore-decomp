// Cast helper (0x01002e10): ask the object held by a ref (possibly null) for interface 0x1007ae63 (Cast, slot 3).
#include "game/types.h"

struct Object_1002e10 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_1002e10 {
    Object_1002e10* mpObject;
};

// @ 0x01002e10
void* CastTo_1002e10(const Ref_1002e10& ref)
{
    Object_1002e10* p = ref.mpObject;
    return p ? p->Cast(0x1007ae63) : 0;
}
