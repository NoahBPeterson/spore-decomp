// Cast helper (0x00c375b0): ask a possibly null object for interface 0x303154cc (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c375b0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c375b0
void* CastTo_c375b0(Object_c375b0* p)
{
    return p ? p->Cast(0x303154cc) : 0;
}
