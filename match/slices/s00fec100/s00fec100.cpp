// Lookup and cast (0x00fec100): look up object 0x0397bff3 (0xb20c60) and, if found, ask it for interface
// 0x0397bff2 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec100 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec100* __stdcall Lookup_fec100(uint32_t id);   // 0x00b20c60

// @ 0x00fec100
void* LookupAs_fec100()
{
    Object_fec100* o = Lookup_fec100(0x0397bff3);
    return o ? o->Cast(0x0397bff2) : 0;
}
