// Cast helper (0x00c52240): ask a possibly null object for interface 0xaeb336b4 (Cast, vtable slot 2).
#include "game/types.h"

struct Object_c52240 {
    virtual void v0();
    virtual void v1();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c52240
void* CastTo_c52240(Object_c52240* p)
{
    return p ? p->Cast(0xaeb336b4) : 0;
}
