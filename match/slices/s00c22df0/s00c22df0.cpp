// Cast helper (0x00c22df0): ask a possibly null object for interface 0x0581147f (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c22df0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c22df0
void* CastTo_c22df0(Object_c22df0* p)
{
    return p ? p->Cast(0x0581147f) : 0;
}
