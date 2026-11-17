// Cast helper (0x00bd8460): ask a possibly null object for interface 0x0175cdc9 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_bd8460 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00bd8460
void* CastTo_bd8460(Object_bd8460* p)
{
    return p ? p->Cast(0x0175cdc9) : 0;
}
