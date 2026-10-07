// Slice s006eed00 — `anonymous namespace'::CreateTestModel (3213 bytes).
// Builds a 2x2x2 cube (24 vertices "V3FN3F": position + normal, 36 indices),
// wraps it in an rw::graphics::Mesh with a test material and returns a new,
// AddRef'd SP::cEffectsModel.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
};

// Dynamically initialized unit axes (.bss 0x01618db4 / 0x01618e3c / 0x01618e48).
extern Vector3 kZAxis;
extern Vector3 kXAxis;
extern Vector3 kYAxis;

namespace rw { namespace graphics {

struct VertexDescriptor {
    VertexDescriptor* m_nextParent;
    VertexDescriptor* m_nextSibling;
    void* m_vertexDeclaration;
    unsigned short m_numElements;
    unsigned char m_lockFlags;
    unsigned char m_stride;       // +0xf
};

struct VertexBuffer;

// Generic strided element iterator.
struct VertexElementIterator {
    char* mpData;
    uint32_t mStride;
    template <class T> T& Get() { return *(T*)mpData; }
    void operator++() { mpData += mStride; }
};

struct LockedVertexBuffer {
    void* mpData;
    VertexBuffer* mpVB;
    void GetElementIterator(VertexElementIterator& out, int element);   // 011f9ae0
};

struct VertexBuffer {
    VertexDescriptor* m_desc;
    void* m_d3dVB;
    uint32_t m_base;          // +0x8
    uint32_t m_numVertices;   // +0xc

    void* Lock(uint32_t flags, uint32_t offset, uint32_t size);   // 011f3620
    void Unlock();                                                // 011f36a0

    VertexBuffer* Lock(uint32_t flags, LockedVertexBuffer& out, uint32_t first = 0, uint32_t count = 0)
    {
        if (count == 0)
            count = m_numVertices;
        uint8_t stride = m_desc->m_stride;
        void* p = Lock(flags, (m_base + first) * stride, stride * count);
        if (p == 0)
            return 0;
        out.mpData = p;
        out.mpVB = this;
        return this;
    }
};

struct LockedIndexBuffer {
    uint16_t* mpData;
    uint32_t mFormat;
    uint32_t mFlags;
};

struct IndexBuffer {
    void* m_d3dIB;
    uint32_t m_base;
    uint32_t m_numIndices;    // +0x8
    int Lock(uint32_t flags, LockedIndexBuffer* out);     // 011f4f20
    int Unlock(LockedIndexBuffer* lock);                  // 011f4fd0
};

struct Mesh {
    void SetIndexBuffer(IndexBuffer* ib);                 // 011f96e0
    void SetIndexCount(uint32_t n);                       // 011f96b0
    void SetVertexBuffer(int stream, VertexBuffer* vb);   // 011f9670
};

}} // namespace rw::graphics

using rw::graphics::VertexBuffer;
using rw::graphics::IndexBuffer;
using rw::graphics::Mesh;

struct IndexBufferDesc;
extern IndexBufferDesc g_IndexBufferDesc;   // 0x015d07b0

rw::graphics::VertexDescriptor* GetVertexDescriptor(const char* name);                    // 007625d0
VertexBuffer* CreateVertexBuffer(rw::graphics::VertexDescriptor* d, int n, int a, int b);  // 00762b70
IndexBuffer* CreateIndexBuffer(IndexBufferDesc* d, int a, int n, int b, int c, int e);     // 00762c60

namespace SP {
class cMaterial;
class IMaterialManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual cMaterial* GetMaterial(uint32_t id);   // +0x28
};
IMaterialManager* MaterialManager();   // 0067dd70
Mesh* CreateMesh(int n);               // 00761840

struct cBoundingBox {
    Vector3 mLower;
    Vector3 mUpper;
    cBoundingBox(float x0, float y0, float z0, float x1, float y1, float z1)
        : mLower(x0, y0, z0), mUpper(x1, y1, z1) {}
};

class cEffectsModel {
public:
    void* vftable;
    int mnRefCount;   // +0x4
    uint32_t mPad[0x24];   // retail size 0x98
    cEffectsModel(int count, Mesh** meshes, cMaterial** materials, const cBoundingBox& bbox);   // 006ed8d0
    void AddRef() { mnRefCount++; }
};
} // namespace SP

void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void* p, const char* name, int flags, unsigned debugFlags, const char* file, int line);

namespace {

SP::cEffectsModel* CreateTestModel()
{
    rw::graphics::VertexDescriptor* pDesc = GetVertexDescriptor("V3FN3F");
    VertexBuffer* pVB = CreateVertexBuffer(pDesc, 24, 0, 0);

    rw::graphics::LockedVertexBuffer lock;
    pVB = pVB->Lock(2, lock);

    rw::graphics::VertexElementIterator pos;
    pos.mpData = (char*)lock.mpData;
    pos.mStride = lock.mpVB->m_desc->m_stride;
    rw::graphics::VertexElementIterator nrm;
    lock.GetElementIterator(nrm, 1);

    const Vector3 c[8] = {
        Vector3(-1.0f, -1.0f, -1.0f),
        Vector3( 1.0f, -1.0f, -1.0f),
        Vector3(-1.0f,  1.0f, -1.0f),
        Vector3( 1.0f,  1.0f, -1.0f),
        Vector3(-1.0f, -1.0f,  1.0f),
        Vector3( 1.0f, -1.0f,  1.0f),
        Vector3(-1.0f,  1.0f,  1.0f),
        Vector3( 1.0f,  1.0f,  1.0f),
    };

    // -Z face
    pos.Get<Vector3>() = c[1]; ++pos; nrm.Get<Vector3>() = -kZAxis; ++nrm;
    pos.Get<Vector3>() = c[0]; ++pos; nrm.Get<Vector3>() = -kZAxis; ++nrm;
    pos.Get<Vector3>() = c[3]; ++pos; nrm.Get<Vector3>() = -kZAxis; ++nrm;
    pos.Get<Vector3>() = c[2]; ++pos; nrm.Get<Vector3>() = -kZAxis; ++nrm;
    // +Z face
    pos.Get<Vector3>() = c[4]; ++pos; nrm.Get<Vector3>() = kZAxis; ++nrm;
    pos.Get<Vector3>() = c[5]; ++pos; nrm.Get<Vector3>() = kZAxis; ++nrm;
    pos.Get<Vector3>() = c[6]; ++pos; nrm.Get<Vector3>() = kZAxis; ++nrm;
    pos.Get<Vector3>() = c[7]; ++pos; nrm.Get<Vector3>() = kZAxis; ++nrm;
    // -X face
    pos.Get<Vector3>() = c[0]; ++pos; nrm.Get<Vector3>() = -kXAxis; ++nrm;
    pos.Get<Vector3>() = c[4]; ++pos; nrm.Get<Vector3>() = -kXAxis; ++nrm;
    pos.Get<Vector3>() = c[2]; ++pos; nrm.Get<Vector3>() = -kXAxis; ++nrm;
    pos.Get<Vector3>() = c[6]; ++pos; nrm.Get<Vector3>() = -kXAxis; ++nrm;
    // +X face
    pos.Get<Vector3>() = c[5]; ++pos; nrm.Get<Vector3>() = kXAxis; ++nrm;
    pos.Get<Vector3>() = c[1]; ++pos; nrm.Get<Vector3>() = kXAxis; ++nrm;
    pos.Get<Vector3>() = c[7]; ++pos; nrm.Get<Vector3>() = kXAxis; ++nrm;
    pos.Get<Vector3>() = c[3]; ++pos; nrm.Get<Vector3>() = kXAxis; ++nrm;
    // -Y face
    pos.Get<Vector3>() = c[0]; ++pos; nrm.Get<Vector3>() = -kYAxis; ++nrm;
    pos.Get<Vector3>() = c[1]; ++pos; nrm.Get<Vector3>() = -kYAxis; ++nrm;
    pos.Get<Vector3>() = c[4]; ++pos; nrm.Get<Vector3>() = -kYAxis; ++nrm;
    pos.Get<Vector3>() = c[5]; ++pos; nrm.Get<Vector3>() = -kYAxis; ++nrm;
    // +Y face
    pos.Get<Vector3>() = c[3]; ++pos; nrm.Get<Vector3>() = kYAxis; ++nrm;
    pos.Get<Vector3>() = c[2]; ++pos; nrm.Get<Vector3>() = kYAxis; ++nrm;
    pos.Get<Vector3>() = c[7]; ++pos; nrm.Get<Vector3>() = kYAxis; ++nrm;
    pos.Get<Vector3>() = c[6]; ++pos; nrm.Get<Vector3>() = kYAxis; ++nrm;

    pVB->Unlock();

    IndexBuffer* pIB = CreateIndexBuffer(&g_IndexBufferDesc, 2, 36, 8, 4, 0);
    rw::graphics::LockedIndexBuffer ilock;
    pIB->Lock(2, &ilock);
    uint16_t* idx = ilock.mpData;
    idx[0]  = 0;  idx[1]  = 1;  idx[2]  = 2;  idx[3]  = 2;  idx[4]  = 1;  idx[5]  = 3;
    idx[6]  = 4;  idx[7]  = 5;  idx[8]  = 6;  idx[9]  = 6;  idx[10] = 5;  idx[11] = 7;
    idx[12] = 8;  idx[13] = 9;  idx[14] = 10; idx[15] = 10; idx[16] = 9;  idx[17] = 11;
    idx[18] = 12; idx[19] = 13; idx[20] = 14; idx[21] = 14; idx[22] = 13; idx[23] = 15;
    idx[24] = 16; idx[25] = 17; idx[26] = 18; idx[27] = 18; idx[28] = 17; idx[29] = 19;
    idx[30] = 20; idx[31] = 21; idx[32] = 22; idx[33] = 22; idx[34] = 21; idx[35] = 23;
    pIB->Unlock(&ilock);

    Mesh* pMesh = SP::CreateMesh(1);
    pMesh->SetIndexBuffer(pIB);
    pMesh->SetIndexCount(pIB->m_numIndices);
    pMesh->SetVertexBuffer(0, pVB);

    SP::cMaterial* pMaterial = SP::MaterialManager()->GetMaterial(0x9473a597);

    SP::cEffectsModel* pModel = new ("Graphics", 0, 0, 0, 0) SP::cEffectsModel(1, &pMesh, &pMaterial,
        SP::cBoundingBox(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f));
    pModel->AddRef();
    return pModel;
}

} // namespace

// Keep the anonymous-namespace function emitted.
SP::cEffectsModel* CreateTestModel_ref() { return CreateTestModel(); }
