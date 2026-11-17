// Cast helper (0x005ff6a0): ask a possibly null object for interface 0x0f00a8a0 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_5ff6a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x005ff6a0
void* CastTo_5ff6a0(Object_5ff6a0* p)
{
    return p ? p->Cast(0x0f00a8a0) : 0;
}
