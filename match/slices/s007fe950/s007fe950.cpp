// Cast helper (0x007fe950): ask the object held by a ref (possibly null) for interface 0xee3f516e (Cast, slot 3).
#include "game/types.h"

struct Object_7fe950 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_7fe950 {
    Object_7fe950* mpObject;
};

// @ 0x007fe950
void* CastTo_7fe950(const Ref_7fe950& ref)
{
    Object_7fe950* p = ref.mpObject;
    return p ? p->Cast(0xee3f516e) : 0;
}
