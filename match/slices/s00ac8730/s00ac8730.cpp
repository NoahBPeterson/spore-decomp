// Cast helper (0x00ac8730): ask a possibly null object for interface 0x4f396a66 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_ac8730 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00ac8730
void* CastTo_ac8730(Object_ac8730* p)
{
    return p ? p->Cast(0x4f396a66) : 0;
}
