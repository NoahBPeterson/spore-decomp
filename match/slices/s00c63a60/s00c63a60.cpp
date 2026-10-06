// Slice s00c63a60 -- Simulator morph-handle hierarchy (cMorphHandle / cTargetMorphHandle).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ----------------------------------------------------------------- shared stubs
struct VObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void v38(void* out);
    virtual void v3c();
    virtual void v40(float f);
    virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(void* out);
};
struct Ref {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3(int);
    virtual bool v4();
};
struct GameDataBase { void ctorGameData(); };
struct SpatialBase  { void ctorSpatialObject(); };
struct SpatialObj   { void SetModelKey(void* key); };

extern "C" int gMorphData18;   // 0x1693d74
extern "C" int gMorphData1c;   // 0x1693d78
extern "C" int gMorphData20;   // 0x1693d7c
extern void* gVtblMorph0;
extern void* gVtblMorph1;
extern void* gVtblMorphSpatial;
extern void* gVtblTarget0;
extern void* gVtblTarget1;
extern void* gVtblTargetSpatial;
extern void* gModelKey;

// @ 0x00c63b20
struct MorphInit {
    uint8_t mFlag;   // +0x00
    char    pad01[0x17];
    int     mA;      // +0x18
    int     mB;      // +0x1c
    int     mC;      // +0x20
    void Init();
};
void MorphInit::Init() {
    mA = gMorphData18;
    mB = gMorphData1c;
    mC = gMorphData20;
    mFlag = 0;
}

// @ 0x00c63c90
struct FlagHolder {
    char pad00[0xd0];
    int* mp;         // +0xd0
    void SetFlag(int v);
};
void FlagHolder::SetFlag(int v) {
    int* p = mp;
    if (p) {
        if (v)
            p[1] |= 1;
        else
            p[1] &= ~1;
    }
}

// @ 0x00c63c40
struct GameDataBase2 { void RemoveOwner(int owner); };
int* FUN_00eedba0(void* out, void* in);   // 0x00eedba0
struct cGameDataThing {
    char pad00[0x9c];
    int* mpObj;   // 0x9c
    void RemoveOwnerFn(int owner);
};
void cGameDataThing::RemoveOwnerFn(int owner) {
    ((GameDataBase2*)this)->RemoveOwner(owner);
    int* p = mpObj;
    if (p) {
        int tmp[3];
        int* r = FUN_00eedba0(tmp, (char*)this - 0x34);
        *(int*)((char*)p + 0x4c) = r[0];
        *(int*)((char*)p + 0x50) = r[1];
        *(int*)((char*)p + 0x54) = r[2];
    }
}

// --------------------------------------------------------------- HandleThing
struct HandleThing {
    char    pad00[0x34];
    char    mSub[0x1a8 - 0x34];
    float   mA;    // 0x1a8
    float   mB;    // 0x1ac
    float   mC;    // 0x1b0
    uint8_t mEn;   // 0x1b4
    void Fn();
    void SetEnabled(bool v);
};

// @ 0x00c63ae0
void HandleThing::Fn() {
    VObj* p = (VObj*)((char*)this + 0x34);
    if (mEn)
        p->v40(mC * mA + mB);
    else
        p->v40(1.0f);
}

// @ 0x00c643a0  (complete, near miss)
void HandleThing::SetEnabled(bool v) {
    if (mEn != v) {
        VObj* p = (VObj*)((char*)this + 0x34);
        mEn = v;
        if (v)
            p->v40(mC * mA + mB);
        else
            p->v40(1.0f);
    }
}

// ------------------------------------------------------------------ morph tgt
// @ 0x00c63a60  (complete, near miss: register allocation / this-null check)
struct MorphA {
    void* QueryInterface(unsigned id);
    void* Fallback(unsigned id);
};
void* MorphA::QueryInterface(unsigned id) {
    if (id == 0x7a81824)
        return this;
    if (id == 0x1186577)
        return this ? (char*)this + 0x34 : 0;
    if (id == 0x7a309fb)
        return this;
    return Fallback(id);
}
void* MorphA::Fallback(unsigned id) { (void)id; return 0; }

// @ 0x00c63aa0  (complete, near miss)
struct MorphB {
    void* QueryInterface(unsigned id);
    void* Fallback(unsigned id);
};
void* MorphB::QueryInterface(unsigned id) {
    if (id == 0x7abdd8d)
        return this;
    if (id == 0x1186577)
        return this ? (char*)this + 0x34 : 0;
    if (id == 0x7a309fb)
        return this;
    return Fallback(id);
}
void* MorphB::Fallback(unsigned id) { (void)id; return 0; }

// @ 0x00c63be0  (complete, near miss: store ordering)
struct cMorphHandle {
    char data[0x200];
    cMorphHandle();
};
cMorphHandle::cMorphHandle() {
    ((GameDataBase*)this)->ctorGameData();
    ((SpatialBase*)((char*)this + 0x34))->ctorSpatialObject();
    *(void**)((char*)this + 0) = &gVtblMorph0;
    *(void**)((char*)this + 4) = &gVtblMorph1;
    *(void**)((char*)this + 0x34) = &gVtblMorphSpatial;
    *(float*)((char*)this + 0x108) = 0.0f;
    *(float*)((char*)this + 0x10c) = 0.0f;
    *(float*)((char*)this + 0x110) = 0.0f;
    *(uint8_t*)((char*)this + 0x114) = 1;
    *(uint8_t*)((char*)this + 0x115) = 1;
    *(uint8_t*)((char*)this + 0xda) = 0;
}

// @ 0x00c63e30  (partial: ctor store ordering not reproduced)
void cTargetMorphHandle_ctor_stub() {}

// @ 0x00c63dd0  (complete, near miss: vcall register)
struct AppObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void* v58(void* a, int b);
};
AppObj* SP_App();                // 0x0067dd10
struct Ctx { bool Check(); };    // 0x007c4900

struct Target {
    char  pad00[0x108];
    float f108;   // 0x108
    float f10c;   // 0x10c
    float f110;   // 0x110
    void Offset(float* p, int a);
};
void Target::Offset(float* p, int a) {
    Ctx* c = (Ctx*)((AppObj*)SP_App())->v58(p, a);
    if (c->Check()) {
        float x = f108 + p[0];
        float y = f10c + p[1];
        float z = f110 + p[2];
        p[0] = x;
        p[1] = y;
        p[2] = z;
    }
}

// @ 0x00c63ef0  (complete, near miss: store schedule)
struct Target2 {
    char pad00[0x134];
    Ref* mp134;   // 0x134
    void Dtor();
    void Release();
};
void Target2::Dtor() {
    *(void**)this = &gVtblTarget0;
    *(void**)((char*)this + 4) = &gVtblTarget1;
    *(void**)((char*)this + 0x34) = &gVtblTargetSpatial;
    if (mp134)
        mp134->v1();
    *(void**)this = &gVtblMorph0;
    *(void**)((char*)this + 4) = &gVtblMorph1;
    *(void**)((char*)this + 0x34) = &gVtblMorphSpatial;
    ((SpatialBase*)((char*)this + 0x34))->ctorSpatialObject();
    ((GameDataBase*)this)->ctorGameData();
}

// @ 0x00c63f40
void Target2::Release() {
    if (mp134) {
        if (mp134->v4())
            mp134->v3(0);
    }
    Ref* p = mp134;
    if (p) {
        mp134 = 0;
        p->v1();
    }
}

// =====================================================================
// Partially-reconstructed functions (see partial.txt).
// =====================================================================

// @ 0x00c63b40  (partial)
int ComparePair(void* a, int b, void* c) { (void)a; (void)b; (void)c; return 0; }
// @ 0x00c63b90  (partial)
void CopyPair(void* a, void* b) { (void)a; (void)b; }
// @ 0x00c63cb0  (partial)
void FUN_c63cb0() {}
// @ 0x00c63f90  (partial)
void FUN_c63f90() {}
// @ 0x00c640e0  (partial)
void FUN_c640e0() {}
// @ 0x00c64170  (partial)
void FUN_c64170() {}
// @ 0x00c642e0  (partial)
void FUN_c642e0() {}
// @ 0x00c64400  (partial)
int FUN_c64400() { return 0; }
// @ 0x00c64460  (partial)
void FUN_c64460() {}
// @ 0x00c64590  (partial)
void FUN_c64590() {}
// @ 0x00c64630  (partial)
int FUN_c64630() { return 0; }
// @ 0x00c64880  (partial)
void FUN_c64880() {}
// @ 0x00c64940  (partial)
void FUN_c64940() {}
