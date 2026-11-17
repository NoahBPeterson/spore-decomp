// Lookup and cast (0x00cb6ea0): look up object 0x04f76f0d (0xb20c60) and, if found, ask it for interface
// 0x04f76f08 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_cb6ea0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_cb6ea0* __stdcall Lookup_cb6ea0(uint32_t id);   // 0x00b20c60

// @ 0x00cb6ea0
void* LookupAs_cb6ea0()
{
    Object_cb6ea0* o = Lookup_cb6ea0(0x04f76f0d);
    return o ? o->Cast(0x04f76f08) : 0;
}
