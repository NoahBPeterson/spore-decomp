// Cast helper (0x00b67700): ask a possibly null object for interface 0x03960c0a (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b67700 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b67700
void* CastTo_b67700(Object_b67700* p)
{
    return p ? p->Cast(0x03960c0a) : 0;
}
