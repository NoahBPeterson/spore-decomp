// Cast helper (0x00fe7290): ask a possibly null object for interface 0x303154cb (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fe7290 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00fe7290
void* CastTo_fe7290(Object_fe7290* p)
{
    return p ? p->Cast(0x303154cb) : 0;
}
