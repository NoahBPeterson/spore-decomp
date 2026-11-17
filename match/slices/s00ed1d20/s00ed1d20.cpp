// Cast helper (0x00ed1d20): ask a possibly null object for interface 0x52deed23 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ed1d20 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ed1d20
void* CastTo_ed1d20(Object_ed1d20* p)
{
    return p ? p->Cast(0x52deed23) : 0;
}
