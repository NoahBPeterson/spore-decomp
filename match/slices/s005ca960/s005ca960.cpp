// Cast helper (0x005ca960): ask a possibly null object for interface 0x8ed27e7a (Cast, vtable slot 3).
#include "game/types.h"

struct Object_5ca960 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x005ca960
void* CastTo_5ca960(Object_5ca960* p)
{
    return p ? p->Cast(0x8ed27e7a) : 0;
}
