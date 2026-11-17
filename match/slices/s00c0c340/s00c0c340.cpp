// Cast helper (0x00c0c340): ask a possibly null object for interface 0x070704db (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c0c340 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c0c340
void* CastTo_c0c340(Object_c0c340* p)
{
    return p ? p->Cast(0x070704db) : 0;
}
