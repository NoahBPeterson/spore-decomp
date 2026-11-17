// Lookup and cast (0x00fec220): look up object 0x04222283 (0xb20c60) and, if found, ask it for interface
// 0x0422227c (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec220 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec220* __stdcall Lookup_fec220(uint32_t id);   // 0x00b20c60

// @ 0x00fec220
void* LookupAs_fec220()
{
    Object_fec220* o = Lookup_fec220(0x04222283);
    return o ? o->Cast(0x0422227c) : 0;
}
