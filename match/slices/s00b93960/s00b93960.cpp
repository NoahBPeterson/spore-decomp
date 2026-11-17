// Lookup and cast (0x00b93960): look up object 0x018c816a (0xb20c60) and, if found, ask it for interface
// 0x901f1362 (Cast, vtable slot 3).
#include "game/types.h"

struct Object_b93960 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
Object_b93960* __stdcall Lookup_b93960(uint32_t id);   // 0x00b20c60

// @ 0x00b93960
void* LookupAs_b93960()
{
    Object_b93960* o = Lookup_b93960(0x018c816a);
    return o ? o->Cast(0x901f1362) : 0;
}
