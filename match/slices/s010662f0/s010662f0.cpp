// Cast helper (0x010662f0): ask a possibly null object for interface 0x03e4353b (Cast, vtable slot 3).
#include "game/types.h"

struct Object_10662f0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x010662f0
void* CastTo_10662f0(Object_10662f0* p)
{
    return p ? p->Cast(0x03e4353b) : 0;
}
