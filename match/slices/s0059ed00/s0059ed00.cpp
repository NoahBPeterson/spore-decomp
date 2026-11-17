// Cast helper (0x0059ed00): ask a possibly null object for interface 0x053eb526 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_59ed00 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x0059ed00
void* CastTo_59ed00(Object_59ed00* p)
{
    return p ? p->Cast(0x053eb526) : 0;
}
