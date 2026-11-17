// Cast helper (0x00b676c0): ask a possibly null object for interface 0x0629baec (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b676c0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b676c0
void* CastTo_b676c0(Object_b676c0* p)
{
    return p ? p->Cast(0x0629baec) : 0;
}
