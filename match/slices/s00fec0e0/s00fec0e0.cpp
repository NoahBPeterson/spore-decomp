// Lookup and cast (0x00fec0e0): look up object 0x03960c0e (0xb20c60) and, if found, ask it for interface
// 0x03960c0a (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec0e0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec0e0* __stdcall Lookup_fec0e0(uint32_t id);   // 0x00b20c60

// @ 0x00fec0e0
void* LookupAs_fec0e0()
{
    Object_fec0e0* o = Lookup_fec0e0(0x03960c0e);
    return o ? o->Cast(0x03960c0a) : 0;
}
