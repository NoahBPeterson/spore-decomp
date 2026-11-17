// Cast helper (0x00ae3330): ask the object held by a ref (possibly null) for interface 0x013f94d4 (Cast, slot 46).
#include "game/types.h"

struct Object_ae3330 {
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
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void* Cast(uint32_t typeID);
};
struct Ref_ae3330 {
    Object_ae3330* mpObject;
};

// @ 0x00ae3330
void* CastTo_ae3330(const Ref_ae3330& ref)
{
    Object_ae3330* p = ref.mpObject;
    return p ? p->Cast(0x013f94d4) : 0;
}
