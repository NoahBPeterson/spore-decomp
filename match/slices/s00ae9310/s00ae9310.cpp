// Cast helper (0x00ae9310): ask a possibly null object for interface 0x901f1362 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ae9310 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ae9310
void* CastTo_ae9310(Object_ae9310* p)
{
    return p ? p->Cast(0x901f1362) : 0;
}
