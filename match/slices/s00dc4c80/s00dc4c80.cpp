// Cast helper (0x00dc4c80): ask a possibly null object for interface 0x03df2cb9 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_dc4c80 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00dc4c80
void* CastTo_dc4c80(Object_dc4c80* p)
{
    return p ? p->Cast(0x03df2cb9) : 0;
}
