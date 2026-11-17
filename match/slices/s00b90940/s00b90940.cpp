// Cast helper (0x00b90940): ask the object held by a ref (possibly null) for interface 0x52aa6117 (Cast, slot 3).
#include "game/types.h"

struct Object_b90940 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_b90940 {
    Object_b90940* mpObject;
};

// @ 0x00b90940
void* CastTo_b90940(const Ref_b90940& ref)
{
    Object_b90940* p = ref.mpObject;
    return p ? p->Cast(0x52aa6117) : 0;
}
