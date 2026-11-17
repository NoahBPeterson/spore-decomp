// Lookup and cast (0x00fec380): look up object 0x04633285 (0xb20c60) and, if found, ask it for interface
// 0x0463327e (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec380 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec380* __stdcall Lookup_fec380(uint32_t id);   // 0x00b20c60

// @ 0x00fec380
void* LookupAs_fec380()
{
    Object_fec380* o = Lookup_fec380(0x04633285);
    return o ? o->Cast(0x0463327e) : 0;
}
