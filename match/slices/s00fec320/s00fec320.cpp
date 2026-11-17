// Lookup and cast (0x00fec320): look up object 0x02adedff (0xb20c60) and, if found, ask it for interface
// 0x02aeefff (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec320 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec320* __stdcall Lookup_fec320(uint32_t id);   // 0x00b20c60

// @ 0x00fec320
void* LookupAs_fec320()
{
    Object_fec320* o = Lookup_fec320(0x02adedff);
    return o ? o->Cast(0x02aeefff) : 0;
}
