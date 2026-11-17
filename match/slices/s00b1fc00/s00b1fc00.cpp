// Cast helper (0x00b1fc00): ask a possibly null object for interface 0x01b92b27 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b1fc00 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b1fc00
void* CastTo_b1fc00(Object_b1fc00* p)
{
    return p ? p->Cast(0x01b92b27) : 0;
}
