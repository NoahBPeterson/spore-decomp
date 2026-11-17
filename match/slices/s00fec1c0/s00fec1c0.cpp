// Lookup and cast (0x00fec1c0): look up object 0x0330fc49 (0xb20c60) and, if found, ask it for interface
// 0x0330fc43 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec1c0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec1c0* __stdcall Lookup_fec1c0(uint32_t id);   // 0x00b20c60

// @ 0x00fec1c0
void* LookupAs_fec1c0()
{
    Object_fec1c0* o = Lookup_fec1c0(0x0330fc49);
    return o ? o->Cast(0x0330fc43) : 0;
}
