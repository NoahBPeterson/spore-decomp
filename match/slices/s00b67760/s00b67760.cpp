// Cast helper (0x00b67760): ask the object held by a ref (possibly null) for interface 0x0e9cb8ba (Cast, slot 3).
#include "game/types.h"

struct Object_b67760 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_b67760 {
    Object_b67760* mpObject;
};

// @ 0x00b67760
void* CastTo_b67760(const Ref_b67760& ref)
{
    Object_b67760* p = ref.mpObject;
    return p ? p->Cast(0x0e9cb8ba) : 0;
}
