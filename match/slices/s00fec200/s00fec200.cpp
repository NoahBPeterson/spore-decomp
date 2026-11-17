// Lookup and cast (0x00fec200): look up object 0x035ed8f6 (0xb20c60) and, if found, ask it for interface
// 0x035ed8f0 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec200 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec200* __stdcall Lookup_fec200(uint32_t id);   // 0x00b20c60

// @ 0x00fec200
void* LookupAs_fec200()
{
    Object_fec200* o = Lookup_fec200(0x035ed8f6);
    return o ? o->Cast(0x035ed8f0) : 0;
}
