// slice s00452080 -- SP::cSPEditorBlock::BuildNewPhysicsShape (4555 bytes).
// Builds the Havok rigid body the editor uses for a block: either a convex hull of the model's
// transformed hull (when the "use hull" bool property 0x590aa7f is set and the prop list has
// 0xf9efc0) or a box of the block's bounding box translated to the box centre.
// Retail layout (ModAPI EditorRigblock): mpPropList +0xc, mpModel +0x10, mpModelWorld +0x18,
// mPosition +0x48, mTotalOrientation +0x60, mHullData +0x1a4, mScale +0x1d8,
// mDeformationHandles +0x6cc.
// Flags: /Od /Oy /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc), like s004b8af0
// (editor physics world): /Oy gives the `and esp,-16` esp-relative frame.
#include "types.h"

#pragma pack(push, 4)

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long dwTlsIndex);

// ---------------------------------------------------------------------------
// Havok 3.1 (only what this function needs)
// ---------------------------------------------------------------------------
typedef float hkReal;

class hkMemory {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void* allocateChunk(int nbytes, int cl);                 // +0x10
    virtual void deallocateChunk(void* p, int nbytes, int cl);       // +0x14
    static hkMemory* s_instance;                                     // 0x016E4178
    static hkMemory& getInstance() { return *s_instance; }
};

extern unsigned long g_hkThreadMemoryTls;                            // 0x016E4174
class hkThreadMemory {
public:
    void deallocateChunk(void* p, int nbytes, int cl);               // 0x0107DB10
    static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }
};

#define HK_DECLARE_CLASS_ALLOCATOR(CLS) \
    void* operator new(unsigned int nbytes) { \
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
    __forceinline void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    void set(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
    void setZero4() { x = y = z = w = 0.0f; }
    hkReal& operator()(int i) { return (&x)[i]; }
};

class hkMatrix3 {
public:
    hkVector4 m_col0, m_col1, m_col2;
    void operator=(const hkMatrix3& m);                              // 0x0044A8C0
    hkVector4& getColumn(int i) { return (&m_col0)[i]; }
    hkReal& operator()(int r, int c) { return getColumn(c)(r); }
    __forceinline void setIdentity()
    {
        hkVector4 zero;
        zero.setZero4();
        getColumn(0) = zero;
        getColumn(1) = zero;
        getColumn(2) = zero;
        hkReal one = 1.0f;
        (*this)(0, 0) = one;
        (*this)(1, 1) = one;
        (*this)(2, 2) = one;
    }
};
class hkRotation : public hkMatrix3 {};

class hkTransform {
public:
    hkRotation m_rotation;                      // +0x0
    hkVector4 m_translation;                    // +0x30
    hkRotation& getRotation() { return m_rotation; }
    __forceinline void setIdentity() { m_rotation.setIdentity(); m_translation.setZero4(); }
    void setTranslation(const hkVector4& t) { m_translation = t; }
};

template <class T> class hkArray {
public:
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    hkArray() : m_data(0), m_size(0), m_capacityAndFlags(0x80000000) {}
    __forceinline ~hkArray() { releaseMemory(); }
    int getCapacity() const { return m_capacityAndFlags & 0x3fffffff; }
    __forceinline void releaseMemory()
    {
        if ((m_capacityAndFlags & 0x80000000) == 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), 0x14);
    }
};

struct hkStridedVertices {
    const hkReal* m_vertices;
    int m_numVertices;
    int m_striding;
};

struct hkGeometry {
    hkArray<hkVector4> m_vertices;              // +0x0
    hkArray<hkVector4> m_triangles;             // +0xc (Triangle, 12 bytes; only the dtor touches it)
    hkGeometry();                                                    // 0x00453400
    ~hkGeometry();                                                   // 0x00453460
};

struct hkGeometryUtility {
    // "LtCreateConvex"/"Hull" timer
    static void createConvexGeometry(const hkStridedVertices& verts, hkGeometry& geometryOut,
                                     hkArray<hkVector4>& planeEquationsOut, int flags);  // 0x010EDF70
};

struct hkMassProperties {
    hkReal m_volume;                            // +0x0
    hkReal m_mass;                              // +0x4
    hkVector4 m_centerOfMass;                   // +0x10
    hkMatrix3 m_inertiaTensor;                  // +0x20
    hkMassProperties();                                              // 0x00453250
};

struct hkInertiaTensorComputer {
    static int computeVertexHullVolumeMassProperties(const hkReal* vertexIn, int striding, int numVertices,
                                                     hkReal mass, hkMassProperties& result);  // 0x011252D0
    static int computeBoxVolumeMassProperties(const hkVector4& halfExtents, hkReal mass,
                                              hkMassProperties& result);                    // 0x01124110
};

extern hkReal hkConvexShapeDefaultRadius;                            // 0x015BA104

class hkShape : public hkReferencedObject { public: int m_userData; };
class hkConvexShape : public hkShape { public: hkReal m_radius; };  // +0xc
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
class hkConvexVerticesShape : public hkConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x24)
    uint32_t pad10[(0x50 - 0x10) / 4];
    hkConvexVerticesShape(hkStridedVertices vertsIn, const hkArray<hkVector4>& planeEquations,
                          hkReal radius);                            // 0x010C1FE0
};

#pragma pack(push, 8)
struct hkPropertyValue {
    uint64_t m_data;
    hkPropertyValue(void* p) { m_data = (uint32_t)p; }
};
#pragma pack(pop)

struct hkRigidBodyCinfo {
    unsigned int m_collisionFilterInfo;         // +0x0
    hkShape* m_shape;                           // +0x4
    uint32_t pad08[2];
    hkVector4 m_position;                       // +0x10
    hkVector4 m_rotation;                       // +0x20
    hkVector4 m_linearVelocity;                 // +0x30
    hkVector4 m_angularVelocity;                // +0x40
    hkMatrix3 m_inertiaTensor;                  // +0x50
    hkVector4 m_centerOfMass;                   // +0x80
    hkReal m_mass;                              // +0x90
    hkReal m_linearDamping;                     // +0x94
    hkReal m_angularDamping;                    // +0x98
    hkReal m_friction;                          // +0x9c
    hkReal m_restitution;                       // +0xa0
    hkReal m_maxLinearVelocity;                 // +0xa4
    hkReal m_maxAngularVelocity;                // +0xa8
    hkReal m_allowedPenetrationDepth;           // +0xac
    signed char m_motionType;                   // +0xb0
    signed char m_rigidBodyDeactivatorType;     // +0xb1
    signed char m_solverDeactivation;           // +0xb2
    signed char m_qualityType;                  // +0xb3
    hkRigidBodyCinfo();                                              // 0x01087ED0
};

class hkRigidBody : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x2a)
    uint32_t pad08[(0xd0 - 0x8) / 4];
    hkRigidBody(const hkRigidBodyCinfo& info);                       // 0x010878B0
    void setTransform(const hkTransform& transform);                 // 0x01087890
    void addProperty(unsigned int key, hkPropertyValue value);      // 0x010825A0 (hkWorldObject)
};

// ---------------------------------------------------------------------------
// Spore math / model types
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) { x = a; y = b; z = c; }
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
};
Vector3 operator-(const Vector3& a, const Vector3& b);              // 0x0041DB10

// cSPVector3: same data, its converting copy ctor lives out of line.
struct cSPVector3 : public Vector3 {
    cSPVector3(const Vector3& v);                                    // 0x004098A0
};

struct Matrix3 { float m[9]; };                 // plain POD: copies with rep movsd
struct PODVector3 { float x, y, z; };           // plain POD: copies through integer regs
extern Matrix3 g_Matrix3Identity;                                    // 0x015D2428
extern PODVector3 g_Vector3Zero;                                     // 0x015D255C

struct BoundingBox {
    Vector3 mMin, mMax;
    Vector3 GetCenter();                                             // 0x00409B90
};

struct cSPTransform {
    unsigned short mFlags;                      // +0x0
    unsigned short mModificationCount;          // +0x2
    PODVector3 mTranslation;                    // +0x4
    float mScale;                               // +0x10
    Matrix3 mRotation;                          // +0x14
    cSPTransform(const cSPTransform& o);                             // 0x0040CE80
    cSPTransform& operator=(const cSPTransform& o);                  // 0x00537DC0
    void SetIdentity()
    {
        mRotation = g_Matrix3Identity;
        mScale = 1.0f;
        mTranslation = g_Vector3Zero;
        mFlags = 0;
        mModificationCount = 0;
    }
    void SetScale(float s) { mScale = s; ++mModificationCount; }
};

namespace EA {
template <class T> class AutoRefCount {
public:
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}

namespace SP {

struct Property {
    uint32_t pad00[4];
    unsigned short pad10;
    unsigned short mnType;                      // +0x12
    bool* GetValueBool();                                            // 0x0041E920
};

class cPropertyList {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual bool HasProperty(uint32_t id);                           // +0x1c
    virtual void _v20();
    virtual bool GetProperty(uint32_t id, Property*& result);        // +0x24
};

inline bool GetBool(cPropertyList* pPropList, uint32_t propID, bool& dst)
{
    Property* prop;
    if (pPropList && pPropList->GetProperty(propID, prop) && prop->mnType == 1) {
        dst = *prop->GetValueBool();
        return true;
    }
    return false;
}

class cMWModel {
public:
    uint32_t pad00[2];
    cSPTransform mTransform;                    // +0x8
};

struct HullVertices {
    float* mpData;
    float& operator[](int i) { return *(mpData + i); }
};

struct cMWTransformedHull {
    int mStride;                                // +0x0
    int field_4;                                // +0x4
    int mNumVertices;                           // +0x8
    int mNumFaces;                              // +0xc
    HullVertices mVertices;                     // +0x10
};

class cIModelWorld {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6c();
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual void _v80(); virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual void _v90(); virtual void _v94(); virtual void _v98(); virtual void _v9c();
    virtual void _va0(); virtual void _va4(); virtual void _va8(); virtual void _vac();
    virtual void _vb0(); virtual void _vb4(); virtual void _vb8(); virtual void _vbc();
    virtual void _vc0(); virtual void _vc4(); virtual void _vc8(); virtual void _vcc();
    virtual void _vd0(); virtual void _vd4(); virtual void _vd8();
    virtual void GetTransformedHull(cMWModel* model, cMWTransformedHull*& hull);  // +0xdc
};

class cSPEditorHandleDeform {
public:
    uint32_t pad000[0x180 / 4];
    float mValue;                               // +0x180
};

template <class T> struct HandleVector {
    T* mpBegin;
    T* mpEnd;
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return *(mpBegin + n); }
};

class cSPEditorBlock {
public:
    uint32_t pad000[0xc / 4];
    EA::AutoRefCount<cPropertyList> mpPropList;     // +0xc
    EA::AutoRefCount<cMWModel> mpModel;             // +0x10
    uint32_t pad014;
    EA::AutoRefCount<cIModelWorld> mpModelWorld;    // +0x18
    uint32_t pad01c[(0x48 - 0x1c) / 4];
    Vector3 mPosition;                              // +0x48
    uint32_t pad054[(0x60 - 0x54) / 4];
    Matrix3 mTotalOrientation;                      // +0x60
    uint32_t pad084[(0x1a4 - 0x84) / 4];
    cMWTransformedHull* mHullData;                  // +0x1a4
    uint32_t pad1a8[(0x1d8 - 0x1a8) / 4];
    float mScale;                                   // +0x1d8
    uint32_t pad1dc[(0x6cc - 0x1dc) / 4];
    HandleVector<EA::AutoRefCount<cSPEditorHandleDeform> > mDeformationHandles;  // +0x6cc

    BoundingBox GetBBox(int type, bool a, bool b);                   // 0x0044AE00
    void SetDeformationHandleValue(int idx, float value, float* a, bool b, bool c);  // 0x0043D690
    hkRigidBody* BuildNewPhysicsShape();
};

namespace EditorUtils {
    void GetHavokRotationFromMatrix(const Matrix3& m, hkRotation& out);  // 0x004A92C0
}

// @ 0x00452080
hkRigidBody* cSPEditorBlock::BuildNewPhysicsShape()
{
    hkRigidBodyCinfo info;
    hkRigidBody* body = 0;

    for (int i = 0, count = mDeformationHandles.size(); i < count; ++i)
        SetDeformationHandleValue(i, mDeformationHandles[i]->mValue, 0, false, false);

    bool useHull;
    if (!GetBool(mpPropList, 0x590aa7f, useHull))
        useHull = false;

    BoundingBox bbox = GetBBox(1, false, false);
    cSPVector3 size(bbox.mMax - bbox.mMin);

    if (useHull && mpPropList->HasProperty(0xf9efc0)) {
        // Fetch the hull with the model at identity rotation/translation and the block scale.
        cSPTransform savedTransform(mpModel->mTransform);
        mpModel->mTransform.SetIdentity();
        mpModel->mTransform.SetScale(mScale);
        mpModelWorld->GetTransformedHull(mpModel, mHullData);
        mpModel->mTransform = savedTransform;

        if (mHullData && mHullData->mNumFaces != 0) {
            hkStridedVertices verts;
            verts.m_vertices = &mHullData->mVertices[0];
            verts.m_numVertices = mHullData->mNumVertices;
            verts.m_striding = mHullData->mStride;
            hkGeometry geometry;
            hkArray<hkVector4> planeEquations;
            hkGeometryUtility::createConvexGeometry(verts, geometry, planeEquations, 1);

            hkConvexVerticesShape* shape = new hkConvexVerticesShape(verts, planeEquations, 0.0f);
            info.m_shape = shape;
            info.m_position.set(0.0f, 0.0f, 0.0f, 0.0f);
            info.m_motionType = 6;

            hkMassProperties massProperties;
            info.m_mass = size[0] * size[1] * size[2];
            hkInertiaTensorComputer::computeVertexHullVolumeMassProperties(
                &mHullData->mVertices[0], mHullData->mStride, mHullData->mNumVertices, info.m_mass, massProperties);
            info.m_inertiaTensor = massProperties.m_inertiaTensor;
            info.m_centerOfMass = massProperties.m_centerOfMass;
            info.m_mass = massProperties.m_mass;

            body = new hkRigidBody(info);
            shape->removeReference();
        }
    } else {
        Vector3 position;
        position = mPosition;
        Vector3 halfExtents(size[0] * 0.5f, size[1] * 0.5f, size[2] * 0.5f);

        hkBoxShape* box = new hkBoxShape(hkVector4(halfExtents[0], halfExtents[1], halfExtents[2]),
                                         hkConvexShapeDefaultRadius);
        box->m_radius = 0.01f;

        Vector3 center = GetBBox(0, false, false).GetCenter();
        Vector3 offset;
        offset = center - position;
        hkConvexTranslateShape* translated =
            new hkConvexTranslateShape(box, hkVector4(offset[0], offset[1], offset[2]));
        info.m_shape = translated;
        info.m_motionType = 6;

        hkTransform transform;
        transform.setIdentity();
        transform.setTranslation(hkVector4(position[0], position[1], position[2]));
        EditorUtils::GetHavokRotationFromMatrix(mTotalOrientation, transform.getRotation());

        info.m_restitution = 0.0f;
        info.m_mass = size[0] * size[1] * size[2];
        hkMassProperties massProperties;
        hkInertiaTensorComputer::computeBoxVolumeMassProperties(
            hkVector4(halfExtents[0], halfExtents[1], halfExtents[2]), info.m_mass, massProperties);
        info.m_inertiaTensor = massProperties.m_inertiaTensor;
        info.m_centerOfMass = massProperties.m_centerOfMass;
        info.m_mass = massProperties.m_mass;
        info.m_rigidBodyDeactivatorType = 1;

        body = new hkRigidBody(info);
        body->setTransform(transform);
        box->removeReference();
    }

    if (body)
        body->addProperty(0, hkPropertyValue(this));
    return body;
}

} // namespace SP

#pragma pack(pop)
