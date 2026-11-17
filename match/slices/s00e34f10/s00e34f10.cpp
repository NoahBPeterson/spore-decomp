// Cast helper (0x00e34f10): ask a possibly null object for interface 0x0403df5f (Cast, vtable slot 3).
#include "game/types.h"

struct Object_e34f10 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00e34f10
void* CastTo_e34f10(Object_e34f10* p)
{
    return p ? p->Cast(0x0403df5f) : 0;
}
