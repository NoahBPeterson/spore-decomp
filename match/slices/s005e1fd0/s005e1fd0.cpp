// Cast helper (0x005e1fd0): ask the object held by a ref (possibly null) for interface 0x0f15f4bd (Cast, slot 3).
#include "game/types.h"

struct Object_5e1fd0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_5e1fd0 {
    Object_5e1fd0* mpObject;
};

// @ 0x005e1fd0
void* CastTo_5e1fd0(const Ref_5e1fd0& ref)
{
    Object_5e1fd0* p = ref.mpObject;
    return p ? p->Cast(0x0f15f4bd) : 0;
}
