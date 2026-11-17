// Cast helper (0x00c4f040): ask a possibly null object for interface 0x0422227d (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c4f040 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c4f040
void* CastTo_c4f040(Object_c4f040* p)
{
    return p ? p->Cast(0x0422227d) : 0;
}
