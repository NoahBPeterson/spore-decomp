// Cast helper (0x00c37590): ask a possibly null object for interface 0x303154cd (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c37590 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c37590
void* CastTo_c37590(Object_c37590* p)
{
    return p ? p->Cast(0x303154cd) : 0;
}
