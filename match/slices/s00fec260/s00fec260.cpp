// Lookup and cast (0x00fec260): look up object 0x0347092f (0xb20c60) and, if found, ask it for interface
// 0x03470928 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec260 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec260* __stdcall Lookup_fec260(uint32_t id);   // 0x00b20c60

// @ 0x00fec260
void* LookupAs_fec260()
{
    Object_fec260* o = Lookup_fec260(0x0347092f);
    return o ? o->Cast(0x03470928) : 0;
}
