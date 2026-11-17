// Lookup and cast (0x00c716d0): look up object 0x044462a6 (0xb20c60) and, if found, ask it for interface
// 0x044462a6 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c716d0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_c716d0* __stdcall Lookup_c716d0(uint32_t id);   // 0x00b20c60

// @ 0x00c716d0
void* LookupAs_c716d0()
{
    Object_c716d0* o = Lookup_c716d0(0x044462a6);
    return o ? o->Cast(0x044462a6) : 0;
}
