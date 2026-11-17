// Lookup and cast (0x00bbd160): look up object 0x0403df5c (0xb20c60) and, if found, ask it for interface
// 0x0403df5f (Cast, vtable slot 3).
#include "game/types.h"

struct Object_bbd160 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_bbd160* __stdcall Lookup_bbd160(uint32_t id);   // 0x00b20c60

// @ 0x00bbd160
void* LookupAs_bbd160()
{
    Object_bbd160* o = Lookup_bbd160(0x0403df5c);
    return o ? o->Cast(0x0403df5f) : 0;
}
