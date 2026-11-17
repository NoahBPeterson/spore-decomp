// Cast helper (0x005994b0): ask a possibly null object for interface 0x0f15f4bd (Cast, vtable slot 3).
#include "game/types.h"

struct Object_5994b0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x005994b0
void* CastTo_5994b0(Object_5994b0* p)
{
    return p ? p->Cast(0x0f15f4bd) : 0;
}
