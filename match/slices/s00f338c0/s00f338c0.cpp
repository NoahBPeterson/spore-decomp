// Slice s00f338c0 -- Simulator terrain-sphere object and its transform helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// 0x00f338c0 fills a run of cSPTransform elements from a single source value
// (the fixed-capacity insert path of vecT38).  The remaining functions are the
// property-list plumbing, constructor/destructor and terrain-state members of
// SP::cTerrainSphere (see symbols/slices/s00f338c0.txt).
#include "types.h"
#include <new>
#include <string.h>

// ---------------------------------------------------------------- basic types
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

// ---------------------------------------------------------------- smart-pointer element (0x10)
struct RCObj { virtual void AddRef(); virtual void Release(); };
struct SmartPtr {
    void* p;
    SmartPtr& operator=(const SmartPtr& o) {
        if (p != o.p) {
            if (o.p) ((RCObj*)o.p)->AddRef();
            void* old = p;
            p = o.p;
            if (old) ((RCObj*)old)->Release();
        }
        return *this;
    }
};
struct E { SmartPtr sp; int a; int b; float c; };

// @ 0x00F33A10
E* CopyFwd(E* first, E* last, E* dest) { for (; first != last; ++first, ++dest) *dest = *first; return dest; }
// @ 0x00F33AC0
E* CopyBwd(E* first, E* last, E* dest) { while (first != last) { --last; --dest; *dest = *last; } return dest; }

// ---------------------------------------------------------------- EA allocation
void* EAAllocate(uint32_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void  EAFree(void* p);                                                          // 0x00f47380

// eastl vector storage header (20 bytes).  The last four bytes are the inline
// allocator and are deliberately not initialised by the constructors.
struct Vec20 {
    void* mpBegin;                 // +0x00
    void* mpEnd;                   // +0x04
    void* mpCapacity;              // +0x08
    uint32_t mAllocator[2];        // +0x0c
    void DestroyRange(void* first, void* last);   // 0x006a4950
};

inline void FreeVectorBuffer(void* p)
{
    if (p && ((int*)p)[-1] != 0)
        EAFree(p);
}

// ---------------------------------------------------------------- property list
struct Property {
    uint32_t mData[4];             // +0x00
    uint16_t mnFlags;              // +0x10
    uint16_t mnType;               // +0x12
    uint32_t* GetUInt();           // 0x0041ea00
};

struct cPropertyList {
    virtual void AddRef();                                        // +0x00
    virtual void Release();                                       // +0x04
    virtual void v08();                                           // +0x08
    virtual void v0c();                                           // +0x0c
    virtual void v10();                                           // +0x10
    virtual void SetProperty(uint32_t id, void* value);           // +0x14
    virtual void Remove(uint32_t id);                             // +0x18
    virtual bool HasProperty(uint32_t id);                        // +0x1c
    virtual void v20();                                           // +0x20
    virtual bool GetProperty(uint32_t id, Property** out);        // +0x24
    virtual void v28();                                           // +0x28
    virtual void AttachParent(cPropertyList* parent);             // +0x2c
    char mPad[0x2c];
    cPropertyList* mpParent;                                      // +0x30
    cPropertyList();                                              // 0x006a1c40
    void SetParent(cPropertyList* parent);                        // 0x006a1710
};

// Retail spelling of the property-list parameter type used by PObj.
struct CPL : cPropertyList {};

struct Res;
struct cTerrainSphere;

// Secondary base subobject (retail vtable 0x13ec458).
struct ContentValidationSummarizer {
    virtual void v0();
    virtual void v4();
};

// The 0x40-byte validation reporter installed as the current capture object.
struct ReporterBase {
    virtual void AddRef();                                        // +0x00
    virtual void Release();                                       // +0x04
    virtual void v08();                                           // +0x08
    virtual Res* GetRes(uint32_t id);                             // +0x0c
    virtual void v10();                                           // +0x10
};
struct Reporter : ReporterBase, ContentValidationSummarizer {
    uint32_t m08;                  // +0x08
    cPropertyList* mpProps;        // +0x0c
    Vec20 mV10;                    // +0x10
    uint32_t m24;                  // +0x24
    uint32_t m28;                  // +0x28
    uint32_t m2c;                  // +0x2c
    uint32_t m30;                  // +0x30
    uint32_t m34;                  // +0x34
    uint32_t m38;                  // +0x38
    cTerrainSphere* mpOwner;       // +0x3c
    Reporter(cTerrainSphere* owner, cPropertyList* props);        // inlined in 0x00f33bf0
};

// Terrain resource returned by Reporter::GetRes().
struct Res {
    virtual void AddRef();                                        // +0x00
    virtual void Release();                                       // +0x04
    virtual void v08();                                           // +0x08
    virtual void v0c();                                           // +0x0c
    char mPad[0x20];
    cPropertyList* mpProps;        // +0x24
    Vec20 mV28;                    // +0x28
};

// Global reporter list rooted at 0x016065d8.
struct ReporterList {
    Reporter** mpBegin;            // +0x00
    Reporter** mpEnd;              // +0x04
    Reporter** mpCapacity;         // +0x08
    uint32_t mAllocator[2];        // +0x0c
    uint32_t mCount;               // +0x14
    uint32_t mSerial;              // +0x18
    uint32_t mLimit;               // +0x1c
    bool mEnabled;                 // +0x20
    void Add(Reporter* item);                                     // 0x00f342d0
    void erase(Reporter** first, Reporter** last);                // 0x00e25bd0
    void DoInsertPtr(Reporter** pos, Reporter** value);           // 0x00aea5d0
};

void __cdecl CopyReporterPtrs(Reporter** first, Reporter** last, Reporter** dest);   // 0x006782c0

struct Registrar {
    void RegisterVector(Vec20* vector);                           // 0x00f41180
};
struct App {
    char mPad[0x74];
    Registrar* mpRegistrar;        // +0x74
};

extern ReporterList g_repList;     // 0x016065d8
extern Reporter* g_current;        // 0x016065fc
extern App* g_app;                 // 0x016c7aa4

// ---------------------------------------------------------------- transform fill
// 0x38-byte element (cSPTransform): flags/modcount, translation, uniform scale,
// then the 3x3 rotation.
struct cSPTransform {
    uint16_t mFlags;               // +0x00
    uint16_t mModCount;            // +0x02
    float mTranslation[3];         // +0x04
    float mScale;                  // +0x10
    float mRotation[9];            // +0x14
};

// @ 0x00f338c0
void FillTransforms(cSPTransform* dest, uint32_t count, const cSPTransform* value)
{
    if (count != 0) {
        do {
            if (dest) {
                dest->mFlags = value->mFlags;
                dest->mModCount = value->mModCount;
                dest->mTranslation[0] = value->mTranslation[0];
                dest->mTranslation[1] = value->mTranslation[1];
                dest->mTranslation[2] = value->mTranslation[2];
                dest->mScale = value->mScale;
                dest->mRotation[0] = value->mRotation[0];
                dest->mRotation[1] = value->mRotation[1];
                dest->mRotation[2] = value->mRotation[2];
                dest->mRotation[3] = value->mRotation[3];
                dest->mRotation[4] = value->mRotation[4];
                dest->mRotation[5] = value->mRotation[5];
                dest->mRotation[6] = value->mRotation[6];
                dest->mRotation[7] = value->mRotation[7];
                dest->mRotation[8] = value->mRotation[8];
            }
            --count;
            ++dest;
        } while (count != 0);
    }
}

// ---------------------------------------------------------------- property-list object
struct PObj {
    char pad0[0xc];
    cPropertyList* mC;             // +0x00c
    char pad10[0xf4-0x10];
    int mF4;                       // +0x0f4
    int mF8;                       // +0x0f8
    int mFC;                       // +0x0fc
    void setF4(int* p);
    void resetParent(CPL* p);
    void v323c0();
    void v32cb0();
    void v32d10();
};

// @ 0x00F33B50
void PObj::setF4(int* p)
{
    if (mF4 != p[0] || mF8 != p[1] || mFC != p[2]) {
        mF4 = p[0]; mF8 = p[1]; mFC = p[2];
        v323c0();
        v32cb0();
    }
}

// @ 0x00F33BB0
void PObj::resetParent(CPL* p)
{
    v32d10();
    if (p != mC) {
        p->AttachParent(mC);
        p->SetParent(mC->mpParent);
    }
}

// ---------------------------------------------------------------- terrain manager / vectors
struct FloatVector {
    float* mpBegin;                // +0x00
    float* mpEnd;                  // +0x04
    float* mpCapacity;             // +0x08
    uint32_t mAllocator[2];        // +0x0c
    void operator=(const FloatVector& src);            // 0x0050d4e0
    void Resize(int count, uint32_t* alloc);           // 0x004aa350
};
struct Vector3Vector {
    Vector3* mpBegin;              // +0x00
    Vector3* mpEnd;                // +0x04
    Vector3* mpCapacity;           // +0x08
    uint32_t mAllocator[2];        // +0x0c
    Vector3Vector() {}                                 // trivial
    Vector3Vector(const Vector3Vector& src);           // 0x00473460
    void operator=(const Vector3Vector& src);          // 0x00473500
};

struct cTerrainStateMgr {
    void Refresh();                                            // 0x00fbee30
    Vector3* GetStop2(Vector3* out, char flag);                // 0x00fb92c0
    Vector3* GetStop3(Vector3* out, char flag);                // 0x00fb9310
    Vector3* GetStop0(Vector3* out, char flag);                // 0x00fb9360
    Vector3* GetStop1(Vector3* out, char flag);                // 0x00fb93b0
    Vector3Vector* BuildPoints(Vector3Vector* out, char build);    // 0x00fbf430
    FloatVector* BuildValues(FloatVector* out);                // 0x00fbf3d0
    void ApplyVectors(FloatVector values, Vector3Vector points);   // 0x00fbf1c0 (ret 0x28)
};

// ---------------------------------------------------------------- terrain placement args
struct Terrain {
    char mPad[0x60];
    float m60;                     // +0x60
    float m64;                     // +0x64
};
struct TerrainDesc {
    uint32_t m00;                  // +0x00
    Vector3 m04;                   // +0x04
    float m10;                     // +0x10
    float mMatrix[9];              // +0x14
};
struct IWorldObj {
    virtual void AddRef();                                         // +0x00
    virtual void Release();                                        // +0x04
    virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void SetPosition(const Vector3* pos);                  // +0x38
    virtual void SetRotation(const Quaternion* rot);               // +0x3c
    virtual void SetScale(float scale);                            // +0x40
};

// 0x10-byte refcounted placement value.
struct V4 {
    RCObj* mpObj;                  // +0x00
    Terrain* mpTerrain;            // +0x04
    uint32_t mTag;                 // +0x08
    float mScale;                  // +0x0c
    V4* Assign(const V4* src);     // 0x00f00b00
};

// 0x14-byte EA::Variant (4 data words, flags, type).
struct Variant {
    uint32_t mData[4];             // +0x00
    uint16_t mnFlags;              // +0x10
    uint16_t mnType;               // +0x12
};
struct VariantKey { uint32_t mInstance, mType, mGroup; };

bool __cdecl WrapVariant(Variant* out, uint16_t type, uint16_t subType,
                         const void* data, uint32_t size, uint32_t count);   // 0x0093dd80
void __cdecl DestroyVariant(Variant* v, int freeMemory);                     // 0x0093db80
bool __cdecl GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3* out);   // 0x006a1110
void __cdecl SetPropertyVector3(cPropertyList* list, uint32_t id, int copy, const Vector3* v); // 0x006a0e50
void* __cdecl GetScriptManager();                                            // 0x00f48a80

struct cTerrainResourceManager {
    void ApplyScriptSets(uint32_t scriptId, cPropertyList* props);           // 0x00f93dd0
};

// ---------------------------------------------------------------- terrain helpers
void* __cdecl FindTerrain(int key);                                          // 0x00ecc100
float* __cdecl SurfaceDirection(float* out, float* dir, int a3, int* flag, int a5);   // 0x00eec2b0
void* __cdecl ToWorldObject(void* obj);                                      // 0x00b18e00
Quaternion* __cdecl QuaternionFromMatrix33(Quaternion* out, const float* matrix, float w);   // 0x00472b80

// ---------------------------------------------------------------- the terrain sphere
class PaintSystemBase {
public:
    virtual void v0();
    virtual void v4();
};

struct IRefcounted {
    virtual void AddRef();
    virtual void Release();
};

// Custom refcounted object at +0x10: refcount sits at +0x04.
struct CustomRef {
    virtual void Destroy(int release);
    int mRefCount;                 // +0x04
};

void RemoveMessageHandler(void* handler, void* a, void* b, void* c, void* d);   // 0x00571db0
class cTerrainSphere : public PaintSystemBase, public ContentValidationSummarizer {
public:
    uint32_t m08;                  // +0x08
    cPropertyList* mpProps;        // +0x0c
    void* mp10;                    // +0x10  custom refcounted object
    Vec20 mV14;                    // +0x14
    Vec20 mV28;                    // +0x28
    Vec20 mV3c;                    // +0x3c
    Vec20 mV50;                    // +0x50
    Vec20 mV64;                    // +0x64
    Vec20 mV78;                    // +0x78
    Vec20 mV8c;                    // +0x8c
    Vec20 mVa0;                    // +0xa0
    Vec20 mVb4;                    // +0xb4
    char mC8[0x18];                // +0xc8
    Vector3 mE0;                   // +0xe0
    char mEC[8];                   // +0xec
    uint32_t mF4;                  // +0xf4
    uint32_t mF8;                  // +0xf8
    uint32_t mFC;                  // +0xfc
    void* mp100;                   // +0x100  refcounted
    uint8_t m104;                  // +0x104
    uint8_t mPad105[3];
    Vector3Vector mV108;           // +0x108
    FloatVector mV11c;             // +0x11c
    Vector3 m130;                  // +0x130
    Vector3 m13c;                  // +0x13c
    Vector3 m148;                  // +0x148
    Vector3 m154;                  // +0x154
    uint32_t m160;                 // +0x160
    Vec20 mV164;                   // +0x164
    uint32_t m178;                 // +0x178  message handler token
    uint32_t m17c;                 // +0x17c
    uint32_t m180;                 // +0x180
    uint32_t m184;                 // +0x184
    uint32_t m188;                 // +0x188
    uint8_t m18c;                  // +0x18c
    uint8_t m18d;                  // +0x18d
    uint16_t mPad18e;
    void* mp190;                   // +0x190
    cTerrainStateMgr* mp194;       // +0x194
    Registrar* mp198;              // +0x198
    Vec20 mV19c;                   // +0x19c
    void* mp1b0;                   // +0x1b0
    uint32_t m1b4;                 // +0x1b4
    uint8_t m1b8;                  // +0x1b8
    char mPad1b9[3];

    cTerrainSphere();              // 0x00f33f90
    ~cTerrainSphere();             // 0x00f340e0

    void ResetCurrent();                                          // 0x00f33bf0
    bool AddTerrainPlacement(V4* out, int key, TerrainDesc* desc,
                             uint32_t tag, IWorldObj* owner);     // 0x00f33d70
    void UpdateTerrainState(char build);                          // 0x00f343a0
    void SetTerrainVectors(FloatVector* values, Vector3Vector* points);  // 0x00f344e0
    void PublishWorld();                                          // 0x00f34560
    void SetPlayerColorIDs();                                     // 0x00f34660

    void PublishProperties();                                     // 0x00f32d10
    IWorldObj* GetObjectForTerrain(Terrain* terrain);             // 0x00f33640
};

// @ 0x00f342d0
void ReporterList::Add(Reporter* item)
{
    if (!mEnabled)
        return;

    if (mCount < mLimit) {
        if (mCount < (uint32_t)(mpEnd - mpBegin))
            erase(mpBegin + mCount, mpEnd);
    } else {
        if (mpBegin + 1 < mpEnd)
            CopyReporterPtrs(mpBegin + 1, mpEnd, mpBegin);
        --mpEnd;
        if (*mpEnd)
            (*mpEnd)->Release();
        --mCount;
    }

    if (item)
        item->AddRef();

    if (mpEnd < mpCapacity) {
        Reporter** slot = mpEnd;
        ++mpEnd;
        if (slot) {
            *slot = item;
            if (item)
                item->AddRef();
        }
    } else {
        Reporter* tmp = item;
        DoInsertPtr(mpEnd, &tmp);
    }

    if (item)
        item->Release();
    ++mCount;
    ++mSerial;
}

// ---------------------------------------------------------------- Reporter
inline Reporter::Reporter(cTerrainSphere* owner, cPropertyList* props)
    : m08(0), mpProps(props), m24(0), m28(0), m2c(0), m30(0), mpOwner(owner)
{
    mV10.mpBegin = 0;
    mV10.mpEnd = 0;
    mV10.mpCapacity = 0;
    if (mpProps)
        mpProps->AddRef();
}

// @ 0x00f33f90
cTerrainSphere::cTerrainSphere()
{
    m08 = 0;
    mpProps = 0;
    mp10 = 0;
    mV14.mpBegin = 0; mV14.mpEnd = 0; mV14.mpCapacity = 0;
    mV28.mpBegin = 0; mV28.mpEnd = 0; mV28.mpCapacity = 0;
    mV3c.mpBegin = 0; mV3c.mpEnd = 0; mV3c.mpCapacity = 0;
    mV50.mpBegin = 0; mV50.mpEnd = 0; mV50.mpCapacity = 0;
    mV64.mpBegin = 0; mV64.mpEnd = 0; mV64.mpCapacity = 0;
    mV78.mpBegin = 0; mV78.mpEnd = 0; mV78.mpCapacity = 0;
    mV8c.mpBegin = 0; mV8c.mpEnd = 0; mV8c.mpCapacity = 0;
    mVa0.mpBegin = 0; mVa0.mpEnd = 0; mVa0.mpCapacity = 0;
    mVb4.mpBegin = 0; mVb4.mpEnd = 0; mVb4.mpCapacity = 0;
    mF4 = 0;
    mF8 = 0;
    mFC = 0;
    mp100 = 0;
    m104 = 1;
    mV108.mpBegin = 0; mV108.mpEnd = 0; mV108.mpCapacity = 0;
    mV11c.mpBegin = 0; mV11c.mpEnd = 0; mV11c.mpCapacity = 0;
    mV164.mpBegin = 0; mV164.mpEnd = 0; mV164.mpCapacity = 0;
    m178 = 0;
    m17c = 0;
    m180 = 0;
    m184 = 0;
    m188 = 0;
    m18d = 1;
    mp190 = 0;
    mp194 = 0;
    mp198 = 0;
    mV19c.mpBegin = 0; mV19c.mpEnd = 0; mV19c.mpCapacity = 0;
    mp1b0 = 0;
    m1b8 = 0;
}

// @ 0x00f340e0
cTerrainSphere::~cTerrainSphere()
{
    // Destroy the V4 vector's elements before releasing its storage.
    mV19c.DestroyRange(mV19c.mpBegin, mV19c.mpEnd);

    if (m178) {
        void* handler = (void*)m178;
        m178 = 0;
        RemoveMessageHandler(handler, (void*)m17c, (void*)m180, (void*)m184, (void*)m188);
    }

    FreeVectorBuffer(mV164.mpBegin);
    FreeVectorBuffer(mV11c.mpBegin);
    FreeVectorBuffer(mV108.mpBegin);
    if (mp100) {
        IRefcounted* p = (IRefcounted*)mp100;
        p->Release();
    }
    FreeVectorBuffer(mVb4.mpBegin);
    FreeVectorBuffer(mVa0.mpBegin);
    FreeVectorBuffer(mV8c.mpBegin);
    mV78.DestroyRange(mV78.mpBegin, mV78.mpEnd);
    FreeVectorBuffer(mV78.mpBegin);
    FreeVectorBuffer(mV64.mpBegin);
    FreeVectorBuffer(mV50.mpBegin);
    FreeVectorBuffer(mV3c.mpBegin);
    FreeVectorBuffer(mV28.mpBegin);
    FreeVectorBuffer(mV14.mpBegin);

    if (mp10) {
        CustomRef* p = (CustomRef*)mp10;
        if (--p->mRefCount == 0) {
            p->mRefCount = 1;
            p->Destroy(1);
        }
    }
    if (mpProps)
        mpProps->Release();
}

// @ 0x00f33bf0
void cTerrainSphere::ResetCurrent()
{
    cPropertyList* props = 0;

    if (g_repList.mEnabled && g_repList.mCount != 0) {
        Reporter* reporter = g_repList.mpBegin[g_repList.mCount - 1];
        Res* res = reporter->GetRes(0x73e4f04);
        if (res) {
            props = res->mpProps;
            if (props)
                props->AddRef();
            goto have_list;
        }
    }

    {
        void* mem = EAAllocate(0x38, "Simulator", 0, 0, 0, 0);
        if (mem) {
            props = new (mem) cPropertyList();
            if (props)
                props->AddRef();
        }
    }

have_list:
    PublishProperties();
    if (props != mpProps) {
        props->AttachParent(mpProps);
        props->SetParent(mpProps->mpParent);
    }

    Reporter* rep = 0;
    {
        void* mem = EAAllocate(0x40, "Simulator", 0, 0, 0, 0);
        if (mem)
            rep = new (mem) Reporter(this, props);
    }
    if (rep)
        rep->AddRef();

    mp198 = g_app->mpRegistrar;
    mp198->RegisterVector(&rep->mV10);

    Reporter* old = g_current;
    if (rep != old) {
        if (rep)
            rep->AddRef();
        g_current = rep;
        if (old)
            old->Release();
    }
    g_repList.mEnabled = false;
    if (rep)
        rep->Release();
    if (props)
        props->Release();
}

// @ 0x00f33d70
bool cTerrainSphere::AddTerrainPlacement(V4* out, int key, TerrainDesc* desc,
                                         uint32_t tag, IWorldObj* owner)
{
    Terrain* terrain = (Terrain*)FindTerrain(key);
    if (!terrain)
        return false;

    Vector3 surface;
    int one = 1;
    SurfaceDirection(&surface.x, &desc->m04.x, 0, &one, 1);

    if (!owner)
        owner = GetObjectForTerrain(terrain);

    float alpha;
    if (terrain->m64 > terrain->m60)
        alpha = (desc->m10 - terrain->m60) / (terrain->m64 - terrain->m60);
    else
        alpha = 0.5f;
    if (alpha < 0.0f)
        alpha = 0.0f;
    if (alpha > 1.0f)
        alpha = 1.0f;

    IWorldObj* iface = (IWorldObj*)ToWorldObject(owner);
    iface->SetPosition(&surface);

    Quaternion quat;
    QuaternionFromMatrix33(&quat, desc->mMatrix, 0.0f);
    iface->SetRotation(&quat);
    iface->SetScale(alpha + 3.0f);

    V4 tmp;
    tmp.mpObj = (RCObj*)owner;
    if (owner)
        owner->AddRef();
    tmp.mpTerrain = terrain;
    tmp.mTag = tag;
    tmp.mScale = 1.0f;
    out->Assign(&tmp);
    if (owner)
        owner->Release();

    return true;
}

// @ 0x00f343a0
void cTerrainSphere::UpdateTerrainState(char build)
{
    mp194->Refresh();

    // The original reuses a single 0x14-byte stack scratch area for the
    // Vector3 results and for both returned vector temporaries.  Keeping the
    // three lifetimes in disjoint scopes reproduces that stack reuse.
    {
        Vector3 value;
        m148 = *mp194->GetStop2(&value, build);
        m154 = *mp194->GetStop3(&value, build);
        m130 = *mp194->GetStop0(&value, build);
        m13c = *mp194->GetStop1(&value, build);
    }
    {
        Vector3Vector points;
        mV108 = *mp194->BuildPoints(&points, build);
        FreeVectorBuffer(points.mpBegin);
    }
    {
        FloatVector values;
        mV11c = *mp194->BuildValues(&values);
        FreeVectorBuffer(values.mpBegin);
    }
}

// @ 0x00f344e0
void cTerrainSphere::SetTerrainVectors(FloatVector* values, Vector3Vector* points)
{
    mV11c = *values;
    mV108 = *points;

    Vector3Vector pointsCopy(mV108);

    FloatVector valuesCopy;
    int count = (int)(mV11c.mpEnd - mV11c.mpBegin);
    valuesCopy.Resize(count, mV11c.mAllocator);
    memcpy(valuesCopy.mpBegin, mV11c.mpBegin, (char*)mV11c.mpEnd - (char*)mV11c.mpBegin);
    valuesCopy.mpEnd = valuesCopy.mpBegin + count;

    mp194->ApplyVectors(valuesCopy, pointsCopy);
}

// @ 0x00f34560
void cTerrainSphere::PublishWorld()
{
    if (!g_current)
        return;

    Res* res = g_current->GetRes(0x73e4f04);
    if (!res)
        return;

    res->AddRef();

    cPropertyList* props = 0;
    {
        void* mem = EAAllocate(0x38, "Simulator", 0, 0, 0, 0);
        if (mem)
            props = new (mem) cPropertyList();
    }

    cPropertyList* old = res->mpProps;
    if (props != old) {
        if (props)
            props->AddRef();
        res->mpProps = props;
        if (old)
            old->Release();
    }

    props = res->mpProps;
    PublishProperties();
    if (props != mpProps) {
        props->AttachParent(mpProps);
        props->SetParent(mpProps->mpParent);
    }

    mp198->RegisterVector(&res->mV28);

    g_repList.mEnabled = true;
    g_repList.Add((Reporter*)res);

    if (g_current) {
        Reporter* current = g_current;
        g_current = 0;
        current->Release();
    }
    res->Release();
}

// @ 0x00f34660
void cTerrainSphere::SetPlayerColorIDs()
{
    uint32_t colorId = 0;

    if (mpProps) {
        Property* prop = 0;
        if (mpProps->GetProperty(0x2a907b7, &prop) && prop->mnType == 0xa) {
            uint32_t* value = prop->GetUInt();
            colorId = *value;
        }
    }

    mpProps->Remove(0x3abb0af);

    if (mpProps->HasProperty(0x3a23f99)) {
        GetPropertyAsVector3(mpProps, 0x3a23f99, &mE0);
        SetPropertyVector3(mpProps, 0x40d6a39, 1, &mE0);
    }

    cTerrainResourceManager* mgr = (cTerrainResourceManager*)GetScriptManager();
    mgr->ApplyScriptSets(colorId, mpProps);

    VariantKey keys[32];
    VariantKey* begin = keys;
    VariantKey* end = keys;

    begin[0].mInstance = 0x57974ac6;
    begin[0].mType = 0;
    begin[0].mGroup = 0;
    end = begin + 1;

    if (m160 != 0) {
        begin[1].mInstance = m160;
        begin[1].mType = 0;
        begin[1].mGroup = 0;
        end = begin + 2;
    }

    mpProps->Remove(0x3abb0af);

    Variant var;
    var.mData[0] = 0;
    var.mData[1] = 0;
    var.mData[2] = 0;
    var.mData[3] = 0;
    var.mnFlags = 0;
    var.mnType = 0;
    WrapVariant(&var, 0x20, 0x98, begin, 0xc, (uint32_t)(end - begin));
    mpProps->SetProperty(0x3abb0af, &var);
    if (var.mnFlags & 4)
        DestroyVariant(&var, 0);
}
