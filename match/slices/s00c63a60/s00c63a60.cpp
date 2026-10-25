// Slice s00c63a60 -- Simulator morph-handle hierarchy (cMorphHandle / cTargetMorphHandle).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// Codegen-only compiler barrier (emits no instructions); used to pin store order where cl's
// scheduler would otherwise move an independent store above its neighbours.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ----------------------------------------------------------------- shared stubs
struct VObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void* v2c();
    virtual void v30(); virtual void v34();
    virtual void v38(void* out);
    virtual void v3c(void* q);
    virtual void v40(float f);
    virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void* v60(void* out);
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
// The image is not relocatable, so the retail constructors store their vftable addresses as plain
// 32-bit immediates; writing them as integer constants reproduces those immediates byte for byte.
enum {
    kVtblMorph0  = 0x1470eb8,   // cMorphHandle primary vftable
    kVtblMorph1  = 0x147112c,   // cMorphHandle second base vftable
    kVtblMorphSp = 0x1470df0,   // cMorphHandle spatial sub-object vftable
    kVtblTgt0    = 0x1470ff8,   // cTargetMorphHandle primary vftable
    kVtblTgt1    = 0x1470fe4,   // cTargetMorphHandle second base vftable
    kVtblTgtSp   = 0x1470f20    // cTargetMorphHandle spatial sub-object vftable
};
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

// @ 0x00c643a0  (complete, near miss: vftable load not hoisted above the flag store)
void HandleThing::SetEnabled(bool v) {
    if (mEn == v)
        return;
    mEn = v;
    if (v)
        ((VObj*)((char*)this + 0x34))->v40(mC * mA + mB);
    else
        ((VObj*)((char*)this + 0x34))->v40(1.0f);
}

// ------------------------------------------------------------------ morph tgt
// 0x00b18460 is the shared type-id cast helper (this in ecx, id on the stack, ret 4); the original
// tail-jumps to it from the QueryInterface fallbacks.
struct MorphCastHelper {
    void* FUN_00b18460(unsigned id);              // 0x00b18460
};

// @ 0x00c63a60  (complete, near miss: block layout only - registers match retail)
struct MorphA {
    void* QueryInterface(unsigned id);
};
void* MorphA::QueryInterface(unsigned id) {
    if (id == 0x7a81824)
        return this;
    if (id == 0x1186577)
        return this ? (char*)this + 0x34 : 0;
    return (id == 0x7a309fb) ? (void*)this : ((MorphCastHelper*)this)->FUN_00b18460(id);
}

// @ 0x00c63aa0  (complete, near miss: block layout only - registers match retail)
struct MorphB {
    void* QueryInterface(unsigned id);
};
void* MorphB::QueryInterface(unsigned id) {
    if (id == 0x7abdd8d)
        return this;
    if (id == 0x1186577)
        return this ? (char*)this + 0x34 : 0;
    return (id == 0x7a309fb) ? (void*)this : ((MorphCastHelper*)this)->FUN_00b18460(id);
}

struct cMorphHandle {
    void*   mpVtbl;          // +0x000  primary vftable
    void*   mpVtbl04;        // +0x004  second base vftable
    char    pad08[0x2c];     // +0x008
    void*   mpVtblSpatial;   // +0x034  spatial sub-object vftable
    char    pad38[0xa2];     // +0x038 ... +0x0d9
    uint8_t mVis;            // +0x0da
    char    padDb[0x2d];     // +0x0db ... +0x107
    float   mF108;           // +0x108
    float   mF10c;           // +0x10c
    float   mF110;           // +0x110
    uint8_t mB114;           // +0x114
    uint8_t mB115;           // +0x115
    char    pad116[2];       // +0x116 ... +0x117
    cMorphHandle();
    void Offset(float* p, int a);
};

// @ 0x00c63be0  (complete, near miss: only the `xorps` placement differs)
// Without the barriers cl reorders the six stores of this block (it hoists the [edi] vftable store
// and the two flag bytes above the [esi]/[esi+4] stores); the original keeps strict source order.
cMorphHandle::cMorphHandle() {
    ((GameDataBase*)this)->ctorGameData();
    ((SpatialBase*)&mpVtblSpatial)->ctorSpatialObject();
    _ReadWriteBarrier();
    mpVtbl = (void*)kVtblMorph0;
    _ReadWriteBarrier();
    mpVtbl04 = (void*)kVtblMorph1;
    _ReadWriteBarrier();
    mpVtblSpatial = (void*)kVtblMorphSp;
    _ReadWriteBarrier();
    mF108 = 0.0f;
    _ReadWriteBarrier();
    mF10c = 0.0f;
    _ReadWriteBarrier();
    mF110 = 0.0f;
    _ReadWriteBarrier();
    mB114 = 1;
    _ReadWriteBarrier();
    mB115 = 1;
    _ReadWriteBarrier();
    mVis = 0;
}

extern uint8_t gTgtMorphKeyData; // 0x15777e4

struct cTargetMorphHandle : cMorphHandle {
    float   mF118;              // +0x118
    float   mF11c;              // +0x11c
    float   mF120;              // +0x120
    uint8_t mB124;              // +0x124
    char    pad125[3];          // +0x125 ... +0x127
    int     mI128;              // +0x128
    float   mF12c;              // +0x12c
    int     mI130;              // +0x130
    Ref*    mpRef;              // +0x134
    char    pad138[0x200 - 0x138];
    cTargetMorphHandle();
    void Dtor();
    void Release();
};

// @ 0x00c63e30
cTargetMorphHandle::cTargetMorphHandle()
{
    mpVtbl = (void*)kVtblTgt0;
    _ReadWriteBarrier();
    mpVtbl04 = (void*)kVtblTgt1;
    _ReadWriteBarrier();
    mpVtblSpatial = (void*)kVtblTgtSp;
    _ReadWriteBarrier();
    SpatialObj* spatial = (SpatialObj*)&mpVtblSpatial;
    mF118 = 0.0f;
    _ReadWriteBarrier();
    mF11c = 0.0f;
    _ReadWriteBarrier();
    mF120 = 0.0f;
    _ReadWriteBarrier();
    mB124 = 0;
    _ReadWriteBarrier();
    mI128 = 0;
    _ReadWriteBarrier();
    mF12c = 0.0f;
    _ReadWriteBarrier();
    mI130 = 3;
    _ReadWriteBarrier();
    mpRef = 0;
    _ReadWriteBarrier();
    spatial->SetModelKey(&gTgtMorphKeyData);
}

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

void cMorphHandle::Offset(float* p, int a) {
    Ctx* c = (Ctx*)((AppObj*)SP_App())->v58(p, a);
    if (c->Check()) {
        float x = mF108 + p[0];
        float y = mF10c + p[1];
        float z = mF110 + p[2];
        p[0] = x;
        p[1] = y;
        p[2] = z;
    }
}

// @ 0x00c63ef0  (complete, near miss: the +0x134 load is hoisted above the vftable stores)
void cTargetMorphHandle::Dtor() {
    mpVtbl = (void*)kVtblTgt0;
    mpVtbl04 = (void*)kVtblTgt1;
    mpVtblSpatial = (void*)kVtblTgtSp;
    _ReadWriteBarrier();
    if (mpRef)
        mpRef->v1();
    mpVtbl = (void*)kVtblMorph0;
    mpVtbl04 = (void*)kVtblMorph1;
    mpVtblSpatial = (void*)kVtblMorphSp;
    ((SpatialBase*)&mpVtblSpatial)->ctorSpatialObject();
    ((GameDataBase*)this)->ctorGameData();
}

// @ 0x00c63f40
void cTargetMorphHandle::Release() {
    if (mpRef) {
        if (mpRef->v4())
            mpRef->v3(0);
    }
    Ref* p = mpRef;
    if (p) {
        mpRef = 0;
        p->v1();
    }
}

// =====================================================================
// Partially-reconstructed functions (see partial.txt).
// =====================================================================

// @ 0x00c63b40  (ComparePair)
extern "C" float QuaternionSlerp(void*, void*, void*);
char ComparePair(void* a, void* b, void* c)
{
    float r = QuaternionSlerp(((VObj*)((char*)c + 0x34))->v2c(), b,
                              ((VObj*)((char*)a + 0x34))->v2c());
    if (r > 2.0f)
        return 0;
    return 1;
}

// @ 0x00c63b90  (CopyPair)
// The original folds an identical void-returning overload of the SP helper at
// 0x00698b30 (ICF); using the float overload here would leave an `fstp st(0)`.
extern "C" void QuaternionSlerpVoid(void*, void*, void*);
void CopyPair(void* a, void* b)
{
    QuaternionSlerpVoid(((VObj*)((char*)a + 0x34))->v2c(),
                        (char*)b + 0x118,
                        ((VObj*)((char*)b + 0x34))->v2c());
}
// ---------------------------------------------------------------------
// Objects the handle methods below talk to.
// ---------------------------------------------------------------------

// Handle primary vtable; slot 0x68 is the per-frame update.
struct KObj {
    virtual void k00(); virtual void k04(); virtual void k08(); virtual void k0c();
    virtual void k10(); virtual void k14(); virtual void k18(); virtual void k1c();
    virtual void k20(); virtual void k24(); virtual void k28(); virtual void k2c();
    virtual void k30(); virtual void k34(); virtual void k38(); virtual void k3c();
    virtual void k40(); virtual void k44(); virtual void k48(); virtual void k4c();
    virtual void k50(); virtual void k54(); virtual void k58(); virtual void k5c();
    virtual void k60(); virtual void k64(); virtual void k68();
};
// Same layout as VObj, but slot 0x2c also accepts a direction vector.
struct VObjDir {
    virtual void d00(); virtual void d04(); virtual void d08(); virtual void d0c();
    virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28();
    virtual void* v2c(float* dir);
    virtual void d30(); virtual void d34();
    virtual void d38(void* out);
    virtual void d3c(void* q);
    virtual void d40(float f);
    virtual void d44(); virtual void d48(); virtual void d4c();
    virtual void d50(); virtual void d54(); virtual void d58(); virtual void d5c();
    virtual void* d60(void* out);
};
// App object seen through slot 0x58 as a two-pointer call (the existing
// AppObj view declares the same slot as (void*, int)).
struct AppObj2 {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
    virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4c();
    virtual void a50(); virtual void a54();
    virtual void* v58(void* a, void* b);
};
// Camera/view context at 0x007c46f0 (same helper as slice s007c3ba0; the
// call site leaves the Vector3 pointers in App::v58's argument area).
struct ViewCtx { void Update(); };
// Planet model (0x00b3d350) and its surface-orientation helpers.
struct PlanetModelObj {
    void* BuildSurfaceOrientation(void* dst, void* src);            // 0x00b7f190
    void* BuildSurfaceOrientation_2(void* dst, void* a, void* b);   // 0x00b7f1f0
    void* BuildSurfaceOrientation2(void* dst, void* src);           // 0x00b7f250
};
PlanetModelObj* PlanetModel();
// Render context at +0xd4 (slots used here: 0x44, 0x74, 0x80, 0x10c).
struct CtxD4 {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40();
    virtual bool s44(void* a, void* b, void* t, void* f, void* out);
    virtual void s48(); virtual void s4c(); virtual void s50(); virtual void s54();
    virtual void s58(); virtual void s5c(); virtual void s60(); virtual void s64();
    virtual void s68(); virtual void s6c(); virtual void s70();
    virtual void s74(void* a, int b, float c, void* d);
    virtual void s78(); virtual void s7c();
    virtual void s80(void* a, int b, void* c, void* d, void* e);
    virtual void s84(); virtual void s88(); virtual void s8c(); virtual void s90();
    virtual void s94(); virtual void s98(); virtual void s9c(); virtual void sA0();
    virtual void sA4(); virtual void sA8(); virtual void sAc(); virtual void sB0();
    virtual void sB4(); virtual void sB8(); virtual void sBc(); virtual void sC0();
    virtual void sC4(); virtual void sC8(); virtual void sCc(); virtual void sD0();
    virtual void sD4(); virtual void sD8(); virtual void sDc(); virtual void sE0();
    virtual void sE4(); virtual void sE8(); virtual void sEc(); virtual void sF0();
    virtual void sF4(); virtual void sF8(); virtual void sFc(); virtual void s100();
    virtual void s104(); virtual void s108();
    virtual void s10c(void* a, void* b);
};
// The pile object owning the +0xd0/+0xd4 fields and the +0x108..+0x1d0 block.
struct Kin {
    char data[0x200];
    void Fn63cb0();
    void Fn63f90();
    void Fn64170();
    void Fn642e0();
};
struct CtxOut {
    float     a;    // +0x00
    float     b;    // +0x04
    float     c;    // +0x08
    float     d;    // +0x0c
    float     e;    // +0x10
    uint8_t   f0;   // +0x14
    uint8_t   f1;   // +0x15
};
struct TVec { float x, y, z; };
struct TVec4 { float x, y, z, w; };
extern "C" double sqrt(double);
extern "C" void* __cdecl memset(void* dst, int val, unsigned n);

// @ 0x00c63cb0
void Kin::Fn63cb0()
{
    char* self = (char*)this;
    float f;
    CtxOut out;
    float v2[3];
    float v1[3];
    ((ViewCtx*)((AppObj2*)SP_App())->v58(v1, v2))->Update();
    memset(&out, 0, 22);
    int t = *(int*)(self + 0xd0);
    if (((CtxD4*)*(void**)(self + 0xd4))->s44(v1, v2, (void*)t, &f, &out)) {
        out.a = v1[0] + (v2[0] - v1[0]) * f;
        out.b = v1[1] + (v2[1] - v1[1]) * f;
        out.c = v1[2] + (v2[2] - v1[2]) * f;
        float* p = (float*)((VObj*)(self + 0x34))->v2c();
        *(float*)(self + 0x108) = p[0] - out.a;
        *(float*)(self + 0x10c) = p[1] - out.b;
        *(float*)(self + 0x110) = p[2] - out.c;
    }
}

// @ 0x00c63f90
void Kin::Fn63f90()
{
    char* self = (char*)this;
    float* p = (float*)((VObj*)(self + 0x34))->v2c();
    float* r;
    if (*(float*)(self + 0x118) == p[0] && *(float*)(self + 0x11c) == p[1]
        && *(float*)(self + 0x120) == p[2]) {
        float dst[4];
        r = (float*)PlanetModel()->BuildSurfaceOrientation(
                dst, ((VObj*)(self + 0x34))->v2c());
    } else {
        float* q = (float*)((VObj*)(self + 0x34))->v2c();
        float dx = *(float*)(self + 0x118) - q[0];
        float dy = *(float*)(self + 0x11c) - q[1];
        float dz = *(float*)(self + 0x120) - q[2];
        float k = 1.0f / (float)sqrt((double)((dx * dx + dy * dy) + dz * dz + 1e-8f));
        float dir[3];
        dir[0] = k * dx;
        dir[1] = k * dy;
        dir[2] = k * dz;
        float dst2[4];
        r = (float*)PlanetModel()->BuildSurfaceOrientation2(
                dst2, ((VObjDir*)(self + 0x34))->v2c(dir));
    }
    float quat[4];
    quat[0] = r[0];
    quat[1] = r[1];
    quat[2] = r[2];
    quat[3] = r[3];
    ((VObj*)(self + 0x34))->v3c(quat);
}
// @ 0x00c640e0  (complete, near miss: result stores are interleaved)
struct Vec3f { float x, y, z; };
struct CmpObj64 { void Fn(); };
void CmpObj64::Fn()
{
    char* self = (char*)this;
    float tmp[3];
    Vec3f* v = (Vec3f*)((VObj*)(self + 0x34))->v60(tmp);
    float s = *(float*)(self + 0x1bc);
    Vec3f sc;
    sc.x = v->x * s;
    sc.y = v->y * s;
    sc.z = v->z * s;
    Vec3f out;
    out.x = sc.x + *(float*)(self + 0x198);
    out.y = sc.y + *(float*)(self + 0x19c);
    out.z = sc.z + *(float*)(self + 0x1a0);
    ((VObj*)(self + 0x34))->v38(&out);
}
// @ 0x00c64170
void Kin::Fn64170()
{
    char* self = (char*)this;
    void* d0 = *(void**)(self + 0xd0);
    if (!d0)
        return;
    float a = *(float*)(self + 0x1c4);
    float b = *(float*)(self + 0x1c0) + *(float*)(self + 0x1b4);
    float c = *(float*)(self + 0x1c8) * a;
    float d = *(float*)(self + 0x1cc) * a;
    if (c > b) {
        a = (a / c) * b;
        b = c;
    } else if (d < b) {
        a = (a / d) * b;
        b = d;
    }
    ((VObj*)(self + 0x34))->v40(a);
    float ratio = (c == d) ? 1.0f : (b - c) / (d - c);
    float abc[3];
    abc[0] = 0.0f;
    abc[1] = ratio;
    abc[2] = 0.0f;
    CtxD4* ctx = (CtxD4*)*(void**)(self + 0xd4);
    ctx->s80(d0, *(int*)(self + 0x1d0), &abc[2], abc, 0);
    ctx->s74(d0, *(int*)(self + 0x1d0), (abc[0] - abc[2]) * abc[1] + abc[2], 0);
    ctx->s10c(d0, 0);
}

// @ 0x00c642e0
void Kin::Fn642e0()
{
    char* self = (char*)this;
    Fn63cb0();
    *(TVec4*)(self + 0x17c) = *(TVec4*)(self + 0x198);
    *(TVec*)(self + 0x170) = *(TVec*)(self + 0x18c);
    TVec4 local;
    PlanetModel()->BuildSurfaceOrientation_2(&local, self + 0x18c, self + 0x198);
    *(int*)(self + 0x128) = 0;
    *(int*)(self + 0x12c) = 0;
    *(int*)(self + 0x130) = 0;
    *(int*)(self + 0x134) = 0;
    int* lv = (int*)&local;
    *(int*)(self + 0x15c) = lv[0];
    *(int*)(self + 0x160) = lv[1];
    *(int*)(self + 0x164) = lv[2];
    *(int*)(self + 0x168) = lv[3];
    *(uint8_t*)(self + 0x120) = 0;
}
// @ 0x00c64400  (ComparePairDist)
extern "C" double sqrt(double);
char FUN_c64400(void* a, void* b)
{
    float* p1 = (float*)((VObj*)((char*)b + 0x34))->v2c();
    float* p2 = (float*)((VObj*)((char*)a + 0x34))->v2c();
    float dx = p2[0] - p1[0];
    float dy = p2[1] - p1[1];
    float dz = p2[2] - p1[2];
    float len = (float)sqrt((double)((dx * dx + dz * dz) + dy * dy));
    if (2.0f < len)
        return 0;
    return 1;
}
// ---------------------------------------------------------------------
// Pile/chain helpers (share the PathObj whose +4/+8 hold the element
// vector; 0x00c64630/0x00c64590/0x00c64880 all take &that vector).
// ---------------------------------------------------------------------
struct PathObj {
    uint8_t   mFlag;    // +0x00
    char      pad01[3];
    void**    mpBegin;  // +0x04
    void**    mpEnd;    // +0x08
    char      pad0c[0x0c];
    float     f18;      // +0x18
    float     f1c;      // +0x1c
    float     f20;      // +0x20
    void Fn64460(void* h);
    void Fn64940(void* h);
};
// 0x00c63b90 as a float-returning copy (body identical to CopyPair).
float CopyPairF(void* a, void* b)
{
    return QuaternionSlerp(((VObj*)((char*)a + 0x34))->v2c(),
                           (char*)b + 0x118,
                           ((VObj*)((char*)b + 0x34))->v2c());
}

// @ 0x00c64460
void PathObj::Fn64460(void* h)
{
    int count = (int)(((char*)mpEnd - (char*)mpBegin) >> 2);
    if ((unsigned)count > 1 && mpBegin[count - 1] == h) {
        void* first = mpBegin[0];
        float* p = (float*)((VObj*)((char*)h + 0x34))->v2c();
        float dx = p[0] - *(float*)((char*)first + 0x118);
        float dy = p[1] - *(float*)((char*)first + 0x11c);
        float dz = p[2] - *(float*)((char*)first + 0x120);
        if ((float)sqrt((double)(dz * dz + dy * dy + dx * dx)) < 2.5f) {
            ((VObj*)((char*)this + 0x34))->v38((char*)first + 0x118);
            mFlag = 1;
        } else {
            mFlag = 0;
        }
    } else {
        mFlag = 0;
    }
    TVec cur;
    cur.x = *(float*)((char*)mpBegin[0] + 0x118);
    cur.y = *(float*)((char*)mpBegin[0] + 0x11c);
    cur.z = *(float*)((char*)mpBegin[0] + 0x120);
    for (int i = 0; i < (int)(((char*)mpEnd - (char*)mpBegin) >> 2); ++i) {
        char* e = (char*)mpBegin[i];
        *(TVec*)(e + 0x118) = cur;
        cur = *(TVec*)((VObj*)(e + 0x34))->v2c();
        ((KObj*)e)->k68();
    }
}

// @ 0x00c64590
float FUN_c64590(void** vec, int idx, void* a, void* b)
{
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    int count = (int)(((char*)end - (char*)begin) >> 2);
    if (idx + 2 == count) {
        float* p1 = (float*)((VObj*)((char*)b + 0x34))->v2c();
        float* p2 = (float*)((VObj*)((char*)a + 0x34))->v2c();
        float dx = p2[0] - p1[0];
        float dy = p2[1] - p1[1];
        float dz = p2[2] - p1[2];
        return (float)sqrt((double)(dz * dz + (dy * dy + dx * dx))) - 0.05f;
    }
    return QuaternionSlerp(((VObj*)((char*)a + 0x34))->v2c(),
                           ((VObj*)((char*)b + 0x34))->v2c(),
                           ((VObj*)((char*)begin[idx + 2] + 0x34))->v2c());
}

// @ 0x00c64630
int FUN_c64630(void** vec, void* h, float px, float py, float pz)
{
    if (py * py + pz * pz + px * px < 1.5258789e-05f) {
        float* p = (float*)((VObj*)((char*)h + 0x34))->v2c();
        px = p[0];
        py = p[1];
        pz = p[2];
    }
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    int count = (int)(((char*)end - (char*)begin) >> 2);
    int i = 0;
    for (; i < count; ++i)
        if (begin[i] == h)
            break;
    if (i == count)
        i = 0;
    if (count == 1)
        return 0;
    if (i == 0) {
        void* next = begin[1];
        if (!ComparePair(h, &px, next))
            return 0;
        float slerp = QuaternionSlerp(((VObj*)((char*)h + 0x34))->v2c(),
                                      (char*)h + 0x118,
                                      ((VObj*)((char*)next + 0x34))->v2c());
        if (slerp <= FUN_c64590(vec, 0, h, next))
            return 0;
        return (int)next;
    }
    if (i == count - 1) {
        void* prev = begin[i - 1];
        if (!ComparePair(h, &px, prev))
            return 0;
        float* p1 = (float*)((VObj*)((char*)prev + 0x34))->v2c();
        float* p2 = (float*)((VObj*)((char*)h + 0x34))->v2c();
        float dx = p2[0] - p1[0];
        float dy = p2[1] - p1[1];
        float dz = p2[2] - p1[2];
        float cp = CopyPairF(h, prev) + 0.5f;
        if ((float)sqrt((double)((dz * dz + dy * dy) + dx * dx)) - 0.05f <= cp)
            return 0;
        return (int)prev;
    }
    void* next = begin[i + 1];
    void* prev = begin[i - 1];
    float slerp = QuaternionSlerp(((VObj*)((char*)h + 0x34))->v2c(),
                                  (char*)h + 0x118,
                                  ((VObj*)((char*)next + 0x34))->v2c());
    float r1 = FUN_c64590(vec, i, h, next);
    float cp = CopyPairF(h, prev);
    if (ComparePair(h, &px, next) && slerp > r1 && cp > r1)
        return (int)next;
    if (!ComparePair(h, &px, prev))
        return 0;
    if (slerp <= cp)
        return 0;
    return (int)prev;
}

// @ 0x00c64880
void FUN_c64880(void** vec, void* a, void* b)
{
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    int count = (int)(((char*)end - (char*)begin) >> 2);
    int ia = 0;
    if (count > 0) {
        void** p = begin;
        for (int i = 0; i < count; ++i, ++p)
            if (*p == a) {
                ia = i;
                break;
            }
    }
    int ib = 0;
    if (count > 0) {
        void** p = begin;
        for (int i = 0; i < count; ++i, ++p)
            if (*p == b) {
                ib = i;
                break;
            }
    }
    void* old = begin[ia];
    if (b != old) {
        if (b)
            ((Ref*)b)->v0();
        begin[ia] = b;
        if (old)
            ((Ref*)old)->v1();
    }
    old = begin[ib];
    if (a != old) {
        if (a)
            ((Ref*)a)->v0();
        begin[ib] = a;
        if (old)
            ((Ref*)old)->v1();
    }
}

// @ 0x00c64940
void PathObj::Fn64940(void* h)
{
    int r = FUN_c64630((void**)((char*)this + 4), h, f18, f1c, f20);
    if (r)
        FUN_c64880((void**)((char*)this + 4), h, (void*)r);
    Fn64460(h);
    int* p = (int*)((VObj*)((char*)h + 0x34))->v2c();
    *(int*)((char*)this + 0x18) = p[0];
    *(int*)((char*)this + 0x1c) = p[1];
    *(int*)((char*)this + 0x20) = p[2];
}
