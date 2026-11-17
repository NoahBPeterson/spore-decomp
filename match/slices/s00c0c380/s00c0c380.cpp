// Cast helper (0x00c0c380): ask a possibly null object for interface 0x4f176642 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c0c380 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c0c380
void* CastTo_c0c380(Object_c0c380* p)
{
    return p ? p->Cast(0x4f176642) : 0;
}
