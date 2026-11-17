// Cast helper (0x00b5cc20): ask a possibly null object for interface 0x011966ed (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b5cc20 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00b5cc20
void* CastTo_b5cc20(Object_b5cc20* p)
{
    return p ? p->Cast(0x011966ed) : 0;
}
