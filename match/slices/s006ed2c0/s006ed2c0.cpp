// Slice s006ed2c0 — SP::cEffectsRenderer particle helpers and SP::cEffectsModel
// particle/model helpers (retail offsets).
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include "types.h"

// ---- vtable-slot helper ------------------------------------------------------
#define VTSLOT(o, off) (*(void**)((char*)(*(void**)o) + (off)))

typedef char     (__thiscall *TFc_v)(void*);
typedef char     (__thiscall *TFc_p)(void*, void*);
typedef void     (__thiscall *TFv_v)(void*);
typedef void     (__thiscall *TFv_i)(void*, int);
typedef void     (__thiscall *TFv_u)(void*, unsigned);
typedef void     (__thiscall *TFv_p)(void*, void*);
typedef unsigned (__thiscall *TFu_v)(void*);
typedef void*    (__thiscall *TFp_v)(void*);
typedef void*    (__thiscall *TFp_i)(void*, int);
typedef void*    (__thiscall *TFp_p)(void*, void*);
typedef void*    (__thiscall *TFp_pp)(void*, void*, void*);

// ---- stub types --------------------------------------------------------------
struct IRefCounted {
    virtual void AddRef() = 0;   // vtable +0
    virtual void Release() = 0;  // vtable +4
};

template<class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Release() { T* p = mpObject; if (p) { mpObject = 0; p->Release(); } }
    AutoRefCount& operator=(T* p) { if (mpObject) { T* old = mpObject; mpObject = p; old->Release(); } else mpObject = p; return *this; }
};

// EASTL-style vector: out-of-line members keep the calls separate (as originally).
template<class T>
struct evec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    char mAllocator[4];
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T& operator[](unsigned n) { return *(mpBegin + n); }
    void push_back(const T& v);
    void erase(T* first, T* last);
};

// ---- free-id / id-list vector (12-byte outline) ------------------------------
struct UIntVecInl {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity;
    void DoInsertValue(unsigned* pos, const unsigned& v);   // 0x004558A0
    void push_back(const unsigned& v) {
        unsigned* e = mpEnd;
        if (e < mpCapacity) { mpEnd = e + 1; if (e) *e = v; }
        else DoInsertValue(e, v);
    }
};
struct UIntVecOut {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity;
    void push_back(const unsigned& v);                      // 0x00454860
    void DoInsertValue(unsigned* pos, const unsigned& v);   // 0x004558A0
};

// ---- particle-set element types ----------------------------------------------
struct cTextureParticleSet {
    char pad0[0x48];
    bool mActive;        // +0x48
    bool mInActiveList;  // +0x49
    char pad1[0x70 - 0x4a];
    void* mabc0(const cTextureParticleSet& v);   // 0x006EABC0 (placement construct)
};

struct cModelParticleSet {
    void* mpRef0;            // +0x00 (intrusive reference-counted object)
    char pad0[0x50 - 0x04];
    bool mActive;            // +0x50
    char pad1[0x5c - 0x51];
    void* mpField5c;         // +0x5c
    IRefCounted* mpField60;  // +0x60
    int mField64;            // +0x64
    void* m6eb8c0(void* p);  // 0x006EB8C0 (destroy-last helper)
    void  m6eac80(void* p);  // 0x006EAC80 (construct/assign helper)
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
};

struct DispatchData { void* p0; void* p1; void* p2; };

// ---- rw::core::arena::Arena --------------------------------------------------
struct Arena {
    int  GetNumExportedObjects();                        // 0x011E23A0
    void GetExportedObjectByIndex(int index, void* out);  // 0x011E28E0
};

struct ExportedObject {
    int   mType;   // +0x00
    void* mpData;  // +0x04
};

// ---- free helper callees -----------------------------------------------------
void  FUN_006e9330(const void* p);                    // 0x006E9330
void  FUN_006ebb00(void* a, void* b, void* c);        // 0x006EBB00
void* FUN_006e9460(void* a, void* b, void* c);        // 0x006E9460
void  FUN_006e94a0(void* a, void* b, void* c);        // 0x006E94A0
void  FUN_006ebb40(void* a, void* b, void* c);        // 0x006EBB40
void* FUN_006eba70(void* a, void* b, void* c);        // 0x006EBA70
void  FUN_006e94f0(void* a, void* b, void* c);        // 0x006E94F0
void* FUN_00f473a0(unsigned size, const char* tag, int a, int b, const char* file, int line);  // 0x00F473A0
void  FUN_00f47380(void* p);                          // 0x00F47380
void* FUN_0067dd70();                                 // 0x0067DD70 (SP::MaterialManager)
extern float g_arenaBound[3];                         // 0x01618D1C
extern float g_one;                                   // 0x01485720 (_HK_REAL_ONE)

// ---- SP::cEffectsModel (retail: bbox at +0x50, refs vector at +0x70) ---------
class cEffectsModel {
public:
    void* mpVtable;                                  // +0x00
    int   mField4;                                   // +0x04
    evec<DispatchData> mDispatchData;                // +0x08
    void* mDispatchInlinePtr;                        // +0x18
    char  padD0[4];                                  // +0x1c
    char  mDispatchBuf[0x30];                        // +0x20 .. +0x50
    Vector3 mBoxMin;                                 // +0x50
    Vector3 mBoxMax;                                 // +0x5c
    float   mBoundingRadius;                         // +0x68
    AutoRefCount<IRefCounted> mAsyncRequest;         // +0x6c
    evec<AutoRefCount<IRefCounted> > mResourceRefs;  // +0x70
    void* mResInlinePtr;                             // +0x80
    char  padR0[4];                                  // +0x84
    char  mResBuf[0x10];                             // +0x88 .. +0x98

    cEffectsModel(unsigned a, unsigned b, unsigned c, const float* box);  // 6ed8d0
    void AddResourceRef(IRefCounted* p);                                  // 6edaa0
    void Reset();                                                         // 6edb10
    void UpdateFromResource(int* res);                                    // 6edbc0
    char Update();                                                        // 6ee140
    void me90(int a, unsigned b, unsigned c);                             // 0x006ECE90
    void mdd0(int a, int b);                                              // 0x006ECDD0
    void me30(int a, int b, int c);                                       // 0x006ECE30
    void ComputeRadius();
};

// ---- SP::cEffectsRenderer (retail offsets) ----------------------------------
class cEffectsRenderer {
public:
    char pad0[0x174];
    evec<cTextureParticleSet> mTextureParticleSets;    // +0x174
    char pad1[4];                                       // +0x184
    evec<unsigned short> mActiveTextureParticleSets;   // +0x188
    char pad2[0x1b8 - 0x198];
    cModelParticleSet* mModelBegin;      // +0x1b8
    cModelParticleSet* mModelEnd;        // +0x1bc
    cModelParticleSet* mModelCapacity;   // +0x1c0
    char pad3[0x1cc - 0x1c4];
    UIntVecOut mFreeIDs;                 // +0x1cc
    char pad4[0x1e0 - 0x1d8];
    IRefCounted* mSys1e0;                // +0x1e0

    void SetTextureParticleActive(int index, bool active);   // 6ed2c0
    void RemoveParticleSet(int index);                       // 6ed340
};

// ---- key/flag activation list (vtable obj at +0x0c, id vector at +0x10) -------
struct cEffectsKeyedList {
    char pad0[0x0c];
    void* mpObj0c;        // +0x0c
    UIntVecInl mIds;      // +0x10
    int ActivateByKey(unsigned a, unsigned b);   // 6ed440
};

// ---- out-of-line EASTL vector instantiations ---------------------------------
struct vectorCTex {
    cTextureParticleSet* mpBegin; cTextureParticleSet* mpEnd; cTextureParticleSet* mpCapacity;
    void DoInsertValue(cTextureParticleSet* pos, const cTextureParticleSet& v);  // 6ed5b0
};
struct vectorCMod {
    cModelParticleSet* mpBegin; cModelParticleSet* mpEnd; cModelParticleSet* mpCapacity;
    void DoInsertValue(cModelParticleSet* pos, const cModelParticleSet& v);      // 6ed6f0
};

// ---- 0x006ed2c0 --------------------------------------------------------------
// @ 0x006ed2c0
void cEffectsRenderer::SetTextureParticleActive(int index, bool active)
{
    if (index < 0 || index >= (int)mTextureParticleSets.size())
        return;
    cTextureParticleSet& p = mTextureParticleSets[index];
    if (p.mActive == active)
        return;
    p.mActive = active;
    if (!active)
        return;
    if (p.mInActiveList)
        return;
    mActiveTextureParticleSets.push_back((unsigned short)index);
    p.mInActiveList = 1;
}

// ---- 0x006ed340 --------------------------------------------------------------
// @ 0x006ed340
void cEffectsRenderer::RemoveParticleSet(int index)
{
    if (index >= 0 && index < (mModelEnd - mModelBegin)) {
        cModelParticleSet* p = mModelBegin + index;
        if (p->mpField60 != 0) {
            ((TFv_i)VTSLOT(p->mpField60, 0x0c))(p->mpField60, p->mField64);
            if (p->mpField60 != 0) {
                IRefCounted* q = p->mpField60;
                p->mpField60 = 0;
                ((TFv_v)VTSLOT(q, 0x04))(q);
            }
            p->mField64 = -1;
            unsigned* e = mFreeIDs.mpEnd;
            if (e < mFreeIDs.mpCapacity) {
                mFreeIDs.mpEnd = e + 1;
                if (e) *e = (unsigned)index;
            } else {
                mFreeIDs.DoInsertValue(e, (unsigned&)index);
            }
        } else {
            void* r = p->mpRef0;
            if (r != 0) {
                p->mpRef0 = 0;
                int* rc = (int*)((char*)r + 4);
                int n = *rc + (-1);
                *rc = n;
                if (n == 0) {
                    *rc = 1;
                    ((TFv_i)VTSLOT(r, 0x00))(r, 1);
                }
                p->mActive = false;
                if (p->mpField5c != 0) {
                    if (mSys1e0 != 0)
                        ((TFv_p)VTSLOT(mSys1e0, 0x20))(mSys1e0, p->mpField5c);
                    p->mpField5c = 0;
                }
                mFreeIDs.push_back((unsigned&)index);
            }
        }
    }
}

// ---- 0x006ed440 --------------------------------------------------------------
// @ 0x006ed440
int cEffectsKeyedList::ActivateByKey(unsigned a, unsigned b)
{
    if (mpObj0c != 0 && (a & b) != 0xffffffffu) {
        if (mIds.mpBegin == mIds.mpEnd) {
            unsigned id = ((TFu_v)VTSLOT(mpObj0c, 0x58))(mpObj0c);
            mIds.push_back(id);
        }
        ((TFv_u)VTSLOT(mpObj0c, 0x34))(mpObj0c, (a | b) ? a : 0u);
        unsigned idx = (unsigned)(mIds.mpEnd - mIds.mpBegin);
        mIds.push_back(a);
        return (int)idx;
    }
    return -1;
}

// ---- 0x006ed5b0 --------------------------------------------------------------
// @ 0x006ed5b0
void vectorCTex::DoInsertValue(cTextureParticleSet* pos, const cTextureParticleSet& value)
{
    cTextureParticleSet* end = mpEnd;
    if (end != mpCapacity) {
        cTextureParticleSet* v = const_cast<cTextureParticleSet*>(&value);
        if (v >= pos && v < end)
            v += 1;
        if (end)
            FUN_006e9330(end - 1);
        FUN_006ebb00(pos, end - 1, end);
        pos->mabc0(*v);
        mpEnd = end + 1;
        return;
    }
    unsigned n = (unsigned)(end - mpBegin);
    cTextureParticleSet* mem;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0) {
            mem = 0;
            goto alloc_done;
        }
    }
    mem = (cTextureParticleSet*)FUN_00f473a0(n * 0x70, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
alloc_done:
    {
        cTextureParticleSet* begin = mpBegin;
        cTextureParticleSet* mid = (cTextureParticleSet*)FUN_006e9460(begin, pos, mem);
        FUN_006e94a0(begin, pos, mem);
        if (mid)
            FUN_006e9330(&value);
        cTextureParticleSet* newEnd = (cTextureParticleSet*)FUN_006e9460(pos, end, mid + 1);
        FUN_006e94a0(pos, end, mid + 1);
        if (begin && ((int*)begin)[-1] != 0)
            FUN_00f47380(begin);
        mpBegin = mem;
        mpEnd = newEnd;
        mpCapacity = mem + n;
    }
}

// ---- 0x006ed6f0 --------------------------------------------------------------
// @ 0x006ed6f0
void vectorCMod::DoInsertValue(cModelParticleSet* pos, const cModelParticleSet& value)
{
    cModelParticleSet* end = mpEnd;
    if (end != mpCapacity) {
        cModelParticleSet* v = const_cast<cModelParticleSet*>(&value);
        if (v >= pos && v < end)
            v += 1;
        if (end)
            end->m6eb8c0(end - 1);
        FUN_006ebb40(pos, end - 1, end);
        pos->m6eac80(v);
        mpEnd = end + 1;
        return;
    }
    unsigned n = (unsigned)(end - mpBegin);
    cModelParticleSet* mem;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0) {
            mem = 0;
            goto alloc_done;
        }
    }
    mem = (cModelParticleSet*)FUN_00f473a0(n * 0x68, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
alloc_done:
    {
        cModelParticleSet* begin = mpBegin;
        cModelParticleSet* mid = (cModelParticleSet*)FUN_006eba70(begin, pos, mem);
        FUN_006e94f0(begin, pos, mem);
        if (mid)
            mid->m6eb8c0((void*)&value);
        cModelParticleSet* newEnd = (cModelParticleSet*)FUN_006eba70(pos, end, mid + 1);
        FUN_006e94f0(pos, end, mid + 1);
        if (begin && ((int*)begin)[-1] != 0)
            FUN_00f47380(begin);
        mpBegin = mem;
        mpEnd = newEnd;
        mpCapacity = mem + n;
    }
}

// ---- 0x006ed8d0 --------------------------------------------------------------
// @ 0x006ed8d0
cEffectsModel::cEffectsModel(unsigned a, unsigned b, unsigned c, const float* box)
{
    mField4 = 0;
    mpVtable = (void*)0x140afd4;
    DispatchData* dinl = (DispatchData*)((char*)this + 0x20);
    mDispatchInlinePtr = dinl;
    mDispatchData.mpEnd = dinl;
    mDispatchData.mpBegin = dinl;
    mDispatchData.mpCapacity = dinl + 4;
    const float f = 3.402823466e38f;
    mBoxMin = Vector3(f, f, f);
    mBoxMax = Vector3(-f, -f, -f);
    mAsyncRequest.mpObject = 0;
    AutoRefCount<IRefCounted>* rinl = (AutoRefCount<IRefCounted>*)((char*)this + 0x88);
    mResInlinePtr = rinl;
    mResourceRefs.mpEnd = rinl;
    mResourceRefs.mpBegin = rinl;
    mResourceRefs.mpCapacity = rinl + 4;
    me90(a, b, c);
    mBoxMin = Vector3(box[0], box[1], box[2]);
    mBoxMax = Vector3(box[3], box[4], box[5]);
    ComputeRadius();
}

// ---- bounding-radius helper (max |min|/|max| per axis, then axis max) --------
void cEffectsModel::ComputeRadius()
{
    float bx = mBoxMax.x, by = mBoxMax.y, bz = mBoxMax.z;
    float nx = -mBoxMin.x, ny = -mBoxMin.y, nz = -mBoxMin.z;
    float xf = (bx <= nx) ? nx : bx;
    float yf = (by <= ny) ? ny : by;
    float zf = (bz <= nz) ? nz : bz;
    float m = (yf <= xf) ? xf : yf;
    if (m <= zf && zf != m)
        m = zf;
    mBoundingRadius = m;
}

// ---- 0x006edaa0 --------------------------------------------------------------
// @ 0x006edaa0
void cEffectsModel::AddResourceRef(IRefCounted* p)
{
    AutoRefCount<IRefCounted> ref(p);
    mResourceRefs.push_back(ref);
}

// ---- 0x006edb10 --------------------------------------------------------------
// @ 0x006edb10
void cEffectsModel::Reset()
{
    const float f = 3.402823466e38f;
    Vector3 v(f, f, f);
    mBoxMin = v;
    mBoxMax = -v;
    mBoundingRadius = 0.0f;
    mAsyncRequest.Release();
    mDispatchData.erase(mDispatchData.mpBegin, mDispatchData.mpEnd);
    mResourceRefs.erase(mResourceRefs.mpBegin, mResourceRefs.mpEnd);
}

// ---- 0x006edbc0 --------------------------------------------------------------
// @ 0x006edbc0
void cEffectsModel::UpdateFromResource(int* res)
{
    if (res == 0)
        return;
    int* obj = (int*)((TFp_i)VTSLOT(res, 0x0c))(res, 0x2f4e681b);
    if (obj == 0) {
        // material-copy path (tag 0xe6bce5)
        int* mat = (int*)((TFp_i)VTSLOT(res, 0x0c))(res, 0xe6bce5);
        if (mat == 0)
            return;
        AddResourceRef((IRefCounted*)mat);
        int count = (int)((mat[0x1c / 4] - mat[0x18 / 4]) >> 2);
        if (mat[0xf4 / 4] == mat[0xf8 / 4]) {
            int* aa = (int*)mat[0x18 / 4];
            int* bb = (int*)mat[0xb8 / 4];
            for (int j = 0; j < count; ++j)
                mdd0(aa[j], bb[j]);
        } else {
            int* aa = (int*)mat[0x18 / 4];
            int* bb = (int*)mat[0xb8 / 4];
            int* cc = (int*)mat[0xf4 / 4];
            for (int j = 0; j < count; ++j)
                me30(aa[j], bb[j], cc[j]);
        }
        int* src = (int*)((char*)mat + 0x11c);
        mBoxMin = Vector3(((float*)src)[0], ((float*)src)[1], ((float*)src)[2]);
        mBoxMax = Vector3(((float*)src)[3], ((float*)src)[4], ((float*)src)[5]);
    } else {
        // arena exported-object path (tag 0x2f4e681b)
        Arena* arena = (Arena*)obj[0x18 / 4];
        int n = arena->GetNumExportedObjects();
        const float f = 3.402823466e38f;
        mBoxMin = Vector3(f, f, f);
        mBoxMax = Vector3(-f, -f, -f);
        AddResourceRef((IRefCounted*)obj);
        for (int i = 0; i < n; ++i) {
            ExportedObject out;
            arena->GetExportedObjectByIndex(i, &out);
            if (out.mType == 0x2001a) {
                float* d = (float*)out.mpData;
                void* mm = FUN_0067dd70();
                void* v = ((TFp_pp)VTSLOT(mm, 0x40))(mm, *(void**)&d[2], obj);
                void* mm2 = FUN_0067dd70();
                void* p = ((TFp_p)VTSLOT(mm2, 0x28))(mm2, v);
                DispatchData dd;
                dd.p0 = *(void**)&d[0];
                dd.p1 = p;
                dd.p2 = 0;
                mDispatchData.push_back(dd);
            } else if (out.mType == 0x80005) {
                float* d = (float*)out.mpData;
                if (mBoxMin.x > d[0]) mBoxMin.x = d[0];
                if (d[4] > mBoxMax.x) mBoxMax.x = d[4];
                if (mBoxMin.y > d[1]) mBoxMin.y = d[1];
                if (d[5] > mBoxMax.y) mBoxMax.y = d[5];
                if (mBoxMin.z > d[2]) mBoxMin.z = d[2];
                if (d[6] > mBoxMax.z) mBoxMax.z = d[6];
            }
        }
        if (mBoxMin.x == f) {
            float one = g_one;
            mBoxMin = Vector3(g_arenaBound[0] - one, g_arenaBound[1] - one, g_arenaBound[2] - one);
            mBoxMax = Vector3(g_arenaBound[0] + one, g_arenaBound[1] + one, g_arenaBound[2] + one);
        }
    }
    ComputeRadius();
}

// ---- 0x006ee140 --------------------------------------------------------------
// @ 0x006ee140
char cEffectsModel::Update()
{
    IRefCounted* req = mAsyncRequest.mpObject;
    if (req != 0) {
        if (((TFc_v)VTSLOT(req, 0x10))(req)) {
            AutoRefCount<IRefCounted> local;
            if (((TFc_p)VTSLOT(mAsyncRequest.mpObject, 0x14))(mAsyncRequest.mpObject, &local.mpObject))
                UpdateFromResource((int*)local.mpObject);
            mAsyncRequest.Release();
            return 1;
        }
    }
    return 0;
}