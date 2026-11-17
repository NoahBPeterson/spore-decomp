// Cast helper (0x00ed4f50): ask the object held by a ref (possibly null) for interface 0x0774c96f (Cast, slot 3).
#include "game/types.h"

struct Object_ed4f50 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_ed4f50 {
    Object_ed4f50* mpObject;
};

// @ 0x00ed4f50
void* CastTo_ed4f50(const Ref_ed4f50& ref)
{
    Object_ed4f50* p = ref.mpObject;
    return p ? p->Cast(0x0774c96f) : 0;
}
