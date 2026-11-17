// Cast helper (0x00ad7380): ask a possibly null object for interface 0x0398420d (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ad7380 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ad7380
void* CastTo_ad7380(Object_ad7380* p)
{
    return p ? p->Cast(0x0398420d) : 0;
}
