// Cast helper (0x00efc830): ask a possibly null object for interface 0x07b38ba7 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_efc830 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00efc830
void* CastTo_efc830(Object_efc830* p)
{
    return p ? p->Cast(0x07b38ba7) : 0;
}
