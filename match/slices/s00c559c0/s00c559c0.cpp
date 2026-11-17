// Cast helper (0x00c559c0): ask a possibly null object for interface 0x02afd27e (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c559c0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c559c0
void* CastTo_c559c0(Object_c559c0* p)
{
    return p ? p->Cast(0x02afd27e) : 0;
}
