// Lookup and cast (0x00fec280): look up object 0x04f3bde9 (0xb20c60) and, if found, ask it for interface
// 0x04f3bde8 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec280 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec280* __stdcall Lookup_fec280(uint32_t id);   // 0x00b20c60

// @ 0x00fec280
void* LookupAs_fec280()
{
    Object_fec280* o = Lookup_fec280(0x04f3bde9);
    return o ? o->Cast(0x04f3bde8) : 0;
}
