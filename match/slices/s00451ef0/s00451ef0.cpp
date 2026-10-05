// slice s00451ef0 -- physics object wiring for cSPEditorBlock.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.
#include "types.h"

struct Vec3 { float x, y, z; };
struct Matrix33 { float m[9]; };

struct HkWorldObject {
    void removeReference();
};
struct HkEntity {
    void FUN_01083110(void* local, void* arg);   // 0x01083110
};
struct HkWorld {
    HkEntity* addEntity(HkWorldObject* e, int activation); // 0x01082ee0
    void FUN_01084fa0(HkWorldObject* e, int a, int b);     // 0x01084fa0
};

struct cSPEditorBlock {
    char          pad0[0x48];
    Vec3          mVec48;      // +0x48
    char          pad54[0xa8 - 0x54];
    Matrix33      mMatA8;      // +0xa8
    char          padcc[0x188 - 0xcc];
    HkWorld*      mWorld;      // +0x188
    HkWorldObject* mPhysObj;   // +0x18c
    char          pad190[0x1a8 - 0x190];
    bool          mFlag1a8;    // +0x1a8

    void FUN_00451fe0();       // 0x00451fe0
    void FUN_00451ef0(void* obj); // 0x00451ef0
    void FUN_00452040();       // 0x00452040
    void* BuildNewPhysicsShape(); // 0x00452080
    void FUN_00448fa0(Vec3 v, int one);
    void FUN_0044a0e0();
};

// @ 0x00451fe0
void cSPEditorBlock::FUN_00451fe0() {
    if (mPhysObj != 0) {
        HkEntity* e = *(HkEntity**)((char*)mPhysObj + 8);
        char c;
        e->FUN_01083110(&c, mPhysObj);
        mPhysObj->removeReference();
    }
    mPhysObj = 0;
}

// @ 0x00452040
void cSPEditorBlock::FUN_00452040() {
    mFlag1a8 = true;
    if (mWorld != 0)
        FUN_00451ef0(BuildNewPhysicsShape());
}

// @ 0x00451ef0
void cSPEditorBlock::FUN_00451ef0(void* obj) {
    FUN_00451fe0();
    int n = 6;
    (void)n;
    if (mPhysObj != 0)
        FUN_00451fe0();
    mPhysObj = (HkWorldObject*)obj;
    if (mPhysObj != 0) {
        mWorld->addEntity(mPhysObj, 1);
        mWorld->FUN_01084fa0(mPhysObj, 0, 1);
        Vec3 v = mVec48;
        FUN_00448fa0(v, 1);
        Matrix33 tmp = mMatA8;
        FUN_0044a0e0();
        (void)tmp;
        mFlag1a8 = false;
    }
}
