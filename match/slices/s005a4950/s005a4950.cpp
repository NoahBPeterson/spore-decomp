// Cast helper (0x005a4950): ask the object held by a ref (possibly null) for interface 0xd0d22119 (Cast, slot 3).
#include "game/types.h"

struct Object_5a4950 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_5a4950 {
    Object_5a4950* mpObject;
};

// @ 0x005a4950
void* CastTo_5a4950(const Ref_5a4950& ref)
{
    Object_5a4950* p = ref.mpObject;
    return p ? p->Cast(0xd0d22119) : 0;
}
