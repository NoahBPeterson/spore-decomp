// Cast helper (0x00b18e20): ask a possibly null object for interface 0x02ee8eeb (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b18e20 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b18e20
void* CastTo_b18e20(Object_b18e20* p)
{
    return p ? p->Cast(0x02ee8eeb) : 0;
}
