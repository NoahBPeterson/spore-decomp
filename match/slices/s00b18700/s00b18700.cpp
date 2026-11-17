// Cast helper (0x00b18700): ask a possibly null object for interface 0x0116d858 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b18700 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b18700
void* CastTo_b18700(Object_b18700* p)
{
    return p ? p->Cast(0x0116d858) : 0;
}
