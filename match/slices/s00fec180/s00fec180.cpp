// Lookup and cast (0x00fec180): look up object 0x02f99994 (0xb20c60) and, if found, ask it for interface
// 0x02f9998c (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec180 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec180* __stdcall Lookup_fec180(uint32_t id);   // 0x00b20c60

// @ 0x00fec180
void* LookupAs_fec180()
{
    Object_fec180* o = Lookup_fec180(0x02f99994);
    return o ? o->Cast(0x02f9998c) : 0;
}
