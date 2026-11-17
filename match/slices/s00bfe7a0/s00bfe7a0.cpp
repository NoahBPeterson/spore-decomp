// Lookup and cast (0x00bfe7a0): look up object 0x05776a2c (0xb20c60) and, if found, ask it for interface
// 0x05776a28 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_bfe7a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_bfe7a0* __stdcall Lookup_bfe7a0(uint32_t id);   // 0x00b20c60

// @ 0x00bfe7a0
void* LookupAs_bfe7a0()
{
    Object_bfe7a0* o = Lookup_bfe7a0(0x05776a2c);
    return o ? o->Cast(0x05776a28) : 0;
}
