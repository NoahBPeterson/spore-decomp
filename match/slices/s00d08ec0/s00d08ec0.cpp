// Cast helper (0x00d08ec0): ask the object held by a ref (possibly null) for interface 0xee9b2232 (Cast, slot 3).
#include "game/types.h"

struct Object_d08ec0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_d08ec0 {
    Object_d08ec0* mpObject;
};

// @ 0x00d08ec0
void* CastTo_d08ec0(const Ref_d08ec0& ref)
{
    Object_d08ec0* p = ref.mpObject;
    return p ? p->Cast(0xee9b2232) : 0;
}
