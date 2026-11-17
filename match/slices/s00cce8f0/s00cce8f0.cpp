// Cast helper (0x00cce8f0): ask a possibly null object for interface 0x4ffcdeda (Cast, vtable slot 3).
#include "game/types.h"

struct Object_cce8f0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00cce8f0
void* CastTo_cce8f0(Object_cce8f0* p)
{
    return p ? p->Cast(0x4ffcdeda) : 0;
}
