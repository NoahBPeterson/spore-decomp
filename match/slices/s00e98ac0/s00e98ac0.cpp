// Cast helper (0x00e98ac0): ask a possibly null object for interface 0x0437443d (Cast, vtable slot 3).
#include "game/types.h"

struct Object_e98ac0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};

// @ 0x00e98ac0
void* CastTo_e98ac0(Object_e98ac0* p)
{
    return p ? p->Cast(0x0437443d) : 0;
}
