// Cast helper (0x00b67740): ask a possibly null object for interface 0xb033b403 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b67740 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b67740
void* CastTo_b67740(Object_b67740* p)
{
    return p ? p->Cast(0xb033b403) : 0;
}
