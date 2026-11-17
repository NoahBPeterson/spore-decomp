// Lookup and cast (0x00b938b0): look up object 0x036be27e (0xb20c60) and, if found, ask it for interface
// 0x036be278 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b938b0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_b938b0* __stdcall Lookup_b938b0(uint32_t id);   // 0x00b20c60

// @ 0x00b938b0
void* LookupAs_b938b0()
{
    Object_b938b0* o = Lookup_b938b0(0x036be27e);
    return o ? o->Cast(0x036be278) : 0;
}
