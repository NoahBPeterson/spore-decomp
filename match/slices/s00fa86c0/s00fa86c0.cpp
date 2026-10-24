// Slice s00fa86c0: SP::cTerrainSphere footprint/decal/deferred-update helpers.
//   00fa86c0  cTerrainSphere::CollectFootprintTextures  (thiscall, ret 4)
//   00fa9040  property transform extraction             (cdecl, 4 args)
//   00fa90e0  ResponseCurve copy assignment             (thiscall, ret 4)
//   00fa9140  cTerrainSphere::CreateDecal wrapper       (thiscall, ret 0x10)
//   00fa9170  cTerrainSphere::DoDeferredUpdate          (thiscall)
// Everything is driven through SP::PropertyManager, which hands out refcounted property values;
// a property value exposes its vftable at +0, a count at +8, flags at +0x10 and an id at +0x12.
#include "types.h"
#include <stddef.h>
#include <intrin.h>

#define CHK(cls, name, off) typedef char chk_##cls##_##name[(offsetof(cls, name) == (off)) ? 1 : -1]

struct cProperty;
struct cTerrainMapU32;
struct cTerrainLevelInfo;
struct cSPTransform;
struct cRelevelEntry;
struct cFootprintEntry;

struct Allocator { const char* mpName; };

// ---------------------------------------------------------------------------
// SP::cProperty (refcounted property value)
// ---------------------------------------------------------------------------
struct cProperty {
    virtual void v00() {}
    virtual void Release() {}                       // +0x04
    virtual void v08() {} virtual void v0c() {}
    virtual void v10() {} virtual void v14() {} virtual void v18() {} virtual void v1c() {}
    virtual void v20() {}
    virtual bool v24(void* context, cProperty** ioProperty);   // +0x24
    char pad04[4];
    int mCount;                                     // +0x08
    char pad0c[4];
    uint16_t mFlags;                                // +0x10
    uint16_t mId;                                   // +0x12
};
CHK(cProperty, mCount, 0x08);
CHK(cProperty, mFlags, 0x10);
CHK(cProperty, mId, 0x12);

// ---------------------------------------------------------------------------
// SP::PropertyManager
// ---------------------------------------------------------------------------
struct PropertyManager {
    virtual void v00() {} virtual void v04() {} virtual void v08() {} virtual void v0c() {}
    virtual void v10() {} virtual void v14() {} virtual void v18() {} virtual void v1c() {}
    virtual void v20() {} virtual void v24() {} virtual void v28() {}
    virtual bool GetProperty(int key1, int key2, cProperty** out);   // +0x2c
};

namespace SP { PropertyManager* PropertyManager(); }  // 0x0067de30

// ---------------------------------------------------------------------------
// eastl::vector<EA::AutoRefCount<SP::cTextureInstance>, sp_vector_allocator>
// ---------------------------------------------------------------------------
void** FUN_006f43e0(void** first, void** last, void** dest);   // 0x006f43e0 (copy dispatch)

struct TextureVec {
    void** mpBegin;         // +0x00
    void** mpEnd;           // +0x04
    void** mpCapacity;      // +0x08
    Allocator mAlloc;       // +0x0c
    void reserve(unsigned count);                // 0x004e0880
    void DestroyRange(void** first, void** last);  // 0x0070f520
    // erase(begin, end): move nothing, destroy the range, then drop it off the end
    void clear() {
        void** first = mpBegin;
        void** last = mpEnd;
        void** newEnd = FUN_006f43e0(last, mpEnd, first);
        DestroyRange(newEnd, mpEnd);
        mpEnd -= (last - first);
    }
};
CHK(TextureVec, mpBegin, 0x00);
CHK(TextureVec, mpEnd, 0x04);
CHK(TextureVec, mpCapacity, 0x08);

// Owns a cProperty and releases the previous value on assignment reset().
struct PropRef {
    cProperty* mpProperty;
    PropRef() : mpProperty(0) {}
    void reset() {
        cProperty* p = mpProperty;
        if (p) {
            mpProperty = 0;
            p->Release();
        }
    }
};

// ---------------------------------------------------------------------------
// 0xac-byte relevel records and 0xc-byte extra footprint records
// ---------------------------------------------------------------------------
struct cRelevelEntry {
    char pad00[0x98];
    int mPropertyKeyA;      // +0x98
    char pad9c[4];
    int mPropertyKeyB;      // +0xa0
    char padA4[8];
};
CHK(cRelevelEntry, mPropertyKeyA, 0x98);
CHK(cRelevelEntry, mPropertyKeyB, 0xa0);

struct cFootprintEntry {
    int mKey;               // +0x00
    int mUnused;            // +0x04
    int mKey2;              // +0x08
};
CHK(cFootprintEntry, mKey, 0x00);
CHK(cFootprintEntry, mKey2, 0x08);

// ---------------------------------------------------------------------------
// terrain config and the objects hanging off it
// ---------------------------------------------------------------------------
struct cTerrainLevelInfo {
    char pad00[8];
    int mCount;             // +0x08
};
struct cTerrainMapU32 {
    void BlendMapEdges();   // 0x00f8fe60
};
struct TerrainConfig {
    char pad00[8];
    cTerrainLevelInfo* mpLevel;   // +0x08
    cTerrainMapU32* mpMap;        // +0x0c
    char pad10[0x24];
    float mF34;                   // +0x34  cull radius bias
    float mF38;                   // +0x38  cell scale
};
CHK(TerrainConfig, mpLevel, 0x08);
CHK(TerrainConfig, mpMap, 0x0c);
CHK(TerrainConfig, mF34, 0x34);
CHK(TerrainConfig, mF38, 0x38);

struct cDecalManager {
    int CreateDecal(int a, int b, int c, float d);   // 0x00fa6a50
};

struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};

int FUN_00f8b2b0(cTerrainLevelInfo* level, cTerrainMapU32* map, int index,
                 float f34, float f38, float width,
                 float x0, float y0, float x1, float y1);          // 0x00f8b2b0

// ---------------------------------------------------------------------------
// 0x00fa8850 GenerateImpostorUpdate support: impostor jobs, property lists, textures
// ---------------------------------------------------------------------------
extern unsigned g_impostorParentGroup;                          // 0x015b11fc
extern char FUN_00f96d20;                                       // job callback
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void __cdecl operator_delete__(void* p);                        // 0x00f47380

struct RefObj {
    virtual void Destroy(int del);
    volatile long mnRefCount;                                   // +0x04
};
inline void RefAddRef(RefObj* o) { _InterlockedIncrement(&o->mnRefCount); }
inline void RefRelease(RefObj* o)
{
    if (_InterlockedDecrement(&o->mnRefCount) == 0) {
        _InterlockedExchange(&o->mnRefCount, 1);
        o->Destroy(1);
    }
}
template <class T> struct RCPtr {
    T* p;
    RCPtr(T* x) : p(x) { if (p) RefAddRef(p); }
    ~RCPtr() { if (p) RefRelease(p); }
};

struct cJob_s00fa_86c0 {
    void* fn;                       // +0x00
    unsigned arg;                   // +0x04
    char pad[0x10];
    int flag;                       // +0x18
    int Release();                  // 0x00690120
    void Queue();                   // 0x006909b0
};
struct JobRef {
    cJob_s00fa_86c0* p;
    JobRef() : p(0) {}
    ~JobRef() { if (p) p->Release(); }
    void Reset() { cJob_s00fa_86c0* t = p; if (t) { p = 0; t->Release(); } }
};
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
struct IPropList : IRef {
    void SetParent(IPropList* parent);                          // 0x006a1710
};
struct cPropertyList_s00fa_86c0 : IPropList {
    char pad[0x38 - 4];
    cPropertyList_s00fa_86c0(const char* name);                 // 0x006a1b90
};
struct PLRef {
    IPropList* p;
    PLRef() : p(0) {}
    ~PLRef() { if (p) p->Release(); }
    PLRef& operator=(IPropList* x);                             // 0x004535d0
    void Reset() { IPropList* t = p; if (t) { p = 0; t->Release(); } }
};
struct IMeshBuilder : IRef {
    virtual void s2(), s3(), s4(), s5(), s6(), s7(), s8(), s9(), s10(), s11();
    virtual void s12(), s13(), s14(), s15(), s16(), s17(), s18(), s19(), s20(), s21();
    virtual void s22(), s23(), s24(), s25(), s26(), s27(), s28(), s29(), s30(), s31();
    virtual void s32(), s33(), s34(), s35(), s36(), s37(), s38(), s39(), s40(), s41();
    virtual void s42();
    virtual RefObj* GetMesh();                                  // +0xac
};
struct BuilderRef {
    IMeshBuilder* p;
    BuilderRef(IMeshBuilder* x) : p(x) { if (p) p->AddRef(); }
    ~BuilderRef() { if (p) p->Release(); }
    BuilderRef& operator=(IMeshBuilder* x);                     // 0x00b5f950
};
IMeshBuilder* __cdecl NewMeshBuilder();                         // 0x00715de0
struct MeshHolder {
    RefObj* p;
    MeshHolder(RefObj* x) : p(x) { if (p) RefAddRef(p); }
    ~MeshHolder() { if (p) RefRelease(p); }
};
struct RefVec {
    MeshHolder* mpBegin;
    MeshHolder* mpEnd;
    MeshHolder* mpCapacity;
    unsigned    mAllocator;
    RefVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void PushBack(const MeshHolder& h);                          // 0x0041ef20
    void DestroyRange(MeshHolder* first, MeshHolder* last);      // 0x004243e0
    ~RefVec()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
struct cMITextureSet_s00fa_86c0 {
    char pad[0x70];
    cMITextureSet_s00fa_86c0();                                 // 0x0040d010
    void InsertResource(int slot, void* res);                    // 0x0077cb10
    void setSlotU0(int slot, int v);                             // 0x00777a60
    void setSlotU1(int slot, int v);                             // 0x00777a80
    void setSlotV0(int slot, int v);                             // 0x00777aa0
};
struct cMaterialInfo_s00fa_86c0 : RefObj {
    char pad[0x1c - 8];
    cMaterialInfo_s00fa_86c0();                                 // 0x0077d1d0
    void PushBack(cMITextureSet_s00fa_86c0* ts);                // 0x0077d970
};
struct LockInfo { void* data; int a, b, c, d, e, f; };
struct Tex {
    char pad[0x12];
    unsigned char level;                                        // +0x12
    int  Lock(int mode, int zero, LockInfo* out);               // 0x011ef750
    void Unlock(LockInfo* info);                                // 0x011ef880
};
struct TexObj { Tex* tex; unsigned flags; };
struct ResMgrA {
    virtual void r0(), r1(), r2(), r3(), r4(), r5(), r6(), r7(), r8(), r9(), r10(), r11(), r12();
    virtual void Load(TexObj* t);                               // +0x34
};
struct ResMgrB {
    virtual void u0(), u1(), u2(), u3(), u4(), u5(), u6(), u7(), u8(), u9(), u10(), u11();
    virtual void Update(unsigned a, unsigned b, void* data);    // +0x30
};
ResMgrA* __cdecl GetResMgrA();                                  // 0x0067dd60
ResMgrB* __cdecl GetResMgrB();                                  // 0x0067dda0
struct IScheduler {
    virtual void q0(), q1(), q2(), q3();
    virtual void AddJob(cJob_s00fa_86c0** out);                 // +0x10
};
IScheduler* __cdecl GetScheduler();                             // 0x0068f4d0
void* __cdecl GetSaveArea(unsigned id);                         // 0x006b1f90
bool __cdecl GetModelAsGameMeshes(cJob_s00fa_86c0** pJob, RefVec* vec, unsigned id3, unsigned id4,
                                  cMaterialInfo_s00fa_86c0* rc5, void* vec6, IPropList* list,
                                  void* a8, void* a9, void* saveArea, void* key,
                                  cJob_s00fa_86c0* chain);      // 0x007573a0
struct ImpostorState {
    void Reset();                                               // 0x00f99ff0
};
struct ResKey { unsigned instance, type, group; };
// PropertyManager's property-list slots (the +0x2c slot is looked up by index here so that the
// existing GetProperty declaration on the same class stays the one the other functions use).
typedef char (__thiscall* GetPropListFn)(PropertyManager*, unsigned, unsigned, IPropList**);
typedef void (__thiscall* SetPropListFn)(PropertyManager*, IPropList*, unsigned, unsigned);
static char GetPropList(PropertyManager* pm, unsigned id, unsigned group, IPropList** out)
{
    return ((GetPropListFn)(*(void***)pm)[0x2c / 4])(pm, id, group, out);
}
static void SetPropList(PropertyManager* pm, IPropList* pl, unsigned id, unsigned group)
{
    ((SetPropListFn)(*(void***)pm)[0x34 / 4])(pm, pl, id, group);
}

// ---------------------------------------------------------------------------
// SP::cTerrainSphere (only the fields touched by this slice)
// ---------------------------------------------------------------------------
struct cTerrainSphere {
    virtual void v00() {} virtual void v04() {} virtual void v08() {} virtual void v0c() {}
    virtual void v10() {} virtual void v14() {} virtual void v18() {} virtual void v1c() {}
    virtual void v20() {} virtual void v24() {} virtual void v28() {} virtual void v2c() {}
    virtual void v30() {} virtual void v34() {} virtual void v38() {} virtual void v3c() {}
    virtual void v40() {} virtual void v44() {} virtual void v48() {}
    virtual bool v4c(int level);                    // +0x4c
    char pad04[4];
    cDecalManager* mDecalManager;                   // +0x08
    char pad0c[0x0c];                               // +0x0c
    unsigned keyInstance;                           // +0x18
    unsigned keyType;                               // +0x1c
    unsigned keyGroup;                              // +0x20
    char pad24[8];                                  // +0x24
    TerrainConfig* mConfig;                         // +0x2c
    char pad30[0x740];
    cRelevelEntry* mpRelevelBegin;                  // +0x770
    cRelevelEntry* mpRelevelEnd;                    // +0x774
    char pad778[0x34];
    int mExtraCount;                                // +0x7ac
    cFootprintEntry* mpExtra;                       // +0x7b0
    char pad7b4[0x6c];
    float mRects[6][4];                             // +0x820
    char pad880[4];                                 // +0x880
    TexObj* faceTex[3];                             // +0x884
    void* res3;                                     // +0x890
    cJob_s00fa_86c0* mJob;                          // +0x894
    unsigned f898;                                  // +0x898
    unsigned f89c;                                  // +0x89c
    ImpostorState* mImpostorState;                  // +0x8a0
    unsigned f8a4;                                  // +0x8a4
    unsigned f8a8;                                  // +0x8a8

    void RequestModelFootprint(cProperty* property, TextureVec& out);  // 0x00fa5ee0
    void BuildTerrain(const uint8_t* data);                            // 0x00fa75f0
    void CollectFootprintTextures(TextureVec& out);                    // 0x00fa86c0
    void GenerateImpostorUpdate(int a, int b);                         // 0x00fa8850
    int  CreateDecal(int a, int b, int c, float d);                    // 0x00fa9140
    void DoDeferredUpdate();                                           // 0x00fa9170
    void BuildImpostorMesh(IMeshBuilder* b, const wchar_t* name, float scale, int flag);  // 0x00f9a040
    void PostImpostorStep(int a, int b);                                                  // 0x00fa0560
};
CHK(cTerrainSphere, mDecalManager, 0x08);
CHK(cTerrainSphere, mConfig, 0x2c);
CHK(cTerrainSphere, mpRelevelBegin, 0x770);
CHK(cTerrainSphere, mpRelevelEnd, 0x774);
CHK(cTerrainSphere, mExtraCount, 0x7ac);
CHK(cTerrainSphere, mpExtra, 0x7b0);
CHK(cTerrainSphere, mRects, 0x820);

// ---------------------------------------------------------------------------
// 0x38-byte transform records
// ---------------------------------------------------------------------------
struct cSPTransform { char mData[0x38]; };

cSPTransform* FUN_00f339d0(const cSPTransform* first, const cSPTransform* last,
                           cSPTransform* dest);                  // 0x00f339d0

struct TransformVec {
    cSPTransform* mpBegin;      // +0x00
    cSPTransform* mpEnd;        // +0x04
    cSPTransform* mpCapacity;   // +0x08
    Allocator mAlloc;           // +0x0c
    void resize(unsigned count);   // 0x0041e3b0
};
CHK(TransformVec, mpBegin, 0x00);
CHK(TransformVec, mpEnd, 0x04);
CHK(TransformVec, mpCapacity, 0x08);

// ---------------------------------------------------------------------------
// 0x14-byte response curve data records
// ---------------------------------------------------------------------------
struct Rec20 { char mData[0x14]; };

Rec20* FUN_00951bf0(const Rec20* first, const Rec20* last, Rec20* dest);  // 0x00951bf0

struct ResponseCurve {
    Rec20* mpBegin;         // +0x00
    Rec20* mpEnd;           // +0x04
    Rec20* mpCapacity;      // +0x08
    Allocator mAlloc;       // +0x0c
    void DoAssign(const Rec20* first, const Rec20* last, const void* owner);  // 0x00fa26e0
    ResponseCurve& Assign(const ResponseCurve& other);                        // 0x00fa90e0
};
CHK(ResponseCurve, mpBegin, 0x00);
CHK(ResponseCurve, mpEnd, 0x04);
CHK(ResponseCurve, mpCapacity, 0x08);

// ===========================================================================
// 0x00fa86c0
// ===========================================================================
// @ 0x00fa86c0
void cTerrainSphere::CollectFootprintTextures(TextureVec& out)
{
    PropertyManager* pm = SP::PropertyManager();
    int total = (int)(mpRelevelEnd - mpRelevelBegin) + mExtraCount;
    PropRef prop;
    out.clear();
    out.reserve(total * 3);

    for (int i = 0; i < mExtraCount; ++i) {
        prop.reset();
        cFootprintEntry* entry = mpExtra + i;
        if (pm->GetProperty(entry->mKey, entry->mKey2, &prop.mpProperty))
            RequestModelFootprint(prop.mpProperty, out);
    }

    int numRelevel = (int)(mpRelevelEnd - mpRelevelBegin);
    for (int i = 0; i < numRelevel; ++i) {
        prop.reset();
        cRelevelEntry* record = mpRelevelBegin + i;
        if (pm->GetProperty(record->mPropertyKeyA, record->mPropertyKeyB, &prop.mpProperty))
            RequestModelFootprint(prop.mpProperty, out);
    }

    if (prop.mpProperty)
        prop.mpProperty->Release();
}

// ===========================================================================
// 0x00fa9040
// ===========================================================================
// @ 0x00fa9040
bool GetPropertyTransforms(cProperty* property, void* context, uint16_t id, TransformVec& out)
{
    if (property != 0 && property->v24(context, &property) &&
        property->mId == id && (property->mFlags & 0x10) != 0) {
        uint16_t kind = property->mFlags & 0x30;
        int count;
        const cSPTransform* src;
        if (kind != 0) {
            count = property->mCount;
            src = (const cSPTransform*)*(void**)property;   // the value's leading dword
        } else {
            count = (property->mId != 0);
            src = (property->mId != 0) ? (const cSPTransform*)property : 0;
        }
        out.resize(count);
        FUN_00f339d0(src, src + count, out.mpBegin);
        return true;
    }
    return false;
}

// ===========================================================================
// 0x00fa90e0
// ===========================================================================
// @ 0x00fa90e0
ResponseCurve& ResponseCurve::Assign(const ResponseCurve& other)
{
    if (this != &other) {
        Rec20* first = mpBegin;
        Rec20* last = mpEnd;
        FUN_00951bf0(last, mpEnd, first);
        mpEnd -= (last - first);
        DoAssign(other.mpBegin, other.mpEnd, &other);
    }
    return *this;
}

// ===========================================================================
// 0x00fa9140
// ===========================================================================
// @ 0x00fa9140
int cTerrainSphere::CreateDecal(int a, int b, int c, float d)
{
    if (mDecalManager)
        return mDecalManager->CreateDecal(a, b, c, d);
    return 0;
}

// ===========================================================================
// 0x00fa9170
// ===========================================================================
// @ 0x00fa9170
void cTerrainSphere::DoDeferredUpdate()
{
    if (!v4c(1))
        return;

    static Vector4 sUnitRect(0.0f, 0.0f, 1.0f, 1.0f);

    TerrainConfig* config = mConfig;
    float f34 = config->mF34;
    cTerrainMapU32* map = config->mpMap;
    cTerrainLevelInfo* level = config->mpLevel;
    float f38 = config->mF38;

    bool anyVisible = false;
    for (int i = 0; i < 6; ++i) {
        if (mRects[i][0] != mRects[i][2] && mRects[i][1] != mRects[i][3] &&
            sUnitRect.x < mRects[i][2] && mRects[i][0] < sUnitRect.z &&
            sUnitRect.y < mRects[i][3] && mRects[i][1] < sUnitRect.w) {
            anyVisible = true;
            float width = (float)(unsigned)level->mCount * 0.0009765625f * 50.0f;
            FUN_00f8b2b0(level, map, i, f34, f38, width,
                         mRects[i][0], mRects[i][1], mRects[i][2], mRects[i][3]);
        }
    }
    if (anyVisible)
        map->BlendMapEdges();

    BuildTerrain((const uint8_t*)&mRects[0][0]);
}

// ===========================================================================
// 0x00fa8850  impostor pass/face stepping, then the planet impostor and
// planet-atmosphere impostor mesh jobs (property lists + texture sets)
// ===========================================================================
// @ 0x00fa8850
void cTerrainSphere::GenerateImpostorUpdate(int a, int b)
{
    mImpostorState->Reset();
    if (b < 3)
    {
        int levels[6] = {3, 2, 0, 1, 4, 5};
        Tex* tex = 0;
        if (b == 0 || b == 1 || b == 2)
        {
            TexObj* h = faceTex[b];
            if (!(h->flags & 1))
                GetResMgrA()->Load(h);
            tex = h->tex;
        }
        tex->level = (unsigned char)levels[a];
        LockInfo info;
        if (!tex->Lock(2, 0, &info))
            return;
        GetResMgrB()->Update(f898, f89c, info.data);
        tex->Unlock(&info);
    }
    if (a < 5)
    {
        PostImpostorStep(a + 1, b);
        return;
    }
    if (b < 2)
    {
        PostImpostorStep(0, b + 1);
        return;
    }
    if (a == 5 && b == 2)
    {
        PostImpostorStep(6, 3);
        return;
    }

    PropertyManager* pm = SP::PropertyManager();
    BuilderRef builder(NewMeshBuilder());
    BuildImpostorMesh(builder.p, L"planetImpostor", 1.0f, 1);

    ResKey keyA;
    keyA.instance = keyInstance;
    keyA.type = keyType;
    keyA.group = keyGroup;
    ResKey keyB = keyA;
    keyA.type = 0xe6bce5;
    keyB.type = 0xe6bce5;
    unsigned groupB = (keyGroup & 0xe0ff28ff) | 0x2800;
    keyA.group = (keyA.group & 0xe7ff28ff) | 0x7002800;

    cMITextureSet_s00fa_86c0* ts = new ("Terrain/Sphere/cMITextureSet", 0, 0, 0, 0) cMITextureSet_s00fa_86c0();
    ts->InsertResource(0, faceTex[0]);
    ts->setSlotU0(0, 3);
    ts->setSlotU1(0, 2);
    ts->setSlotV0(0, 2);
    ts->InsertResource(1, faceTex[1]);
    ts->setSlotU0(1, 3);
    ts->setSlotU1(1, 2);
    ts->setSlotV0(1, 2);
    ts->InsertResource(2, faceTex[2]);
    ts->setSlotU0(2, 3);
    ts->setSlotU1(2, 2);
    ts->setSlotV0(2, 2);
    ts->InsertResource(3, res3);
    ts->setSlotU0(3, 3);
    ts->setSlotU1(3, 2);
    ts->setSlotV0(3, 2);

    RCPtr<cMaterialInfo_s00fa_86c0> mi(new ("Terrain/Sphere/cMaterialInfo", 0, 0, 0, 0) cMaterialInfo_s00fa_86c0());
    mi.p->PushBack(ts);

    IScheduler* sched = GetScheduler();
    cJob_s00fa_86c0** pMyJob = &mJob;
    if (mJob)
    {
        cJob_s00fa_86c0* old = mJob;
        *pMyJob = 0;
        old->Release();
    }
    sched->AddJob(pMyJob);
    (*pMyJob)->arg = f8a8;
    (*pMyJob)->fn = &FUN_00f96d20;
    (*pMyJob)->flag = 1;

    PLRef pl2;
    PLRef pl1;
    if (!GetPropList(pm, keyB.instance, groupB, &pl1.p))
    {
        pl1 = new ("Terrain/PlanetImpostor/ImpostorPropertyList", 0, 0, 0, 0) cPropertyList_s00fa_86c0("PlanetImpostor");
        pl2.Reset();
        if (GetPropList(pm, 0x752f1cd8, g_impostorParentGroup, &pl2.p))
            pl1.p->SetParent(pl2.p);
        SetPropList(pm, pl1.p, keyB.instance, groupB);
    }

    JobRef job;
    RefVec v;
    {
        MeshHolder tmp(builder.p->GetMesh());
        v.PushBack(tmp);
    }
    cJob_s00fa_86c0* chain = *pMyJob;
    IPropList* listArg = pl1.p;
    job.Reset();
    GetModelAsGameMeshes(&job.p, &v, keyB.instance, groupB, mi.p, 0, listArg, 0, 0, GetSaveArea(0x11ac1ac), 0, chain);

    builder = NewMeshBuilder();
    BuildImpostorMesh(builder.p, L"planetAtmoImpostor", 1.2f, 0);

    PLRef pl3;
    if (!GetPropList(pm, keyA.instance, keyA.group, &pl3.p))
    {
        pl3 = new ("Terrain/PlanetImpostor/ImpostorPropertyList", 0, 0, 0, 0) cPropertyList_s00fa_86c0("PlanetImpostorAtmosphere");
        pl3.p->SetParent(pl2.p);
        SetPropList(pm, pl3.p, keyA.instance, keyA.group);
    }

    cMITextureSet_s00fa_86c0* ts2 = new ("Terrain/Sphere/cMITextureSet", 0, 0, 0, 0) cMITextureSet_s00fa_86c0();
    ts2->InsertResource(0, res3);
    ts2->setSlotU0(0, 3);
    ts2->setSlotU1(0, 2);
    ts2->setSlotV0(0, 2);

    RCPtr<cMaterialInfo_s00fa_86c0> mi2(new ("Terrain/Sphere/cMaterialInfo", 0, 0, 0, 0) cMaterialInfo_s00fa_86c0());
    mi2.p->PushBack(ts2);

    JobRef job2;
    RefVec v2;
    {
        MeshHolder tmp(builder.p->GetMesh());
        v2.PushBack(tmp);
    }
    cJob_s00fa_86c0* chain2 = *pMyJob;
    IPropList* listArg2 = pl3.p;
    job2.Reset();
    GetModelAsGameMeshes(&job2.p, &v2, keyA.instance, keyA.group, mi2.p, 0, listArg2, 0, 0, GetSaveArea(0x11ac1ac), 0, chain2);

    if (job.p && job2.p)
    {
        job.p->Queue();
        job2.p->Queue();
        (*pMyJob)->Queue();
    }
}
