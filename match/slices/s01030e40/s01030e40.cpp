// Cast helper (0x01030e40): ask a possibly null object for interface 0x02dd8c33 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_1030e40 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x01030e40
void* CastTo_1030e40(Object_1030e40* p)
{
    return p ? p->Cast(0x02dd8c33) : 0;
}
