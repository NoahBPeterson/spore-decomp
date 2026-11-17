// Cast helper (0x00b676e0): ask a possibly null object for interface 0x00ee02c7 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b676e0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b676e0
void* CastTo_b676e0(Object_b676e0* p)
{
    return p ? p->Cast(0x00ee02c7) : 0;
}
