// Cast helper (0x00cf1090): ask a possibly null object for interface 0x102a041a (Cast, vtable slot 3).
#include "game/types.h"

struct Object_cf1090 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00cf1090
void* CastTo_cf1090(Object_cf1090* p)
{
    return p ? p->Cast(0x102a041a) : 0;
}
