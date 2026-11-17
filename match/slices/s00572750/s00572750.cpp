// Cast helper (0x00572750): ask a possibly null object for interface 0x050a993c (Cast, vtable slot 3).
#include "game/types.h"

struct Object_572750 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00572750
void* CastTo_572750(Object_572750* p)
{
    return p ? p->Cast(0x050a993c) : 0;
}
