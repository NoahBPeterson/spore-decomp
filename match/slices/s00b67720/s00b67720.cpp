// Cast helper (0x00b67720): ask a possibly null object for interface 0x0e9cb8ba (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b67720 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b67720
void* CastTo_b67720(Object_b67720* p)
{
    return p ? p->Cast(0x0e9cb8ba) : 0;
}
