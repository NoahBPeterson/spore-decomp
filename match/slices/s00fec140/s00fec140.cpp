// Lookup and cast (0x00fec140): look up object 0x02ba2a0e (0xb20c60) and, if found, ask it for interface
// 0x02ba2a01 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec140 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec140* __stdcall Lookup_fec140(uint32_t id);   // 0x00b20c60

// @ 0x00fec140
void* LookupAs_fec140()
{
    Object_fec140* o = Lookup_fec140(0x02ba2a0e);
    return o ? o->Cast(0x02ba2a01) : 0;
}
