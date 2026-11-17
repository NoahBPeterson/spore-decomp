// Lookup and cast (0x00fec160): look up object 0x035988f4 (0xb20c60) and, if found, ask it for interface
// 0x035988ee (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec160 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec160* __stdcall Lookup_fec160(uint32_t id);   // 0x00b20c60

// @ 0x00fec160
void* LookupAs_fec160()
{
    Object_fec160* o = Lookup_fec160(0x035988f4);
    return o ? o->Cast(0x035988ee) : 0;
}
