// Cast helper (0x01030e60): ask a possibly null object for interface 0x03cdbbe9 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_1030e60 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x01030e60
void* CastTo_1030e60(Object_1030e60* p)
{
    return p ? p->Cast(0x03cdbbe9) : 0;
}
