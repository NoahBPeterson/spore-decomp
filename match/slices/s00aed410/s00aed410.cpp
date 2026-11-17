// Cast helper (0x00aed410): ask a possibly null object for interface 0x035988ee (Cast, vtable slot 3).
#include "game/types.h"

struct Object_aed410 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00aed410
void* CastTo_aed410(Object_aed410* p)
{
    return p ? p->Cast(0x035988ee) : 0;
}
