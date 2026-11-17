// Cast helper (0x00e34ef0): ask a possibly null object for interface 0x03d5c477 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_e34ef0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00e34ef0
void* CastTo_e34ef0(Object_e34ef0* p)
{
    return p ? p->Cast(0x03d5c477) : 0;
}
