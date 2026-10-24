// Slice s00b547b0 (batch cl2 #515) -- 0x00b55020, SP::Havok::CreateShape (1620 bytes).
// Builds the Havok collision shape for a simulator object from its physics property list:
// sphere / capsule-like / box from the object's local extents, or a pre-built shape from
// FUN_00b54c40 (shape types 3 and 6). Optionally wraps convex shapes in an hkConvexTranslateShape
// and computes the mass properties.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"

typedef float hkReal;

class hkMemory {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void* allocateChunk(int nbytes, int cl);                 // +0x10
    virtual void deallocateChunk(void* p, int nbytes, int cl);       // +0x14
    static hkMemory* s_instance;                                     // 0x016E4178
    static hkMemory& getInstance() { return *s_instance; }
};

#define HK_DECLARE_CLASS_ALLOCATOR(CLS) \
    __forceinline void* operator new(unsigned int nbytes) { \
        hkReferencedObject* b = static_cast<hkReferencedObject*>(hkMemory::getInstance().allocateChunk(nbytes, CLS)); \
        b->m_memSizeAndFlags = (unsigned short)nbytes; \
        return b; } \
    void operator delete(void* p) { \
        hkReferencedObject* b = static_cast<hkReferencedObject*>(p); \
        hkMemory::getInstance().deallocateChunk(p, b->m_memSizeAndFlags, CLS); }

class hkBaseObject {
public:
    virtual ~hkBaseObject() {}
};

class hkReferencedObject : public hkBaseObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x12)
    unsigned short m_memSizeAndFlags;           // +0x4
    short m_referenceCount;                     // +0x6
    virtual ~hkReferencedObject() {}
    __forceinline void removeReference()
    {
        if (m_memSizeAndFlags != 0) {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
};

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    hkVector4() {}
    hkVector4(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
};

class hkShape : public hkReferencedObject {
public:
    int m_userData;
    virtual int getType() const;                                     // +0x8 (slot 2)
};
class hkConvexShape : public hkShape { public: hkReal m_radius; };  // +0xc
class hkSphereShape : public hkConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x24)
    hkSphereShape(hkReal radius);                                    // 0x010C3770
};
class hkBoxShape : public hkConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x24)
    hkVector4 m_halfExtents;                    // +0x10
    hkBoxShape(const hkVector4& halfExtents, hkReal radius);        // 0x010C05D0
};
class hkConvexTranslateShape : public hkConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x24)
    hkConvexShape* m_childShape;                // +0x10
    hkVector4 m_translation;                    // +0x20
    hkConvexTranslateShape(const hkConvexShape* childShape, const hkVector4& translation);  // 0x010BFEB0
};

struct hkMassProperties {
    hkReal m_volume;                            // +0x0
    hkReal m_mass;                              // +0x4
    void CopyFrom(const void* src);                                  // 0x00B4D3F0, thiscall ret 4
};
// hkInertiaTensorComputer::computeShapeVolumeMassProperties (cdecl)
void ComputeShapeVolumeMassProperties(const hkShape* shape, hkReal mass, hkMassProperties* out);  // 0x01127680

extern const hkReal kBoxShapeRadius;            // 0x015BA104
extern const hkReal kMinExtent;                 // 0x01569B00
extern const hkReal kRadiusBias;                // 0x01569AB0

// Per-type flag table: hkShapeTypeInfo* at global+0x80, flags dword per shape type at +0x10c.
struct ShapeTypeTable { uint32_t pad[0x10c / 4]; uint32_t flags[1]; };
struct ShapeGlobals { uint32_t pad[0x80 / 4]; ShapeTypeTable* pTable; };
extern ShapeGlobals* g_pShapeGlobals;           // 0x0167ECD0

struct Vector3 { float x, y, z; };
struct BoundingBox { Vector3 mMin; Vector3 mMax; };

namespace App { class PropertyList; }
int GetIntPropertyDefault(const App::PropertyList* pList, uint32_t id, int def);         // 0x004E1C30
float GetFloatPropertyDefault(const App::PropertyList* pList, uint32_t id, float def);   // 0x004E1C70
uint32_t SPIDFromName(const char* name);                                                  // 0x00571CF0

struct PhysicsInfo { uint32_t pad[0x90 / 4]; void* mpData; };    // +0x90 must be non-null

class cSpatialObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30();
    virtual float GetScale();                                        // +0x34
    virtual void _v38(); virtual void _v3c(); virtual void _v40();
    virtual void _v44(); virtual void _v48(); virtual void _v4c(); virtual void _v50();
    virtual void _v54(); virtual void _v58(); virtual void _v5c(); virtual void _v60();
    virtual void _v64();
    virtual const BoundingBox& GetLocalExtents();                    // +0x68
    virtual void _v6c();
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual void _v80(); virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual void _v90(); virtual void _v94(); virtual void _v98(); virtual void _v9c();
    virtual void _va0(); virtual void _va4(); virtual void _va8();
    virtual PhysicsInfo* GetPhysicsInfo();                           // +0xac
};

hkShape* CreateCompoundOrCapsule(const float* extents);                                   // 0x00B4F470 (cdecl)

struct ShapeRequest {
    PhysicsInfo* mpInfo;                        // +0x00
    int mnKind;                                 // +0x04
    int mnCount;                                // +0x08
    uint32_t pad0c[3];
    char mbFlag;                                // +0x18
};
struct ShapeResult {
    uint32_t pad00[3];
    hkShape* mpShape;                           // +0x0c
    uint32_t pad10;
    int mnLayer;                                // +0x14
    uint32_t pad18[2];
    char mMass[1];                              // +0x20
};
ShapeResult* BuildShapeFromRequest(PhysicsInfo* pInfo, float scale, ShapeRequest* pReq);  // 0x00B54C40 (cdecl)

static inline const float& MinF(const float& a, const float& b) { return a > b ? b : a; }
static inline const float& MaxF(const float& a, const float& b) { return a > b ? a : b; }

namespace SP {
namespace Havok {

hkShape* CreateShape(cSpatialObject* pObject, App::PropertyList* pProps, hkMassProperties* pMassProps,
                     int filterType, int* pLayer, bool bGameplayPhantom)
{
    PhysicsInfo* pInfo;
    if (!pProps || !(pInfo = pObject->GetPhysicsInfo()) || !pInfo->mpData)
        return 0;

    bool bComputeMass = true;
    *pLayer = 0;
    int shapeType = GetIntPropertyDefault(pProps, 0x2f5ab240, 2);
    float radiusMult = GetFloatPropertyDefault(pProps, 0xce3f2a3a, 1.0f);
    float boundsMult = GetFloatPropertyDefault(pProps, 0xc87942af, 1.0f);
    float heightFactor = GetFloatPropertyDefault(pProps, 0x4f8a8204, 0.0f);
    float marginMult = GetFloatPropertyDefault(pProps, 0x92d453c4, 0.0f);
    float radiusBiasMult = GetFloatPropertyDefault(pProps, 0xeeb84c5e, 0.0f);

    if (bGameplayPhantom) {
        static uint32_t sShapeTypeId = SPIDFromName("shapeType_Gameplay");
        static uint32_t sRadiusMultId = SPIDFromName("radiusMultiplier_Gameplay");
        static uint32_t sBoundsMultId = SPIDFromName("boundsMultiplier_Gameplay");
        static uint32_t sHeightOffsetId = SPIDFromName("heightOffsetFactor_Gameplay");
        shapeType = GetIntPropertyDefault(pProps, sShapeTypeId, shapeType);
        radiusMult = GetFloatPropertyDefault(pProps, sRadiusMultId, radiusMult);
        boundsMult = GetFloatPropertyDefault(pProps, sBoundsMultId, boundsMult);
        heightFactor = GetFloatPropertyDefault(pProps, sHeightOffsetId, heightFactor);
    }
    if (shapeType == 4)
        shapeType = 2;

    const BoundingBox& box = pObject->GetLocalExtents();
    float ext[3];
    ext[2] = box.mMax.z - box.mMin.z;
    ext[0] = box.mMax.x - box.mMin.x;
    ext[1] = box.mMax.y - box.mMin.y;
    float heightExtra = ext[2] * heightFactor;
    float ex = ext[0] * boundsMult;
    float ey = ext[1] * boundsMult;
    float ez = ext[2] * boundsMult;
    if (heightExtra != 0.0f) {
        float t = ez - heightExtra;
        ez = MaxF(kMinExtent, t);
    }
    float minDim = 1.0e8f;
    minDim = MinF(minDim, ext[0]);
    minDim = MinF(minDim, ext[1]);
    minDim = MinF(minDim, ext[2]);
    float margin = minDim * marginMult;
    ext[0] = ex + margin;
    ext[1] = ey + margin;
    ext[2] = ez + margin;
    ext[0] = MaxF(kMinExtent, ext[0]);
    ext[1] = MaxF(kMinExtent, ext[1]);
    ext[2] = MaxF(kMinExtent, ext[2]);

    hkShape* pShape = 0;
    switch (shapeType) {
    case 0:
        pShape = new hkSphereShape(((ext[2] + ext[1]) + ext[0]) * radiusMult * 0.16666667f);
        *pLayer = 1;
        break;
    case 1:
        pShape = CreateCompoundOrCapsule(ext);
        *pLayer = 1;
        break;
    case 2: {
        hkVector4 halfExtents(ext[0] * 0.5f, ext[1] * 0.5f, ext[2] * 0.5f, 0.0f);
        pShape = new hkBoxShape(halfExtents, kBoxShapeRadius);
        *pLayer = 1;
        break;
    }
    case 3:
    case 6: {
        ShapeRequest req;
        req.mnKind = (shapeType == 3) ? 3 : 6;
        req.mbFlag = (shapeType == 3) ? 1 : 0;
        req.mpInfo = pInfo;
        req.mnCount = 1;
        ShapeResult* pRes = BuildShapeFromRequest(pInfo, pObject->GetScale(), &req);
        if (!pRes)
            return 0;
        pShape = pRes->mpShape;
        pMassProps->CopyFrom(pRes->mMass);
        *pLayer = pRes->mnLayer;
        bComputeMass = false;
        break;
    }
    default:
        return 0;
    }

    if (pShape) {
        ShapeTypeTable* pTable = g_pShapeGlobals->pTable;
        uint32_t isConvex = (pTable->flags[pShape->getType()] >> 1) & 1;
        if (isConvex) {
            int t = pShape->getType();
            if (t == 7 || t == 9)
                ((hkConvexShape*)pShape)->m_radius = (minDim * radiusBiasMult) * 0.5f + kRadiusBias;
        }
        bool bWrap = (filterType == 2 && *pLayer == 1);
        if ((bWrap || heightExtra != 0.0f) && isConvex) {
            hkVector4 offset((box.mMax.x + box.mMin.x) * 0.5f, (box.mMax.y + box.mMin.y) * 0.5f,
                             heightExtra * 0.5f + (box.mMax.z + box.mMin.z) * 0.5f, 0.0f);
            hkShape* pWrapped = new hkConvexTranslateShape((hkConvexShape*)pShape, offset);
            pShape->removeReference();
            pShape = pWrapped;
            *pLayer = 2;
        }
        if (bComputeMass) {
            ComputeShapeVolumeMassProperties(pShape, 1.0f, pMassProps);
            float mass = pMassProps->m_volume;
            float lo = 0.01f;
            if (mass < lo || (lo = 1000.0f, mass > lo))
                mass = lo;
            pMassProps->m_mass = mass;
        }
    }
    return pShape;
}

}  // namespace Havok
}  // namespace SP

// =====================================================================
// s00b547b0 batch additions (gold7 #21): EastL fixed-pool arena helpers.
// =====================================================================

// EastL fixed_pool_base descriptor, 0x18 bytes.
struct EastlFixedPool {
    void*    mpHead;        // +0x00
    uint32_t mnBegin;       // +0x04
    uint32_t mnBlockSize;   // +0x08
    uint32_t mnEnd;         // +0x0c
    uint32_t mnBase;        // +0x10
    uint32_t mnAlign;       // +0x14
    void init(void* begin, uint32_t size, uint32_t block, uint32_t align, uint32_t flags); // 0x00921260 (thiscall)
};

// Scratch object used by FUN_009213c0 (thiscall: ecx = scratch, one stack arg).
struct PoolScratch {
    uint32_t m0, m4, m8;
    uint32_t calc(void* list);      // 0x009213c0
};

extern "C" void*    __cdecl FUN_00921340(int tag);      // 0x00921340

// cPoolHolderA: 00b547b0 (0xc00-byte arena at +0x43c)
class cPoolHolderA {
public:
    uint32_t pad00[2];                  // +0x00
    uint32_t mnCapacity;                // +0x08
    void*    mpBucketList;              // +0x0c
    uint32_t m10;                       // +0x10
    uint32_t m14;                       // +0x14
    uint32_t m18;                       // +0x18
    uint8_t  pad1c[0x34 - 0x1c];        // +0x1c
    uint32_t mArenaHead;                // +0x34
    uint8_t  pad38[0x43c - 0x38];       // +0x38
    uint8_t  mPoolBuf[0xc00];           // +0x43c
    uint32_t mArenaEnd;                 // +0x103c
    cPoolHolderA* Init(int a2, int a3);                 // thiscall, ret 8
    void* RegisterPool(void* p, int a2, const int* r1, const int* r2, int v, const int* r3, EastlFixedPool* pool); // 0x00b516d0
    void Resize(uint32_t n);                            // 0x00b5d220
};

// cPoolHolderB: 00b54890 (0x1000-byte arena at +0x43c)
class cPoolHolderB {
public:
    uint32_t pad00[2];                  // +0x00
    uint32_t mnCapacity;                // +0x08
    void*    mpBucketList;              // +0x0c
    uint32_t m10;                       // +0x10
    uint32_t m14;                       // +0x14
    uint32_t m18;                       // +0x18
    uint8_t  pad1c[0x34 - 0x1c];        // +0x1c
    uint32_t mArenaHead;                // +0x34
    uint8_t  pad38[0x43c - 0x38];       // +0x38
    uint8_t  mPoolBuf[0x1000];          // +0x43c
    uint32_t mArenaEnd;                 // +0x143c
    cPoolHolderB* Init(int a2, int a3);
    void* RegisterPool(void* p, int a2, const int* r1, const int* r2, int v, const int* r3, EastlFixedPool* pool); // 0x00b51a50
    void Resize(uint32_t n);                            // 0x00b4fbd0
};

// cPoolHolderC: 00b54970 (0x80-byte arena at +0x5c)
class cPoolHolderC {
public:
    uint32_t pad00[2];                  // +0x00
    uint32_t mnCapacity;                // +0x08
    void*    mpBucketList;              // +0x0c
    uint32_t m10;                       // +0x10
    uint32_t m14;                       // +0x14
    uint32_t m18;                       // +0x18
    uint32_t mArenaHead;                // +0x34
    uint8_t  pad38[0x5c - 0x38];        // +0x38
    uint8_t  mPoolBuf[0x80];            // +0x5c
    uint32_t mArenaEnd;                 // +0xdc
    cPoolHolderC* Init(int a2, int a3);
    void* RegisterPool(void* p, int a2, const int* r1, const int* r2, int v, const int* r3, EastlFixedPool* pool); // 0x00b51b00
    void Resize(uint32_t n);                            // 0x00b4fbd0
};

extern "C" float DAT_013f0620;   // 0x461c4000 (10000.0f)
extern "C" float DAT_01470f1c;   // 0x40000000 (2.0f)

// @ 0x00b547b0
cPoolHolderA* cPoolHolderA::Init(int a2, int a3)
{
    EastlFixedPool pool;
    PoolScratch scratch;
    pool.mpHead = 0;
    pool.init(&mPoolBuf[0], 0xc00, 0xc, 4, 0);
    pool.mnBegin = (uint32_t)&mArenaHead;
    pool.mnBlockSize = 0xc;
    pool.mnEnd = (uint32_t)&mArenaEnd;
    pool.mnBase = (uint32_t)&mPoolBuf[0];
    void* p = FUN_00921340(0x101);
    RegisterPool(p, a2, &a3, &a3, a3, &a3, &pool);
    m10 = 0x461c4000;
    m14 = 0x40000000;
    m18 = 0;
    uint32_t n = scratch.calc(mpBucketList);
    if (mnCapacity < n)
        Resize(n);
    return this;
}

// @ 0x00b54890
cPoolHolderB* cPoolHolderB::Init(int a2, int a3)
{
    EastlFixedPool pool;
    PoolScratch scratch;
    pool.mpHead = 0;
    pool.init(&mPoolBuf[0], 0x1000, 0x10, 4, 0);
    pool.mnBegin = (uint32_t)&mArenaHead;
    pool.mnBlockSize = 0x10;
    pool.mnEnd = (uint32_t)&mArenaEnd;
    pool.mnBase = (uint32_t)&mPoolBuf[0];
    void* p = FUN_00921340(0x101);
    RegisterPool(p, a2, &a3, &a3, a3, &a3, &pool);
    m10 = 0x461c4000;
    m14 = 0x40000000;
    m18 = 0;
    uint32_t n = scratch.calc(mpBucketList);
    if (mnCapacity < n)
        Resize(n);
    return this;
}

// @ 0x00b54970
cPoolHolderC* cPoolHolderC::Init(int a2, int a3)
{
    EastlFixedPool pool;
    PoolScratch scratch;
    pool.mpHead = 0;
    pool.init(&mPoolBuf[0], 0x80, 0x10, 4, 0);
    pool.mnBegin = (uint32_t)&mArenaHead;
    pool.mnBlockSize = 0x10;
    pool.mnEnd = (uint32_t)&mArenaEnd;
    pool.mnBase = (uint32_t)&mPoolBuf[0];
    void* p = FUN_00921340(9);
    RegisterPool(p, a2, &a3, &a3, a3, &a3, &pool);
    m10 = 0x461c4000;
    m14 = 0x40000000;
    m18 = 0;
    uint32_t n = scratch.calc(mpBucketList);
    if (mnCapacity < n)
        Resize(n);
    return this;
}

// ---------------------------------------------------------------------
// 0x00b54b40 / 0x00b54b80 : small keyed-slot + global list helpers.
// ---------------------------------------------------------------------

struct SPKeyPair { uint32_t lo; uint32_t hi; };

class cPairMapInner {
public:
    uint32_t m00;                  // +0x00
    uint32_t* mpTable;             // +0x04
    int32_t  mnIndex;              // +0x08
    uint32_t* Lookup(const SPKeyPair* key);     // 0x00b54a40 (thiscall, ret 4), returns slot+8
};

struct LookupRec { uint32_t m00, m04, m08; };   // &local_18
extern "C" void __cdecl FUN_00b51bb0(void* out, const void* key);              // 0x00b51bb0
extern "C" void __cdecl FUN_00b52120(void* dst, void* a, uint32_t flags);      // 0x00b52120

// @ 0x00b54a40
uint32_t* cPairMapInner::Lookup(const SPKeyPair* key)
{
    LookupRec local;
    FUN_00b51bb0(&local, key);
    if (local.m00 == mpTable[mnIndex]) {
        local.m00 = key->lo;
        local.m04 = key->hi;
        uint32_t flags = 0;
        local.m08 = 0;
        FUN_00b52120(&local, &local, flags);
    }
    return (uint32_t*)(local.m00 + 8);
}

class cPairMap {
public:
    void      Insert(uint32_t a, uint32_t b, float c);   // 0x00b54b40 (thiscall, ret 0xc)
    uint8_t   pad[0x1858];
    cPairMapInner mInner;                       // +0x1858
};

// @ 0x00b54b40
void cPairMap::Insert(uint32_t a, uint32_t b, float c)
{
    SPKeyPair key;
    uint32_t lo = a, hi = b;
    if (hi < lo) {
        lo = b;
        hi = a;
    }
    key.lo = lo;
    key.hi = hi;
    uint32_t* r = mInner.Lookup(&key);
    *(float*)r = c;
}

extern "C" uint8_t* DAT_0167ed44;   // list begin (0x0167ed44)
extern "C" uint8_t* DAT_0167ed48;   // list end   (0x0167ed48)

struct SPListObj { void Destroy(); };  // 0x00b51ee0 (thiscall, no args)
struct SPListEntry { int32_t mnType; SPListObj* mpObj; };  // 8 bytes

// @ 0x00b54b80
void FUN_00b54b80(void)
{
    int n = ((int)(DAT_0167ed48 - DAT_0167ed44)) >> 3;
    if (n > 0) {
        SPListEntry* base = (SPListEntry*)DAT_0167ed44;
        for (int i = 0; i < n; i++) {
            int t = base[i].mnType;
            if (t - 1 == 0) {
                base[i].mpObj->Destroy();
                base = (SPListEntry*)DAT_0167ed44;
            }
        }
        int m = ((int)(DAT_0167ed48 - (uint8_t*)base)) >> 3;
        DAT_0167ed48 = DAT_0167ed48 + (-m) * 8;
    }
}

// ---------------------------------------------------------------------
// 0x00b54be0 / 0x00b54c40 : command-node registration + shape build.
// ---------------------------------------------------------------------

extern "C" void* __cdecl FUN_00b4f830(int a, int b);          // 0x00b4f830
extern "C" void* __cdecl FUN_00b3d310(...);                    // 0x00b3d310 (variadic)
extern "C" void  __cdecl FUN_00b51840(void* a, void* b, uint32_t c);  // 0x00b51840 (ecx=global)
extern "C" void* __cdecl FUN_00b51780(void* a, void* b);       // 0x00b51780
extern "C" int   __cdecl FUN_00b51040(void* a, float s);       // 0x00b51040
extern "C" char  __cdecl SP_GetPropertyAsKey(void* info, uint32_t key, void* out); // 0x006a1250
extern "C" void  __cdecl FUN_00b4d540(void* dst);              // 0x00b4d540
extern "C" char  __cdecl FUN_00b510b0(void* a, void* b);       // 0x00b510b0
extern "C" int   __cdecl FUN_00b4f660(int a, float s, void* v, int b);  // 0x00b4f660
extern "C" void  __cdecl FUN_00b4d3f0(void* dst);            // 0x00b4d3f0
extern "C" void  __cdecl FUN_00b4d5d0(void* dst, int shape, float s, int kind, int a, int b); // 0x00b4d5d0
extern "C" void  __cdecl FUN_01127680(int shape, float s, void* out);   // hkInertiaTensorComputer
extern "C" int   __cdecl FUN_00b64a00(int id, float s);        // 0x00b64a00
extern "C" void  __cdecl FUN_01081bb0(float s);                // 0x01081bb0 (hkMatrix3::mul)
extern "C" float DAT_0167ecf4, DAT_0167ecf8, DAT_0167ecfc;     // default caps axis extents
extern "C" float DAT_01481064;                                 // 0.5f

struct CmdNode {
    int32_t m00, m04, m08, m0c, m10, m14, m18;
    void*   mpBack;             // +0x1c
};
struct CmdLink {
    int32_t m00;
    int32_t m04;
    void*   mpField8;           // +0x08
};
struct CmdChain { void Unlink(); };                 // 0x00b4d770 (thiscall)
struct CmdTail  { void Run(); };                    // 0x00b545b0 (thiscall)
struct Build830 { uint8_t b[0x84]; void* Build(int a, int b2); }; // 0x00b4f830 (thiscall)

// @ 0x00b54be0
int* __cdecl FUN_00b54be0(int* param_1, int param_2)
{
    Build830 scratch;
    char flag = 0;
    void* u = scratch.Build(param_2, param_2);
    FUN_00b51840(param_1, u, (uint32_t)flag);
    CmdNode* node = (CmdNode*)*param_1;
    ((CmdLink*)node->mpBack)->mpField8 = &node->m10;
    void* o = FUN_00b3d310();
    if (((char*)o)[0x25] != 0) {
        void* o2 = FUN_00b3d310(param_2);
        ((CmdTail*)o2)->Run();
    }
    return param_1;
}

struct ReqRec {                       // &local_110
    void*    mpA;                     // +0x00  (= uVar1)
    uint32_t m04;                     // +0x04  (= local_1b0)
    uint32_t m08;                     // +0x08  (= local_1ac)
};
struct Key3 { uint32_t a, b, c; };    // &local_1a0

struct ShapeObj {                     // param_1
    int32_t m00, m04, m08, m0c, m10, m14, m18, m1c, m20;
    float   f24;                      // +0x24
    uint8_t pad28[0x70 - 0x28];
    float   f70, f74, f78, f7c, f80, f84;   // +0x70..+0x87
    uint8_t pad88[0x90 - 0x88];
    void*   mpInfo;                   // +0x90
};
struct ShapeReq {                     // param_3
    int32_t mpShape;                  // +0x00
    int32_t m04;                      // +0x04
    int32_t mnFlags;                  // +0x08
    int32_t m0c, m10, m14;
    uint8_t mbFlag;                   // +0x18
};
struct ExtRec { float x, y, z, w; };  // &local_1cc
struct WorkRec {                      // generic HK working record
    uint8_t b[0x140];
};
// local_1d8 etc. slots inside WorkRec
struct Blk { float m00; uint8_t pad[0x20]; float m24; };

// @ 0x00b54c40
void* __cdecl FUN_00b54c40(ShapeObj* param_1, float param_2, ShapeReq* param_3)
{
    ExtRec ext;
    Key3   key;
    ReqRec req;
    WorkRec work;

    uint32_t endZ = *(uint32_t*)((uint8_t*)param_1->mpInfo + 0x10);
    uint32_t cenY = *(uint32_t*)((uint8_t*)param_1->mpInfo + 8);
    uint32_t cenZ = *(uint32_t*)((uint8_t*)param_1->mpInfo + 0xc);
    bool built = false;
    uint32_t m1b0 = 0;
    uint32_t m1b4 = cenY;
    ExtRec* pf = (ExtRec*)FUN_00b51780(&key, &m1b4);
    ext = *pf; ext.w = pf->w;
    uint32_t extcx = (uint32_t)&ext.x;
    (void)extcx;
    int r = FUN_00b51040(&ext, param_2);
    req.mpA = (void*)r;
    if (r != 0)
        goto LAB_54e9f;
    r = FUN_00b51040(&ext, 1.0f);
    if (r == 0) {
        key.a = 0; key.b = 0; key.c = 0;
        char c = (char)SP_GetPropertyAsKey(param_1->mpInfo, 0x532d802, &key);
        if (c != 0) {
            FUN_00b4d540(&work);
            c = FUN_00b510b0(&key, &work);
            if (c != 0) {
                req.m04 = m1b0;
                req.m08 = cenZ;
                req.mpA = (void*)cenY;
                int* p = FUN_00b54be0((int*)&work, (int)&req);
                r = (int)(p + 4);
                built = true;
                if (r != 0)
                    goto LAB_54e9f;
            }
        }
        if (param_3 == 0)
            return (void*)(uint32_t)r;
        ext.x = DAT_0167ecf4; ext.y = DAT_0167ecf8; ext.z = DAT_0167ecfc;
        if (param_3->mnFlags == 1) {
            ext.x = (param_1->f70 + param_1->f7c) * DAT_01481064;
            ext.y = (param_1->f80 + param_1->f74) * DAT_01481064;
            ext.z = (param_1->f84 + param_1->f78) * DAT_01481064;
        }
        int shape = FUN_00b4f660(param_3->mpShape, 1.0f, &ext, param_3->m04);
        if (shape == 0)
            return (void*)(uint32_t)r;
        FUN_00b4d5d0(&m1b4, shape, 1.0f, param_3->mnFlags, 0, 0);
        if (param_3->mbFlag != 0)
            FUN_01127680(shape, 1.0f, &work);
        int* p = FUN_00b54be0((int*)&work, 0);
        r = (int)(p + 4);
        built = true;
        if (r == 0)
            return (void*)(uint32_t)r;
    }
LAB_54e9f:
    if (param_2 != 1.0f) {
        int s2 = FUN_00b64a00(*(int*)((uint8_t*)r + 0xc), param_2);
        int ret = r;
        if (s2 != 0) {
            FUN_00b4d5d0(&m1b4, s2, param_2, *(int*)((uint8_t*)r + 0x14), r, 0);
            if (0.0f < *(float*)((uint8_t*)r + 0x24)) {
                FUN_00b4d3f0((uint8_t*)r + 0x20);
                float s = (param_2 * param_2) * param_2;
                FUN_01081bb0(s);
            }
            int* p = FUN_00b54be0((int*)&work, 0);
            ret = (int)(p + 4);
            if (!built) {
                ((CmdChain*)(void*)ret)->Unlink();
                return (void*)(uint32_t)ret;
            }
        }
        return (void*)(uint32_t)ret;
    }
    if (built)
        return (void*)(uint32_t)r;
LAB_54eb5:
    return (void*)(uint32_t)r;
}
