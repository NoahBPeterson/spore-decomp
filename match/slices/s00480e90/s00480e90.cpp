// Slice s00480e90: SP::cSPEditorHandleDeform::RecordHandlePosition (retail, 4202 bytes).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (editor /Od region, no /EHsc).
// Local names were chosen so the /Od name-hash slot order reproduces the original frame.
//
// Retail rewrite of the 2008 dev function: it saves the block model's transform, resets it to identity,
// re-derives the pick ray (SetPickData), retries PickBlocks with a growing pick offset, asks the model world
// for the picked triangle, and records the triangle pinning data (barycentric hit, triangle-local start /
// end offsets, direction axis) before restoring the model transform.
#include "types.h"

// Reserves N dwords of /Od temp space at the point of use: the original frame has two blocks of
// never-referenced slots (1 after the transform copy, 5 after the normalize call), the shape a
// declined inline callee leaves behind.
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- rw::math / cSP math types ----
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Vec3Row { float x, y, z; };              // a matrix row (plain data)
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3(const Vec3Row& r) { x = r.x; y = r.y; z = r.z; }
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vec3Row xAxis, yAxis, zAxis;
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& o);                         // @ 0x41cb40 (out of line)
    static const Matrix33T kIdentity;                        // @ 0x15d4ea8
};
// argument wrappers of the vector-times-matrix helper: the transposed matrix is copied into them
struct MatrixArgA : Matrix33T {
    MatrixArgA(const Matrix33T& m) : Matrix33T(m) {}
};
struct Matrix33Base {
    Vec3Row xAxis, yAxis, zAxis;
    Matrix33Base();                                          // @ 0x402ab0
};
struct MatrixArgB : Matrix33Base {
    MatrixArgB(const Matrix33T& m) { *(Matrix33T*)this = m; }
};
struct Vec3C : Vector3T {                       // Vector3 with an out-of-line copy ctor
    Vec3C(const Vector3T& v);                                // @ 0x4098a0
};
extern const Vector3T kZeroVector;                           // @ 0x15d4fd8

float Vec3Dot(const Vector3T& a, const Vector3T& b);         // @ 0x455cc0
struct cSPPlane {
    float a, b, c, d;
    cSPPlane& Set(float a, float b, float c, float d);       // @ 0x44e410
    float& operator[](int i) { return (&a)[i]; }
    const float& operator[](int i) const { return (&a)[i]; }
    cSPPlane(const cSPVector3& point, const cSPVector3& normal)
    {
        Set(normal[0], normal[1], normal[2], -Vec3Dot(point, normal));
    }
};
struct cSPBoundingBox { cSPVector3 mMin, mMax; };

// out-of-line math helpers (cdecl, results returned through a hidden pointer)
Vector3T Vec3Scale(const Vector3T& v, const float& s);       // @ 0x41dca0
Vector3T Vec3Add(const Vector3T& a, const Vector3T& b);      // @ 0x41dc10
Vector3T Vec3Sub(const Vector3T& a, const Vector3T& b);      // @ 0x41db10
Vector3T Vec3MulMat(const Vector3T& v, const Matrix33T& m);  // @ 0x41daf0
Vector3T Vec3MulMatA(const cSPVector3& v, const MatrixArgA& m);  // @ 0x41daf0
Vector3T Vec3MulMatB(const cSPVector3& v, const MatrixArgB& m);  // @ 0x41daf0
cSPMatrix3 Mat3Transpose(const Matrix33T& m);                // @ 0x41ded0
Vector3T Vec3Normalize(const Vector3T& v);                   // @ 0x436ce0 (out of line here)
float PlaneDistance(const cSPPlane& plane, const Vector3T& point);  // @ 0x44e5d0
inline bool RayPlaneIntersect(const Vector3T& origin, const Vector3T& dir, const cSPPlane& plane, float* t)  // @ 0x44e640
{
    float denom = dir[0] * plane[0] + dir[1] * plane[1] + dir[2] * plane[2];
    if (denom == 0.0f)
        return false;
    float distance = -PlaneDistance(plane, origin) / denom;
    if (t)
        *t = distance;
    return distance >= 0.0f;
}

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3T mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform(const cSPTransform& t);                     // @ 0x40ce80
    cSPTransform& operator=(const cSPTransform& t);          // @ 0x537dc0
    void Reset()
    {
        *(Matrix33T*)&mRotation = cSPMatrix3::kIdentity;
        mScale = 1.0f;
        mTranslation = kZeroVector;
        mFlags = 0;
        mModificationCount = 0;
    }
};

// ---- ref counting ----
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    AutoRefCount* ReleaseAndGetAddressOf()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return this;
    }
};

// ---- eastl::vector<AutoRefCount<cSPEditorBlock>, sp_vector_allocator> ----
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
namespace eastl {
struct sp_vector_allocator {
    sp_vector_allocator() {}
    sp_vector_allocator(const sp_vector_allocator& x);       // @ 0x429360
};
template<class T, class Allocator> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    VectorBase(const Allocator& allocator)
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {}
    ~VectorBase();                                           // @ 0x425990
};
template<class T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}
template<class T, class Allocator> struct vector : VectorBase<T, Allocator> {
    typedef VectorBase<T, Allocator> base_type;
    vector(const Allocator& allocator = Allocator()) : base_type(allocator) {}
    ~vector() { destruct(this->mpBegin, this->mpEnd); }      // @ 0x453eb0
    void push_back(const T& value)                           // @ 0x4541f0
    {
        if (this->mpEnd < this->mpCapacity)
            ::new(this->mpEnd++) T(value);
        else
            DoInsertValueEnd(this->mpEnd, value);
    }
    void DoInsertValueEnd(T* position, const T& value);      // @ 0x454ee0
};
}

#define PV(n) virtual void _v##n();
namespace SP {

struct cMWObject {
    void* mpVtbl;
    uint32_t mFlags;
    cSPTransform mTransform;                    // +0x08
};
struct cMWModel : cMWObject { };

struct cModelVertexData {
    cSPVector3 mPosition;
    cModelVertexData() {}
};

struct cIModelTriangle {
    virtual int AddRef();                                                       // 0x00
    virtual int Release();                                                      // 0x04
    PV(2)
    virtual void GetVertices(cModelVertexData* vertices);                       // 0x0c
};

namespace cMWPickInfo { enum tLevel { kLevel4 = 4 }; }

struct cIModelWorld {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
    PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68)
    virtual void GetTriangle(cMWModel* model, int triangleIndex,
                             AutoRefCount<cIModelTriangle>* triangle, bool useHull);  // 0x114
};

struct cSPEditorBlock {
    PV(0)
    virtual int AddRef();                                                       // 0x04
    virtual int Release();                                                      // 0x08
    char pad04[0x10 - 0x04];
    AutoRefCount<cMWModel> mModel;              // +0x10
    char pad14[0x18 - 0x14];
    AutoRefCount<cIModelWorld> mModelWorld;     // +0x18
    cMWModel* GetModel() const { return mModel; }
    cIModelWorld* GetModelWorld() const { return mModelWorld; }
    cSPBoundingBox GetBBox(int type, bool a, bool b);                           // @ 0x44ae00
    cSPTransform GetGeometryTransform() const;                                  // @ 0x4363d0
};

typedef eastl::vector<AutoRefCount<cSPEditorBlock>, eastl::sp_vector_allocator> BlockVector;

namespace EditorUtils {
    cSPEditorBlock* PickBlocks(BlockVector& ignore, Vector3T origin, Vector3T direction,
                               cSPVector3& hitPoint, cSPVector3& hitNormal, int* triangleIndex,
                               bool& useHull, cMWPickInfo::tLevel* level);      // @ 0x4a4840
    void TransformVertices(cSPTransform& transform, cModelVertexData* vertices); // @ 0x49ef80
    cSPMatrix3 GetTriangleOrientation(cSPVector3 a, Vector3T b, Vector3T c);   // @ 0x499f10
    cSPVector3 CalculateBarycentricCoordinates(cSPVector3 a, Vector3T b, Vector3T c,
                                               cSPVector3 point);               // @ 0x499b40
}
inline bool IsNaN(float f) { return (*(uint32_t*)&f & 0x7fffffff) > 0x7f800000; }
inline bool IsNAN(const cSPVector3& v) { return IsNaN(v.x) || IsNaN(v.y) || IsNaN(v.z); }  // @ 0x481f00
extern int kMaxPickAttempts;                                                    // @ 0x150c4d0

struct cSPEditorTrianglePinningInfo {
    cSPEditorBlock* mTriangleOwner;             // +0x188
    AutoRefCount<cIModelTriangle> mTriangle;    // +0x18c
    cSPVector3 mPositionOffset;                 // +0x190
    cSPVector3 mBarycentricCoordinate;          // +0x19c
};

struct cSPEditorHandleDeform {
    void* mpVtbl;
    void* mpVtbl2;                              // +0x04
    int mRefCount;                              // +0x08
    void* mPropList;                            // +0x0c
    cSPEditorBlock* mBlock;                     // +0x10
    char pad14[0xac - 0x14];
    uint32_t mPinningType;                      // +0xac
    char padb0[0xb8 - 0xb0];
    cSPVector3 mPickOrigin;                     // +0xb8
    cSPVector3 mPickDirection;                  // +0xc4
    char padd0[0xe8 - 0xd0];
    cSPVector3 mHandleStartLocal;               // +0xe8
    cSPVector3 mHandleEndLocal;                 // +0xf4
    cSPVector3 mBlockPositionForPicking;        // +0x100
    cSPVector3 mBlockPickReference;             // +0x10c
    char pad118[0x138 - 0x118];
    cSPVector3 mTriangleHitPoint;               // +0x138
    cSPVector3 mDirectionAxis;                  // +0x144
    Vector3T mOriginalTriangleDirection;        // +0x150
    cSPVector3 mStartOffset;                    // +0x15c
    char pad168[0x174 - 0x168];
    Vector3T mBasePositionOffset;               // +0x174
    char pad180[0x188 - 0x180];
    cSPEditorTrianglePinningInfo mTriangleInfo; // +0x188

    void SetPickData();                                                         // @ 0x480cf0
    void SetPickOffset(float offset);                                           // @ 0x4809c0
    bool RecordHandlePosition(bool pickGeometry);
};

// @ 0x00480e90
bool cSPEditorHandleDeform::RecordHandlePosition(bool pickGeometry)
{
    cSPTransform oldTransform(mBlock->GetModel()->mTransform);
    ScratchSlots<1>();
    mBlock->GetModel()->mTransform.Reset();
    SetPickData();

    int pickTriangleIndex = -1;
    bool hitHull = false;
    if (IsNAN(mPickDirection) || mPickDirection.SquaredLength() < 0.9f)
        pickGeometry = false;

    cIModelWorld* modelWorld = mBlock->GetModelWorld();
    cMWModel* modelPtr = mBlock->GetModel();
    cSPVector3 contactPoint;
    if (pickGeometry) {
        BlockVector pickList;
        pickList.push_back(AutoRefCount<cSPEditorBlock>(mBlock));
        int status;      // declared but never used (a 4-byte gap in the original frame)
        cSPBoundingBox aabb = mBlock->GetBBox(0, false, false);
        cMWPickInfo::tLevel detail = cMWPickInfo::kLevel4;
        int retries = 0;
        float step = 0.05f;
        cSPEditorBlock* pickedBlock = 0;
        cSPVector3 hitNorm;
        while (pickedBlock == 0 && retries < kMaxPickAttempts) {
            pickedBlock = EditorUtils::PickBlocks(pickList, mPickOrigin, mPickDirection, contactPoint, hitNorm,
                                                  &pickTriangleIndex, hitHull, &detail);
            if (pickedBlock == 0)
                SetPickOffset(step);
            step = step * 2.0f;
            retries++;
        }
        if (pickedBlock != 0 && modelPtr != 0 && modelWorld != 0) {
            modelWorld->GetTriangle(modelPtr, pickTriangleIndex, mTriangleInfo.mTriangle.ReleaseAndGetAddressOf(),
                                    hitHull);
        } else {
            mTriangleInfo.mTriangle = 0;
        }
    }

    cIModelTriangle* triangle = mTriangleInfo.mTriangle;
    if (triangle) {
        mTriangleInfo.mTriangleOwner = mBlock;
        cModelVertexData vertexData[3];
        triangle->GetVertices(vertexData);
        EditorUtils::TransformVertices(mBlock->GetGeometryTransform(), vertexData);
        cMWModel* blockModel = mBlock->GetModel();
        cSPMatrix3 triangleRotation = EditorUtils::GetTriangleOrientation(
            vertexData[0].mPosition, vertexData[1].mPosition, vertexData[2].mPosition);

        if (pickGeometry) {
            cSPPlane trianglePlane(vertexData[0].mPosition, triangleRotation.yAxis);
            float rayT;
            bool hit = RayPlaneIntersect(mPickOrigin, mPickDirection, trianglePlane, &rayT);
            cSPVector3 baryCoords = EditorUtils::CalculateBarycentricCoordinates(
                vertexData[0].mPosition, vertexData[1].mPosition, vertexData[2].mPosition, contactPoint);
            cSPVector3 computedPoint = Vec3Add(Vec3Add(Vec3Scale(vertexData[0].mPosition, baryCoords[0]),
                                                       Vec3Scale(vertexData[1].mPosition, baryCoords[1])),
                                               Vec3Scale(vertexData[2].mPosition, baryCoords[2]));
            mTriangleInfo.mBarycentricCoordinate = baryCoords;
        }

        contactPoint = Vec3Add(Vec3Add(Vec3Scale(vertexData[0].mPosition, mTriangleInfo.mBarycentricCoordinate[0]),
                                       Vec3Scale(vertexData[1].mPosition, mTriangleInfo.mBarycentricCoordinate[1])),
                               Vec3Scale(vertexData[2].mPosition, mTriangleInfo.mBarycentricCoordinate[2]));

        cSPMatrix3 rotMatrix(triangleRotation);
        cSPVector3 anchorPoint = contactPoint;
        cSPVector3 basePositionOffset = mBasePositionOffset;
        mBlockPositionForPicking = basePositionOffset;

        mStartOffset = Vec3MulMatA(Vec3Sub(mHandleStartLocal, anchorPoint), Mat3Transpose(rotMatrix));
        if (mPinningType == 0x11f10cfa || mPinningType == 0x9e6e561c) {
            mDirectionAxis = Vec3Sub(mHandleStartLocal, anchorPoint);
            mHandleEndLocal = Vec3Sub(mBlockPositionForPicking, anchorPoint);
        } else {
            mDirectionAxis = Vec3MulMatA(Vec3Sub(mHandleStartLocal, anchorPoint), Mat3Transpose(rotMatrix));
            mHandleEndLocal = Vec3MulMatA(Vec3Sub(mBlockPositionForPicking, anchorPoint), Mat3Transpose(rotMatrix));
        }

        cSPVector3 startDir = Vec3MulMatB(Vec3Sub(mBlockPickReference, mHandleStartLocal), Mat3Transpose(rotMatrix));
        mOriginalTriangleDirection = Vec3Normalize(startDir);
        ScratchSlots<5>();
        mTriangleHitPoint = anchorPoint;
        Vec3C handleEndWorld(Vec3Add(Vec3MulMat(mHandleEndLocal, rotMatrix), anchorPoint));

        mBlock->GetModel()->mTransform = oldTransform;
        return true;
    } else {
        mBlock->GetModel()->mTransform = oldTransform;
        return false;
    }
}

}  // namespace SP
