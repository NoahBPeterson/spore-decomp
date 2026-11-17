// Lookup and cast (0x00d0a610): look up object 0x02ee8ce8 (0xb20c60) and, if found, ask it for interface
// 0x02ee8eeb (Cast, vtable slot 3).
#include "game/types.h"

struct Object_d0a610 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_d0a610* __stdcall Lookup_d0a610(uint32_t id);   // 0x00b20c60

// @ 0x00d0a610
void* LookupAs_d0a610()
{
    Object_d0a610* o = Lookup_d0a610(0x02ee8ce8);
    return o ? o->Cast(0x02ee8eeb) : 0;
}
