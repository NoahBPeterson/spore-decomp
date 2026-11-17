// Cast helper (0x00b60a50): ask a possibly null object for interface 0x02a7ecd2 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b60a50 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b60a50
void* CastTo_b60a50(Object_b60a50* p)
{
    return p ? p->Cast(0x02a7ecd2) : 0;
}
