// Cast helper (0x00b2a390): ask a possibly null object for interface 0xaeb336b4 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b2a390 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b2a390
void* CastTo_b2a390(Object_b2a390* p)
{
    return p ? p->Cast(0xaeb336b4) : 0;
}
