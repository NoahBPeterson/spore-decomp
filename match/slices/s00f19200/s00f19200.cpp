// Cast helper (0x00f19200): ask a possibly null object for interface 0xce9f6639 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_f19200 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00f19200
void* CastTo_f19200(Object_f19200* p)
{
    return p ? p->Cast(0xce9f6639) : 0;
}
