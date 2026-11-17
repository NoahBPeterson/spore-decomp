// Cast helper (0x00ae6740): ask a possibly null object for interface 0x013f94d4 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ae6740 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ae6740
void* CastTo_ae6740(Object_ae6740* p)
{
    return p ? p->Cast(0x013f94d4) : 0;
}
