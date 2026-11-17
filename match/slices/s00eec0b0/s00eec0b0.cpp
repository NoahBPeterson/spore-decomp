// Cast helper (0x00eec0b0): ask a possibly null object for interface 0x074e0069 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_eec0b0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00eec0b0
void* CastTo_eec0b0(Object_eec0b0* p)
{
    return p ? p->Cast(0x074e0069) : 0;
}
