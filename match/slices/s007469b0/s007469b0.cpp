// Slice s007469b0 (0x007469B0..0x007478B0): SP::cModelWorld bounds/occluder/load-queue
// helpers plus EASTL deque/vector instantiations, built /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <new>
#include <string.h>
#include <math.h>

// /arch:SSE float -> int ceil (cvtss2si + cmovb): the original's asm helper, not
// ceilf (which this cl emits as an x87 control-word sequence).
#pragma warning(disable:4035)
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

struct Vec3 { float x, y, z; };

// --- retail types -----------------------------------------------------------
// Only declarations: the recovered bodies call straight into the original image.
// A receiver (ecx) that the image passes in a register is declared as a member,
// which is what reproduces the original argument shape (`ret n` included).
struct cHierGrid_s0070_3700 {                                  // hierarchical grid
    bool Shutdown();                                          // 0x00704060
    bool Init(const Vec3& bounds, float size, int a, int b);  // 0x00704260 (ret 0x10)
};
struct RBTree_e5c780 {                                         // eastl::rbtree<unsigned,...>
    void* find(int* out, const unsigned& key);                 // 0x00e5c780
};
struct PickCtx_7c4510 {                                        // cModelManager pick context
    int pick(float a, float b, void* v1, void* v2);            // 0x007c4510
};
struct ModelInst_73a800 {                                      // cModelInstance
    void SetFlags(int a, int b);                              // 0x0073a800
    void SetAnimationResource(void* res);                     // 0x00742cf0
    void AttachModel(void* model);                            // 0x0073ab40
};
struct AutoRef_7454f0 {                                        // AutoRefCount<T>::Release
    AutoRef_7454f0* Release();                                // 0x007454f0
};
struct BindingSet_7400f0 {                                     // BindingSet (in-place construct)
    void* Construct();                                        // 0x007400f0
};
struct DrawRecord_745f90 {                                     // DrawRecord (in-place construct)
    void* Construct(void* owner);                              // 0x00745f90
};

// --- free callees / globals -------------------------------------------------
void cHierGrid_Remove(void* grid, int id);                                     // 0x00704100
void FUN_00745560(void* out, int a, int b, int c, int d, int e, int f, int g, int h, int i); // 0x00745560
unsigned int FUN_00743b20(void* model);                                        // 0x00743b20
void FUN_00743b50(void* elem, void* dummy);                                    // 0x00743b50 (*elem = 0)
void FUN_0073a820(void* slot, void* dummy);                                    // 0x0073a820 (release *slot)
bool FUN_007453d0(void** out, void* model, unsigned flags);                    // 0x007453d0
void FUN_00745340(void);                                                       // 0x00745340
int  SP_GetPropertyAsIntArray(void* props, uint32_t key, int* count, int* data); // 0x006a07d0
void* operator_new(uint32_t n, const char* name, int a, int b, int c, int d);  // allocator
void  operator_delete_(void* p);
void* RBTreeIncrement_921580(void* node);                                      // 0x00921580
void __stdcall ehvec_ctor_11e0b85(void* ptr, unsigned size, unsigned count, void* ctor, void* dtor); // 0x011e0b85
void __stdcall ehvec_dtor_11e0b22(void* ptr, unsigned size, unsigned count, void* dtor);             // 0x011e0b22

// A refcounted object whose refcount lives at +4 and has a Release at vtable[4].
struct RCObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    int mRefCount;   // +4
};

// cModelWorld modelled with the retail byte offsets used below.
struct OccInfo { int mId; Vec3 mPosition; float mRadius; };   // 0x14
struct CModelWorld {
    unsigned char pad0[0x14];
    int mNumModels;                      // +0x14 (anchor of mModelList dummy)
    unsigned char pad18[0x2bc - 0x18];
    OccInfo* mOccluders;                 // +0x2bc

    void SetWorldBounds(Vec3 bounds[2], float a, float b);
    void UpdateOccluder(int idx, Vec3* pos, float radius);
    void ShutdownModel(int model);
};

// @ 0x007469b0 : SP::cModelWorld::SetWorldBounds
void CModelWorld::SetWorldBounds(Vec3 bounds[2], float param_3, float param_4)
{
    float d[3];
    d[0] = bounds[1].x - bounds[0].x;
    d[1] = bounds[1].y - bounds[0].y;
    d[2] = bounds[1].z - bounds[0].z;

    float* p = d + 1;
    if (!(d[1] > d[0])) p = d;
    if (d[2] > *p) p = d + 2;
    float dim = *p;

    unsigned char* b = (unsigned char*)this;
    if (*(void**)(b + 0x13c) != *(void**)(b + 0x140))
        ((cHierGrid_s0070_3700*)(b + 0x118))->Shutdown();

    for (unsigned char* n = *(unsigned char**)(b + 0x19c); n != b + 0x19c; n = *(unsigned char**)n)
        *(int*)(n + 0x120) = -1;

    if (!(bounds[0].x > bounds[1].x)) {
        float two = dim * 2.0f;
        float q3 = two / (param_3 + 1e-08f);      // grid cell count along param_3
        float q4 = two / (param_4 + 1e-08f);      // grid cell count along param_4

        int c4 = CeilToInt(q4);
        float f4 = (float)(unsigned)c4;
        int e4 = (int)(((*(uint32_t*)&f4) >> 0x17) - 0x7f);   // floor(log2(c4))

        int c3 = CeilToInt(q3);
        float f3 = (float)(unsigned)c3;
        int e3 = (int)(((*(uint32_t*)&f3) >> 0x17) - 0x7f);

        int lvl = e4 > 0 ? e4 : 0;
        int lv2 = e3 < 7 ? e3 : 7;
        if (lv2 < lvl) lv2 = lvl;

        ((cHierGrid_s0070_3700*)(b + 0x118))->Init(*(const Vec3*)bounds, dim, lvl, lv2);
    }
}

// @ 0x00746b40 : SP::cModelWorld::UpdateOccluder
void CModelWorld::UpdateOccluder(int idx, Vec3* pos, float radius)
{
    mOccluders[idx].mPosition = *pos;
    mOccluders[idx].mRadius = radius;
}

// @ 0x00746b90 : SP::cModelWorld::ShutdownModel
struct VViewer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                 virtual void v8(); };
void cModelWorld_ShutdownModel(CModelWorld* self, int model)
{
    unsigned char* b = (unsigned char*)self;
    if (*(int*)(model + 0x120) >= 0) {
        cHierGrid_Remove(b + 0x118, *(int*)(model + 0x120));
        *(int*)(model + 0x120) = -1;
    }
    if (*(int*)(model + 0x134) != 0) {
        VViewer* v = *(VViewer**)(b + 0x224);
        // vtable slot at +0x20
        (*(void(__thiscall**)(VViewer*, int))(((char*)(*(void**)v) + 0x20)))(v, *(int*)(model + 0x134));
        *(int*)(model + 0x134) = 0;
    }
    int p = *(int*)(model + 0xdc);
    if (p) {
        int q = p + 8;
        int* it = *(int**)(p + 8);
        while (it) {
            (*(void(__thiscall**)(int*, int))((char*)(*it) + 0xc))(it, 1);
            int* nx = (int*)(q + 0x48);
            q += 0x48;
            it = (int*)*nx;
        }
        int* raw = (int*)p;
        operator_delete_((char*)raw - 4);
        *(int*)(model + 0xdc) = 0;
    }
    if (*(int**)(model + 0xe0)) {
        int* arr = *(int**)(model + 0xe0);
        int n = *arr;
        for (int i = 0; i < n; ++i) {
            int v = *(int*)(arr + 5 + i);
            if (v != -1) {
                VViewer* vw = *(VViewer**)(b + 0x224);
                (*(void(__thiscall**)(VViewer*, int))(((char*)(*(void**)vw) + 0x14)))(vw, v);
                *(int*)(arr + 5 + i) = -1;
            }
        }
        operator_delete_(arr);
        *(int*)(model + 0xe0) = 0;
    }
    unsigned char* l = *(unsigned char**)(b + 0x4c);
    unsigned char* e = *(unsigned char**)(b + 0x50);
    for (; l != e; l += 4)
        (*(void(__thiscall**)(void*, void*))((char*)(**(void***)l) + 4))(*(void**)l, (void*)(model + 8));
}

// @ 0x00746cc0 : rbtree<unsigned, AutoRefCount<cFeedbackEvent>>::find passthrough
int __fastcall FUN_00746cc0(void* self, void* dummy, unsigned key)
{
    unsigned char* b = (unsigned char*)self;
    int it;
    ((RBTree_e5c780*)(b + 0xc))->find(&it, key);
    if (it != (int)(b + 0x10))
        return *(int*)(it + 0x14);
    return 0;
}

// @ 0x00746cf0 : SP::cModelManager::DebugPick (PDB candidate)
// Context block handed to the object's pick entry point.
struct PickFilter {
    int m0;                    // +0x00
    int m1;                    // +0x04
    int m2;                    // +0x08
    int m3;                    // +0x0c
    int mCallback;             // +0x10 (FUN_00743b20)
    unsigned char mMode;       // +0x14
    unsigned char mPad;        // +0x15
};

int __fastcall FUN_00746cf0(void* self, void* dummy, float a1, float a2, void* ctx)
{
    unsigned char* b = (unsigned char*)self;
    unsigned char* anchor = b + 0x10;
    float best = 0.0f;
    int hit = 0;
    unsigned char found = 0;
    int vec24[3];
    int vec30[3];

    ((PickCtx_7c4510*)ctx)->pick(a1, a2, vec24, vec30);

    PickFilter filter;
    filter.m0 = 0;
    filter.m1 = 0;
    filter.m2 = 0;
    filter.m3 = 0;
    filter.mCallback = (int)FUN_00743b20;
    filter.mMode = 4;
    filter.mPad = 0;

    unsigned char* node = *(unsigned char**)(b + 0x14);
    if (node != anchor) {
        do {
            void* obj = *(void**)(node + 0x14);
            if (*((char*)obj + 0x24) != 0) {
                int r = (*(int(__thiscall**)(void*, void*, void*, float*, PickFilter*))
                         ((char*)(*(void**)obj) + 0x28))(obj, vec24, vec30, &a2, &filter);
                if (r != 0 && a2 > best) { best = a2; hit = r; }
                found = 1;
            }
            node = (unsigned char*)RBTreeIncrement_921580(node);
        } while (node != anchor);
        if (hit != 0) {
            if ((*(uint32_t*)(hit + 4) >> 6 & 1) == 0) *(uint32_t*)(hit + 4) |= 0x40;
            else                                      *(uint32_t*)(hit + 4) &= ~0x40;
        }
    }
    return found;
}

// @ 0x00746de0 : cLoadQueue-ish record constructor (0x48 bytes)
struct Mat3 {
    float m[9];
    void Assign(const void* src);                              // 0x0041cb40
};
struct Rec48 {
    int a, b, c;      // +0 +4 +8
    short d;          // +0xc
    short e;          // +0xe
    Vec3 pos;         // +0x10
    float scale;      // +0x1c
    Mat3 rot;         // +0x20
    unsigned char f;  // +0x44
    Rec48();
};
extern float g_f162eb0c, g_f162eb10, g_f162eb14, g_f162ec38, g_f162ec4c, g_f1485720;
void Matrix3_Assign(void* dst, const void* src);            // 0x0041cb40
Rec48::Rec48()
{
    a = -1;
    b = -1;
    c = 0;
    d = 0;
    e = 0;
    pos.x = g_f162eb0c;
    pos.y = g_f162eb10;
    pos.z = g_f162eb14;
    scale = g_f1485720;
    rot.Assign(&g_f162ec38);
    f = 1;
}
#pragma inline_depth(0)
Rec48* MakeRec48(Rec48* p) { return new (p) Rec48(); }
#pragma inline_depth()

// @ 0x00746e50 : big load-entry constructor
void __fastcall FUN_00746e50(void* self, void* dummy, void* owner)
{
    unsigned char* b = (unsigned char*)self;
    *(int*)(b + 0x00) = 0;
    *(int*)(b + 0x04) = 0;
    ((DrawRecord_745f90*)(b + 8))->Construct(owner);
    // the two 6 x 4-byte ref arrays at +0x9c / +0xb4 are element-constructed to 0
    ehvec_ctor_11e0b85(b + 0x9c, 4, 6, (void*)FUN_00743b50, (void*)FUN_0073a820);
    ehvec_ctor_11e0b85(b + 0xb4, 4, 6, (void*)FUN_00743b50, (void*)FUN_0073a820);
    *(int*)(b + 0xd4) = 0;
    *(int*)(b + 0xd8) = 0;
    *(int*)(b + 0xdc) = 0;
    *(int*)(b + 0xe0) = 0;
    *(short*)(b + 0xe6) = 0;
    *(short*)(b + 0xe4) = 0;
    *(float*)(b + 0xe8) = g_f162eb0c;
    *(float*)(b + 0xec) = g_f162eb10;
    *(float*)(b + 0xf0) = g_f162eb14;
    *(float*)(b + 0xf4) = g_f1485720;
    ((Mat3*)(b + 0xf8))->Assign(&g_f162ec4c);
    *(float*)(b + 0x11c) = g_f1485720;
    *(int*)(b + 0x120) = -1;
    *(unsigned char*)(b + 0x128) = 0;
    *(unsigned char*)(b + 0x129) = 0;
    *(float*)(b + 0x124) = 0.0f;
    *(short*)(b + 0x12a) = 0;
    *(int*)(b + 0x12c) = 0;
    *(int*)(b + 0x130) = 0;
    *(int*)(b + 0x134) = 0;
    *(int*)(b + 0x138) = 0;
    *(short*)(b + 0x70) = 0;
    *(int*)(b + 0x0c) |= 0x80000;
    *(int*)(b + 0xcc) = -1;
    *(short*)(b + 0xd0) = (short)0xffff;
}

// @ 0x00746fc0 : big load-entry destructor
void FUN_00746fc0(void* self)
{
    unsigned char* b = (unsigned char*)self;
    void* p = *(void**)(b + 0xdc);
    if (p) {
        operator_delete_((char*)p - 4);
        *(void**)(b + 0xdc) = 0;
    }
    if (*(int*)(b + 0xe0)) {
        operator_delete_(*(void**)(b + 0xe0));
        *(void**)(b + 0xe0) = 0;
    }
    RCObj* r = (RCObj*)*(void**)(b + 0xd8);
    if (r) {
        if (--r->mRefCount == 0) { r->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)r))(r, 1); }
    }
    for (int i = 0; i < 6; ++i) {
        RCObj* q = (RCObj*)*(void**)(b + 0xb4 + i * 4);
        if (q && --q->mRefCount == 0) { q->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)q))(q, 1); }
        RCObj* s = (RCObj*)*(void**)(b + 0x9c + i * 4);
        if (s && --s->mRefCount == 0) { s->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)s))(s, 1); }
    }
    FUN_00745340();
}

struct Stub007470c0 { void F(); };
// @ 0x007470c0 : partial destructor of referenced members
void Stub007470c0::F()
{
    unsigned char* b = (unsigned char*)this;
    void* volatile self = this;
    *(int*)(b + 0x138) = 0x8000000;
    RCObj* p = (RCObj*)*(void**)(b + 0x98);
    if (p) { *(void**)(b + 0x98) = 0; (*(void(__thiscall**)(RCObj*))(((char*)(*(void**)p) + 4)))(p); }
    RCObj* q = (RCObj*)*(void**)(b + 0x6c);
    if (q) { *(void**)(b + 0x6c) = 0; (*(void(__thiscall**)(RCObj*))(((char*)(*(void**)q) + 4)))(q); }
    unsigned char* slot = b + 0xb4;
    int n = 6;
    do {
        RCObj* a = (RCObj*)*(void**)(slot - 0x18);
        if (a) {
            *(void**)(slot - 0x18) = 0;
            int ac = a->mRefCount;
            a->mRefCount = ac - 1;
            if (ac - 1 == 0) { a->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)a))(a, 1); }
        }
        RCObj* c = (RCObj*)*(void**)(slot);
        if (c) {
            *(void**)(slot) = 0;
            int cc = c->mRefCount;
            c->mRefCount = cc - 1;
            if (cc - 1 == 0) { c->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)c))(c, 1); }
        }
        slot += 4;
    } while (--n);
    RCObj* r = (RCObj*)*(void**)(b + 0xd8);
    if (r) {
        *(void**)(b + 0xd8) = 0;
        int rc = r->mRefCount;
        r->mRefCount = rc - 1;
        if (rc - 1 == 0) { r->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)r))(r, 1); }
    }
    self = this;
}

struct Stub00747190 { void* F(int* src); };
// @ 0x00747190 : copy-assign of an entry (ptr + 6 dwords)
void* Stub00747190::F(int* src)
{
    int* dst = (int*)this;
    *dst = *src;
    int* old = (int*)dst[1];
    int* nw = (int*)src[1];
    if (nw != old) {
        if (nw) (*(void(__thiscall**)(int*))(*(void**)nw))(nw);
        dst[1] = (int)nw;
        if (old) (*(void(__thiscall**)(int*, int))(((char*)(*(void**)old) + 4)))(old, 1);
    }
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    return dst;
}

// @ 0x007471f0 : SP::cModelWorld::cLoadingModel::cLoadingModel
void __fastcall FUN_007471f0(void* self, void* dummy)
{
    unsigned char* b = (unsigned char*)self;
    *(int*)(b + 0x00) = 0;
    *(int*)(b + 0x04) = 0;
    *(int*)(b + 0x08) = 0;
    *(int*)(b + 0x0c) = 0;
    *(int*)(b + 0x10) = 0;
    *(int*)(b + 0x14) = 0;
    *(int*)(b + 0x18) = 0;
    *(unsigned char*)(b + 0x1c) = 0;
    *(int*)(b + 0x20) = 0;
    *(int*)(b + 0x24) = 0;
    *(int*)(b + 0x28) = 0;
    *(int*)(b + 0x2c) = 6;
    *(int*)(b + 0x30) = 0;
    ehvec_ctor_11e0b85(b + 0x34, 4, 6, (void*)FUN_00743b50, (void*)FUN_0073a820);
}

struct CJobObj_s007469b0 {
    int Release();  // 0x00690120 (thiscall, no stack args)
};

struct Stub00747270 { void F(); };
// @ 0x00747270 : SP::cModelWorld::cLoadingModel::~cLoadingModel
void Stub00747270::F()
{
    unsigned char* b = (unsigned char*)this;
    ehvec_dtor_11e0b22(b + 0x34, 4, 6, (void*)FUN_0073a820);
    if (*(void**)(b + 0x30)) ((CJobObj_s007469b0*)*(void**)(b + 0x30))->Release();
    void* p = *(void**)(b + 0x28);
    if (p) {
        int cnt = *(int*)((char*)p + 0x40);
        if (cnt < 2) {
            int bit = (int)((*(unsigned int*)((char*)p + 4) >> 31) & 1u);
            void* q = *(void**)p;
            void** vt = *(void***)q;
            ((void(__thiscall*)(void*, void*, int))(vt[0x170 / 4]))(q, p, bit);
        } else {
            *(int*)((char*)p + 0x40) = cnt - 1;
        }
    }
    if (*(void**)(b + 0x24)) ((CJobObj_s007469b0*)*(void**)(b + 0x24))->Release();
    if (*(void**)(b + 0x20)) ((CJobObj_s007469b0*)*(void**)(b + 0x20))->Release();
    volatile int epilogue = 0;
    RCObj* r = (RCObj*)*(void**)(b + 0x04);
    if (r) (*(void(__thiscall**)(RCObj*))(((char*)(*(void**)r) + 4)))(r);
    epilogue = 1;
}

// Rebuild every non-empty slot from its stored model reference: this is the tail
// shared by the "no property array" path and the bail-out of the resolved path.
static void RefreshSlotsStraight(unsigned char* b)
{
    int k = 0;
    for (int i = 0; i < 6; ++i) {
        if (*(int*)(b + 0x9c + i * 4) == 0) continue;
        int* slot = (int*)(b + 0xb4 + i * 4);
        void* model = *(void**)(b + 0x9c + i * 4);
        *(char*)(b + 0xcc + i) = (char)k;
        void* old = *(void**)slot;
        if (old) {
            *slot = 0;
            if (--*(int*)((char*)old + 4) == 0) {
                *(int*)((char*)old + 4) = 1;
                (*(void(__thiscall**)(void*, int))(*(void**)old))(old, 1);
            }
        }
        FUN_007453d0((void**)slot, model, *(unsigned*)(b + 0x138));
        ((ModelInst_73a800*)(*(void**)(b + 0x9c + i * 4)))->AttachModel(*(void**)slot);
        ++k;
    }
}

// @ 0x00747340 : load-queue model-slot refresh
void __fastcall FUN_00747340(void* self, void* dummy)
{
    unsigned char* b = (unsigned char*)self;
    int count = 0;
    int data = 0;

    if (!SP_GetPropertyAsIntArray(*(void**)(b + 0x98), 0x60cbbef, &count, &data)) {
        RefreshSlotsStraight(b);
        return;
    }

    // 1) resolve the requested subset into local[]
    int local[6];
    ehvec_ctor_11e0b85(local, 4, 6, (void*)FUN_00743b50, (void*)FUN_0073a820);

    int bail = 0;
    for (int i = 0; i < 6; ++i) {
        if (*(int*)(b + 0x9c + i * 4) == 0) continue;
        if (i >= count) continue;
        unsigned idx = *(unsigned*)(data + i * 4);
        if (idx > 5) continue;
        void* src = *(void**)(b + 0x9c + idx * 4);
        if (src == 0) { bail = 1; break; }
        if (local[idx] == 0) {
            int* slot = (int*)((AutoRef_7454f0*)&local[idx])->Release();
            FUN_007453d0((void**)slot, src, *(unsigned*)(b + 0x138));
        }
    }

    if (bail) {
        ehvec_dtor_11e0b22(local, 4, 6, (void*)FUN_0073a820);
        RefreshSlotsStraight(b);
        return;
    }

    // 2) compact the kept references into the slots, build index -> slot map
    signed char map[8];
    int k = 0;
    for (int i = 0; i < 6; ++i) {
        int v = local[i];
        if (v == 0) { map[i] = -1; continue; }
        int* slot = (int*)(b + 0xb4 + k * 4);
        int old = *slot;
        if (v != old) {
            if (v) ++*(int*)(v + 4);
            *slot = v;
            if (old) {
                if (--*(int*)(old + 4) == 0) {
                    *(int*)(old + 4) = 1;
                    (*(void(__thiscall**)(int, int))(*(void**)old))(old, 1);
                }
            }
        }
        map[i] = (signed char)k;
        ++k;
    }

    // 3) point every live entry at its slot, synthesising one when unmapped
    for (int i = 0; i < 6; ++i) {
        if (*(int*)(b + 0x9c + i * 4) == 0) continue;
        if (i < count && *(unsigned*)(data + i * 4) <= 5) {
            signed char s = map[*(unsigned*)(data + i * 4)];
            *(char*)(b + 0xcc + i) = s;
            ((ModelInst_73a800*)(*(void**)(b + 0x9c + i * 4)))->AttachModel(*(void**)(b + 0xb4 + s * 4));
        } else {
            void* obj = operator_new(0xa0, "Graphics/ModelManager/StaticAnimations", 0, 0, 0, 0);
            if (obj) obj = ((BindingSet_7400f0*)obj)->Construct();
            if (obj) ++*(int*)((char*)obj + 4);
            ((ModelInst_73a800*)obj)->SetFlags(1, 0);
            ((ModelInst_73a800*)obj)->SetAnimationResource(0);
            ((ModelInst_73a800*)(*(void**)(b + 0x9c + i * 4)))->AttachModel(obj);
            *(char*)(b + 0xcc + i) = -1;
            if (obj) {
                if (--*(int*)((char*)obj + 4) == 0) {
                    *(int*)((char*)obj + 4) = 1;
                    (*(void(__thiscall**)(void*, int))(*(void**)obj))(obj, 1);
                }
            }
        }
    }
    ehvec_dtor_11e0b22(local, 4, 6, (void*)FUN_0073a820);
}

// @ 0x00747640 : deque entry lookup helper
int __fastcall FUN_00747640(void* self, void* dummy, int* key)
{
    unsigned char* b = (unsigned char*)self;
    int local[4];
    FUN_00745560(local, *(int*)(b + 0x28c), *(int*)(b + 0x290), *(int*)(b + 0x294),
                 *(int*)(b + 0x298), *(int*)(b + 0x29c), *(int*)(b + 0x2a0),
                 *(int*)(b + 0x2a4), *(int*)(b + 0x2a8), *key);
    return local[0] != *(int*)(b + 0x29c);
}

// @ 0x00747720 : deque< cLoadQueueEntry >::~deque
void FUN_00747720(int* d)
{
    int beg = d[2], end = d[4], map = d[5];
    if (beg != d[6]) {
        do {
            RCObj* r = (RCObj*)*(void**)(beg + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            beg += 0x1c;
            if (beg == end) { beg = *(int*)(map + 4); map += 4; end = beg + 0xe0; }
        } while (beg != d[6]);
    }
    if (*d != 0) {
        int last = d[9];
        for (int* p = (int*)d[5]; p < (int*)(last + 4); ++p)
            if (*p) operator_delete_((void*)*p);
        operator_delete_((void*)*d);
    }
}

// @ 0x007477d0 : deque< cLoadQueueEntry >::clear
void FUN_007477d0(int self)
{
    unsigned char* b = (unsigned char*)self;
    uint32_t start = *(uint32_t*)(b + 8);
    if (*(int*)(b + 0x14) == *(int*)(b + 0x24)) {
        while (start < *(uint32_t*)(b + 0x18)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
    } else {
        while (start < *(uint32_t*)(b + 0x10)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
        start = *(uint32_t*)(b + 0x1c);
        while (start < *(uint32_t*)(b + 0x18)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
        if (*(int*)(b + 0x1c)) operator_delete_(*(void**)(b + 0x1c));
    }
    uint32_t* p = (uint32_t*)(*(int*)(b + 0x14) + 4);
    while (p < *(uint32_t**)(b + 0x24)) {
        uint32_t base = *p;
        for (uint32_t q = base; q < base + 0xe0; q += 0x1c) {
            RCObj* r = (RCObj*)*(void**)(q + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
        }
        if (*p) operator_delete_((void*)*p);
        ++p;
    }
    *(int*)(b + 0x18) = *(int*)(b + 8);
    *(int*)(b + 0x1c) = *(int*)(b + 0xc);
    *(int*)(b + 0x20) = *(int*)(b + 0x10);
    *(int*)(b + 0x24) = *(int*)(b + 0x14);
}

// @ 0x007478b0 : vector< cLoadQueueEntry, fixed_vector_allocator >::~vector
void FUN_007478b0(uint32_t* v)
{
    uint32_t beg = *v, end = v[1];
    for (; beg < end; beg += 0x1c) {
        RCObj* r = (RCObj*)*(void**)(beg + 4);
        if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
    }
    if (*v != 0 && *v != v[4])
        operator_delete_((void*)*v);
}
