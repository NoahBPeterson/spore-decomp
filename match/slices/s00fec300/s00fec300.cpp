// Lookup and cast (0x00fec300): look up object 0x04222285 (0xb20c60) and, if found, ask it for interface
// 0x0422227e (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec300 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec300* __stdcall Lookup_fec300(uint32_t id);   // 0x00b20c60

// @ 0x00fec300
void* LookupAs_fec300()
{
    Object_fec300* o = Lookup_fec300(0x04222285);
    return o ? o->Cast(0x0422227e) : 0;
}
