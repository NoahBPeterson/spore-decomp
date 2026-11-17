// Lookup and cast (0x00fec120): look up object 0x032a12f1 (0xb20c60) and, if found, ask it for interface
// 0x032a12f0 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_fec120 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_fec120* __stdcall Lookup_fec120(uint32_t id);   // 0x00b20c60

// @ 0x00fec120
void* LookupAs_fec120()
{
    Object_fec120* o = Lookup_fec120(0x032a12f1);
    return o ? o->Cast(0x032a12f0) : 0;
}
