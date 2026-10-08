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
