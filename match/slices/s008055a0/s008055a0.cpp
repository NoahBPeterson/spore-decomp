// Cast helper (0x008055a0): ask a possibly null object for interface 0x6ec581fd (Cast, vtable slot 3).
#include "game/types.h"

struct Object_8055a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x008055a0
void* CastTo_8055a0(Object_8055a0* p)
{
    return p ? p->Cast(0x6ec581fd) : 0;
}
