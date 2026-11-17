// Cast helper (0x00c9f060): ask a possibly null object for interface 0x017f243b (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c9f060 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c9f060
void* CastTo_c9f060(Object_c9f060* p)
{
    return p ? p->Cast(0x017f243b) : 0;
}
