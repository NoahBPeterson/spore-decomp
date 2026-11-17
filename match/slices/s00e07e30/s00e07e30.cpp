// Cast helper (0x00e07e30): ask a possibly null object for interface 0x0422227e (Cast, vtable slot 3).
#include "game/types.h"

struct Object_e07e30 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00e07e30
void* CastTo_e07e30(Object_e07e30* p)
{
    return p ? p->Cast(0x0422227e) : 0;
}
