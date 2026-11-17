// Cast helper (0x00d57750): ask the object held by a ref (possibly null) for interface 0xd0036e08 (Cast, slot 3).
#include "game/types.h"

struct Object_d57750 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_d57750 {
    Object_d57750* mpObject;
};

// @ 0x00d57750
void* CastTo_d57750(const Ref_d57750& ref)
{
    Object_d57750* p = ref.mpObject;
    return p ? p->Cast(0xd0036e08) : 0;
}
