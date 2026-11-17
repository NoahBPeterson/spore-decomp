// Cast helper (0x00cca0c0): ask the object held by a ref (possibly null) for interface 0x0116d858 (Cast, slot 3).
#include "game/types.h"

struct Object_cca0c0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_cca0c0 {
    Object_cca0c0* mpObject;
};

// @ 0x00cca0c0
void* CastTo_cca0c0(const Ref_cca0c0& ref)
{
    Object_cca0c0* p = ref.mpObject;
    return p ? p->Cast(0x0116d858) : 0;
}
