// Cast helper (0x005ff680): ask a possibly null object for interface 0x2ef0c885 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_5ff680 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x005ff680
void* CastTo_5ff680(Object_5ff680* p)
{
    return p ? p->Cast(0x2ef0c885) : 0;
}
