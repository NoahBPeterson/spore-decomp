// Lookup and cast (0x00fec1e0): look up object 0x0347092d (0xb20c60) and, if found, ask it for interface
// 0x03470926 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec1e0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec1e0* __stdcall Lookup_fec1e0(uint32_t id);   // 0x00b20c60

// @ 0x00fec1e0
void* LookupAs_fec1e0()
{
    Object_fec1e0* o = Lookup_fec1e0(0x0347092d);
    return o ? o->Cast(0x03470926) : 0;
}
