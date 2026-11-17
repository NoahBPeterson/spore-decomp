// Cast helper (0x01002df0): ask a possibly null object for interface 0x03275872 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_1002df0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x01002df0
void* CastTo_1002df0(Object_1002df0* p)
{
    return p ? p->Cast(0x03275872) : 0;
}
