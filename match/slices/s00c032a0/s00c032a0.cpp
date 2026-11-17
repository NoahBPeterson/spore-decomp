// Cast helper (0x00c032a0): ask a possibly null object for interface 0xce9f6639 (Cast, vtable slot 23).
#include "game/types.h"

struct Object_c032a0 {
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

// @ 0x00c032a0
void* CastTo_c032a0(Object_c032a0* p)
{
    return p ? p->Cast(0xce9f6639) : 0;
}
