// Cast helper (0x00cf7d20): ask a possibly null object for interface 0x1007ae63 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_cf7d20 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00cf7d20
void* CastTo_cf7d20(Object_cf7d20* p)
{
    return p ? p->Cast(0x1007ae63) : 0;
}
