// Cast helper (0x00d724f0): ask a possibly null object for interface 0x00e69e1e (Cast, vtable slot 1).
#include "game/types.h"

struct Object_d724f0 {
    virtual void v0();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00d724f0
void* CastTo_d724f0(Object_d724f0* p)
{
    return p ? p->Cast(0x00e69e1e) : 0;
}
