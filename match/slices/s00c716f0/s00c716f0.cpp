// Lookup and cast (0x00c716f0): look up object 0x032f9778 (0xb20c60) and, if found, ask it for interface
// 0x032f9777 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_c716f0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_c716f0* __stdcall Lookup_c716f0(uint32_t id);   // 0x00b20c60

// @ 0x00c716f0
void* LookupAs_c716f0()
{
    Object_c716f0* o = Lookup_c716f0(0x032f9778);
    return o ? o->Cast(0x032f9777) : 0;
}
