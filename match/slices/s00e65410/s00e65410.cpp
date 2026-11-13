#include "game/types.h"

struct SubMgr_00e65410 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void* Create(void* a, int b, int c); // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual void Add(void* obj); // +0x58
};

struct ObjOwner_00e65410 {
    void* vftable;
    void Destroy(void* obj, bool flag) {
        typedef void (__thiscall *Fn)(void*, void*, bool);
        ((Fn)(*(void***)this)[0x170 / 4])(this, obj, flag);
    }
};

struct Obj_00e65410 {
    ObjOwner_00e65410* mpOwner; // +0x00
    int32_t mFlags;             // +0x04
    uint8_t pad08[0x38];
    int32_t mRefCount;          // +0x40
};

struct Mgr_00e65410 {
    uint8_t pad00[0x54];
    SubMgr_00e65410* mpSub;     // +0x54
    void Register(Obj_00e65410* obj); // 0x00e653a0
};

extern Mgr_00e65410* gMgr_016b3c08;

// @ 0x00e65410
void __cdecl CreateAndRegister_00e65410(void* arg, bool addToSub)
{
    Obj_00e65410* obj = (Obj_00e65410*)gMgr_016b3c08->mpSub->Create(arg, 0, 0);
    if (obj) {
        obj->mRefCount++;
        gMgr_016b3c08->Register(obj);
        if (addToSub) {
            gMgr_016b3c08->mpSub->Add(obj);
        }
        if (obj->mRefCount > 1) {
            obj->mRefCount--;
        } else {
            obj->mpOwner->Destroy(obj, (bool)(((uint32_t)obj->mFlags >> 31) & 1));
        }
    }
}
