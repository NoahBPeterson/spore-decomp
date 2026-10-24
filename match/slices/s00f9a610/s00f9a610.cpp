// Slice s00f9a610 -- SP::cTerrainSphere face-rect flush / lighting-region emit, decal
// face-from-normal test, vector helpers, intrusive-ptr range algorithms, GmeRefCount
// dtor/ctor, cSPTransform copy helpers, shader binding and sky/lighting property setters
// (0x00f9a610 .. 0x00f9b400).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (movss/x87 scalar float, no EH frame)
#include "types.h"
#include <math.h>
#include <string.h>

// ---- external helpers ------------------------------------------------------------------
void* __cdecl MemZero(void* p, int value, unsigned int size);       // 0x011e073e (CRT memset thunk)
void  __cdecl operator_delete(void* p);                            // 0x00f47380

// ---- rdata float constants -------------------------------------------------------------
extern const float kOne;        // 0x01485720 == 1.0f
extern const float kTwo;        // 0x01470f1c == 2.0f
extern const float kBig;        // 0x01465544 == 500.0f
extern const float kSignMask;   // 0x013eb8b0 == { -0.0, -0.0, -0.0, -0.0 }

// ---- generic types ---------------------------------------------------------------------
struct float3 {
    float x, y, z;
};
struct Rect {
    float left, top, right, bottom;
};

// ---- reference-counted object with vptr@0 / refcount@4 --------------------------------
struct IRefObj32 {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};
struct IRefCounted2 {
    virtual void Destroy(int a);   // +0x00
    int mRefCount;                 // +0x04
};

// ---- face-rect flush target ------------------------------------------------------------
struct IFaceGrid {
    void FlushRect(void* a, int face, Rect* r);   // 0x00f92ff0 (ret 0xc)
};
struct cPlanetData2 {
    uint8_t pad0[8];
    void*      mp08;            // +0x08
    uint8_t pad0c[0x58 - 0x0c];
    IFaceGrid* mp58;            // +0x58
};

// ---- element types stored in the mpArr2f4 vector --------------------------------------
struct ElemA {                  // position at +0x04
    int      key;               // +0x00
    float3   pos;               // +0x04
    uint8_t  pad10[0x20 - 0x10];
    uint8_t  flag20;            // +0x20
};
struct ElemB {                  // position at +0x10
    int      key;               // +0x00
    uint8_t  pad04[0x10 - 0x04];
    float3   pos;               // +0x10
    uint8_t  pad1c[0x20 - 0x1c];
    uint8_t  flag20;            // +0x20
};
struct ElemC {                  // scalar at +0x1c
    int      key;               // +0x00
    uint8_t  pad04[0x1c - 0x04];
    float    val;               // +0x1c
    uint8_t  flag20;            // +0x20
};

// ---- 8-byte { intrusive_ptr, int } pair used by the range algorithms ------------------
struct RefPair {
    IRefObj32* p;               // +0x00
    int        x;               // +0x04
};

// ---- viewer / material helpers used by RenderLightingRegion ---------------------------
struct cViewer2 {
    uint8_t pad[0x178];
    uint8_t mX178[0x10];        // +0x178
    float   mF188;              // +0x188
    bool Update();              // 0x007c4fd0
    void Clear(uint32_t f);     // 0x007c3c50
    void Reset();               // 0x007c3c10
};
struct IMaterialMgr {
    virtual void v0();          // +0x00
    uint8_t pad[0x28 - 4];
    virtual void* Get(uint32_t id);   // +0x28
};
IMaterialMgr* __cdecl MaterialManager();                  // 0x0067dd70
bool __cdecl FUN_006ddcc0(int a, int b, void* c, void* d);   // 0x006ddcc0
void __cdecl FUN_006ddd80(int a, void* b, int c, void* d);    // 0x006ddd80
struct cSPTransform {
    uint8_t pad[0x178];
    void BackTransformPoint(float3* p);   // 0x004ff6d0 (ret 4)
};
uint32_t __cdecl ColorRGBAToU32(float* rgba);             // 0x????????

// ---- decal helper ----------------------------------------------------------------------
struct cTerrainSphereDecal {
    bool GetBBoxForFace(uint32_t face, float* out);       // 0x????????
};

// ---- sky-state / shader binding --------------------------------------------------------
void __cdecl SetShaderParam(int id, void* a, int b);      // 0x00777ae0 (ret 0xc)
void __cdecl SkyStateUpdate(void* self);                  // 0x00f98970
void __cdecl FUN_00f992e0();                              // 0x00f992e0
void* __cdecl GetManager67b();                            // 0x0067dd50

// ---- property / variant ----------------------------------------------------------------
struct Variant {
    int  mTypeId;    // +0x00
    int  mFlags;     // +0x04
    uint8_t pad8[8];
};
void __cdecl Variant_Destruct(Variant* v, int a);         // EA::Variant::Destruct
bool __cdecl SP_GetPropertyAsVector3(void* props, uint32_t id, float* out);  // SP::GetPropertyAsVector3
void __cdecl FUN_006a3570(void* v);                       // 0x006a3570
void __cdecl FUN_00fbd880(float a, float b);              // 0x00fbd880
void __cdecl FUN_00fbaf10(uint32_t a);                    // 0x00fbaf10
void __cdecl FUN_00fbaf50(float a);                       // 0x00fbaf50
struct IPropListC {
    virtual void v0();   // +0x00
    uint8_t pad[0x14 - 4];
    virtual void Set(uint32_t id, Variant* v);   // +0x14
    virtual void Del(uint32_t id);               // +0x18
};

// ---- GmeRefCount-like object -----------------------------------------------------------
struct vtbl_GmeRefCount { int f; };
extern vtbl_GmeRefCount vtbl_GmeRefCount0;    // 0x013ef094

// ---- the terrain sphere / receiver -----------------------------------------------------
struct cTerrainSphere141 {
    uint8_t  pad0[0x2c];
    cPlanetData2* mpPlanet;         // +0x2c
    uint8_t  pad30[0x2f4 - 0x30];
    uint8_t* mpArr2f4;              // +0x2f4
    uint8_t* mpArr2f8;              // +0x2f8
    uint8_t  pad2fc[0x308 - 0x2fc];
    int      mF308;                 // +0x308
    uint8_t  pad30c[0x36c - 0x30c];
    int      mFaceBase;             // +0x36c
    uint8_t  pad370[4];
    Rect     mRects[24];            // +0x374

    void FUN_00f9a610();                                   // 0x00f9a610
    void FUN_00f9a680(int key, const float3* v);           // 0x00f9a680
    void FUN_00f9a6f0(int key, const float3* v);           // 0x00f9a6f0
    void FUN_00f9a760(int key, float v);                   // 0x00f9a760
    void RenderLightingRegion(void* a, void* b);           // 0x00f9a7c0
    bool FUN_00f9abc0(float* dir);                         // 0x00f9abc0
};

// ----------------------------------------------------------------------------------------
// @ 0x00f9a610
void cTerrainSphere141::FUN_00f9a610()
{
    void* a = mpPlanet->mp08;
    for (int i = 0; i < 6; i++) {
        Rect& r = mRects[6 + i - 6 * mFaceBase];
        if (r.left != r.right && r.top != r.bottom)
            mpPlanet->mp58->FlushRect(a, i, &r);
    }
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9a680
void cTerrainSphere141::FUN_00f9a680(int key, const float3* v)
{
    int n = (int)(mpArr2f8 - mpArr2f4) >> 2;
    if (n <= 0)
        return;
    uint8_t** p = (uint8_t**)mpArr2f4;
    int i = 0;
    while (*(int*)*p != key) {
        i++;
        p++;
        if (n <= i)
            return;
    }
    ElemA* e = (ElemA*)((uint8_t**)mpArr2f4)[i];
    e->pos = *v;
    ((ElemA*)((uint8_t**)mpArr2f4)[i])->flag20 = 1;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9a6f0
void cTerrainSphere141::FUN_00f9a6f0(int key, const float3* v)
{
    int n = (int)(mpArr2f8 - mpArr2f4) >> 2;
    if (n <= 0)
        return;
    uint8_t** p = (uint8_t**)mpArr2f4;
    int i = 0;
    while (*(int*)*p != key) {
        i++;
        p++;
        if (n <= i)
            return;
    }
    ElemB* e = (ElemB*)((uint8_t**)mpArr2f4)[i];
    e->pos = *v;
    ((ElemB*)((uint8_t**)mpArr2f4)[i])->flag20 = 1;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9a760
void cTerrainSphere141::FUN_00f9a760(int key, float v)
{
    int n = (int)(mpArr2f8 - mpArr2f4) >> 2;
    if (n <= 0)
        return;
    uint8_t** p = (uint8_t**)mpArr2f4;
    int i = 0;
    while (*(int*)*p != key) {
        i++;
        p++;
        if (n <= i)
            return;
    }
    ElemC* e = (ElemC*)((uint8_t**)mpArr2f4)[i];
    e->val = v;
    ((ElemC*)((uint8_t**)mpArr2f4)[i])->flag20 = 1;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9a7c0
void cTerrainSphere141::RenderLightingRegion(void* a, void* b)
{
    // 'this' is unused; `a` is the lighting-region object, `b` is passed through unchanged.
    uint8_t* region = (uint8_t*)a;
    cViewer2* viewer = (cViewer2*)(region + 4);

    region[0x1d4] = 0;
    int n = (*(int*)(region + 0x1c0) - *(int*)(region + 0x1bc)) >> 2;
    if (n == 0) {
        if (viewer->Update()) {
            viewer->Clear(7);
            viewer->Reset();
            return;
        }
        return;
    }
    if (!viewer->Update())
        return;
    viewer->Clear(7);
    IMaterialMgr* mm = MaterialManager();
    void* mat = mm->Get(0x44558011);
    void* buf = 0;
    void* extra = 0;
    if (!FUN_006ddcc0(3, n * 4, &buf, &extra)) {
        viewer->Reset();
        return;
    }
    MemZero(buf, 0, 0x70);
    if (n > 0) {
        float3 nrm[4];
        nrm[0].x = 0.0f; nrm[0].y = 0.0f; nrm[0].z = 0.0f;
        nrm[1].x = 1.0f; nrm[1].y = 0.0f; nrm[1].z = 0.0f;
        nrm[2].x = 1.0f; nrm[2].y = 1.0f; nrm[2].z = 0.0f;
        nrm[3].x = 0.0f; nrm[3].y = 1.0f; nrm[3].z = 0.0f;
        int off = 0;
        for (int i = 0; i < n; i++) {
            uint8_t* e = *(uint8_t**)(*(int*)(region + 0x1bc) + i * 4);
            float3 p;
            p.x = *(float*)(e + 4);
            p.y = *(float*)(e + 8);
            p.z = *(float*)(e + 0xc);
            ((cSPTransform*)(region + 0x178))->BackTransformPoint(&p);
            float u = p.x * kTwo - kOne;
            float w = p.y * kTwo - kOne;
            uint8_t* v = (uint8_t*)buf + off;
            *(float*)(v + 0x00) = u; *(float*)(v + 0x04) = w; *(float*)(v + 0x08) = 0.0f;
            *(float*)(v + 0x1c) = u; *(float*)(v + 0x20) = w; *(float*)(v + 0x24) = 0.0f;
            *(float*)(v + 0x38) = u; *(float*)(v + 0x3c) = w; *(float*)(v + 0x40) = 0.0f;
            *(float*)(v + 0x54) = u; *(float*)(v + 0x58) = w; *(float*)(v + 0x5c) = 0.0f;

            float h = (*(float*)(e + 0x1c) / *(float*)(region + 0x188)) * kTwo;
            *(float*)(v + 0x00) += -h;
            *(float*)(v + 0x04) +=  h;
            *(float*)(v + 0x1c) +=  h;
            *(float*)(v + 0x20) +=  h;
            *(float*)(v + 0x38) +=  h;
            *(float*)(v + 0x3c) += -h;
            *(float*)(v + 0x54) += -h;
            *(float*)(v + 0x58) += -h;

            *(float3*)(v + 0x10) = nrm[0];
            *(float3*)(v + 0x2c) = nrm[1];
            *(float3*)(v + 0x48) = nrm[2];
            *(float3*)(v + 0x64) = nrm[3];

            float rgba[3];
            rgba[0] = *(float*)(e + 0x10);
            rgba[1] = *(float*)(e + 0x14);
            rgba[2] = *(float*)(e + 0x18);
            uint32_t c = ColorRGBAToU32(rgba);
            *(uint32_t*)(v + 0x0c) = c;
            *(uint32_t*)(v + 0x28) = c;
            *(uint32_t*)(v + 0x44) = c;
            *(uint32_t*)(v + 0x60) = c;
            off += 0x70;
        }
    }
    FUN_006ddd80(3, mat, mF308, b);
    viewer->Reset();
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9abc0
bool cTerrainSphere141::FUN_00f9abc0(float* dir)
{
    float x = dir[0];
    float y = dir[1];
    float z = dir[2];
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    float u, v;
    uint32_t face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            u = (y / x + kOne) * 0.5f;
            v = (z / ax + kOne) * 0.5f;
            face = 2;
            if (x < 0.0f)
                face = 3;
        } else {
            u = (z / y + kOne) * 0.5f;
            v = (x / ay + kOne) * 0.5f;
            face = (y < 0.0f) ? 5 : 4;
        }
    } else {
        u = (x / z + kOne) * 0.5f;
        v = (y / az + kOne) * 0.5f;
        face = (z < 0.0f) ? 1 : 0;
    }
    uint32_t* self = (uint32_t*)this;
    int* list = (int*)(self[0x74] + 0x218 + (*self >> 0x18) * 0x14);
    uint32_t idx = *self & 0xffffff;
    cTerrainSphereDecal* dec;
    if (idx < (uint32_t)((list[1] - *list) >> 2))
        dec = *(cTerrainSphereDecal**)(*list + idx * 4);
    else
        dec = 0;
    float bb[4];
    if (!dec->GetBBoxForFace(face, bb))
        return false;
    if (bb[0] < u && u < bb[2] && bb[1] < v && v < bb[3])
        return true;
    return false;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9ada0
void FUN_00f9ada0(float* dst, const float* src)
{
    float inv = 1.0f / sqrtf(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
    dst[0] = src[0] * inv;
    dst[1] = src[1] * inv;
    dst[2] = src[2] * inv;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9adf0
RefPair* FUN_00f9adf0(RefPair* first, RefPair* last, RefPair* dst)
{
    if (first != last) {
        do {
            if (dst) {
                IRefObj32* p = first->p;
                dst->p = p;
                if (p)
                    p->AddRef();
                dst->x = first->x;
            }
            first++;
            dst++;
        } while (first != last);
    }
    return dst;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9ae80
RefPair* FUN_00f9ae80(RefPair* first, RefPair* last, RefPair* dst)
{
    if (first != last) {
        do {
            IRefObj32* a = first->p;
            IRefObj32* b = dst->p;
            if (a != b) {
                if (a)
                    a->AddRef();
                dst->p = a;
                if (b)
                    b->Release();
            }
            dst->x = first->x;
            first++;
            dst++;
        } while (first != last);
    }
    return dst;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9aee0
void FUN_00f9aee0(float* p, unsigned int n, const float* src)
{
    if (n <= 0)
        return;
    float* q = p + 1;
    do {
        float* base = q - 1;
        if (base) {
            base[0] = src[0];
            base[1] = src[1];
            base[2] = src[2];
            base[3] = src[3];
            base[4] = src[4];
        }
        n--;
        q += 5;
    } while (n > 0);
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9af30
void __cdecl FUN_00f96eb0(int base, int a, int idx, void* p5, void* p6, void* p7, void* p8, void* p9);
void __cdecl FUN_00f9af30(int base, int a, int n, int i, void* p5, void* p6, void* p7, void* p8, void* p9)
{
    int child;
    for (;;) {
        int l = i * 2;
        child = l + 2;
        if (n <= child)
            break;
        if (*(unsigned*)(child * 0x10 + 8 + base) < *(unsigned*)(child * 0x10 + base - 8))
            child = l + 1;
        int src = child * 0x10 + base;
        int dst = i * 0x10 + base;
        *(int*)(dst + 0)  = *(int*)(src + 0);
        *(int*)(dst + 4)  = *(int*)(src + 4);
        *(int*)(dst + 8)  = *(int*)(src + 8);
        *(int*)(dst + 12) = *(int*)(src + 12);
        i = child;
    }
    if (child == n) {
        int src = child * 0x10 - 0x10 + base;
        int dst = i * 0x10 + base;
        *(int*)(dst + 0)  = *(int*)(src + 0);
        *(int*)(dst + 4)  = *(int*)(src + 4);
        *(int*)(dst + 8)  = *(int*)(src + 8);
        *(int*)(dst + 12) = *(int*)(src + 12);
        i = child - 1;
    }
    FUN_00f96eb0(base, a, i, p5, p6, p7, p8, p9);
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9aff0
RefPair* FUN_00f9aff0(RefPair* first, RefPair* last, RefPair* dst)
{
    if (last != first) {
        do {
            IRefObj32* a = (last - 1)->p;
            IRefObj32* b = (dst - 1)->p;
            last--;
            dst--;
            if (a != b) {
                if (a)
                    a->AddRef();
                dst->p = a;
                if (b)
                    b->Release();
            }
            dst->x = last->x;
        } while (last != first);
    }
    return dst;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b050
void FUN_00f9b050(float* first, float* last, float* dst)
{
    for (; first != last; first += 5) {
        if (dst) {
            dst[0] = first[0];
            dst[1] = first[1];
            dst[2] = first[2];
            dst[3] = first[3];
            dst[4] = first[4];
        }
        dst += 5;
    }
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b0a0
struct CGmeRefCount {
    uint32_t      mF0;          // +0x00
    void*         mVtbl4;       // +0x04
    uint8_t       pad8[0x18 - 0x8];
    IRefCounted2* mp18;         // +0x18
    IRefCounted2* mp1c;         // +0x1c
    void* Destroy(uint8_t flags);
    void  Destroy2();
};
void* CGmeRefCount::Destroy(uint8_t flags)
{
    IRefCounted2* p = mp18;
    if (p) {
        int rc = p->mRefCount;
        p->mRefCount = rc - 1;
        if (rc - 1 == 0) {
            p->mRefCount = 1;
            p->Destroy(1);
        }
    }
    mVtbl4 = &vtbl_GmeRefCount0;
    if (flags & 1)
        operator delete(this);
    return this;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b0f0
struct CGmeRefCount2 {
    void*         mVtbl0;       // +0x00
    void*         mVtbl4;       // +0x04
    uint32_t      mF8;          // +0x08
    float         mFC;          // +0x0c
    float         mF10;         // +0x10
    float         mF14;         // +0x14
    IRefCounted2* mp18;         // +0x18
    IRefCounted2* mp1c;         // +0x1c
    void Construct(float a, float b, float c, IRefCounted2* p5, IRefCounted2* p6);
};
extern void* vtbl_01490908;     // 0x01490908
extern void* vtbl_01490904;     // 0x01490904
extern void* vtbl_01490940;     // 0x01490940
extern void* vtbl_0149093c;     // 0x0149093c
void CGmeRefCount2::Construct(float a, float b, float c, IRefCounted2* p5, IRefCounted2* p6)
{
    mVtbl4 = &vtbl_GmeRefCount0;
    mF8 = 0;
    mFC = a;
    mF10 = b;
    mVtbl0 = &vtbl_01490908;
    mVtbl4 = &vtbl_01490904;
    mF14 = c;
    mp18 = p5;
    if (p5)
        p5->mRefCount++;
    mVtbl0 = &vtbl_01490940;
    mVtbl4 = &vtbl_0149093c;
    mp1c = p6;
    if (p6)
        p6->mRefCount++;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b170
void CGmeRefCount::Destroy2()
{
    IRefCounted2* p = mp1c;
    if (p) {
        int rc = p->mRefCount;
        p->mRefCount = rc - 1;
        if (rc - 1 == 0) {
            p->mRefCount = 1;
            p->Destroy(1);
        }
    }
    p = mp18;
    if (p) {
        int rc = p->mRefCount;
        p->mRefCount = rc - 1;
        if (rc - 1 == 0) {
            p->mRefCount = 1;
            p->Destroy(1);
        }
    }
    mVtbl4 = &vtbl_GmeRefCount0;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b1e0
struct Matrix33 { uint8_t pad[0x30]; };
struct cSPTransform2 {
    uint16_t mFlags;            // +0x00
    uint16_t mModCount;         // +0x02
    float    mTrans[3];         // +0x04
    float    mScale;            // +0x10
    Matrix33 mRot;              // +0x14
    uint8_t  pad44[0x98 - 0x44];
    float    mF98;              // +0x98
    float    mF9c;              // +0x9c
    float    mFa0;              // +0xa0
    float    mFa4;              // +0xa4
    float    mFa8;              // +0xa8
    cSPTransform2* Init(const cSPTransform2* src);
    cSPTransform2* CopyFrom(const float* pos, const cSPTransform2* src, bool flag);
};
extern float g_DAT_16c9e8c;     // 0x016c9e8c
extern float g_DAT_16c9e90;     // 0x016c9e90
extern float g_DAT_16c9e94;     // 0x016c9e94
extern float g_DAT_16c9f24;     // 0x016c9f24
void __cdecl Matrix3_Assign(Matrix33* dst, float* src);   // 0x0041cb40
void* __cdecl cSPTransformOps_Assign(void* dst, const void* src);  // 0x00537dc0
cSPTransform2* cSPTransform2::Init(const cSPTransform2* src)
{
    mModCount = 0;
    mFlags = 0;
    mTrans[0] = g_DAT_16c9e8c;
    mTrans[1] = g_DAT_16c9e90;
    mTrans[2] = g_DAT_16c9e94;
    mScale = kOne;
    Matrix3_Assign(&mRot, &g_DAT_16c9f24);
    mF98 = 0.0f;
    mF9c = 0.0f;
    mFa0 = 0.0f;
    cSPTransformOps_Assign(this, src);
    mF98 = src->mF98;
    mF9c = src->mF9c;
    mFa0 = src->mFa0;
    mFa4 = src->mFa4;
    memcpy((uint8_t*)this + 0x38, (const uint8_t*)src + 0x38, 0x60);
    mFa8 = src->mFa8;
    return this;
}
// ----------------------------------------------------------------------------------------
// @ 0x00f9b2b0
void* __cdecl FUN_00f96390(void* a, void* b);            // 0x00f96390
cSPTransform2* cSPTransform2::CopyFrom(const float* pos, const cSPTransform2* src, bool flag)
{
    mFlags = src->mFlags;
    mModCount = src->mModCount;
    mTrans[0] = src->mTrans[0];
    mTrans[1] = src->mTrans[1];
    mTrans[2] = src->mTrans[2];
    mScale = src->mScale;
    Matrix3_Assign(&mRot, (float*)&src->mRot);
    mF98 = pos[0];
    mF9c = pos[1];
    mFa0 = pos[2];
    mFa4 = flag ? 0x4000000 : 0;
    mFa8 = (float)(int)FUN_00f96390((void*)src, (void*)pos);
    MemZero((uint8_t*)this + 0x38, 0, 0x60);
    return this;
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b350
struct cSkyThing {
    virtual void v0();
    uint8_t pad[0x94 - 4];
    virtual bool IsVisible(void* mgr);   // +0x94
};
struct cLightingSet {
    cSkyThing* mpVtbl0;         // +0x00
    uint8_t pad[0x6e0 - 4];
    void FUN_00f9b350();
};
void cLightingSet::FUN_00f9b350()
{
    void* mgr = GetManager67b();
    if (mpVtbl0->IsVisible(mgr)) {
        SkyStateUpdate(this);
        SetShaderParam(0x305, (uint8_t*)this + 0x4f8, 0);
        SetShaderParam(0x306, (uint8_t*)this + 0x6c8, 0);
        FUN_00f992e0();
        SetShaderParam(0x24c, (uint8_t*)this + 0x638, 0);
        SetShaderParam(0x24d, (uint8_t*)this + 0x6d8, 0);
        return;
    }
    SetShaderParam(0x305, 0, 0);
    SetShaderParam(0x306, 0, 0);
    SetShaderParam(0x24c, 0, 0);
}

// ----------------------------------------------------------------------------------------
// @ 0x00f9b400
struct cLightSet400 {
    uint8_t pad[0x28];
    IPropListC* mpProps;        // +0x28
    uint8_t pad2c[0x814 - 0x2c];
    int     mCount814;          // +0x814
    void FUN_00f9b400(float sel, unsigned int a, unsigned int b);
};
void cLightSet400::FUN_00f9b400(float sel, unsigned int a, unsigned int b)
{
    float f = 0.0f;
    if ((unsigned int)((int)sel - 1) < 0x40) {
        float v[4];
        v[0] = kOne;
        v[1] = kOne;
        v[2] = kBig;
        float fi = (float)(int)sel;
        if ((int)sel < 0) fi += 4294967296.0f;
        f = (fi - 0.5f) * 0.015625f;
        if (SP_GetPropertyAsVector3(mpProps, 0x3a23f99, v)) {
            Variant var;
            var.mTypeId = 0;
            var.mFlags = 0;
            v[0] = fi;
            v[1] = fi;
            FUN_006a3570(v);
            mpProps->Set(0x3a23f9a, &var);
            if (var.mFlags & 4)
                Variant_Destruct(&var, 0);
            mCount814++;
        }
    } else {
        if (sel != 0.0f) {
            goto after;
        }
        float v[4];
        v[0] = kOne;
        v[1] = kOne;
        v[2] = kBig;
        SP_GetPropertyAsVector3(mpProps, 0x3a23f99, v);
        mpProps->Del(0x3a23f9a);
        f = (v[0] - 0.5f) * 0.015625f;
        mCount814++;
    }
    FUN_00fbd880(f, f);
after:
    if (a < 0x10) {
        Variant var;
        var.mTypeId = 0;
        var.mFlags = 0;
        *(unsigned int*)&var = a;   // operator=<unsigned int>
        mpProps->Set(0x536250c, &var);
        if (var.mFlags & 4)
            Variant_Destruct(&var, 0);
        FUN_00fbaf10(a);
    }
    if (b < 0x10) {
        Variant var;
        var.mFlags = 0;
        var.mTypeId = 0;
        *(unsigned int*)&var = b;
        mpProps->Set(0x536250d, &var);
        if (var.mFlags & 4)
            Variant_Destruct(&var, 0);
        FUN_00fbaf50(sel);
    }
}
