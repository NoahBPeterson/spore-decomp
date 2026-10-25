// Slice s006eae40 -- effects camera manager, render-entity copy/sort/dtor helpers, and the
// effects renderer's buffered-model flush (0x006eae40).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <string.h>
#include <intrin.h>
#include <xmmintrin.h>
#include <math.h>
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

struct Vec3 { float x, y, z; };
static inline Vec3 MakeV3(float c) { Vec3 v; v.x = c; v.y = c; v.z = c; return v; }

struct E7 {
    void GetImageResource(void*);   // refcount-copy helper (0x576650)
    void r41cb40(void*);            // rw::math::Matrix33::Assign
};

extern void   f_f47380(void*);
extern void   f7c4d00(int);
extern float  g1533c74;

#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]

// ---- free helpers ----
void __stdcall f990(char* p1, char* p2);             // 0x6eb990
void f9d0(uint* p1, uint* p2, int extra);            // 0x6eb9d0
void fbe50(uint* p1, uint* p2, uint v);              // 0x6ebe50
void fbea0(uint* p1, uint* p2, uint* p3, int p4);    // 0x6ebea0
extern void f_ac2060(uint*, int, int, int, uint, uint, int);
extern void f_ac3fa0(uint*, uint*, int);

struct CEM7 {
    char m[0x20];
    void UpdateCameraView(int a, uint flags);
};

struct S7 {
    char m_unk[0x240];
    void m6eb8c0(void* src);
    S7*  m6ebb80(void* src);
    S7*  mebf50();
    void mec090();
};

// ---------------------------------------------------------------------------
// @ 0x006eae40  SP::cEffectsRenderer::ReleaseAndDrawModelBuffer (see the end of this file)

// ---------------------------------------------------------------------------
// @ 0x006eb6e0  SP::cEffectsCameraManager::UpdateCameraView
void CEM7::UpdateCameraView(int a, uint flags)
{
    char* self = (char*)this;
    void* cam = *(void**)(self + 0xc);
    if (cam == 0 || ((int(__thiscall*)(void*))VFN(cam, 0x3c))(cam) == 0) {
        f7c4d00(a);
        return;
    }
    float v[3];
    v[0] = *(float*)(a + 4);
    v[1] = *(float*)(a + 8);
    v[2] = *(float*)(a + 0xc);
    if (flags & 1) {
        if (flags & 0x10)
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101b542, v);
        else
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101b541, v);
    } else {
        if (flags & 0x10)
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101b537, v);
        else
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101b534, v);
    }
    if (flags & 8) {
        cam = *(void**)(self + 0xc);
        float q = *(float*)(a + 0x10);
        if (flags & 0x10)
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101d445, &q);
        else
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101d4c7, &q);
    }
    if (flags & 2) {
        cam = *(void**)(self + 0xc);
        float q[4];
        q[0] = *(float*)(a + 0x18);
        q[1] = *(float*)(a + 0x1c);
        q[2] = *(float*)(a + 0x20);
        q[3] = *(float*)(a + 0x24);
        if (flags & 0x10)
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101d51f, q);
        else
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101d576, q);
    }
}

// ---------------------------------------------------------------------------
// The 0x68-byte render-entity element whose copy constructor is 0x006eb8c0. The compiler
// generates the member-wise copy from these declarations; the non-trivial member destructors
// are what make cl wrap the copy constructor in an exception frame (state 0 records `this`).
struct RefCounted {
    virtual void v0();
    int mRefCount;                     // +0x4 (bumped by the +0x00 member's inlined copy)
};
struct RefCountedVirt {                // +0x60 member: its copy calls vtable slot 0
    virtual void v0();
    int mRefCount;
};
// +0x00 member: intrusive pointer, copy increments the pointee's refcount inline.
struct SmartPtrRef {
    RefCounted* mp;
    SmartPtrRef() : mp(0) {}
    SmartPtrRef(const SmartPtrRef& o) : mp(o.mp) { if (mp) mp->mRefCount++; }
    ~SmartPtrRef() { if (mp) mp->mRefCount--; }
};
// +0x60 member: intrusive pointer, copy calls the pointee's virtual slot 0 inline.
struct SmartPtrVirt {
    RefCountedVirt* mp;
    SmartPtrVirt() : mp(0) {}
    SmartPtrVirt(const SmartPtrVirt& o) : mp(o.mp) { if (mp) mp->v0(); }
    ~SmartPtrVirt() { if (mp) mp->mRefCount--; }
};
struct Matrix33 {                      // +0x2c (copy constructor 0x0041cb40, out of line)
    float m[9];
    Matrix33(const Matrix33&);
};
struct RenderEntity {
    SmartPtrRef  mBase;                // +0x00
    float        mF4, mF8, mFC, mF10, mF14;   // +0x04
    unsigned short mW18, mW1A;         // +0x18
    float        mG1C, mG20, mG24, mG28;      // +0x1c
    Matrix33     mMat;                 // +0x2c
    char         mA;                   // +0x50
    char         mB;                   // +0x51
    int          mI0, mI1, mI2;        // +0x54
    SmartPtrVirt mExtra;               // +0x60
    int          mI3;                  // +0x64
    RenderEntity(const RenderEntity& src);
};

// @ 0x006eb8c0
RenderEntity::RenderEntity(const RenderEntity& src)
    : mBase(src.mBase), mF4(src.mF4), mF8(src.mF8), mFC(src.mFC), mF10(src.mF10),
      mF14(src.mF14), mW18(src.mW18), mW1A(src.mW1A), mG1C(src.mG1C), mG20(src.mG20),
      mG24(src.mG24), mG28(src.mG28), mMat(src.mMat), mA(src.mA), mB(src.mB),
      mI0(src.mI0), mI1(src.mI1), mI2(src.mI2), mExtra(src.mExtra), mI3(src.mI3) {}

// ---------------------------------------------------------------------------
// @ 0x006eb990
void __stdcall f990(char* p1, char* p2)
{
    for (; p1 < p2; p1 += 0x70) {
        void* r = *(void**)(p1 + 0x28);
        if (r != 0) {
            int v = (*(volatile int*)((char*)r + 4) += -1);
            if (v == 0) {
                *(int*)((char*)r + 4) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(void*, int))VFN(r, 0))(r, 1);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006eb9d0
void f9d0(uint* p1, uint* p2, int extra)
{
    int n = (int)p2 - (int)p1 >> 3;
    if (n > 1) {
        uint* e = p2 - 2;
        do {
            uint a = e[0], b = e[1];
            e[0] = p1[0];
            e[1] = p1[1];
            f_ac2060(p1, 0, n - 1, 0, a, b, extra);
            e -= 2;
            n = (8 - (int)p1) + (int)e >> 3;
        } while (n > 1);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ebb80
S7* S7::m6ebb80(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    *(uint*)d = *(uint*)s;
    memcpy(d + 8, s + 8, 32);
    ((E7*)(d + 0x28))->GetImageResource(*(void**)(s + 0x28));
    ((E7*)(d + 0x2c))->GetImageResource(*(void**)(s + 0x2c));
    *(uint*)(d + 0x3c) = *(uint*)(s + 0x3c);
    *(uint*)(d + 0x40) = *(uint*)(s + 0x40);
    *(uint*)(d + 0x44) = *(uint*)(s + 0x44);
    *(uint*)(d + 0x30) = *(uint*)(s + 0x30);
    *(uint*)(d + 0x34) = *(uint*)(s + 0x34);
    *(uint*)(d + 0x38) = *(uint*)(s + 0x38);
    *(uchar*)(d + 0x48) = *(uchar*)(s + 0x48);
    *(uchar*)(d + 0x49) = *(uchar*)(s + 0x49);
    *(uint*)(d + 0x4c) = *(uint*)(s + 0x4c);
    *(uint*)(d + 0x50) = *(uint*)(s + 0x50);
    *(uint*)(d + 0x54) = *(uint*)(s + 0x54);
    *(float*)(d + 0x58) = *(float*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    *(uint*)(d + 0x60) = *(uint*)(s + 0x60);
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    *(uint*)(d + 0x68) = *(uint*)(s + 0x68);
    void* n = *(void**)(s + 0x6c);
    _ReadWriteBarrier();
    void* o = *(void**)(d + 0x6c);
    if (n != o) {
        if (n)
            ((void(__thiscall*)(void*))VFN(n, 4))(n);
        *(void**)(d + 0x6c) = n;
        if (o)
            ((void(__thiscall*)(void*))VFN(o, 8))(o);
    }
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x006ebe50
void fbe50(uint* p1, uint* p2, uint v)
{
    while (1) {
        while (*p1 > v)
            p1 += 2;
        p2 -= 2;
        while (*p2 < v)
            p2 -= 2;
        if (p2 <= p1)
            break;
        uint a = p1[0], b = p1[1];
        p1[0] = p2[0];
        p1[1] = p2[1];
        p2[0] = a;
        p2[1] = b;
        p1 += 2;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ebea0
void fbea0(uint* p1, uint* p2, uint* p3, int p4)
{
    f_ac3fa0(p1, p2, p4);
    for (uint* it = p2; it < p3; it += 2) {
        uint a = *it;
        if (*p1 < a) {
            uint b = it[1];
            *it = *p1;
            it[1] = p1[1];
            f_ac2060(p1, 0, ((int)p2 - (int)p1) >> 3, 0, a, b, p4);
        }
    }
    f9d0(p1, p2, p4);
}

// ---------------------------------------------------------------------------
// @ 0x006ebf50
S7* S7::mebf50()
{
    char* p = (char*)this;
    float C = g1533c74;
    *(void**)p = (void*)0x140afd4;
    *(int*)(p + 4) = 0;
    char* q = p + 0x20;
    *(void**)(p + 0x18) = q;
    *(void**)(p + 0xc) = q;
    *(void**)(p + 8) = q;
    *(void**)(p + 0x10) = p + 0x50;
    *(Vec3*)(p + 0x50) = MakeV3(C);
    *(Vec3*)(p + 0x5c) = MakeV3(-C);
    *(float*)(p + 0x68) = 0.0f;
    *(int*)(p + 0x6c) = 0;
    char* q2 = p + 0x88;
    *(void**)(p + 0x80) = q2;
    *(void**)(p + 0x74) = q2;
    *(void**)(p + 0x70) = q2;
    *(void**)(p + 0x78) = p + 0x98;
    return this;
}

// ---------------------------------------------------------------------------
// The class whose destructor is 0x006ec000. It has no virtual functions of its own: the shared
// refcount dispatch table 0x013ef094 (the ICF-folded GmeRefCount vtable) is installed by its
// constructor 0x006ebf50 and restored by the inlined base destructor at the end of ~FxEntity.
// Layout: fixed-buffer vector at +0x08 (inline storage at +0x20), scalars +0x50..+0x68, a
// refcounted pointer at +0x6c and an eastl::vector<AutoRefCount<cPropertyList>> at +0x70.
struct RefBase {
    void* mpTable;                     // +0x00  dispatch table (0x013ef094)
    int   mRefCount;                   // +0x04
    ~RefBase() { mpTable = (void*)0x013ef094; }
};
void __cdecl FreeBlock(void* p) throw();       // 0x00f47380 (operator delete)

// +0x08: eastl vector with a fixed_vector_allocator whose inline storage begins at mpInline.
struct FixedVec {
    void* mpBegin;                     // +0x00
    void* mpEnd;                       // +0x04
    void* mpCap;                       // +0x08
    void* mpReserved;                  // +0x0c
    void* mpInline;                    // +0x10
    ~FixedVec() { if (mpBegin && mpBegin != mpInline) FreeBlock(mpBegin); }
};
// +0x6c: intrusive pointer released through vtable slot +4.
struct SmartRef {
    void* mp;
    ~SmartRef() { if (mp) ((void(__thiscall*)(void*))VFN(mp, 4))(mp); }
};
// +0x70: eastl vector whose destructor (0x007c80c0) is out of line.
struct PropVec {
    void* mpBegin; void* mpEnd; void* mpCap; void* mpReserved; void* mpInline;
    ~PropVec();
};
struct FxEntity : RefBase {
    FixedVec  mCont;                   // +0x08
    int       mGap1C;                  // +0x1c
    int       mInline[12];             // +0x20
    Vec3      mV50;                    // +0x50
    Vec3      mV5C;                    // +0x5c
    float     mF68;                    // +0x68
    SmartRef  mPtr6C;                  // +0x6c
    PropVec   mProp;                   // +0x70
    ~FxEntity();
};

// @ 0x006ec000
FxEntity::~FxEntity() {}


// ---------------------------------------------------------------------------
// @ 0x006ec090
void S7::mec090()
{
    char* p = (char*)this;
    int i = *(int*)(p + 4);
    if ((int)((*(int*)(p + 0xc) - i) & 0xfffffffe) > 2 && i != 0 && i != *(int*)(p + 0x14))
        f_f47380((void*)i);
}

// ===========================================================================
// SP::cEffectsRenderer::ReleaseAndDrawModelBuffer (0x006eae40)
// ===========================================================================
struct V3 {                                                         // 3 floats with a user copy ctor (movss copies)
    float x, y, z;
    V3() {}
    V3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    V3(const V3& o) : x(o.x), y(o.y), z(o.z) {}
};

__declspec(align(16)) struct Vector4 {
    union {
        __m128 m;
        struct { float x, y, z, w; };
    };
    Vector4() {}
    Vector4(float ax, float ay, float az, float aw) { m = _mm_set_ps(aw, az, ay, ax); }
    Vector4(const Vector4& o) : m(o.m) {}
    Vector4& operator=(const Vector4& o) { m = o.m; return *this; }
};

// Direct3D 9 device: only SetStreamSourceFreq (vtable +0x198) is used here.
struct IDirect3DDevice9 {
    virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
    virtual void pv4(); virtual void pv5(); virtual void pv6(); virtual void pv7();
    virtual void pv8(); virtual void pv9(); virtual void pv10(); virtual void pv11();
    virtual void pv12(); virtual void pv13(); virtual void pv14(); virtual void pv15();
    virtual void pv16(); virtual void pv17(); virtual void pv18(); virtual void pv19();
    virtual void pv20(); virtual void pv21(); virtual void pv22(); virtual void pv23();
    virtual void pv24(); virtual void pv25(); virtual void pv26(); virtual void pv27();
    virtual void pv28(); virtual void pv29(); virtual void pv30(); virtual void pv31();
    virtual void pv32(); virtual void pv33(); virtual void pv34(); virtual void pv35();
    virtual void pv36(); virtual void pv37(); virtual void pv38(); virtual void pv39();
    virtual void pv40(); virtual void pv41(); virtual void pv42(); virtual void pv43();
    virtual void pv44(); virtual void pv45(); virtual void pv46(); virtual void pv47();
    virtual void pv48(); virtual void pv49(); virtual void pv50(); virtual void pv51();
    virtual void pv52(); virtual void pv53(); virtual void pv54(); virtual void pv55();
    virtual void pv56(); virtual void pv57(); virtual void pv58(); virtual void pv59();
    virtual void pv60(); virtual void pv61(); virtual void pv62(); virtual void pv63();
    virtual void pv64(); virtual void pv65(); virtual void pv66(); virtual void pv67();
    virtual void pv68(); virtual void pv69(); virtual void pv70(); virtual void pv71();
    virtual void pv72(); virtual void pv73(); virtual void pv74(); virtual void pv75();
    virtual void pv76(); virtual void pv77(); virtual void pv78(); virtual void pv79();
    virtual void pv80(); virtual void pv81(); virtual void pv82(); virtual void pv83();
    virtual void pv84(); virtual void pv85(); virtual void pv86(); virtual void pv87();
    virtual void pv88(); virtual void pv89(); virtual void pv90(); virtual void pv91();
    virtual void pv92(); virtual void pv93(); virtual void pv94(); virtual void pv95();
    virtual void pv96(); virtual void pv97(); virtual void pv98(); virtual void pv99();
    virtual void pv100(); virtual void pv101();
    virtual long __stdcall SetStreamSourceFreq(uint stream, uint setting);   // +0x198
};

// One buffered model instance as queued by the effects system (0x50 bytes).
struct ModelInstance {
    Vector4 mRow[4];     // +0x00 transform; row 3 holds the translation
    uint    mColor[4];   // +0x40 RGBA
};

struct VertexBuffer {
    char pad00[8];
    uint mStart;                                                    // +0x08
    int  Lock(int type, void** ppData, int* pStart, int start, int count);   // 0x006dd250
    void Unlock();                                                  // 0x011f36a0
};

struct RenderState {                                                // object at g+0x30d7c
    char pad00[0x1c];
    int  mField1c;
    int  mField20;
    void SetA(int v);                                               // 0x011f96e0
    void SetB(int v);                                               // 0x011f96b0
    void SetC(int a, int b);                                        // 0x011f9670
    void Draw();                                                    // 0x011f9710
};

struct RenderCtx {                                                  // *0x01618d10
    char pad00[0x10];
    ModelInstance mInstances[1];                                    // +0x10, stride 0x50
    char padRest[0x30d7c - 0x10 - 0x50];
    RenderState*  mState;                                           // +0x30d7c
    VertexBuffer* mVB;                                              // +0x30d80
    uint          mUsed;                                            // +0x30d84
};
extern RenderCtx* g_pCtx;                                           // 0x01618d10

struct ShaderDataItem { char pad[8]; void Push(); };                // 0x007789d0 (thiscall)
struct EmbeddedState {
    char pad00[4];
    uint mState;                                                    // +0x04
    uint mSoftStateDirty;                                           // +0x08
    void D3D9SetTransform(const void* m, int slot, int flag);       // 0x011edc10
    void Dispatch();                                                // 0x011ee580 (CompiledState::Dispatch)
};

struct DrawData {                                                   // per-dispatch draw description
    char pad00[8];
    int  mField08;                                                  // +0x08
    char pad0c[0xc];
    int  mField18;                                                  // +0x18
    char pad1c[8];
    struct { char pad[0xc]; int mField0c; }* mpField24;             // +0x24
};
struct StateHolder { char pad[4]; EmbeddedState* mpState; };        // +0x04
struct DispatchPair {                                               // 12-byte dispatch entry
    DrawData*       mpData;                                         // +0x00
    StateHolder*    mpHolder;                                       // +0x04
    ShaderDataItem* mpShader;                                       // +0x08
};

struct ModelBase {                                                  // SP::cEffectsModel
    char pad00[8];
    DispatchPair* mDispatchBegin;                                   // +0x08
    DispatchPair* mDispatchEnd;                                     // +0x0c
    char pad10[0x40];
    Vec3 mBoxMin;                                                   // +0x50
    Vec3 mBoxMax;                                                   // +0x5c
    void DispatchWithAdditionalMaterial(int material);              // 0x006e7110
    void DispatchList(void* list, int material);                    // 0x006e73d0
};

struct FrustumCull {
    uint FrustumTestSphere(const V3* mn, const V3* mx, int flags);   // 0x00700120
};

struct AppConfig { char pad[0xe0]; float mMinAlpha; };
struct AppProps { char pad[0x3c]; AppConfig* mConfig; };
extern AppProps* sAppProperties;                                    // 0x015fd918

struct ColorRGBA { uint r, g, b, a; };
extern ColorRGBA g_whiteColor;                                      // 0x0140afc4
extern ColorRGBA g_color;                                           // 0x016f96a8
extern uint g_renderStateDirty;                                     // 0x016fa38c
extern uint g_softStateDirty;                                       // 0x016f9528
extern int  g_16f921c, g_16f9244, g_16f9240;

void  __cdecl SetBlendMode(uint mode);                              // 0x011f1340
uint  __cdecl ColorRGBAToU32(const void* rgba);                     // 0x004580c0
void  __cdecl EffectsDispatch(const void* m, int mode);            // 0x005291f0
bool  __cdecl PushShaderDataNull();                                 // 0x00777bf0
void  __cdecl PopShaderData();                                      // 0x00777c10
void  __cdecl SetShaderData(EmbeddedState* s);                      // 0x00777b50
void  __cdecl SetVertexDescriptor(void* vdesc);                     // 0x007611a0
void  __cdecl VertexDescriptorChange(void* vdesc);                  // 0x006dd2a0
extern IDirect3DDevice9* g_d3dDevice;                               // 0x016f89d0
extern const float kSignMask;                                       // 0x013eb8b0

struct EffectsRenderer {
    char pad000[0x14c];
    void* mCurrentVDesc;                                            // +0x14c
    char pad150;
    bool  mCanUseInstancing;                                        // +0x151
    char pad152[6];
    int   mMinInstancingCount;                                      // +0x158
    int   mBufferedCount;                                           // +0x15c
    int   mFlag160;                                                 // +0x160
    char pad164[0x1a8 - 0x164];
    ModelBase* mModel;                                              // +0x1a8
    void*      mList;                                               // +0x1ac
    char pad1b0[0x258 - 0x1b0];
    FrustumCull mFrustum;                                           // +0x258
    char pad25c[0x364 - 0x259];
    int   mMaterial;                                                // +0x364
    char pad368[4];
    int   mCounter36c;                                              // +0x36c
    int   mCounter370;                                              // +0x370

    int ReleaseAndDrawModelBuffer();                                // 0x006eae40
};

static inline Vector4 GetRow(const ModelInstance& m, int i) { return m.mRow[i]; }
static inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }

struct Box3 { V3 mMin, mMax; };

// @ 0x006eae40  SP::cEffectsRenderer::ReleaseAndDrawModelBuffer
int EffectsRenderer::ReleaseAndDrawModelBuffer()
{
    if (mBufferedCount != 0) {
        SetBlendMode(0x60005);
        g_renderStateDirty |= 0x60100;
        g_16f921c = 1;
        g_16f9244 = 5;
        g_16f9240 = 0;

        if (mCurrentVDesc == 0 || mBufferedCount < mMinInstancingCount) {
            // Not enough instances to be worth hardware instancing: cull and draw each one.
            Box3 box = *(Box3*)&mModel->mBoxMin;
            V3 neg(-box.mMin.x, -box.mMin.y, -box.mMin.z);
            if (mList != 0) {
                V3 ext(Max(neg.x, box.mMax.x), Max(neg.y, box.mMax.y), Max(neg.z, box.mMax.z));
                float minAlpha = sAppProperties->mConfig->mMinAlpha;
                for (int i = 0; i < mBufferedCount; i++) {
                    RenderCtx* g = g_pCtx;
                    const ModelInstance& inst = g->mInstances[i];
                    if (*(float*)&inst.mColor[3] > minAlpha) {
                        float r = sqrtf(inst.mRow[0].z * inst.mRow[0].z + inst.mRow[0].y * inst.mRow[0].y +
                                        inst.mRow[0].x * inst.mRow[0].x);
                        V3 t = *(V3*)&inst.mRow[3];
                        V3 mn(t.x - ext.x * r, t.y - ext.y * r, t.z - ext.z * r);
                        V3 mx(ext.x * r + t.x, ext.y * r + t.y, ext.z * r + t.z);
                        if ((mFrustum.FrustumTestSphere(&mn, &mx, 0x200) & 0x40) == 0) {
                            const ModelInstance& cur = g_pCtx->mInstances[i];
                            EffectsDispatch(&cur, 2);
                            g_softStateDirty |= 0x10;
                            g_color = *(ColorRGBA*)&g_pCtx->mInstances[i].mColor;
                            mModel->DispatchList(mList, mMaterial);
                        }
                    }
                }
            } else {
                V3 ext(Max(neg.x, box.mMax.x), Max(neg.y, box.mMax.y), Max(neg.z, box.mMax.z));
                float minAlpha = sAppProperties->mConfig->mMinAlpha;
                for (int i = 0; i < mBufferedCount; i++) {
                    RenderCtx* g = g_pCtx;
                    const ModelInstance& inst = g->mInstances[i];
                    if (*(float*)&inst.mColor[3] > minAlpha) {
                        float r = sqrtf(inst.mRow[0].z * inst.mRow[0].z + inst.mRow[0].y * inst.mRow[0].y +
                                        inst.mRow[0].x * inst.mRow[0].x);
                        V3 t = *(V3*)&inst.mRow[3];
                        V3 mn(t.x - ext.x * r, t.y - ext.y * r, t.z - ext.z * r);
                        V3 mx(ext.x * r + t.x, ext.y * r + t.y, ext.z * r + t.z);
                        if ((mFrustum.FrustumTestSphere(&mn, &mx, 0x200) & 0x40) == 0) {
                            const ModelInstance& cur = g_pCtx->mInstances[i];
                            EffectsDispatch(&cur, 2);
                            g_softStateDirty |= 0x10;
                            g_color = *(ColorRGBA*)&g_pCtx->mInstances[i].mColor;
                            mModel->DispatchWithAdditionalMaterial(mMaterial);
                        }
                    }
                }
            }
        } else {
            // Hardware instancing: pack every queued transform into the instance vertex buffer
            // and draw them with one call.
            int i;
            if (g_pCtx->mUsed + mBufferedCount > 0x9c4)
                g_pCtx->mUsed = 0;
            if (!mCanUseInstancing)
                g_pCtx->mUsed = 0;
            int start = g_pCtx->mUsed;
            void* data;
            int lockType = 6;
            if (start != 0)
                lockType = 10;
            if (!g_pCtx->mVB->Lock(lockType, &data, &start, start, mBufferedCount))
                return 0;
            g_pCtx->mUsed += mBufferedCount;

            float* dst = (float*)data;
            for (i = 0; i < mBufferedCount; i++, dst += 13) {
                const ModelInstance& m = g_pCtx->mInstances[i];
                dst[0] = GetRow(m, 0).x;
                dst[1] = GetRow(m, 1).x;
                dst[2] = GetRow(m, 2).x;
                dst[3] = GetRow(m, 3).x;
                dst[4] = GetRow(m, 0).y;
                dst[5] = GetRow(m, 1).y;
                dst[6] = GetRow(m, 2).y;
                dst[7] = GetRow(m, 3).y;
                dst[8] = GetRow(m, 0).z;
                dst[9] = GetRow(m, 1).z;
                dst[10] = GetRow(m, 2).z;
                dst[11] = GetRow(m, 3).z;
                *(uint*)&dst[12] = ColorRGBAToU32(&m.mColor);
            }
            g_pCtx->mVB->Unlock();

            DispatchPair* entry = mModel->mDispatchBegin;
            if (entry != mModel->mDispatchEnd) {
                PushShaderDataNull();
                DrawData* draw = entry->mpData;
                EmbeddedState* state = entry->mpHolder->mpState;
                g_pCtx->mState->mField1c = 0;
                g_pCtx->mState->mField20 = draw->mpField24->mField0c;
                g_pCtx->mState->SetA(draw->mField08);
                g_pCtx->mState->SetB(draw->mField18);
                g_pCtx->mState->SetC(0, (int)draw->mpField24);

                struct { Vector4 r[4]; } ident = {
                    { Vector4(1.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f),
                      Vector4(0.0f, 0.0f, 1.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f) } };
                if (state->mSoftStateDirty & 1)
                    state->D3D9SetTransform(&ident, 4, 1);
                else
                    EffectsDispatch(&ident, 4);
                g_softStateDirty |= 0x10;
                g_color = g_whiteColor;
                SetVertexDescriptor(mCurrentVDesc);
                SetShaderData(state);
                state->Dispatch();
                if (entry->mpShader)
                    entry->mpShader->Push();
                VertexDescriptorChange(mCurrentVDesc);
                g_d3dDevice->SetStreamSourceFreq(0, mBufferedCount | 0x40000000);
                g_d3dDevice->SetStreamSourceFreq(1, 0x80000001);
                VertexBuffer* vb = g_pCtx->mVB;
                vb->mStart = start;
                g_pCtx->mState->Draw();
                vb->mStart = 0;
                g_d3dDevice->SetStreamSourceFreq(0, 1);
                g_d3dDevice->SetStreamSourceFreq(1, 1);
                PopShaderData();
            }
        }
        mBufferedCount = 0;
    }
    if (mFlag160 == 0)
        mCounter36c++;
    else
        mCounter370++;
    return 0;
}
