// Cast helper (0x00ac8710): ask a possibly null object for interface 0x0116dd1b (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ac8710 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ac8710
void* CastTo_ac8710(Object_ac8710* p)
{
    return p ? p->Cast(0x0116dd1b) : 0;
}
