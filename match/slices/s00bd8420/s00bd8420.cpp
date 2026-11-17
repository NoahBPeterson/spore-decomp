// Cast helper (0x00bd8420): ask the object held by a ref (possibly null) for interface 0x03d5c477 (Cast, slot 3).
#include "game/types.h"

struct Object_bd8420 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_bd8420 {
    Object_bd8420* mpObject;
};

// @ 0x00bd8420
void* CastTo_bd8420(const Ref_bd8420& ref)
{
    Object_bd8420* p = ref.mpObject;
    return p ? p->Cast(0x03d5c477) : 0;
}
