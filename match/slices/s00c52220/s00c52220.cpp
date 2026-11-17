// Cast helper (0x00c52220): ask a possibly null object for interface 0x02dd8c33 (Cast, vtable slot 2).
#include "game/types.h"

struct Object_c52220 {
    virtual void v0();
    virtual void v1();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00c52220
void* CastTo_c52220(Object_c52220* p)
{
    return p ? p->Cast(0x02dd8c33) : 0;
}
