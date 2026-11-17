// Lookup and cast (0x00fec3a0): look up object 0x046332a5 (0xb20c60) and, if found, ask it for interface
// 0x0463329e (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec3a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec3a0* __stdcall Lookup_fec3a0(uint32_t id);   // 0x00b20c60

// @ 0x00fec3a0
void* LookupAs_fec3a0()
{
    Object_fec3a0* o = Lookup_fec3a0(0x046332a5);
    return o ? o->Cast(0x0463329e) : 0;
}
