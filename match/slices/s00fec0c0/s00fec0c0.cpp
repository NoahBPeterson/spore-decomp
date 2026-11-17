// Lookup and cast (0x00fec0c0): look up object 0x02afd284 (0xb20c60) and, if found, ask it for interface
// 0x02afd27e (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec0c0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec0c0* __stdcall Lookup_fec0c0(uint32_t id);   // 0x00b20c60

// @ 0x00fec0c0
void* LookupAs_fec0c0()
{
    Object_fec0c0* o = Lookup_fec0c0(0x02afd284);
    return o ? o->Cast(0x02afd27e) : 0;
}
