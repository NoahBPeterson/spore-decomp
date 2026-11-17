// Cast helper (0x00befb60): ask the object held by a ref (possibly null) for interface 0x0137e8e0 (Cast, slot 23).
#include "game/types.h"

struct Object_befb60 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_befb60 {
    Object_befb60* mpObject;
};

// @ 0x00befb60
void* CastTo_befb60(const Ref_befb60& ref)
{
    Object_befb60* p = ref.mpObject;
    return p ? p->Cast(0x0137e8e0) : 0;
}
