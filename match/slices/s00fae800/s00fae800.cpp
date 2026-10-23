// Retail terrain decal / terrain quad methods, 0x00fae800 .. 0x00faf4db.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast  (retail float math is SSE scalar:
// movss/addss/mulss/comiss, and never promotes to double, so /fp:fast is required).
//
// Layouts come from the 2008 dev-build PDB (tools/pdb_type.py, symbols/pdb_names.json)
// plus the shifts the retail build applies:
//
//   SP::cTerrainSphereDecal : SP::cTerrainDecal : EA::Swarm::cDecal
//       The dev base starts with cDecal::mTransform at +0; retail inserts a vtable
//       pair at the front, so mTransform sits at +0x8 (its mRotation at +0x1c) and
//       every cDecal/cTerrainDecal field is +8.  The cTerrainSphereDecal fields
//       (mRefCount, mpParentSphere, mpTerrainMapSet, mFaceArray) stay at their dev
//       offsets (+0x74/+0x78/+0x7c/+0x80); mPosition and everything after it is +4
//       (dev +0x90 -> retail +0x94) because retail inserts four bytes at +0x90.
//       0x00fae800 reads +0x50 as an angle (cDecal::mTurns), +0x54 as a scale
//       (cDecal::mAspect) and +0x70 as the decal type (cTerrainDecal::mType, == 9
//       selects the "no aspect" path), which pins those three shifts.
//
//   SP::cTerrainSphereQuad
//       Keeps the dev prefix exactly (mSphere +0, mParent +4, mChildren[4] +8,
//       mChunkRes +0x18, mFace +0x1c, mFaceMin +0x20, mFaceMax +0x28) but the
//       retail tail is rewritten: the atmosphere UV rect is at +0x58/+0x5c/+0x60,
//       a skip flag at +0x6c, the dirty flags at +0x90/+0x91, the atmosphere vertex
//       buffer slot at +0x94 and the above/below bit map at +0x170/+0x174/+0x178.
//
// The mesh pool functions (0x00faed90 .. 0x00faef90) drive the two global
// doubly-linked lists of terrain chunk vertex/index buffer pairs (the "above" and
// "below" water meshes) that live in the global array at 0x016ca640.
#include "types.h"
#include <string.h>
#include <math.h>

namespace rw { namespace graphics {

// rw::graphics::VertexDescriptor (dev PDB): the vertex stride is the byte at +0xf.
class VertexDescriptor {
public:
    VertexDescriptor* m_nextParent;       // +0x00
    VertexDescriptor* m_nextSibling;      // +0x04
    void*             m_vertexDeclaration;// +0x08
    unsigned short    m_numElements;      // +0x0c
    unsigned char     m_lockFlags;        // +0x0e
    unsigned char     m_stride;           // +0x0f
    unsigned int      m_elementsUsed;     // +0x10
    unsigned int      m_elementHash;      // +0x14
};

// rw::graphics::VertexBuffer (dev PDB, size 0x1c).
class VertexBuffer {
public:
    VertexDescriptor* m_desc;             // +0x00
    void*             m_d3dVB;            // +0x04
    unsigned int      m_base;             // +0x08
    unsigned int      m_numVertices;      // +0x0c
    unsigned int      m_usage;            // +0x10
    unsigned char     m_stride;           // +0x14
    unsigned char     m_lockFlags;        // +0x15
    unsigned short    m_pad0;             // +0x16
    void*             m_disposableBuffer; // +0x18

    void* D3D9Lock(unsigned int usage, unsigned int size1, unsigned int size2); // 0x011f3620
    VertexBuffer* Unlock();                                                     // 0x011f36a0
};

// rw::graphics::IndexBuffer (dev PDB, size 0x1c).
class IndexBuffer {
public:
    struct Locked { void* mpData; unsigned int mField4; unsigned int mField8; };

    void*         m_d3dIB;            // +0x00
    unsigned int  m_base;             // +0x04
    unsigned int  m_numIndices;       // +0x08
    unsigned int  m_usage;            // +0x0c
    unsigned int  m_fmt;              // +0x10
    unsigned int  m_primType;         // +0x14
    void*         m_disposableBuffer; // +0x18

    IndexBuffer* Lock(unsigned int count, Locked& out);  // 0x011f4f20
    IndexBuffer* Unlock(Locked& out);                    // 0x011f4fd0
};

// rw::graphics::Mesh : rw::graphics::EmbeddedMesh (dev PDB, size 0x28).
class Mesh {
public:
    unsigned int  m_instancedSize;    // +0x00
    unsigned int  m_primTypeCache;    // +0x04
    IndexBuffer*  m_indexBuffer;      // +0x08
    unsigned int  m_primCount;        // +0x0c
    unsigned int  m_numVertexBuffers; // +0x10
    unsigned int  m_start;            // +0x14
    unsigned int  m_numIndices;       // +0x18
    unsigned int  m_minVertex;        // +0x1c
    unsigned int  m_vertexRange;      // +0x20
    VertexBuffer* m_vertexBuffer[1];  // +0x24

    void SetVertexBuffer(unsigned int index, VertexBuffer* vb); // 0x011f9670
    void SetIndexBuffer(IndexBuffer* ib);                       // 0x011f96e0
    void SetNumIndices(unsigned int n);                         // 0x011f96b0
    void D3D9RecalculatePrimCount();                            // 0x011f9710
};

}}  // namespace rw::graphics

namespace rw { namespace math { namespace fpu {

// rw::math::fpu::Matrix33Template<float,0> (dev PDB, 0x24 bytes).  Its copy
// constructor is an out-of-line engine function (0x0041cb40); only the declaration
// is needed here.
template <class T, int Align>
struct Matrix33Template {
    T m[9];
    Matrix33Template(const Matrix33Template& other);  // 0x0041cb40
};

}}}  // namespace rw::math::fpu

namespace EA {

template <class T>
struct RectT {
    T x0;
    T y0;
    T x1;
    T y1;
};

}  // namespace EA

namespace SP {

using rw::graphics::IndexBuffer;
using rw::graphics::Mesh;
using rw::graphics::VertexBuffer;

struct cSPVector2 { float x; float y; };
struct cSPVector3 { float x; float y; float z; };

// cSPMatrix3 is the engine's rw::math::fpu::Matrix33Template<float,0>.
typedef rw::math::fpu::Matrix33Template<float, 0> cSPMatrix3;

// cSPTransform (dev PDB, size 0x38): two 16-bit flags then the translation, scale
// and rotation (the rotation at +0x14 is the cSPMatrix3 copy source).
struct cSPTransform {
    unsigned short mFlags;             // +0x00
    unsigned short mModificationCount; // +0x02
    cSPVector3     mTranslation;       // +0x04
    float          mScale;             // +0x10
    cSPMatrix3     mRotation;          // +0x14

    // 0x00537dc0 (cSPTransformOps::Assign): copies a transform, fixing up the
    // derived rotation/scale cache.
    cSPTransform& Assign(const void* src);
};

// The decal flag word at +0xb8.  Only the two bits the setup path touches are used
// here; the engine stores it as a bitset (bit 3 = "atmosphere/UV valid").
struct cDecalFlags {
    unsigned int mBits;  // +0x00
    bool test(int i) const { return ((mBits >> i) & 1) != 0; }
    void set(int i, bool v) {
        if (v)
            mBits |= (1u << i);
        else
            mBits &= ~(1u << i);
    }
};

// SP::cCubeMapCoord (dev PDB, size 0xc): a point on one cube face.
struct cCubeMapCoord {
    float mU;      // +0x0
    float mV;      // +0x4
    int   mFace;   // +0x8
};

// SP::cTerrainMapSet (dev PDB, size 0x5c); the decal code reads mRadius.
class cTerrainMapSet {
public:
    unsigned char mPad00[0x34];
    float mRadius;      // +0x34
    float mMaxHeight;   // +0x38
    float mWaterHeight; // +0x3c
    float mWaterDelta;  // +0x40
    float mBeachHeight; // +0x44
};

// The texture instance embedded at the end of the decal (0x00faec70 loads it with
// SP::GetImageResource, 0x00576650).
class cTextureInstance {
public:
    void GetImageResource(unsigned int id);  // 0x00576650
};

// SP::cTerrainSphere (vtable only used here): slot +0xc returns the map set,
// slot +0x10 returns the sphere's terrain info block.
class cTerrainSphere {
public:
    virtual void vtable00();
    virtual void vtable04();
    virtual void vtable08();
    virtual cTerrainMapSet* GetMapSet();   // +0x0c
    virtual void* GetInfo();               // +0x10

    void MergeFaceBox(unsigned int face, EA::RectT<float> box);  // 0x00f98620
};

// SP::cTerrainSphereDecal::tFaceInfo (dev PDB, size 0x14).
struct tFaceInfo {
    unsigned int       mFace;             // +0x00
    EA::RectT<float>   mBoundingBoxFace;  // +0x04
};

// SP::cTerrainSphereDecal : SP::cTerrainDecal : EA::Swarm::cDecal.
// Only the members these functions touch are spelled out; the gaps are the base
// classes' fields (see the file header for the retail shifts).
class cTerrainSphereDecal {
public:
    unsigned char mPad00[0x08];
    cSPTransform  mTransform;        // +0x08  (cDecal::mTransform)
    unsigned char mPad40[0x10];      // +0x40 .. cDecal::mColorAlpha region
    float         mTurns;            // +0x50  (cDecal::mTurns)
    float         mAspect;           // +0x54  (cDecal::mAspect)
    unsigned char mPad58[0x18];
    int           mType;             // +0x70  (cTerrainDecal::mType)
    unsigned int  mRefCount;         // +0x74
    cTerrainSphere* mpParentSphere;  // +0x78
    cTerrainMapSet* mpTerrainMapSet; // +0x7c
    tFaceInfo*    mFaceArrayBegin;   // +0x80
    tFaceInfo*    mFaceArrayEnd;     // +0x84
    unsigned char mPad88[0x0c];
    cCubeMapCoord mPosition;         // +0x94
    float         mUSize;            // +0xa0
    float         mVSize;            // +0xa4
    float         mUSizeInput;       // +0xa8
    float         mVSizeInput;       // +0xac
    float         mDecalRadius;      // +0xb0
    unsigned char mPadB4[0x04];
    cDecalFlags   mFlags;            // +0xb8
    unsigned char mPadBC[0x10];
    float         mTexXform[8];      // +0xcc  (the decal's projective texture transform)
    unsigned char mPadEC[0x3c];
    cTextureInstance mTexture;       // +0x128

    void UpdateDecalUV();                                             // 0x00fae800
    void SetupDecal(int id, unsigned int textureId, cTerrainSphere* sphere,
                    const cSPTransform* xf, float turns, bool flag);  // 0x00faec70
    void UpdateDecalShaderData(const cSPTransform* xf, float repeat); // 0x00fadc20
};

// SP::cTerrainSphereQuad.  The dev prefix is unchanged; the retail tail is the
// atmosphere / above-below-map bookkeeping.
class cTerrainSphereQuad {
public:
    cTerrainSphere*     mSphere;             // +0x00
    cTerrainSphereQuad* mParent;             // +0x04
    cTerrainSphereQuad* mChildren[4];        // +0x08
    int                 mChunkRes;           // +0x18
    int                 mFace;               // +0x1c
    cSPVector2          mFaceMin;            // +0x20
    cSPVector2          mFaceMax;            // +0x28
    float               mFaceScale;          // +0x30
    unsigned char       mPad34[0x24];
    float               mAtmoU0;             // +0x58
    float               mAtmoV0;             // +0x5c
    float               mAtmoStep;           // +0x60
    unsigned char       mPad64[0x08];
    bool                mAtmoSkip;           // +0x6c
    unsigned char       mPad6D[0x23];
    bool                mDirtyVertices;      // +0x90
    bool                mDirtyIndices;       // +0x91
    unsigned char       mPad92[0x02];
    VertexBuffer**      mAtmoVertexBuffer;   // +0x94
    unsigned char       mPad98[0xd8];
    unsigned int*       mAboveBelowMap;      // +0x170
    int                 mAboveBelowMapSize;  // +0x174
    int                 mAboveBelowMapStride;// +0x178

    void MarkVerticesDirty(int face, const float* box);    // 0x00faf140
    void MarkIndicesDirty(int face, const float* box);     // 0x00faf400
    bool BuildAtmosphereVertices();                        // 0x00faf220
    void ClearAboveBelowRange(int row, int col, int res);  // 0x00faf070
};

// One entry of the global terrain chunk mesh list: a vertex/index buffer pair with
// doubly-linked list pointers.
struct TerrainMeshSlot {
    VertexBuffer*    mpVertexBuffer;  // +0x00
    IndexBuffer*     mpIndexBuffer;   // +0x04
    TerrainMeshSlot* mpPrev;          // +0x08
    TerrainMeshSlot* mpNext;          // +0x0c
};

// The holder 0x00faeda0 / 0x00faeec0 / 0x00faed90 operate on: two pointers to the
// head and tail entries of the global slot array.
struct cTerrainMeshListHolder {
    TerrainMeshSlot* mpHeadA;  // +0x00  (&gTerrainMeshSlots[0])
    TerrainMeshSlot* mpHeadB;  // +0x04  (&gTerrainMeshSlots[0xBFF])
    int              mField8;  // +0x08
    int              mFieldC;  // +0x0c

    cTerrainMeshListHolder();            // 0x00faed90
    void Create(void* device, int res);  // 0x00faeda0
    void Destroy();                      // 0x00faeec0
};

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------
extern int  gIndexBufferDesc;                     // 0x015d07b0
extern void* gTerrainDeviceA;                     // 0x016c9e74
extern void* gTerrainDeviceB;                     // 0x016c9e6c
extern void* gTerrainDeviceC;                     // 0x016c9e3c
extern float gDecalAngleScale;                    // 0x016ca638
extern TerrainMeshSlot gTerrainMeshSlots[0xC00];  // 0x016ca640
extern IndexBuffer*  gTerrainAtmosphereIB;        // 0x016d6640
extern VertexBuffer* gTerrainAtmosphereVB;        // 0x016d6644
extern Mesh*         gTerrainAtmosphereMesh;      // 0x016d6648

// ---------------------------------------------------------------------------
// Engine helpers (defined elsewhere)
// ---------------------------------------------------------------------------
Mesh* CreateMesh(int flags);                              // 0x00761840
VertexBuffer* CreateVertexBuffer(void* device, unsigned int numVertices,
                                 unsigned int a, unsigned int b);  // 0x00762b70
IndexBuffer* CreateIndexBuffer(void* desc, unsigned int numIndices,
                               unsigned int maxIndex, unsigned int a,
                               unsigned int b, unsigned int c);    // 0x00762c60
void DestroyVertexBuffer(VertexBuffer* vb);                // 0x00762a00
void DestroyIndexBuffer(IndexBuffer* ib);                  // 0x00762a30

// 0x00fad1d0: cdecl, normalises the decal transform before the UV maths.
void FixupDecalTransform(cSPTransform* xf);
// 0x00685200: cdecl, folds a cube face's (u,v) back into range.  Its first argument
// points at the face index that follows the (u,v) pair inside a cCubeMapCoord.
void MapCubeFaceUV(int* face, float* u, float* v, int a, int b, int c);

// 0x00faef10: binds a vertex/index buffer pair to the global atmosphere mesh.
void __stdcall SetupTerrainMesh(VertexBuffer* vb, IndexBuffer* ib,
                                unsigned int start, unsigned int numIndices);
// 0x00faef90: lazily builds the global terrain atmosphere mesh.
void InitTerrainAtmosphereMesh();
// 0x00faf100: moves 200-byte terrain records backwards.
void ShiftTerrainRecords(void* srcBegin, void* srcEnd, void* dstEnd);

}  // namespace SP

// ---------------------------------------------------------------------------
// 0x00faed90: zero-initialises the terrain mesh list holder.
// @ 0x00faed90
SP::cTerrainMeshListHolder::cTerrainMeshListHolder()
{
    mpHeadA = 0;
    mpHeadB = 0;
    mField8 = 0;
    mFieldC = 0;
}

// ---------------------------------------------------------------------------
// 0x00faf100: moves 200-byte terrain records backwards (a memmove that copies from
// the end down to the start so overlapping ranges are safe).
// @ 0x00faf100
void SP::ShiftTerrainRecords(void* srcBegin, void* srcEnd, void* dstEnd)
{
    while (srcEnd != srcBegin) {
        srcEnd = (char*)srcEnd - 200;
        dstEnd = (char*)dstEnd - 200;
        memcpy(dstEnd, srcEnd, 200);
    }
}

// ---------------------------------------------------------------------------
// 0x00faeec0: frees every vertex/index buffer pair in the global slot list and
// clears the holder.
// @ 0x00faeec0
void SP::cTerrainMeshListHolder::Destroy()
{
    IndexBuffer** pp = &SP::gTerrainMeshSlots[0].mpIndexBuffer;
    do {
        if (pp[-1])
            DestroyVertexBuffer((VertexBuffer*)pp[-1]);
        pp[-1] = 0;
        if (*pp)
            DestroyIndexBuffer(*pp);
        *pp = 0;
        pp += 4;
    } while ((int)pp < (int)&SP::gTerrainMeshSlots[0xC00].mpIndexBuffer);

    mpHeadA = 0;
    mpHeadB = 0;
    mField8 = 0;
    mFieldC = 0;
}

// ---------------------------------------------------------------------------
// 0x00faef10: rebinds the global terrain mesh to a new vertex/index buffer pair.
// @ 0x00faef10
void __stdcall SP::SetupTerrainMesh(VertexBuffer* vb, IndexBuffer* ib,
                                   unsigned int start, unsigned int numIndices)
{
    SP::gTerrainAtmosphereMesh->SetIndexBuffer(ib);
    Mesh* mesh = SP::gTerrainAtmosphereMesh;
    unsigned int numVertices = vb->m_numVertices;
    mesh->m_minVertex = 0;
    mesh->m_vertexRange = numVertices;
    SP::gTerrainAtmosphereMesh->SetVertexBuffer(0, vb);
    SP::gTerrainAtmosphereMesh->SetVertexBuffer(1, (VertexBuffer*)SP::gTerrainDeviceC);
    SP::gTerrainAtmosphereMesh->SetNumIndices(numIndices);
    SP::gTerrainAtmosphereMesh->m_start = start;
    SP::gTerrainAtmosphereMesh->D3D9RecalculatePrimCount();
}

// ---------------------------------------------------------------------------
// 0x00faf070: clears one run of the above/below water bit map for a row of the
// quad's chunk grid.
// @ 0x00faf070
void SP::cTerrainSphereQuad::ClearAboveBelowRange(int row, int col, int res)
{
    int i = col * res + 1;
    int end = i + res;
    if (i >= end)
        return;

    int rowShift = row * res + 1;
    unsigned int clearMask = ~(((1 << res) - 1) << (rowShift % 32));
    int shift = rowShift / 32;

    do {
        int index = mAboveBelowMapStride * i + shift;
        ++i;
        mAboveBelowMap[index] &=
            mAboveBelowMap[mAboveBelowMapSize / 2 + index] | clearMask;
    } while (i < end);
}

// ---------------------------------------------------------------------------
// 0x00faf140: marks the quads that overlap a face-space box as having dirty
// vertices, descending the quad tree.
// @ 0x00faf140
void SP::cTerrainSphereQuad::MarkVerticesDirty(int face, const float* box)
{
    if (face != mFace)
        return;

    float cx = (mFaceMin.x + mFaceMax.x) * 0.5f;
    float cy = (mFaceMin.y + mFaceMax.y) * 0.5f;

    if (cx > box[0]) {
        if (cy > box[1] && mChildren[0])
            mChildren[0]->MarkVerticesDirty(face, box);
        if (box[3] >= cy && mChildren[2])
            mChildren[2]->MarkVerticesDirty(face, box);
    }
    if (box[2] >= cx) {
        if (cy > box[1] && mChildren[1])
            mChildren[1]->MarkVerticesDirty(face, box);
        if (box[3] >= cy && mChildren[3])
            mChildren[3]->MarkVerticesDirty(face, box);
    }
    mDirtyVertices = true;
}

// ---------------------------------------------------------------------------
// 0x00faf400: as above but for the index buffer, and only while the quad is still
// in its "atmosphere built" state (the byte at +0x6c).
// @ 0x00faf400
void SP::cTerrainSphereQuad::MarkIndicesDirty(int face, const float* box)
{
    if (face != mFace)
        return;
    if (mAtmoSkip != 0)
        return;

    float cx = (mFaceMin.x + mFaceMax.x) * 0.5f;
    float cy = (mFaceMin.y + mFaceMax.y) * 0.5f;

    if (cx > box[0]) {
        if (cy > box[1] && mChildren[0])
            mChildren[0]->MarkIndicesDirty(face, box);
        if (box[3] >= cy && mChildren[2])
            mChildren[2]->MarkIndicesDirty(face, box);
    }
    if (box[2] >= cx) {
        if (cy > box[1] && mChildren[1])
            mChildren[1]->MarkIndicesDirty(face, box);
        if (box[3] >= cy && mChildren[3])
            mChildren[3]->MarkIndicesDirty(face, box);
    }
    mDirtyIndices = true;
}

// ---------------------------------------------------------------------------
// 0x00faef90: lazily creates the global terrain atmosphere mesh (a one-triangle
// mesh used to draw the atmosphere shell over each chunk).
// @ 0x00faef90
void SP::InitTerrainAtmosphereMesh()
{
    if (SP::gTerrainAtmosphereMesh != 0)
        return;

    SP::gTerrainAtmosphereMesh = CreateMesh(2);

    VertexBuffer* secondVB = (VertexBuffer*)SP::gTerrainDeviceB;
    SP::gTerrainAtmosphereVB = CreateVertexBuffer(SP::gTerrainDeviceA, 3, 0, 0);
    SP::gTerrainAtmosphereIB = CreateIndexBuffer(&SP::gIndexBufferDesc, 1, 3, 8, 4, 0);

    IndexBuffer::Locked locked;
    SP::gTerrainAtmosphereIB->Lock(2, locked);
    unsigned short* indices = (unsigned short*)locked.mpData;
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    SP::gTerrainAtmosphereIB->Unlock(locked);

    Mesh* mesh = SP::gTerrainAtmosphereMesh;
    mesh->m_minVertex = 0;
    mesh->m_vertexRange = SP::gTerrainAtmosphereVB->m_numVertices;
    SP::gTerrainAtmosphereMesh->SetVertexBuffer(0, SP::gTerrainAtmosphereVB);
    SP::gTerrainAtmosphereMesh->SetVertexBuffer(1, secondVB);
    SP::gTerrainAtmosphereMesh->SetIndexBuffer(SP::gTerrainAtmosphereIB);
}

// ---------------------------------------------------------------------------
// 0x00faeda0: fills the global terrain chunk mesh slot array: one vertex/index
// buffer pair per chunk resolution step, wired into a doubly-linked list whose
// head/tail entries are the two ends of the array.
// @ 0x00faeda0
void SP::cTerrainMeshListHolder::Create(void* device, int res)
{
    int numVertices = (res + 3) * (res + 3);
    int numIndices = (res + 2) * (res + 2) * 6;
    int numPrimitives = numIndices / 3;

    mpHeadA = &SP::gTerrainMeshSlots[0];
    SP::gTerrainMeshSlots[0].mpPrev = 0;
    SP::gTerrainMeshSlots[0].mpNext = &SP::gTerrainMeshSlots[1];
    SP::gTerrainMeshSlots[0].mpVertexBuffer =
        CreateVertexBuffer(device, numVertices, 0, 0);
    SP::gTerrainMeshSlots[0].mpIndexBuffer =
        CreateIndexBuffer(&SP::gIndexBufferDesc, numPrimitives, numIndices, 8, 4, 0);

    mpHeadB = &SP::gTerrainMeshSlots[0xBFF];
    SP::gTerrainMeshSlots[0xBFF].mpPrev = &SP::gTerrainMeshSlots[0xBFE];
    SP::gTerrainMeshSlots[0xBFF].mpNext = 0;
    SP::gTerrainMeshSlots[0xBFF].mpVertexBuffer =
        CreateVertexBuffer(device, numVertices, 0, 0);
    SP::gTerrainMeshSlots[0xBFF].mpIndexBuffer =
        CreateIndexBuffer(&SP::gIndexBufferDesc, numPrimitives, numIndices, 8, 4, 0);

    TerrainMeshSlot* slot = &SP::gTerrainMeshSlots[1];
    do {
        slot->mpVertexBuffer = CreateVertexBuffer(device, numVertices, 0, 0);
        slot->mpIndexBuffer =
            CreateIndexBuffer(&SP::gIndexBufferDesc, numPrimitives, numIndices, 8, 4, 0);
        slot->mpPrev = slot - 1;
        slot->mpNext = slot + 1;
        ++slot;
    } while (slot < &SP::gTerrainMeshSlots[0xBFF]);

    mField8 = 0;
    mFieldC = 0;
}

// ---------------------------------------------------------------------------
// 0x00faec70: points the decal at its texture, parent sphere and transform, then
// (if the "valid" flag bit was set) refreshes the UV transform and merges the
// decal's face boxes into the sphere.
// @ 0x00faec70
void SP::cTerrainSphereDecal::SetupDecal(int id, unsigned int textureId,
                                         cTerrainSphere* sphere,
                                         const cSPTransform* xf, float turns,
                                         bool flag)
{
    mRefCount = (unsigned int)id;
    mTexture.GetImageResource(textureId);
    mpParentSphere = sphere;
    mpTerrainMapSet = sphere->GetMapSet();
    mTransform.Assign(xf);
    mTurns = turns;

    mFlags.set(3, flag);
    mFlags.set(1, false);

    if (mFlags.test(3)) {
        UpdateDecalUV();
        for (int i = 0; i < (int)(mFaceArrayEnd - mFaceArrayBegin); ++i) {
            if (mpParentSphere->GetMapSet())
                mpParentSphere->MergeFaceBox(mFaceArrayBegin[i].mFace,
                                             mFaceArrayBegin[i].mBoundingBoxFace);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00faf220: fills the quad's atmosphere vertex buffer with the (mChunkRes+3)^2
// grid of cube-map coordinates covering the quad's face patch.  Every vertex is
// the same packed value (the coordinate is generated for the cube map lookup
// only), and each row/column step is 1/mChunkRes.
// @ 0x00faf220
bool SP::cTerrainSphereQuad::BuildAtmosphereVertices()
{
    VertexBuffer* vb = *mAtmoVertexBuffer;
    unsigned char stride = vb->m_desc->m_stride;

    unsigned int* data = (unsigned int*)vb->D3D9Lock(
        10, (unsigned int)stride * vb->m_base,
        (unsigned int)stride * vb->m_numVertices);
    if (!data)
        return false;

    int n = mChunkRes + 3;
    unsigned char step2 = vb->m_desc->m_stride;

    mSphere->GetMapSet();
    mSphere->GetMapSet();
    mSphere->GetInfo();

    float step = 1.0f / (float)mChunkRes;
    float negStep = -step;
    float v = negStep;

    if (n > 0) {
        do {
            float u = negStep;
            int cols = n;
            do {
                cCubeMapCoord coord;
                coord.mU = mAtmoStep * u + mAtmoU0;
                coord.mV = mAtmoStep * v + mAtmoV0;
                coord.mFace = mFace;
                if (coord.mU < 0.0f || coord.mV < 0.0f ||
                    coord.mU > 1.0f || coord.mV > 1.0f) {
                    MapCubeFaceUV(&coord.mFace, &coord.mU, &coord.mV, 0, 0, 0);
                }

                // both halves of the packed atmosphere vertex carry the same
                // biased fixed-point cube map coordinate
                unsigned short packed = (unsigned short)((int)coord.mU + 0x8000);
                *data = ((unsigned int)packed << 16) | (unsigned int)packed;

                data = (unsigned int*)((char*)data + step2);
                u += step;
            } while (--cols);
            v += step;
        } while (--n);
    }

    (*mAtmoVertexBuffer)->Unlock();
    return true;
}

// ---------------------------------------------------------------------------
// 0x00fae800: recomputes the decal's cube-map position and its projective texture
// transform from the parent sphere's radius and the decal's orientation, and (when
// anything changed) hands the new transform to the shader-data update.
// @ 0x00fae800
void SP::cTerrainSphereDecal::UpdateDecalUV()
{
    float angle = mTurns * SP::gDecalAngleScale;
    float fSin = sinf(angle);
    float fCos = cosf(angle);
    float fRepeat = (mType == 9) ? 1.0f : mAspect;

    cSPTransform xf = mTransform;
    rw::math::fpu::Matrix33Template<float, 0> rot(mTransform.mRotation);
    FixupDecalTransform(&xf);

    float fNegSin = -fSin;
    float fHalfScale = 0.5f / xf.mScale;
    float f12 = (rot.m[0] * fCos + rot.m[3] * fSin) * fHalfScale;
    float f13 = (rot.m[1] * fCos + rot.m[4] * fSin) * fHalfScale;
    float f7 = (rot.m[2] * fCos + rot.m[5] * fSin) * fHalfScale;
    float fNegHalf = -0.5f / (xf.mScale * fRepeat);
    float f10 = (rot.m[0] * fNegSin + rot.m[3] * fCos) * fNegHalf;
    float f14 = (rot.m[1] * fNegSin + rot.m[4] * fCos) * fNegHalf;
    float f8 = (rot.m[2] * fNegSin + rot.m[5] * fCos) * fNegHalf;

    float fAbsX = fabsf(xf.mTranslation.x);
    float fAbsY = fabsf(xf.mTranslation.y);
    float fAbsZ = fabsf(xf.mTranslation.z);

    mTexXform[3] = 0.5f - ((xf.mTranslation.x * f12 + xf.mTranslation.z * f7) +
                           xf.mTranslation.y * f13);
    mTexXform[0] = f12;
    mTexXform[1] = f13;
    mTexXform[2] = f7;
    mTexXform[4] = f10;
    mTexXform[5] = f14;
    mTexXform[7] = 0.5f - ((xf.mTranslation.x * f10 + xf.mTranslation.z * f8) +
                           xf.mTranslation.y * f14);
    mTexXform[6] = f8;

    float fU;
    float fV;
    int face;
    if (fAbsZ < fAbsX || fAbsZ < fAbsY) {
        if (fAbsY < fAbsX) {
            fU = (xf.mTranslation.y / xf.mTranslation.x + 1.0f) * 0.5f;
            fV = (xf.mTranslation.z / fAbsX + 1.0f) * 0.5f;
            face = (xf.mTranslation.x < 0.0f) ? 3 : 2;
        } else {
            fU = (xf.mTranslation.z / xf.mTranslation.y + 1.0f) * 0.5f;
            fV = (xf.mTranslation.x / fAbsY + 1.0f) * 0.5f;
            face = (xf.mTranslation.y < 0.0f) ? 5 : 4;
        }
    } else {
        fU = (xf.mTranslation.x / xf.mTranslation.z + 1.0f) * 0.5f;
        fV = (xf.mTranslation.y / fAbsZ + 1.0f) * 0.5f;
        face = (xf.mTranslation.z < 0.0f) ? 1 : 0;
    }

    float fUSize = xf.mScale /
                   ((mpParentSphere->GetMapSet()->mRadius * SP::gDecalAngleScale) * 0.25f);
    float fVSize = fUSize * fRepeat;

    if (mPosition.mU != fU || mPosition.mV != fV || mPosition.mFace != face ||
        mUSizeInput != fUSize || mVSizeInput != fVSize) {
        mPosition.mU = fU;
        mPosition.mV = fV;
        mUSizeInput = fUSize;
        mVSizeInput = fVSize;
        mUSize = fUSize;
        mVSize = fVSize;
        mPosition.mFace = face;
        mDecalRadius = (fVSize > fUSize) ? (fVSize * 0.55f) : (fUSize * 0.55f);
        UpdateDecalShaderData(&xf, fRepeat);
    }
}

