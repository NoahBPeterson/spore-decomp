// SP::cTerrainSphere::UpdateQuadsPostCamera: after the camera moved, walk the quad tree from the six
// face roots, cull by distance/facing and frustum, refine, and fill the per-frame render arrays.
// Retail layout of cTerrainSphere differs from the 2008 PDB here; offsets below come from the disassembly.
#include <new>
#include <math.h>
#include <string.h>
#include <intrin.h>
#include "types.h"

struct Vec3f { float x, y, z; };

extern float g_ZeroX;                                   // 0x016c9e8c
extern float g_ZeroY;                                   // 0x016c9e90
extern float g_ZeroZ;                                   // 0x016c9e94
extern float g_Ident[9];                                // 0x016c9f24 (3x3 block to 0x016c9f44)

struct cQuad {
    char pad0[8];
    cQuad* children[4];            // +8
    char pad1[0x34 - 0x18];
    Vec3f centre;                  // +0x34
    char pad2[0x64 - 0x40];
    float lodKey;                  // +0x64
    char pad3[0x70 - 0x68];
    Vec3f sphereCentre;            // +0x70
    float sphereRadius;            // +0x7c
    void Refine();                 // 0x00fb77b0
    void MarkChild();              // 0x00fb5090
};

struct QItem { cQuad* quad; uint32_t flags; };
struct QContainer { cQuad* quad; float lod; uint32_t key; uint32_t zero; };

struct QuadStack {                 // global at 0x016ca24c
    QItem* mpBegin;
    QItem* mpEnd;
    QItem* mpCapacity;
    void DoInsertValue(QItem* pos, const QItem& v);     // 0x00b534c0 (ret 8)
    void push_back(const QItem& v)
    {
        if (mpEnd < mpCapacity) {
            QItem* p = mpEnd++;
            ::new ((void*)p) QItem(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
extern QuadStack g_QuadStack;   // 0x016ca24c

struct QCVector {                  // eastl::vector<QContainer, sp_vector_allocator>, 0x14 bytes
    QContainer* mpBegin;
    QContainer* mpEnd;
    QContainer* mpCapacity;
    uint32_t alloc[2];
    void DoInsertValue(QContainer* pos, const QContainer& v);   // 0x00c19d10 (ret 8)
    void push_back(const QContainer& v)
    {
        if (mpEnd < mpCapacity) {
            QContainer* p = mpEnd++;
            ::new ((void*)p) QContainer(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    void clear()
    {
        QContainer* first = mpBegin;
        QContainer* last = mpEnd;
        CopyRange(last, last, first);
        mpEnd += (first - last);
    }
    static void* CopyRange(QContainer* a, QContainer* b, QContainer* c);   // 0x00705250 (cdecl)
};

struct Property {
    char pad[0x12];
    short type;
    float* GetFloat();             // 0x0041ea70
};

struct cDirectPropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);       // +0x24
    bool GetDescription(uint32_t id);                            // 0x006a25a0 (ret 4)
    float GetFloatProperty(uint32_t id);                         // 0x006a2710 (ret 4)
};
extern cDirectPropertyList* sAppProperties;                      // 0x015fd918

// Direct State-system globals driven by DrawLayerRTT.
extern uint32_t* g_16f6ee0;                                      // 0x016f6ee0 (pointer to state flags)
extern void* g_16c9e68;                                          // 0x016c9e68
extern void* g_16c9f5c;                                          // 0x016c9f5c
extern bool g_15b14e8;                                           // 0x015b14e8
extern void** g_ppRaster16c9f58;                                 // 0x016c9f58
extern unsigned g_rasterStageDirty;                              // 0x016fa3a8
extern int g_rasterCur16f9674;                                   // 0x016f9674
extern unsigned g_16f9554;                                       // 0x016f9554
extern int g_16fa1c4;                                            // 0x016fa1c4
extern int g_16fa1c8;                                            // 0x016fa1c8
extern int g_16fa1d4;                                            // 0x016fa1d4
extern int g_16fa1d8;                                            // 0x016fa1d8
extern int g_16fa1dc;                                            // 0x016fa1dc

void FUN_00f96b40();                                             // 0x00f96b40
void FUN_00f96c60();                                             // 0x00f96c60
void FUN_00f9e280();                                             // 0x00f9e280
void FUN_00f9e350();                                             // 0x00f9e350

struct cFrustumCull {
    uint32_t buf[0x3b];
    cFrustumCull(void* camera);                                  // 0x006ffe00 (ret 4)
    void SetNear(float f);                                       // 0x006ffa80 (ret 4)
    uint32_t FrustumTestSphere(const Vec3f* centre, const float* radius, uint32_t flags);   // 0x00700120
};

struct SPTransform {
    short a, b;
    Vec3f pos;
    float scale;
    float rot[9];
    SPTransform() : a(0), b(0), scale(1.0f)
    {
        pos.x = g_ZeroX; pos.y = g_ZeroY; pos.z = g_ZeroZ;
        for (int i = 0; i < 9; ++i) rot[i] = g_Ident[i];
    }
};

struct cViewer { void GetTransform(SPTransform* out); void Clear(unsigned mask); };  // 0x007c40f0 / 0x007c3c50

struct cTerrainInfo { char pad[0x34]; float radius; };

bool QuadDetailTest(cQuad* q, void* terrain, float* outDist);    // 0x00f97960 (stdcall, ret 0xc)
void SortQuads(QContainer* first, QContainer* last, bool flag);  // 0x00fa2660 (cdecl)

// --------------------------------------------------------- shared helper types

struct ResKey { uint32_t instance, type, group; };

// Object with an intrusive reference count in the 8 bytes after its vptr.
struct RefObj {
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
};

// Intrusive smart pointer (EA::AutoRefCount<T>); the ctor/dtor add/release one
// reference and a copy addrefs again.
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

// Resource object whose intrusive count is a plain interlocked word at +8.
struct ResRef {
    uint32_t mVtbl;                     // +0x00
    uint32_t mPad;                      // +0x04
    volatile long mRefCount;            // +0x08
    void AddRef() { _InterlockedIncrement(&mRefCount); }
    void Release()
    {
        _InterlockedExchangeAdd(&mRefCount, -1);
        long n = _InterlockedExchangeAdd(&mRefCount, 0);
        if (n < 1)
            _InterlockedExchangeAdd(&mRefCount, 1);
        else
            _InterlockedExchangeAdd(&mRefCount, 0);
    }
};

bool GetPropertyAsKey(cDirectPropertyList* list, uint32_t id, ResKey* out);   // 0x006a1250
bool GetPropertyAsVector3(cDirectPropertyList* list, uint32_t id, Vec3f* out); // 0x006a1110

// Manager returned by PropertyManager(); slot 0x2c builds a property list.
struct PropertyMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool v2c(void* a, void* b, void** out);   // +0x2c
};
PropertyMgr* PropertyManager();                        // 0x0067de30

// cResourceManager's GetResource(key, 0): the key is passed by value.
struct IResMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void* v1c(ResKey key, int d);               // +0x1c
};
IResMgr* GetResourceManager();                          // 0x0067dd60

// 0x14-byte eastl vector of reference-counted object pointers (the "out" list).
// The intrusive copy uses the object's virtual AddRef (vtable slot 0) while the
// temporary's destructor releases through the raw +8 interlocked word (0x576620).
struct RefVec {
    ResRef** mpBegin;
    ResRef** mpEnd;
    ResRef** mpCapacity;
    uint32_t mAlloc[2];
    void Add(ResRef** value);                                 // 0x00420660 (ret 4)
    void DoInsertValue(ResRef** pos, const ResRef** value);   // 0x00425a80 (ret 8)
    __forceinline void push_back(ResRef* v)
    {
        ResRef** e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) {
                *e = v;
                if (v)
                    v->AddRef();
            }
        } else {
            DoInsertValue(e, (const ResRef**)&v);
        }
    }
};

// A one-pointer slot whose destructor drops the reference (0x00576620).
struct ObjSlot { ResRef* mp; void Release(); };
// The second property list's object list (0x14-byte eastl vector) and its helper.
struct ModelKeyVec {
    ResKey* mpBegin;
    ResKey* mpEnd;
    ResKey* mpCapacity;
    uint32_t mAlloc[2];
    void DoCopy(ResKey* last, ResKey* first);         // 0x0050f740 (ret 8)
};

// The 0x14-byte eastl vector of Transform records (0x38-byte elements).
struct TransformVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAlloc[2];
};

// 0x14-byte eastl vector of 4-byte pointers with intrusive refcounts.
// copy_refs (0x5f4e10) is eastl's uninitialized copy; DoDestroyValues (0x5f3680)
// releases the elements between its two arguments.
struct PtrRefVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    uint32_t mAlloc[2];
    void DoDestroyValues(void** first, void** last);   // 0x5f3680 (ret 8)
};

// Free cdecl helpers on those vectors.
void* DoXformCopy(void* a, void* b, void* c);       // 0x00f339d0 (cdecl, 3 args)
void* DoPtrCopyRefs(void* a, void* b, void* c);     // 0x005f4e10 (cdecl, 3 args)

// The 0x8b0 / 0x8c4 lists hold 8-byte { object, param } entries.
struct Entry8 { RefObj* mObj; void* mParam; };
struct Entry8Vec {
    Entry8* mpBegin;
    Entry8* mpEnd;
    Entry8* mpCapacity;
    void Add(Entry8* pos, const Entry8* value);       // 0x00fa2440 (ret 8)
    void push_back(const Entry8& v)
    {
        Entry8* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) {
                e->mObj = v.mObj;
                if (e->mObj)
                    e->mObj->AddRef();
                e->mParam = v.mParam;
            }
        } else {
            Add(mpEnd, &v);
        }
    }
};

// Terrain record (0xac bytes) that carries an embedded property list.
struct TerrainRec {
    char  pad000[0x38];
    float mFaceBoxes[0x18];           // +0x38
    void* mField98;                   // +0x98
    uint32_t mField9c;                // +0x9c
    void* mFieldA0;                   // +0xa0
    uint32_t mFlags;                  // +0xa4
    char  pad0a8[0x04];
};

class cTerrainSphere {
public:
    virtual void vfn0(); virtual void vfn1(); virtual void vfn2();
    virtual cTerrainInfo* GetInfo();                             // +0xc
    void UpdateQuadsPostCamera(void* camera);                    // 0x00fa5610

    char pad0[0x110 - 4];
    bool mStaticRTTValid;            // +0x110
    char pad114[0x118 - 0x111];
    cQuad* faceRoots[6];             // +0x118
    cQuad* atmoRoots[6];             // +0x130
    char pad1[0x190 - 0x148];
    QCVector renderQuads;            // +0x190
    QCVector faceRootArray;          // +0x1a4
    QCVector atmoRootArray;          // +0x1b8
    char pad2[0x1e8 - 0x1cc];
    bool flagA;                      // +0x1e8
    char pad3[0x30c - 0x1e9];
    char decalState[0x20];           // +0x30c (QuadDetailTest terrain state)

    // Offsets touched by the gold7 group; the members between them are padding.
    char pad32c_770[0x770 - 0x32c];  // +0x32c .. +0x76c (raster decal state at +0x32c)
    TerrainRec* mRecBase_770;        // +0x770
    TerrainRec* mRecEnd_770;         // +0x774
    void* pad778[3];                 // +0x778 .. +0x784
    TerrainRec* mRecBase_784;        // +0x784
    TerrainRec* mRecEnd_784;         // +0x788
    char pad78c_7ac[0x7ac - 0x78c];
    int mCount_7ac;                  // +0x7ac
    ResKey* mModelKeys;              // +0x7b0 (ModelKeyVec begin..cap here)
    ResKey* mModelKeysEnd;           // +0x7b4
    ResKey* mModelKeysCap;           // +0x7b8
    uint32_t mAlloc7bc[2];           // +0x7bc
    void* mModelXforms;              // +0x7c4 (TransformVec begin..cap here)
    void* mModelXformsEnd;           // +0x7c8
    void* mModelXformsCap;           // +0x7cc
    uint32_t mAlloc7d0[2];           // +0x7d0
    void** mModelPtrs;               // +0x7d8 (PtrRefVec begin..cap here)
    void** mModelPtrsEnd;            // +0x7dc
    void** mModelPtrsCap;            // +0x7e0
    uint32_t mAlloc7e4[2];           // +0x7e4
    char pad7ec_8b0[0x8b0 - 0x7ec];
    Entry8* mEntries8b0;             // +0x8b0
    Entry8* mEntries8b0End;          // +0x8b4
    Entry8* mEntries8b0Cap;          // +0x8b8
    char pad8bc_8c4[0x8c4 - 0x8bc];
    Entry8* mEntries8c4;             // +0x8c4
    Entry8* mEntries8c4End;          // +0x8c8
    Entry8* mEntries8c4Cap;          // +0x8cc
    char pad8d0_8dc[0x8dc - 0x8d0];
    void* mpFaceQuads;               // +0x8dc
    char pad8e0[0x8e4 - 0x8e0];
    cViewer* viewer;                 // +0x8e4

    void DrawLayerRTT(void** a1, void* a2, void* a3);         // 0x00fa5cc0
    void ClearModels();                                       // 0x00fa5e40
    void RequestModelFootprint(cDirectPropertyList* list, PtrRefVec* out);   // 0x00fa5ee0
    void AddPaintDecalsFromModels(void* param);               // 0x00fa6130
    void AddEntry8b0(RefObj* obj, void* param);               // 0x00fa6320
    void AddEntry8c4(RefObj* obj, void* param);               // 0x00fa63d0

    void ApplyModelFootprint(const void* xform, void* props, void* a3, float* faceBoxes, bool bDecal);   // 0x00fa3c10

    // Fixed-RTT helpers (this-relative, callee cleans the stack arguments).
    void FUN_00fa3860(void* a, void* b);                      // 0x00fa3860
    void FUN_00f9c470(void* a, void* b);                      // 0x00f9c470
    void FUN_00f9df20(void* a, void* b, void* c, void* d);    // 0x00f9df20
    void FUN_00f998f0();                                      // 0x00f998f0
};

// @ 0x00fa5cc0
void cTerrainSphere::DrawLayerRTT(void** a1, void* a2, void*)
{
    cDirectPropertyList* props = sAppProperties;
    bool bBase = props->GetDescription(0x201a4e50);
    bool bRefl = props->GetDescription(0xf1a9135a);
    bool bSecond = props->GetDescription(0x797fcd8c);

    *g_16f6ee0 &= ~2u;
    if (bBase) {
        if (g_16c9e68 == 0)
            FUN_00f96b40();
        if (!mStaticRTTValid) {
            FUN_00fa3860(*a1, a2);
            *g_16f6ee0 |= 2u;
        }
    } else {
        if (mpFaceQuads)
            FUN_00f998f0();
        if (g_16c9e68 != 0)
            FUN_00f96c60();
    }
    *g_16f6ee0 &= ~8u;
    if (bRefl) {
        if (g_16c9f5c == 0)
            FUN_00f9e280();
        if (!mStaticRTTValid) {
            FUN_00f9c470(*a1, a2);
            *g_16f6ee0 |= 8u;
        }
    } else {
        if (g_16c9f5c != 0)
            FUN_00f9e350();
    }
    if (g_15b14e8 && (bRefl || bBase))
        ((cViewer*)*a1)->Clear(6);

    if (bSecond) {
        uint32_t bit = 0x200;
        g_rasterStageDirty |= bit;
        g_rasterCur16f9674 = 0;
        FUN_00f9df20(*a1, *g_ppRaster16c9f58, pad32c_770, a2);
        g_rasterCur16f9674 = (int)*g_ppRaster16c9f58;
        g_rasterStageDirty |= bit;
        g_16f9554 |= 0x73;
        int three = 3;
        g_16fa1c4 = three;
        g_16fa1c8 = three;
        int two = 2;
        g_16fa1d8 = two;
        g_16fa1d4 = two;
        g_16fa1dc = two;
    }
}

// @ 0x00fa5e40
void cTerrainSphere::ClearModels()
{
    ModelKeyVec* keys = (ModelKeyVec*)((char*)this + 0x7b0);

    mCount_7ac = 0;
    keys->DoCopy(keys->mpBegin, keys->mpEnd);

    char* xfBegin = (char*)mModelXforms;
    char* xfEnd = (char*)mModelXformsEnd;
    DoXformCopy(xfEnd, xfEnd, xfBegin);
    // clear(): the element count is negated and scaled back, so the end returns to begin.
    int xfCount = (int)(xfEnd - xfBegin) / -0x38;
    mModelXformsEnd = (char*)mModelXformsEnd + xfCount * 0x38;

    PtrRefVec* ptr = (PtrRefVec*)((char*)this + 0x7d8);
    void** ptrBegin = ptr->mpBegin;
    void** ptrEnd = ptr->mpEnd;
    void* copied = DoPtrCopyRefs(ptrEnd, ptrEnd, ptrBegin);
    ptr->DoDestroyValues((void**)copied, ptr->mpEnd);
    int ptrCount = (int)((char*)ptrEnd - (char*)ptrBegin) >> 2;
    ptr->mpEnd = (void**)((char*)ptr->mpEnd - ptrCount * 4);
}

// @ 0x00fa5ee0
void cTerrainSphere::RequestModelFootprint(cDirectPropertyList* list, PtrRefVec* out)
{
    Vec3f scale = { 10.0f, 0.0f, 0.1f };
    ResKey key = { 0, 0, 0 };

    if (GetPropertyAsVector3(list, 0x3b28c1d, &scale)) {
        if (GetPropertyAsKey(list, 0x442151e, &key)) {
            IResMgr* mgr = GetResourceManager();
            ResRef* obj = (ResRef*)mgr->v1c(key, 0);
            if (obj) {
                obj->AddRef();
                ((RefVec*)out)->Add(&obj);
                ((ObjSlot*)&obj)->Release();
            }
        }
    }
    if (GetPropertyAsKey(list, 0x3b28c1b, &key)) {
        IResMgr* mgr = GetResourceManager();
        ResRef* obj = (ResRef*)mgr->v1c(key, 0);
        if (obj) {
            obj->AddRef();
            ((RefVec*)out)->push_back(obj);
            obj->Release();
        }
    }
    if (GetPropertyAsKey(list, 0x3abc381, &key)) {
        IResMgr* mgr = GetResourceManager();
        ResRef* obj = (ResRef*)mgr->v1c(key, 0);
        if (obj) {
            obj->AddRef();
            ((RefVec*)out)->push_back(obj);
            obj->Release();
        }
    }
}

// @ 0x00fa6130
void cTerrainSphere::AddPaintDecalsFromModels(void* param)
{
    PropertyMgr* mgr = PropertyManager();
    RefObj* list = 0;
    for (int i = 0; i < mCount_7ac; ++i) {
        if (list) {
            RefObj* old = list;
            list = 0;
            old->Release();
        }
        ResKey* rec = &mModelKeys[i];
        if (mgr->v2c((void*)rec->instance, (void*)rec->group, (void**)&list)) {
            ApplyModelFootprint((char*)mModelXforms + i * 0x38, list, param, 0, true);
        }
    }
    int n = (int)((char*)mRecEnd_770 - (char*)mRecBase_770) / 0xac;
    for (int i = 0; i < n; ++i) {
        if (list) {
            RefObj* old = list;
            list = 0;
            old->Release();
        }
        TerrainRec* rec = (TerrainRec*)((char*)mRecBase_770 + i * 0xac);
        if (mgr->v2c(rec->mField98, rec->mFieldA0, (void**)&list)) {
            ApplyModelFootprint(rec, list, param, rec->mFaceBoxes, true);
        }
    }
    n = (int)((char*)mRecEnd_784 - (char*)mRecBase_784) / 0xac;
    for (int i = 0; i < n; ++i) {
        if (list) {
            RefObj* old = list;
            list = 0;
            old->Release();
        }
        TerrainRec* rec = (TerrainRec*)((char*)mRecBase_784 + i * 0xac);
        if (mgr->v2c(rec->mField98, rec->mFieldA0, (void**)&list)) {
            ApplyModelFootprint(rec, list, param, rec->mFaceBoxes, true);
            rec->mFlags &= 0xf7ffffff;
        }
    }
    if (list)
        list->Release();
}

// @ 0x00fa6320
void cTerrainSphere::AddEntry8b0(RefObj* obj, void* param)
{
    RefObj* local = 0;
    if (obj) {
        obj->AddRef();
        local = obj;
    }
    Entry8 e = { local, param };
    ((Entry8Vec*)&mEntries8b0)->push_back(e);
    if (e.mObj)
        e.mObj->Release();
}

// @ 0x00fa63d0
void cTerrainSphere::AddEntry8c4(RefObj* obj, void* param)
{
    RefObj* local = 0;
    if (obj) {
        obj->AddRef();
        local = obj;
    }
    Entry8 e = { local, param };
    ((Entry8Vec*)&mEntries8c4)->push_back(e);
    if (e.mObj)
        e.mObj->Release();
}
// @ 0x00fa5610
void cTerrainSphere::UpdateQuadsPostCamera(void* camera)
{
    renderQuads.clear();
    faceRootArray.clear();
    atmoRootArray.clear();

    cDirectPropertyList* props = sAppProperties;
    flagA = props->GetDescription(0x563886c);
    bool markChildren = props->GetDescription(0x563886d);

    cFrustumCull cull((char*)camera + 0xc0);
    Property* prop;
    if (props && props->GetProperty(0x13d7382, &prop) && prop->type == 0xd) {
        float f = *prop->GetFloat();
        cull.SetNear(f);
    }

    for (int i = 0; i < 6; ++i) {
        QItem it = { faceRoots[i], 0 };
        g_QuadStack.push_back(it);
    }

    bool useDistCull = sAppProperties->GetDescription(0x541a775);
    float maxCamDist = sAppProperties->GetFloatProperty(0x62f89dc);
    float cullDist = sAppProperties->GetFloatProperty(0x63fe1bc);
    float facing = sAppProperties->GetFloatProperty(0x541ac31);
    float radiusScale = GetInfo()->radius;

    SPTransform xf;
    viewer->GetTransform(&xf);
    if (maxCamDist < sqrtf(xf.pos.z * xf.pos.z + (xf.pos.y * xf.pos.y + xf.pos.x * xf.pos.x)))
        useDistCull = false;

    while (g_QuadStack.mpBegin != g_QuadStack.mpEnd) {
        QItem item = g_QuadStack.mpEnd[-1];
        --g_QuadStack.mpEnd;
        cQuad* q = item.quad;
        bool test = true;
        if (useDistCull) {
            float vz = q->centre.z * radiusScale - xf.pos.z;
            float vx = q->centre.x * radiusScale - xf.pos.x;
            float vy = q->centre.y * radiusScale - xf.pos.y;
            if ((vx * vx + vz * vz) + vy * vy > cullDist * cullDist) {
                float nx = -vx, nz = -vz, ny = -vy;
                float inv = 1.0f / sqrtf((nx * nx + nz * nz + ny * ny) + 1e-08f);
                float dot = ((nz * inv) * q->centre.z + (ny * inv) * q->centre.y) + (inv * nx) * q->centre.x;
                if (facing > dot)
                    test = false;
            }
        }
        if (!test)
            continue;
        uint32_t fl = cull.FrustumTestSphere(&q->sphereCentre, &q->sphereRadius, item.flags);
        if (fl & 0x40)
            continue;
        float dist;
        if (!QuadDetailTest(q, decalState, &dist)) {
            if (q->children[0] == 0)
                q->Refine();
            if (q->children[0] != 0) {
                cQuad** pc = q->children;
                for (int i = 4; i; --i) {
                    QItem ci = { *pc, fl };
                    g_QuadStack.push_back(ci);
                    ++pc;
                }
            }
            if (q->children[0] != 0)
                continue;
        }
        float lod = q->lodKey;
        uint32_t bits;
        memcpy(&bits, &dist, 4);
        QContainer c = { q, lod, (uint32_t)((int)bits >> 31) ^ (bits | 0x80000000u), 0 };
        renderQuads.push_back(c);
        if (markChildren && q->children[0] != 0) {
            cQuad** pc = q->children;
            for (int i = 4; i; --i) {
                if ((*pc)->children[0] != 0)
                    (*pc)->MarkChild();
                ++pc;
            }
        }
    }
    SortQuads(renderQuads.mpBegin, renderQuads.mpEnd, false);

    for (int i = 0; i < 6; ++i) {
        QContainer a = { faceRoots[i], 1.0f, 0, 0 };
        faceRootArray.push_back(a);
        QContainer b = { atmoRoots[i], 1.0f, 0, 0 };
        atmoRootArray.push_back(b);
    }
}
