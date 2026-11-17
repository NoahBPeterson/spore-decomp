// Cast helper (0x00ac8960): ask a possibly null object for interface 0xd0036e08 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ac8960 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ac8960
void* CastTo_ac8960(Object_ac8960* p)
{
    return p ? p->Cast(0xd0036e08) : 0;
}
