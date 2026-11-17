// Cast helper (0x00ad7360): ask the object held by a ref (possibly null) for interface 0x01186577 (Cast, slot 3).
#include "game/types.h"

struct Object_ad7360 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_ad7360 {
    Object_ad7360* mpObject;
};

// @ 0x00ad7360
void* CastTo_ad7360(const Ref_ad7360& ref)
{
    Object_ad7360* p = ref.mpObject;
    return p ? p->Cast(0x01186577) : 0;
}
