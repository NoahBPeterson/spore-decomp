// Lookup and cast (0x00daed70): look up object 0x061494be (0xb20c60) and, if found, ask it for interface
// 0x061494bd (Cast, vtable slot 3).
#include "game/types.h"

struct Object_daed70 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_daed70* __stdcall Lookup_daed70(uint32_t id);   // 0x00b20c60

// @ 0x00daed70
void* LookupAs_daed70()
{
    Object_daed70* o = Lookup_daed70(0x061494be);
    return o ? o->Cast(0x061494bd) : 0;
}
