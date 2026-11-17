// Cast helper (0x00b18720): ask a possibly null object for interface 0x0436f315 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b18720 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b18720
void* CastTo_b18720(Object_b18720* p)
{
    return p ? p->Cast(0x0436f315) : 0;
}
