// Cast helper (0x00576790): ask the object held by a ref (possibly null) for interface 0x2f4e681b (Cast, slot 3).
#include "game/types.h"

struct Object_576790 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_576790 {
    Object_576790* mpObject;
};

// @ 0x00576790
void* CastTo_576790(const Ref_576790& ref)
{
    Object_576790* p = ref.mpObject;
    return p ? p->Cast(0x2f4e681b) : 0;
}
