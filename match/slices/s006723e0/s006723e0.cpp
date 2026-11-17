// Cast helper (0x006723e0): ask a possibly null object for interface 0xeef3af8c (Cast, vtable slot 3).
#include "game/types.h"

struct Object_6723e0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x006723e0
void* CastTo_6723e0(Object_6723e0* p)
{
    return p ? p->Cast(0xeef3af8c) : 0;
}
