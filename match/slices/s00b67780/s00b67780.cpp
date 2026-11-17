// Cast helper (0x00b67780): ask the object held by a ref (possibly null) for interface 0x0436f315 (Cast, slot 3).
#include "game/types.h"

struct Object_b67780 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_b67780 {
    Object_b67780* mpObject;
};

// @ 0x00b67780
void* CastTo_b67780(const Ref_b67780& ref)
{
    Object_b67780* p = ref.mpObject;
    return p ? p->Cast(0x0436f315) : 0;
}
