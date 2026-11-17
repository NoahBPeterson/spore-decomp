// Cast helper (0x00ac86f0): ask a possibly null object for interface 0x011c0ba3 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ac86f0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ac86f0
void* CastTo_ac86f0(Object_ac86f0* p)
{
    return p ? p->Cast(0x011c0ba3) : 0;
}
