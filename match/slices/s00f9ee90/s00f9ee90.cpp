// Slice s00f9ee90 -- SP::cTerrainSphere effect-surface registration / transform
// plumbing (SPTerrainSphere.obj family), plus the image-layer rectangle copy.
//
//   0x00f9ee90  effect-surface sub-helper (ret 0xc)
//   0x00f9ef70  model-effect refresh (ret 4)
//   0x00f9f100  sub-object reset (returns this)
//   0x00f9f1a0  sub-object release (tail-jumps the cViewer destructor)
//   0x00f9f360  surface rect blit, 32-bit elements
//   0x00f9f4c0  surface rect blit, 8-bit elements
//   0x00f9f620  cSPTransform block copy (ret 4)
//   0x00f9f7b0  sift-down helper for a 16-byte-key sort
//   0x00f9f810  sort driver over that helper
//   0x00f9f8f0  copy 0x14-byte elements
//   0x00f9f950  transform block constructor
//   0x00f9f9f0  SP::cTerrainSphere::UpdateEffectSurfaces
//   0x00f9fe70  SP::cTerrainSphere::RenderColorMap
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <stddef.h>

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchangeAdd)

// =====================================================================================
// 0x00f9f200 -- image-layer rectangle copy (from an earlier wave, retained verbatim)
// =====================================================================================

struct LockInfo {                      // 7 dwords written by Surface::Lock; data pointer at +0
    void* data;
    int   rest[6];
};

class Surface {
public:
    bool Lock(int flags, int zero, LockInfo* out);   // 0x011ef750 (thiscall, ret 0xc)
    void Unlock(LockInfo* out);                      // 0x011ef880 (thiscall, ret 4)
};

struct SrcImage {
    char  pad0[8];
    int   width;                       // +8
    char  pad1[4];
    char* data;                        // +0x10
};

// Floor for a float via round-to-nearest cvtss2si, corrected down when it rounded up (cmovb).
#pragma warning(disable : 4035)   // FloorF returns through eax
static __forceinline int FloorF(float x) {
    __asm {
        movss   xmm0, x
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov     ecx, eax
        sub     ecx, 1
        ucomiss xmm0, xmm1
        cmovb   eax, ecx
    }
}

bool __cdecl CopyImageRectToSurface(Surface* a1, const SrcImage* p2, int p3, const float* p4) {
    LockInfo out;
    bool ok = false;
    if (a1->Lock(2, 0, &out)) {

    int w = p2->width;
    float fw = (float)w;
    int left   = FloorF(p4[0] * fw);
    int right  = FloorF(p4[2] * fw);
    int top    = FloorF(p4[1] * fw);
    int bottom = FloorF(p4[3] * fw);

    char* srcBase = p2->data + (w * w * p3) * 2;
    char* dstBase = (char*)out.data;

    if (top < bottom) {
        int rows = bottom - top;
        short* dst = (short*)dstBase + (top * w + left);
        int stride = w * 2;
        do {
            if (left < right) {
                int n = right - left;
                char* d = (char*)dst;
                do {
                    *(short*)d = *(short*)(d + (srcBase - dstBase));
                    d += 2;
                    n = n - 1;
                } while (n != 0);
            }
            dst = (short*)((char*)dst + stride);
            rows = rows - 1;
        } while (rows != 0);
    }

    a1->Unlock(&out);
        return true;
    }
    return ok;
}

// =====================================================================================
// Declarations shared by the 0x00f9ee90 block
// =====================================================================================

// ---- callees ------------------------------------------------------------------------
void* __cdecl SP_EffectsManager();                                  // 0x0067ddd0
void* __cdecl SP_App();                                             // 0x0067dd10
void* __cdecl SP_CreateOfflineEffect(void* mgr);                    // 0x007dad80
int   __cdecl SP_RunOfflineWorld(void* effect, void* out, int h);   // 0x007dae20
int   __cdecl FUN_006f24a0(void* a, void* b);                       // 0x006f24a0
bool  __cdecl ResolveModels(void* vec, uint32_t name, int* outN, void** out); // 0x006a0ae0
void  __cdecl rw_Matrix33_Assign(void* dst, const void* src);       // 0x0041cb40
void  __cdecl FUN_007c4000(void* self);                             // 0x007c4000
void* __cdecl FUN_007c3f70(void* self);                             // 0x007c3f70
void* __cdecl EA_Allocate(unsigned size, const char* name, int, int, int, int); // 0x00f473a0
void  __cdecl operator_delete(void* p);                             // 0x00f47380
void* __cdecl FUN_00f9b0f0(void* self, float a, float b, float c, void* ref, void* x); // 0x00f9b0f0
void  __cdecl FUN_00f717b0(void* a, void* b, void* c);              // 0x00f717b0

// ---- globals ------------------------------------------------------------------------
extern const float G_15b1174;   // 0x015b1174  offline-world time scale
extern const float G_1471064;   // 0x01471064  0.5f
extern const float G_1485720;   // 0x01485720  1.0f
extern const float G_16c9e8c;   // 0x016c9e8c
extern const float G_16c9e90;   // 0x016c9e90
extern const float G_16c9e94;   // 0x016c9e94
extern const float G_16c9ea8;   // 0x016c9ea8
extern const float G_16c9eac;   // 0x016c9eac
extern const float G_16c9eb0;   // 0x016c9eb0
extern void* G_16c9f50;         // 0x016c9f50

// ---- shared structures --------------------------------------------------------------

// rw Matrix33 (0x24): three 3-float rows; Assign at 0x0041cb40.
struct Matrix3 {
    float row0[3];              // +0x00
    float row1[3];              // +0x0c
    float row2[3];              // +0x18
    Matrix3& Assign(const Matrix3& m);
};
extern const Matrix3 G_16c9eb4;   // 0x016c9eb4 identity
extern const Matrix3 G_16c9f24;   // 0x016c9f24 identity

// cSPTransform (0x38): {u16 flags; u16 modcount; f32 t[3]; f32 scale; Matrix3 rot}
struct cSPTransform {
    uint16_t mFlags;            // +0x00
    uint16_t mModCount;         // +0x02
    float    mTranslation[3];   // +0x04
    float    mScale;            // +0x10
    Matrix3  mRotation;         // +0x14
    cSPTransform& operator=(const cSPTransform& o);   // 0x00537dc0
};
typedef char cSPTransform_size_check[(sizeof(cSPTransform) == 0x38) ? 1 : -1];

// Float vector used by the effect-parameter block.
struct Vec4 { float x, y, z, w; };

// Ref-counted handle: the intrusive release idiom the original uses everywhere.
struct RefCounted {
    void*         mpVtbl;        // +0x00
    void*         mp04;          // +0x04
    volatile long mnRefCount;    // +0x08
    int Release()
    {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};

// The 0x1c-byte event-modifier block allocated by UpdateEffectSurfaces.
struct EventModifier {
    void* mpVtbl;               // +0x00
    void* mpVtbl4;              // +0x04
    int   m08;                  // +0x08
    float m0c;                  // +0x0c
    float m10;                  // +0x10
    float m14;                  // +0x14
    void* m18;                  // +0x18
};

// The object returned by CreateOfflineEffect.
struct OfflineEffect {
    virtual void v00();
    virtual void v04();
    virtual bool Query(uint32_t id, uint32_t b, void** out);       // +0x08 ret 0xc
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void Fill(uint32_t a, const void* p, uint32_t n);      // +0x48 ret 0xc
};

// The property list at this+0x28: a 3-float vector at +0x08.
struct cDirectPropertyList {
    void*  mpVtbl;              // +0x00
    void*  mp04;                // +0x04
    Vec4   mVector;             // +0x08
};

// The terrain / map-set header at this+0x2c.
struct PlanetHeader {
    void*   mpMap0;      // +0x08
    void*   mpMap1;      // +0x0c
    void*   mpMap2;      // +0x10
    uint8_t pad14[0x34 - 0x14];
    float   m34;         // +0x34
    float   m38;         // +0x38
    float   m3c;         // +0x3c
};

// Effects state manager (this+0x20c): GetTime returns a float.
struct StateMgr { float GetTime(); };    // 0x00fb9aa0

// Effects-manager singleton: only the slots used by this slice.
struct IEffectsManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void* v18();                                           // +0x18
    virtual void* v1c();                                           // +0x1c
    virtual void  v20(void* obj, int v);                           // +0x20 ret 8
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void  SetEffect(uint32_t id, int b, void* obj);        // +0x78 ret 0xc
    virtual void* GetEffect(uint32_t id, int b, int c);            // +0x7c ret 0xc
};

// App singletons used by UpdateEffectSurfaces.
struct AppObj {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual void* v2c();
    virtual void* v30();
    virtual void* v34();
    virtual void* v38();
    virtual void* v3c();
    virtual void* v40();
    virtual void* v44();
    virtual void* v48();
    virtual void* v4c();
    virtual void* v50();                                           // +0x50
};
struct Render30Obj {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();                                           // +0x1c
};

// cSurfaceDecalManager: ctor 0x00a80ee0, SetSurface 0x00a81310, 0x00a80200.
struct cSurfaceDecalManager {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    void SetSurface(void* surface);                                 // 0x00a81310
};
cSurfaceDecalManager* __cdecl FUN_00a80ee0(void* self);            // 0x00a80ee0 (returns ctor this)
void __cdecl FUN_00a80200(void* self, void* a);                    // 0x00a80200

// cViewer sub-object helpers (constructor 0x007c3f70, destructor 0x007c4000).
struct cViewerSub {
    int   mDummy;          // keeps the member 4 bytes wide
    void* Construct();     // 0x007c3f70, returns this
    void  Destruct();      // 0x007c4000
};

// Allocator block header (the word just before an operator_delete'd pointer).
struct BlockHeader { int mnFlags; };

// 16-byte element with an unsigned key at +8 (the sort helper's element).
struct Elem16 {
    uint32_t w0, w1, key, w3;
};
void __cdecl FUN_00f9af30(Elem16* first, int a, int n, int b, Elem16 tmp, unsigned key); // 0x00f9af30

// 5-float (0x14-byte) record copied by 0x00f9f8f0.
struct Rec5 { float f[5]; };

// -------------------------------------------------------------------------------------
// cTerrainSphere (offsets as used by this slice's flat model; sibling offset =
// PDB offset + 0xe0 in the shader/synthesize region, matching the other slices).
// -------------------------------------------------------------------------------------
class cTerrainSphere {
public:
    // 0x00f9ee90
    void   EffectSurfacePass(void* a, void* outT, void* outObj);
    // 0x00f9ef70
    void   RefreshModelEffects(void* arg);
    // 0x00f9f100
    void*  ResetTransformBlock();
    // 0x00f9f1a0
    void   ReleaseTransformBlock();
    // 0x00f9f9f0
    void   UpdateEffectSurfaces();
    // 0x00f9fe70
    void   RenderColorMap(void* stats, uint32_t arg);
    // 0x00f98290 / 0x00f9c0d0
    bool   UpdateAboveRaster(int face, float* rect, int a, void* b);
    void   UpdateColorMap(int face, void* b);

    cViewerSub mViewer;              // +0x004 (vptr occupies +0x000)
    uint8_t  pad00c[0x28 - 0x08];
    cDirectPropertyList* mpProps;    // +0x028
    PlanetHeader*        mpPlanet;   // +0x02c
    uint8_t  pad030[0x110 - 0x30];
    uint8_t  m111;                   // +0x110
    uint8_t  pad111[0x178 - 0x111];
    cSPTransform mTransform;         // +0x178
    int32_t  m1b0;                   // +0x1b0
    int32_t  m1b4;                   // +0x1b4
    RefCounted* mp1b8;               // +0x1b8  ref-counted handle
    void*    mp1bc;                  // +0x1bc  operator_delete'd block
    void*    mp1c0;                  // +0x1c0
    void*    mp1c4;                  // +0x1c4
    uint8_t  pad1c8[0x20c - 0x1c8];
    StateMgr* mpStateMgr;            // +0x20c
    uint8_t  pad210[0x494 - 0x210];
    float    mSynthBBox[6][4];       // +0x494
    uint8_t  mValidSynthTex;         // +0x4f4
    uint8_t  pad4f5[0x924 - 0x4f5];
    int32_t  m924;                   // +0x924

    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual int   RunEffect(uint32_t cmd, float t, void* a, void* mgr, void* b,
                            int c, int d);                        // +0x18 ret 0x1c
};
typedef char cTS_props_off[(offsetof(cTerrainSphere, mpProps)     == 0x028) ? 1 : -1];
typedef char cTS_planet_off[(offsetof(cTerrainSphere, mpPlanet)   == 0x02c) ? 1 : -1];
typedef char cTS_xform_off [(offsetof(cTerrainSphere, mTransform) == 0x178) ? 1 : -1];
typedef char cTS_state_off [(offsetof(cTerrainSphere, mpStateMgr) == 0x20c) ? 1 : -1];
typedef char cTS_bbox_off  [(offsetof(cTerrainSphere, mSynthBBox) == 0x494) ? 1 : -1];
typedef char cTS_valid_off [(offsetof(cTerrainSphere, mValidSynthTex) == 0x4f4) ? 1 : -1];
typedef char cTS_size_check[(sizeof(cTerrainSphere) == 0x928) ? 1 : -1];

// -------------------------------------------------------------------------------------
// @ 0x00f9ee90
void cTerrainSphere::EffectSurfacePass(void* a, void* outT, void* outObj)
{
    void* mgr = SP_EffectsManager();
    OfflineEffect* eff = (OfflineEffect*)SP_CreateOfflineEffect(mgr);
    void* capture = 0;
    if (!eff->Query(0xf3cfbb40u, 0, &capture)) {
        if (eff)
            eff->v04();
        return;
    }
    Vec4 v;
    v.x = mpProps->mVector.x;
    v.y = mpProps->mVector.y;
    v.z = mpProps->mVector.z;
    v.w = 0.0f;
    ((OfflineEffect*)capture)->Fill(6, &v, 3);
    int h = RunEffect(0x21, G_15b1174, &v, mgr, &v, 0, 0);
    int r = SP_RunOfflineWorld(eff, capture, h);
    if (outObj)
        *(int*)outObj = r;
    if (outT)
        *(float*)outT = 0.0f;
    if (capture)
        ((OfflineEffect*)capture)->v04();
    (void)a;
}

// -------------------------------------------------------------------------------------
// @ 0x00f9ef70
void cTerrainSphere::RefreshModelEffects(void* arg)
{
    AppObj* app = (AppObj*)SP_App();
    if (app->v38() == (void*)0x01654c10)
        return;
    IEffectsManager* em = (IEffectsManager*)SP_EffectsManager();
    OfflineEffect* eff = (OfflineEffect*)SP_CreateOfflineEffect(em);
    int n = 0;
    void* out = 0;
    if (ResolveModels(mpProps, 0x6875cfd, &n, &out) && n > 0) {
        char* p = (char*)out;
        for (int i = 0; i < n; ++i, p += 0xc) {
            void* ref = 0;
            if (eff->Query(*(uint32_t*)p, *(uint32_t*)(p + 8), &ref)) {
                int h = RunEffect(0x21, G_15b1174, 0, em, 0, 0, 0);
                SP_RunOfflineWorld(eff, ref, h);
            }
        }
    }
    if (out)
        ((OfflineEffect*)out)->v04();
    void* capture = 0;
    if (eff->Query(0xf3cfbb40u, 0, &capture)) {
        Vec4 v;
        v.x = mpProps->mVector.x;
        v.y = mpProps->mVector.y;
        v.z = mpProps->mVector.z;
        v.w = 1.0f;
        ((OfflineEffect*)capture)->Fill(6, &v, 3);
        int h = RunEffect(0x21, G_15b1174, em, 0, 0, 0, 0);
        SP_RunOfflineWorld(eff, capture, h);
    }
    if (eff)
        eff->v04();
    (void)arg;
}

// -------------------------------------------------------------------------------------
// @ 0x00f9f100
void* cTerrainSphere::ResetTransformBlock()
{
    mViewer.Construct();
    mTransform.mFlags = 0;
    mTransform.mModCount = 0;
    mTransform.mTranslation[0] = G_16c9e8c;
    mTransform.mTranslation[1] = G_16c9e90;
    mTransform.mTranslation[2] = G_16c9e94;
    mTransform.mScale = G_1485720;
    mTransform.mRotation.Assign(G_16c9f24);
    m1b0 = -1;
    m1b4 = -1;
    mp1b8 = 0;
    mp1bc = 0;
    mp1c0 = 0;
    mp1c4 = 0;
    return this;
}

// -------------------------------------------------------------------------------------
// @ 0x00f9f1a0
void cTerrainSphere::ReleaseTransformBlock()
{
    if (mp1bc != 0 && ((BlockHeader*)mp1bc - 1)->mnFlags != 0)
        operator_delete(mp1bc);
    if (mp1b8 != 0)
        mp1b8->Release();
    mViewer.Destruct();
}

// -------------------------------------------------------------------------------------
// @ 0x00f9f360
bool __cdecl FUN_00f9f360(Surface* a1, const SrcImage* p2, int p3, const float* p4)
{
    LockInfo lock;
    if (!a1->Lock(2, 0, &lock))
        return false;

    int w = p2->width;
    float fw = (float)w;
    int left   = FloorF(p4[0] * fw);
    int right  = FloorF(p4[2] * fw);
    int top    = FloorF(p4[1] * fw);
    int bottom = FloorF(p4[3] * fw);

    int* srcBase = (int*)p2->data + w * w * p3;
    int* dstBase = (int*)lock.data;

    if (top < bottom) {
        int* dst = dstBase + top * w + left;
        int rows = bottom - top;
        do {
            if (left < right) {
                int* d = dst;
                int* s = srcBase;
                int n = right - left;
                do { *d++ = *s++; } while (--n != 0);
            }
            dst += w;
            --rows;
        } while (rows != 0);
    }

    a1->Unlock(&lock);
    return true;
}

// -------------------------------------------------------------------------------------
// @ 0x00f9f4c0
bool __cdecl FUN_00f9f4c0(Surface* a1, const SrcImage* p2, int p3, const float* p4)
{
    LockInfo lock;
    if (!a1->Lock(2, 0, &lock))
        return false;

    int w = p2->width;
    float fw = (float)w;
    int left   = FloorF(p4[0] * fw);
    int right  = FloorF(p4[2] * fw);
    int top    = FloorF(p4[1] * fw);
    int bottom = FloorF(p4[3] * fw);

    char* srcBase = p2->data + w * w * p3;
    char* dstBase = (char*)lock.data;

    if (top < bottom) {
        char* dst = dstBase + top * w + left;
        int rows = bottom - top;
        do {
            if (left < right) {
                char* d = dst;
                char* s = srcBase;
                int n = right - left;
                do { *d++ = *s++; } while (--n != 0);
            }
            dst += w;
            --rows;
        } while (rows != 0);
    }

    a1->Unlock(&lock);
    return true;
}

// -------------------------------------------------------------------------------------
// The transform block copied by 0x00f9f620: a cSPTransform followed by 24 floats and
// 5 ints (total 0xac bytes).
struct BigXform {
    cSPTransform mBase;          // +0x00  (0x38)
    float        mF[24];         // +0x38 .. +0x94
    int          mD[5];          // +0x98 .. +0xa8
    BigXform* CopyFrom(const BigXform* o);
};

// @ 0x00f9f620
BigXform* BigXform::CopyFrom(const BigXform* o)
{
    mBase = o->mBase;
    for (int i = 0; i < 24; ++i)
        mF[i] = o->mF[i];
    for (int i = 0; i < 5; ++i)
        mD[i] = o->mD[i];
    return this;
}

// -------------------------------------------------------------------------------------
// @ 0x00f9f7b0
void __cdecl FUN_00f9f7b0(Elem16* first, Elem16* last, unsigned key)
{
    int n = (int)(last - first);
    if (n < 2)
        return;
    int i = ((n - 2) >> 1) + 1;
    do {
        --i;
        Elem16 tmp = first[i];
        FUN_00f9af30(first, i, n, i, tmp, key);
    } while (i != 0);
}

// -------------------------------------------------------------------------------------
// @ 0x00f9f810
void __cdecl FUN_00f9f810(Elem16* first, Elem16* last, unsigned key)
{
    int n = (int)(last - first);
    if (n <= 1)
        return;
    Elem16* p = last - 1;
    do {
        Elem16 tmp = *p;
        *p = *first;
        FUN_00f9af30(first, 0, n - 1, 0, tmp, key);
        --p;
        n = (int)(p - first) + 1;
    } while (n > 1);
}

// -------------------------------------------------------------------------------------
// @ 0x00f9f8f0
void __cdecl FUN_00f9f8f0(Rec5** out, const Rec5* src, const Rec5* srcEnd, Rec5* dst)
{
    *out = dst;
    if (src == srcEnd)
        return;
    do {
        if (dst) {
            dst->f[0] = src->f[0];
            dst->f[1] = src->f[1];
            dst->f[2] = src->f[2];
            dst->f[3] = src->f[3];
            dst->f[4] = src->f[4];
        }
        ++src;
        ++dst;
    } while (src != srcEnd);
    *out = dst;
}

// -------------------------------------------------------------------------------------
// The 0x68-byte block constructed by 0x00f9f950.
struct SphereBlock {
    cSPTransform mA;             // +0x00
    float m38, m3c, m40, m44;    // +0x38 .. +0x44
    float m48, m4c, m50, m54;    // +0x48 .. +0x54
    float m58, m5c;              // +0x58, +0x5c
    int   m60, m64;              // +0x60, +0x64
    SphereBlock* Init();
};

// @ 0x00f9f950
SphereBlock* SphereBlock::Init()
{
    mA.mFlags = 0;
    mA.mModCount = 0;
    mA.mTranslation[0] = G_16c9ea8;
    mA.mTranslation[1] = G_16c9eac;
    mA.mTranslation[2] = G_16c9eb0;
    mA.mScale = G_1485720;
    mA.mRotation.Assign(G_16c9eb4);
    float one = G_1485720;
    m38 = one; m3c = one; m40 = one; m44 = one;
    m48 = one; m4c = one; m50 = one; m54 = one;
    int z = 0;
    m60 = z;
    m58 = 0.0f;
    m5c = 0.0f;
    m64 = z;
    return this;
}

// -------------------------------------------------------------------------------------
// @ 0x00f9f9f0
void cTerrainSphere::UpdateEffectSurfaces()
{
    IEffectsManager* em = (IEffectsManager*)SP_EffectsManager();
    float h0 = mpPlanet->m34;
    float h1 = mpPlanet->m38;
    float h2 = mpPlanet->m3c * mpPlanet->m38;
    float t = mpStateMgr->GetTime() * G_1471064;
    void* ref = mpPlanet->mpMap0;
    void* map1 = mpPlanet->mpMap1;
    (void)map1;
    (void)t;

    EventModifier* m0 = (EventModifier*)EA_Allocate(
        0x1c, "Terrain/Sphere/cTerrainEffectSurfaceHeight", 0, 0, 0, 0);
    if (m0) {
        m0->mpVtbl4 = (void*)0x013ef094;
        m0->m08 = 0;
        m0->m0c = h0;
        m0->mpVtbl = (void*)0x01490908;
        m0->mpVtbl4 = (void*)0x01490904;
        m0->m10 = h1;
        m0->m14 = -h1;
        m0->m18 = ref;
        if (ref)
            (*(int*)((char*)ref + 4))++;
    }
    em->SetEffect(0x2e892928u, 0, m0);

    EventModifier* m1 = (EventModifier*)EA_Allocate(
        0x1c, "Terrain/Sphere/cTerrainEffectSurfaceHeight", 0, 0, 0, 0);
    if (m1) {
        m1->mpVtbl4 = (void*)0x013ef094;
        m1->m08 = 0;
        m1->m0c = h0;
        m1->m10 = h1;
        m1->m14 = h2;
        m1->mpVtbl = (void*)0x01490908;
        m1->mpVtbl4 = (void*)0x01490904;
        m1->m18 = ref;
        if (ref)
            (*(int*)((char*)ref + 4))++;
    }
    em->SetEffect(0x2e892929u, 0, m1);

    void* m2 = EA_Allocate(
        0x20, "Terrain/Sphere/cTerrainEffectSurfaceHeightAndNormal", 0, 0, 0, 0);
    void* m2c = m2 ? FUN_00f9b0f0(m2, h0, h1, -h1, ref, map1) : 0;
    em->SetEffect(0x2e89292bu, 0, m2c);

    EventModifier* s0 = (EventModifier*)EA_Allocate(
        0x10, "Terrain/Sphere/cTerrainEffectSurfaceSphere", 0, 0, 0, 0);
    if (s0) {
        s0->m08 = 0;
        s0->mpVtbl = (void*)0x01490984;
        s0->mpVtbl4 = (void*)0x01455a60;
        s0->m0c = h2 + h0;
    }
    em->SetEffect(0x2e89292au, 0, s0);

    EventModifier* s1 = (EventModifier*)EA_Allocate(
        0x10, "Terrain/Sphere/cTerrainEffectSurfaceSphere", 0, 0, 0, 0);
    if (s1) {
        s1->m08 = 0;
        s1->mpVtbl = (void*)0x01490984;
        s1->mpVtbl4 = (void*)0x01455a60;
        s1->m0c = h0 + h2;
    }
    em->SetEffect(0x3598109u, 0, s1);

    EventModifier* s2 = (EventModifier*)EA_Allocate(
        0x10, "Terrain/Sphere/cTerrainEffectSurfaceDoubleSidedSphere", 0, 0, 0, 0);
    if (s2) {
        s2->m08 = 0;
        s2->mpVtbl = (void*)0x014908d0;
        s2->mpVtbl4 = (void*)0x01455a60;
        s2->m0c = h2 + h0;
    }
    em->SetEffect(0x4fe7337u, 0, s2);

    AppObj* app = (AppObj*)SP_App();
    Render30Obj* r30 = (Render30Obj*)app->v50();
    void* p = r30->v1c();
    FUN_00f717b0(mpPlanet, mpStateMgr, p);
    em->v20((void*)m924, -1);

    cSurfaceDecalManager* decal = FUN_00a80ee0(
        EA_Allocate(0xb8, "Terrain/Sphere/cSurfaceDecalManager/DecalTypeFastTerrain", 0, 0, 0, 0));
    if (decal)
        decal->v08();
    decal->v00();
    decal->SetSurface(em->GetEffect(0x2e892928u, 0, 0));
    FUN_00a80200(decal, em->v1c());
    em->v20(decal, 6);

    cSurfaceDecalManager* decal2 = FUN_00a80ee0(
        EA_Allocate(0xb8, "Terrain/Sphere/cSurfaceDecalManager/DecalTypeFastAndWaterTerrain", 0, 0, 0, 0));
    if (decal2 != decal) {
        if (decal2)
            decal2->v08();
        decal->v0c();
        decal = decal2;
    }
    decal->v00();
    decal->SetSurface(em->GetEffect(0x2e892929u, 0, 0));
    FUN_00a80200(decal, em->v1c());
    em->v20(decal, 7);

    cSurfaceDecalManager* decal3 = FUN_00a80ee0(
        EA_Allocate(0xb8, "Terrain/Sphere/cSurfaceDecalManager/DecalTypeFastWater", 0, 0, 0, 0));
    cSurfaceDecalManager* decal4 = decal;
    if (decal3 != decal) {
        if (decal3)
            decal3->v08();
        decal4 = decal3;
        if (decal)
            decal->v0c();
    }
    decal4->v00();
    decal4->SetSurface(em->GetEffect(0x2e89292au, 0, 0));
    FUN_00a80200(decal4, em->v1c());
    em->v20(decal4, 8);

    FUN_006f24a0(G_16c9f50, (char*)this + 0xc);
    m111 = 1;
    decal4->v0c();
}

// -------------------------------------------------------------------------------------
// @ 0x00f9fe70
void cTerrainSphere::RenderColorMap(void* stats, uint32_t arg)
{
    for (int i = 0; i < 6; ++i) {
        float* rect = mSynthBBox[i];
        if (rect[0] != rect[2] && rect[1] != rect[3]) {
            if (!UpdateAboveRaster(i, rect, 0, stats))
                return;
            rect[0] = 0.0f;
            rect[1] = 0.0f;
            rect[2] = 0.0f;
            rect[3] = 0.0f;
            UpdateColorMap(i, stats);
            mValidSynthTex = 1;
        }
    }
    (void)arg;
}