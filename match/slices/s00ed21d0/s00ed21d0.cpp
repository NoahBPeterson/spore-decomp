// Cast helper (0x00ed21d0): ask the object held by a ref (possibly null) for interface 0x0722de63 (Cast, slot 3).
#include "game/types.h"

struct Object_ed21d0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_ed21d0 {
    Object_ed21d0* mpObject;
};

// @ 0x00ed21d0
void* CastTo_ed21d0(const Ref_ed21d0& ref)
{
    Object_ed21d0* p = ref.mpObject;
    return p ? p->Cast(0x0722de63) : 0;
}
