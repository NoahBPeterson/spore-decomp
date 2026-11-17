// Cast helper (0x010536a0): ask a possibly null object for interface 0x114242e6 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_10536a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x010536a0
void* CastTo_10536a0(Object_10536a0* p)
{
    return p ? p->Cast(0x114242e6) : 0;
}
