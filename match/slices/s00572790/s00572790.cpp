// Cast helper (0x00572790): ask a possibly null object for interface 0x029da727 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_572790 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00572790
void* CastTo_572790(Object_572790* p)
{
    return p ? p->Cast(0x029da727) : 0;
}
