// Cast helper (0x00e19cd0): ask a possibly null object for interface 0x02aa5ada (Cast, vtable slot 3).
#include "game/types.h"

struct Object_e19cd0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00e19cd0
void* CastTo_e19cd0(Object_e19cd0* p)
{
    return p ? p->Cast(0x02aa5ada) : 0;
}
