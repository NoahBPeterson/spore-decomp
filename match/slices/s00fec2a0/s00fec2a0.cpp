// Lookup and cast (0x00fec2a0): look up object 0x04f77499 (0xb20c60) and, if found, ask it for interface
// 0x04f77498 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec2a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec2a0* __stdcall Lookup_fec2a0(uint32_t id);   // 0x00b20c60

// @ 0x00fec2a0
void* LookupAs_fec2a0()
{
    Object_fec2a0* o = Lookup_fec2a0(0x04f77499);
    return o ? o->Cast(0x04f77498) : 0;
}
