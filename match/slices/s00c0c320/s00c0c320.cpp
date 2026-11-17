// Cast helper (0x00c0c320): ask the object held by a ref (possibly null) for interface 0x013f94d4 (Cast, slot 3).
#include "game/types.h"

struct Object_c0c320 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_c0c320 {
    Object_c0c320* mpObject;
};

// @ 0x00c0c320
void* CastTo_c0c320(const Ref_c0c320& ref)
{
    Object_c0c320* p = ref.mpObject;
    return p ? p->Cast(0x013f94d4) : 0;
}
