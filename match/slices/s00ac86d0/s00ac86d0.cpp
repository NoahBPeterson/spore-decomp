// Cast helper (0x00ac86d0): ask a possibly null object for interface 0xee9b2232 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ac86d0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ac86d0
void* CastTo_ac86d0(Object_ac86d0* p)
{
    return p ? p->Cast(0xee9b2232) : 0;
}
