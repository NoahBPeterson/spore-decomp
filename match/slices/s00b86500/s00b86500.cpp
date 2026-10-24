// Slice s00b86500 -- 0x00b86a10, 2210 bytes (__stdcall, ret 8).
//
// Sibling of SP::BuildPathRibbon (0x00b872c0, slice s00b872c0): builds a miter-joined ribbon for a
// polyline of planet points, but on a constant-radius shell instead of the terrain.  The shell
// radius comes from the planet's terrain source (PlanetModel()+0x24, virtual +0x0c returns a record
// whose floats +0x34/+0x38/+0x3c give radius = f3c * f38 + f34; 0 without a terrain source) plus 2.0,
// and each point is just unit(P) * radius (no per-point terrain height lookup).  The quad emission
// and the chunked upload via cStaticBuffer::GetVertexBuffer / memcpy / Unlock are identical.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (x87 fsqrt/fdiv for 1/sqrt, SSE for the rest).
//
// @ 0x00b86a10

#include <string.h>
#include <math.h>
#include <xmmintrin.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

struct Vec3 { float x, y, z; };

struct RibbonVertex {           // 0x24 bytes
    Vec3 pos;
    Vec3 miter;
    uint32_t color;
    float u;
    float v;
};

struct PathVector {             // eastl::vector<Vec3>
    Vec3* mpBegin;
    Vec3* mpEnd;
};

namespace SP {

struct cTerrainParams {          // record returned by cTerrainSource vslot +0x0c
    char pad[0x34];
    float f34;
    float f38;
    float f3c;
};

class cTerrainSource {          // object at PlanetModel()+0x24
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual cTerrainParams* GetParams();                             // +0x0c
    virtual int Slot4();                                             // +0x10 (result unused)
};

class cPlanetModel { public:
    uint32_t pad[9];
    cTerrainSource* mpTerrain;                                       // +0x24
};
cPlanetModel* PlanetModel();                                         // 0x00b3d350

class cStaticBuffer {
public:
    int GetVertexBuffer(int count, RibbonVertex** ppOut, int* pOut2);   // 0x007a47c0
    void Unlock();                                                   // 0x007a4650
};

class cStaticBufferDraw { public:
    cStaticBuffer* mpBuffer;
};
}

extern SP::cStaticBufferDraw* gStaticBufferDraw;                     // 0x015ddc84
void __cdecl EASTL_allocator_deallocate(void* p);                    // 0x00f47380

// eastl::fixed_vector<RibbonVertex, 128> (vector part)
struct VertexVector {
    RibbonVertex* mpBegin;
    RibbonVertex* mpEnd;
    RibbonVertex* mpCapacity;
    uint32_t mAllocatorPad;
    RibbonVertex* mpPool;
    uint32_t mPad2;
    RibbonVertex mStorage[128];
    void resize(unsigned n);                                         // 0x00b86910
};

__forceinline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// ---------------------------------------------------------------------------------------
// Graph-editor helpers at 0x00b86500..0x00b86909.
// ---------------------------------------------------------------------------------------
struct GraphNodeValue {
    uint32_t mValue[3];
};

struct GraphNode {
    int mID;                                // +00
    GraphNodeValue mValue;                  // +04
    uint8_t mFlag10;                        // +10
    uint8_t mFlag11;                        // +11
    unsigned short pad12;
    uint32_t mField14;                      // +14
};

struct GraphNodeVector {
    GraphNode* mpBegin;
    GraphNode* mpEnd;
    GraphNode* mpCapacity;
    uint32_t mAllocator;
    void InsertAt(GraphNode* position, const GraphNodeValue* value); // 0x00b85220
};

struct GraphEdge {
    uint32_t mLow;
    uint32_t mHigh;
};

struct GraphEdgeVector {
    GraphEdge* mpBegin;
    GraphEdge* mpEnd;
    GraphEdge* mpCapacity;
    uint32_t mAllocator;
    void InsertAt(GraphEdge* position, const GraphEdge* value);      // 0x00b534c0
};

struct GraphExtra {
    uint32_t mLow;                          // +00
    uint32_t mHigh;                         // +04
    void* mpPayload;                        // +08
    uint8_t mData[0x10];                    // +0c
    void DestroyPayload();                  // 0x00473500
};

struct GraphExtraVector {
    GraphExtra* mpBegin;
    GraphExtra* mpEnd;
    GraphExtra* mpCapacity;
    uint32_t mAllocator;
};

class cGraphCallback {
public:
    void Invoke(void* list, int value);     // 0x00b859c0
};

class cGraphA8 {
public:
    uint8_t mData[0x24];
    cGraphCallback* mpCallback;             // +24
};

class cGraphList {
public:
    GraphNode* mpBegin;
    GraphNode* mpEnd;
    void DestroyRange(GraphNode* first, GraphNode* last); // 0x0050f740
};

class IGraphObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual uint32_t GetID();               // +0x4c
};

class cGraphEditor {
public:
    uint8_t mData00[0x80];
    GraphNodeVector mNodes;                 // +80
    uint8_t mData8c[0x18];
    cGraphA8* mpA8;                         // +a8
    GraphEdgeVector mEdgesA;                // +ac
    uint8_t mPadBC[4];
    GraphEdgeVector mEdgesB;                // +c0
    uint8_t mPadD0[4];
    GraphExtraVector mExtras;               // +d4
    uint8_t mPadE4[4];
    uint8_t mDirtyA;                        // +e8
    uint8_t mDirtyB;                        // +e9
    uint8_t mDirtyC;                        // +ea
    uint8_t padEB;

    int AddNode(const GraphNodeValue* value, bool flag);       // 0x00b86500
    int SelectNode(void* object, cGraphList* list, int index); // 0x00b86590
    void AddEdgeA(uint32_t a, uint32_t b);                     // 0x00b86650
    void AddEdgeB(uint32_t a, uint32_t b);                     // 0x00b866f0
    void RemoveEdge(uint32_t a, uint32_t b);                   // 0x00b86790
};

extern "C" void __cdecl FreeAllocation(void* p);                 // 0x00f47380

// @ 0x00b86500
int cGraphEditor::AddNode(const GraphNodeValue* value, bool flag)
{
    GraphNode* end = mNodes.mpEnd;
    if (end < mNodes.mpCapacity)
        mNodes.mpEnd = end + 1;
    else
        mNodes.InsertAt(end, value);

    GraphNode* node = mNodes.mpEnd - 1;
    node->mID = -1;
    node->mValue.mValue[0] = value->mValue[0];
    node->mValue.mValue[1] = value->mValue[1];
    node->mValue.mValue[2] = value->mValue[2];
    node->mFlag10 = flag;
    node->mFlag11 = 0;
    node->mField14 = 0;
    return (int)(mNodes.mpEnd - mNodes.mpBegin) - 1;
}

// @ 0x00b86590
int cGraphEditor::SelectNode(void* object, cGraphList* list, int index)
{
    uint32_t id = ((IGraphObject*)object)->GetID();
    list->DestroyRange(list->mpBegin, list->mpEnd);

    int found = 0;
    int count = (int)(mNodes.mpEnd - mNodes.mpBegin);
    for (int i = 0; i < count; ++i) {
        GraphNode* node = mNodes.mpBegin + i;
        if (node->mID == (int)id) {
            if (found == index) {
                cGraphA8* a8 = mpA8;
                if (a8->mpCallback)
                    a8->mpCallback->Invoke(list, 0);
            }
            ++found;
        }
    }
    return found;
}

// @ 0x00b86650
void cGraphEditor::AddEdgeA(uint32_t a, uint32_t b)
{
    uint32_t lo = a < b ? a : b;
    uint32_t hi = a < b ? b : a;
    int count = (int)(mEdgesA.mpEnd - mEdgesA.mpBegin);
    for (int i = 0; i < count; ++i) {
        GraphEdge* e = mEdgesA.mpBegin + i;
        if (e->mLow == lo && e->mHigh == hi)
            return;
    }

    GraphEdge value;
    value.mLow = lo;
    value.mHigh = hi;
    if (mEdgesA.mpEnd < mEdgesA.mpCapacity) {
        mEdgesA.mpEnd->mHigh = hi;
        mEdgesA.mpEnd->mLow = lo;
        ++mEdgesA.mpEnd;
    } else {
        mEdgesA.InsertAt(mEdgesA.mpEnd, &value);
    }
    mDirtyA = 1;
}

// @ 0x00b866f0
void cGraphEditor::AddEdgeB(uint32_t a, uint32_t b)
{
    uint32_t lo = a < b ? a : b;
    uint32_t hi = a < b ? b : a;
    int count = (int)(mEdgesB.mpEnd - mEdgesB.mpBegin);
    for (int i = 0; i < count; ++i) {
        GraphEdge* e = mEdgesB.mpBegin + i;
        if (e->mLow == lo && e->mHigh == hi)
            return;
    }

    GraphEdge value;
    value.mLow = lo;
    value.mHigh = hi;
    if (mEdgesB.mpEnd < mEdgesB.mpCapacity) {
        mEdgesB.mpEnd->mHigh = hi;
        mEdgesB.mpEnd->mLow = lo;
        ++mEdgesB.mpEnd;
    } else {
        mEdgesB.InsertAt(mEdgesB.mpEnd, &value);
    }
    mDirtyB = 1;
}

// @ 0x00b86790
void cGraphEditor::RemoveEdge(uint32_t a, uint32_t b)
{
    uint32_t lo = a < b ? a : b;
    uint32_t hi = a < b ? b : a;

    int countA = (int)(mEdgesA.mpEnd - mEdgesA.mpBegin);
    for (int i = 0; i < countA; ++i) {
        GraphEdge* e = mEdgesA.mpBegin + i;
        if (e->mLow == lo && e->mHigh == hi) {
            GraphEdge* last = mEdgesA.mpEnd - 1;
            e->mLow = last->mLow;
            e->mHigh = last->mHigh;
            --mEdgesA.mpEnd;
            mDirtyA = 1;
            break;
        }
    }

    int countB = (int)(mEdgesB.mpEnd - mEdgesB.mpBegin);
    for (int i = 0; i < countB; ++i) {
        GraphEdge* e = mEdgesB.mpBegin + i;
        if (e->mLow == lo && e->mHigh == hi) {
            GraphEdge* last = mEdgesB.mpEnd - 1;
            e->mLow = last->mLow;
            e->mHigh = last->mHigh;
            --mEdgesB.mpEnd;
            mDirtyB = 1;
            break;
        }
    }

    int countE = (int)(mExtras.mpEnd - mExtras.mpBegin);
    for (int i = 0; i < countE; ++i) {
        GraphExtra* e = mExtras.mpBegin + i;
        if (e->mLow == lo && e->mHigh == hi) {
            GraphExtra* last = mExtras.mpEnd - 1;
            e->mLow = last->mLow;
            e->mHigh = last->mHigh;
            e->DestroyPayload();
            --mExtras.mpEnd;
            if (mExtras.mpEnd->mpPayload &&
                *((uint32_t*)mExtras.mpEnd->mpPayload - 1) != 0)
                FreeAllocation(mExtras.mpEnd->mpPayload);
            mDirtyC = 1;
            break;
        }
    }
}

// @ 0x00b86a10
void __stdcall BuildPathRibbonOnShell(PathVector* path, unsigned color)
{
    if ((unsigned)(path->mpEnd - path->mpBegin) < 2)
        return;

    SP::cStaticBufferDraw* draw = gStaticBufferDraw;
    uint32_t col = color | 0xff000000;

    float radius;
    SP::cPlanetModel* planet = SP::PlanetModel();
    if (planet->mpTerrain != 0) {
        SP::cTerrainParams* tp = planet->mpTerrain->GetParams();
        radius = tp->f3c * tp->f38 + tp->f34;
    } else {
        radius = 0.0f;
    }

    VertexVector verts;
    verts.mpBegin = verts.mStorage;
    verts.mpEnd = verts.mStorage;
    verts.mpCapacity = verts.mStorage + 128;
    verts.mpPool = verts.mStorage;
    verts.resize((unsigned)(path->mpEnd - path->mpBegin) * 4 - 4);

    RibbonVertex* out = verts.mpBegin;
    Vec3 prevM, prevS;
    float length = 0.0f;
    int n = (int)(path->mpEnd - path->mpBegin);

    for (int i = 0; i < n; i++) {
        const Vec3* P = path->mpBegin + i;
        const Vec3* Q = P;
        if (i != 0)
            Q = P - 1;
        const Vec3* R = P;
        if (i != n - 1)
            R = P + 1;

        // m1 = normalize(Q x P)
        float c1x = P->z * Q->y - P->y * Q->z;
        float c1y = P->x * Q->z - P->z * Q->x;
        float c1z = P->y * Q->x - P->x * Q->y;
        float r1 = 1.0f / sqrtf((c1x * c1x + c1z * c1z + c1y * c1y) + 1e-08f);
        Vec3 m1;
        m1.x = c1x * r1;
        m1.y = c1y * r1;
        m1.z = c1z * r1;

        // m2 = normalize(P x R)
        float c2x = P->y * R->z - P->z * R->y;
        float c2y = P->z * R->x - P->x * R->z;
        float c2z = P->x * R->y - P->y * R->x;
        float r2 = 1.0f / sqrtf((c2z * c2z + c2y * c2y + c2x * c2x) + 1e-08f);
        Vec3 m2;
        m2.x = c2x * r2;
        m2.y = c2y * r2;
        m2.z = c2z * r2;

        float cosv;
        if (i == 0 || i == n - 1) {
            cosv = -1.0f;
        } else {
            float d1x = R->x - P->x;
            float d1y = R->y - P->y;
            float d1z = R->z - P->z;
            float d0x = Q->x - P->x;
            float d0y = Q->y - P->y;
            float d0z = Q->z - P->z;
            float dot = (d0z * d1z + d0y * d1y) + d0x * d1x;
            float l1 = sqrtf((d1z * d1z + d1y * d1y) + d1x * d1x);
            float l0 = sqrtf((d0x * d0x + d0z * d0z) + d0y * d0y);
            cosv = Clamp(dot / (l1 * l0), -1.0f, 0.999f);
        }

        // put the point on the shell
        float px = P->x;
        float inv = 1.0f / sqrtf(((P->y * P->y + P->z * P->z) + px * px));
        Vec3 S;
        S.x = (px * inv) * (radius + 2.0f);
        S.y = (inv * P->y) * (radius + 2.0f);
        S.z = (inv * P->z) * (radius + 2.0f);

        float sx = m2.x + m1.x;
        float sy = m2.y + m1.y;
        float sz = m2.z + m1.z;
        float scale = sqrtf(2.0f / (1.0f - cosv));
        float rs = 1.0f / sqrtf((sx * sx + sz * sz) + sy * sy);
        Vec3 M;
        M.x = (rs * sx) * scale;
        M.y = (sy * rs) * scale;
        M.z = (sz * rs) * scale;

        if (i > 0) {
            out[0].pos.x = prevS.x - prevM.x;
            out[0].pos.y = prevS.y - prevM.y;
            out[0].pos.z = prevS.z - prevM.z;
            out[0].miter = prevM;
            out[0].color = col;
            out[0].u = 0.0f;
            out[0].v = length;

            out[1].pos.x = prevM.x + prevS.x;
            out[1].pos.y = prevM.y + prevS.y;
            out[1].pos.z = prevM.z + prevS.z;
            out[1].miter = prevM;
            out[1].color = col;
            out[1].u = 1.0f;
            out[1].v = length;

            length = sqrtf(((S.z - prevS.z) * (S.z - prevS.z) + (S.y - prevS.y) * (S.y - prevS.y)) +
                           (S.x - prevS.x) * (S.x - prevS.x)) + length;

            out[2].pos.x = S.x + M.x;
            out[2].pos.y = S.y + M.y;
            out[2].pos.z = S.z + M.z;
            out[2].miter = M;
            out[2].color = col;
            out[2].u = 1.0f;
            out[2].v = length;

            out[3].pos.x = S.x - M.x;
            out[3].pos.y = S.y - M.y;
            out[3].pos.z = S.z - M.z;
            out[3].miter = M;
            out[3].color = col;
            out[3].u = 0.0f;
            out[3].v = length;
            out += 4;
        }
        prevM = M;
        prevS = S;
    }

    // upload in chunks
    int total = (int)(verts.mpEnd - verts.mpBegin);
    int done = 0;
    while (done < total) {
        RibbonVertex* dst;
        int extra;
        int got = draw->mpBuffer->GetVertexBuffer(total - done, &dst, &extra);
        memcpy(dst, verts.mpBegin + done, got * sizeof(RibbonVertex));
        draw->mpBuffer->Unlock();
        total = (int)(verts.mpEnd - verts.mpBegin);
        done += got;
    }

    if (verts.mpBegin != 0 && verts.mpBegin != verts.mpPool)
        EASTL_allocator_deallocate(verts.mpBegin);
}
