// Cast helper (0x00e07e50): ask the object held by a ref (possibly null) for interface 0x0422227d (Cast, slot 3).
#include "game/types.h"

struct Object_e07e50 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_e07e50 {
    Object_e07e50* mpObject;
};

// @ 0x00e07e50
void* CastTo_e07e50(const Ref_e07e50& ref)
{
    Object_e07e50* p = ref.mpObject;
    return p ? p->Cast(0x0422227d) : 0;
}
