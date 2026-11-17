// Cast helper (0x00ac7880): ask a possibly null object for interface 0x4f396a66 (Cast, vtable slot 5).
#include "game/types.h"

struct Object_ac7880 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ac7880
void* CastTo_ac7880(Object_ac7880* p)
{
    return p ? p->Cast(0x4f396a66) : 0;
}
