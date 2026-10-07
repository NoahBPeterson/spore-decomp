// Slice s004655e0: (anonymous namespace)::cBlockGeometryExporter::BuildBoundingBoxGeometry
// (SPBake/SPEditorExportUtilities.cpp; dev-PDB name and class layout).  Unoptimized editor module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

namespace rw { namespace math { namespace fpu {
template<class T, int N> struct Vector3Template {
    T x, y, z;
    Vector3Template() {}
    Vector3Template(const Vector3Template& v);                               // 0x004098a0
    // The original's inlined expansion of the copy constructor (cl /Ob1 expanded it at the first
    // five sites of this function and called it out of line at the other seven).
    void CopyConstructInline(const Vector3Template& v) { x = v.x; y = v.y; z = v.z; }
};
template<class T, int N> struct Matrix33Template {
    T m[9];
};
}}}

typedef rw::math::fpu::Vector3Template<float, 0> Vector3f;

struct cSPVector3 : Vector3f {
    cSPVector3() {}
    cSPVector3(const Vector3f& v) : Vector3f(v) {}
};
struct cSPVector2 {
    float x, y;
    static const cSPVector2 ZERO;                                        // 0x015d4104
};
struct cSPMatrix3 : rw::math::fpu::Matrix33Template<float, 0> {};

Vector3f operator-(const Vector3f& a, const Vector3f& b);                // 0x0041db10
Vector3f Cross(const Vector3f& a, const Vector3f& b);                    // 0x0044e460
cSPVector3 Normalize(const Vector3f& v);                                 // 0x00436ce0

struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
    void GetCorners(cSPVector3* corners) const;                          // 0x00466320
};

struct cSPTransform {
    uint16_t mFlags;                          // +0x00
    uint16_t mChangeCount;                    // +0x02
    cSPVector3 mPosition;                     // +0x04
    float mScale;                             // +0x10
    cSPMatrix3 mRotation;                     // +0x14
    cSPTransform();                                                      // 0x00409930
    void SetPosition(const cSPVector3& p) { mPosition = p; mFlags |= 4; mChangeCount++; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mChangeCount++; }
    void ApplyToPoint(cSPVector3& p) const;                              // 0x0044d4f0
};

namespace SP {
class cSPEditorBlock {
public:
    enum eBBoxType { kBBoxType0 = 0, kBBoxType1 = 1 };
    cSPBoundingBox GetBBox(eBBoxType type, bool a, bool b);              // 0x0044ae00
    uint8_t mPad[0x48];
    cSPVector3 mPosition;                     // +0x48
    uint8_t mPad1[0x60 - 0x54];
    cSPMatrix3 mOrientation;                  // +0x60
};
}

namespace eastl {
struct sp_vector_allocator { uint32_t mData[2]; };
template<class T, class A> class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    void push_back(const T& value);
};
}

namespace {

struct cBlockGeometryExporter {
    eastl::vector<unsigned int, eastl::sp_vector_allocator> mTriangleIndices;   // +0x00 (push_back 0x00454860)
    eastl::vector<cSPVector3, eastl::sp_vector_allocator> mPositions;           // +0x14 (push_back 0x004739d0)
    eastl::vector<cSPVector3, eastl::sp_vector_allocator> mNormals;             // +0x28
    eastl::vector<cSPVector2, eastl::sp_vector_allocator> mTextureCoordinates;  // +0x3c (push_back 0x00473f30)

    void BuildBoundingBoxGeometry(SP::cSPEditorBlock* block);
};

// @ 0x004655e0
void cBlockGeometryExporter::BuildBoundingBoxGeometry(SP::cSPEditorBlock* block)
{
    cSPVector3 corners[8];
    block->GetBBox(SP::cSPEditorBlock::kBBoxType1, false, false).GetCorners(corners);

    cSPTransform transform;
    transform.SetPosition(block->mPosition);
    transform.SetRotation(block->mOrientation);
    for (int i = 0; i < 8; i++) {
        transform.ApplyToPoint(corners[i]);
    }
    for (int j = 0; j < 24; j++) {
        mTextureCoordinates.push_back(cSPVector2::ZERO);
    }

    unsigned int baseIndex = 0;
    cSPVector3 normal;

    {
    // face 0-1-2-3
    mPositions.push_back(corners[0]);
    mPositions.push_back(corners[1]);
    mPositions.push_back(corners[2]);
    mPositions.push_back(corners[3]);
    cSPVector3 edgeA0;
    edgeA0.CopyConstructInline(corners[3] - corners[1]);
    cSPVector3 edgeB0;
    edgeB0.CopyConstructInline(corners[0] - corners[1]);
    normal = Normalize(Cross(edgeB0, edgeA0));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 1-5-3-7
    mPositions.push_back(corners[1]);
    mPositions.push_back(corners[5]);
    mPositions.push_back(corners[3]);
    mPositions.push_back(corners[7]);
    cSPVector3 edgeA1;
    edgeA1.CopyConstructInline(corners[7] - corners[5]);
    cSPVector3 edgeB1;
    edgeB1.CopyConstructInline(corners[1] - corners[5]);
    normal = Normalize(Cross(edgeB1, edgeA1));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 5-4-7-6
    mPositions.push_back(corners[5]);
    mPositions.push_back(corners[4]);
    mPositions.push_back(corners[7]);
    mPositions.push_back(corners[6]);
    cSPVector3 edgeA2;
    edgeA2.CopyConstructInline(corners[6] - corners[4]);
    cSPVector3 edgeB2 = corners[5] - corners[4];
    normal = Normalize(Cross(edgeB2, edgeA2));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 3-7-2-6
    mPositions.push_back(corners[3]);
    mPositions.push_back(corners[7]);
    mPositions.push_back(corners[2]);
    mPositions.push_back(corners[6]);
    cSPVector3 edgeA3 = corners[6] - corners[7];
    cSPVector3 edgeB3 = corners[3] - corners[7];
    normal = Normalize(Cross(edgeB3, edgeA3));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 4-0-6-2
    mPositions.push_back(corners[4]);
    mPositions.push_back(corners[0]);
    mPositions.push_back(corners[6]);
    mPositions.push_back(corners[2]);
    cSPVector3 edgeA4 = corners[2] - corners[0];
    cSPVector3 edgeB4 = corners[4] - corners[0];
    normal = Normalize(Cross(edgeB4, edgeA4));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 0-4-1-5
    mPositions.push_back(corners[0]);
    mPositions.push_back(corners[4]);
    mPositions.push_back(corners[1]);
    mPositions.push_back(corners[5]);
    cSPVector3 edgeA5 = corners[5] - corners[4];
    cSPVector3 edgeB5 = corners[0] - corners[4];
    normal = Normalize(Cross(edgeB5, edgeA5));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }
}

} // anonymous namespace

// Keep the anonymous-namespace member emitted.
void BuildBoundingBoxGeometry_ref(void* exporter, SP::cSPEditorBlock* block)
{
    ((cBlockGeometryExporter*)exporter)->BuildBoundingBoxGeometry(block);
}
