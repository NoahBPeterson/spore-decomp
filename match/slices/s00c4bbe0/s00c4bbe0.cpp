// Cast helper (0x00c4bbe0): ask a possibly null object for interface 0xce9f6639 (Cast, vtable slot 2).
#include "game/types.h"

struct Object_c4bbe0 {
    virtual void v0();
    virtual void v1();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c4bbe0
void* CastTo_c4bbe0(Object_c4bbe0* p)
{
    return p ? p->Cast(0xce9f6639) : 0;
}
