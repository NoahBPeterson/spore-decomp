// Lookup and cast (0x00fec240): look up object 0x0347092e (0xb20c60) and, if found, ask it for interface
// 0x03470927 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec240 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec240* __stdcall Lookup_fec240(uint32_t id);   // 0x00b20c60

// @ 0x00fec240
void* LookupAs_fec240()
{
    Object_fec240* o = Lookup_fec240(0x0347092e);
    return o ? o->Cast(0x03470927) : 0;
}
