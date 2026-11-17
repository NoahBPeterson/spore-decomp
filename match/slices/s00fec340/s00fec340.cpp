// Lookup and cast (0x00fec340): look up object 0x0447092d (0xb20c60) and, if found, ask it for interface
// 0x04470926 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec340 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec340* __stdcall Lookup_fec340(uint32_t id);   // 0x00b20c60

// @ 0x00fec340
void* LookupAs_fec340()
{
    Object_fec340* o = Lookup_fec340(0x0447092d);
    return o ? o->Cast(0x04470926) : 0;
}
