// Cast helper (0x00d546f0): ask a possibly null object for interface 0x0436f315 (Cast, vtable slot 2).
#include "game/types.h"

struct Object_d546f0 {
    virtual void v0();
    virtual void v1();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00d546f0
void* CastTo_d546f0(Object_d546f0* p)
{
    return p ? p->Cast(0x0436f315) : 0;
}
