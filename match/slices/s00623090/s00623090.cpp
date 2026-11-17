// Cast helper (0x00623090): ask the object held by a ref (possibly null) for interface 0x04c058d5 (Cast, slot 3).
#include "game/types.h"

struct Object_623090 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_623090 {
    Object_623090* mpObject;
};

// @ 0x00623090
void* CastTo_623090(const Ref_623090& ref)
{
    Object_623090* p = ref.mpObject;
    return p ? p->Cast(0x04c058d5) : 0;
}
