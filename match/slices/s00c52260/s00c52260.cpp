// Cast helper (0x00c52260): ask a possibly null object for interface 0xd0036e08 (Cast, vtable slot 2).
#include "game/types.h"

struct Object_c52260 {
    virtual void v0();
    virtual void v1();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c52260
void* CastTo_c52260(Object_c52260* p)
{
    return p ? p->Cast(0xd0036e08) : 0;
}
