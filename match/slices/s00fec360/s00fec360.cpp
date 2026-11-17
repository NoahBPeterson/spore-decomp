// Lookup and cast (0x00fec360): look up object 0x04622285 (0xb20c60) and, if found, ask it for interface
// 0x0462227e (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec360 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec360* __stdcall Lookup_fec360(uint32_t id);   // 0x00b20c60

// @ 0x00fec360
void* LookupAs_fec360()
{
    Object_fec360* o = Lookup_fec360(0x04622285);
    return o ? o->Cast(0x0462227e) : 0;
}
