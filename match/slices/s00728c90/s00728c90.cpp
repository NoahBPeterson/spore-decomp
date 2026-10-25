// Slice s00728c90 — UV generation: SP::CreateUVsAndCharts and its small enum/index helpers.
// Small switch tables and index lookups are reconstructed; the large chart builders are partial.
#include "types.h"

// ---------------------------------------------------------------------------
// small helpers
// ---------------------------------------------------------------------------

// @ 0x00729430 — enum -> canonical id (A)
int FUN_00729430(int a)
{
    switch (a) {
    case 2:
    case 0x12: return 2;
    case 3:
    case 5:  return 5;
    case 4:  return 6;
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xa:
    case 0xb:
    case 0xc:
    case 0xd: return 8;
    case 0xe: return 9;
    case 0xf: return 10;
    case 0x13: return 3;
    case 0x14: return 4;
    case 0:  return 1;
    case 1:  return 1;
    case 0x10: return 1;
    case 0x11: return 1;
    case 0x15: return 1;
    default:  return 1;
    }
}

// @ 0x007294d0 — enum -> canonical id (B)
int FUN_007294d0(int a)
{
    switch (a) {
    case 0:  return 1;
    case 1:  return 2;
    case 2:  return 3;
    case 3:  return 4;
    case 4:  return 5;
    case 5:  return 7;
    case 8:  return 0xa;
    case 6:  return 8;
    case 7:  return 9;
    case 9:  return 0xb;
    case 10: return 0xc;
    default: return 0;
    }
}

// @ 0x00729560 — enum -> canonical id (C)
int FUN_00729560(int a)
{
    switch (a) {
    case 1:  return 0;
    case 2:  return 1;
    case 3:  return 2;
    case 4:  return 3;
    case 5:  return 4;
    default: return -1;
    case 7:  return 5;
    case 10: return 8;
    case 8:  return 6;
    case 9:  return 7;
    case 0xb: return 9;
    case 0xc: return 10;
    }
}

// @ 0x007295f0 — (enum, sub) -> canonical id
int FUN_007295f0(int a, int b)
{
    switch (a) {
    case 1:
        if (b == 0) return 0;
        break;
    case 2:
        if (b == 0) return 2;
        break;
    case 8:
        if (b < 8) return b + 6;
        break;
    case 3:
        if (b == 0) return 0x13;
        break;
    case 5:
    case 7:
        if (b == 0) return 3;
        if (b == 1) return 5;
        break;
    case 6:
        if (b == 0) return 4;
        break;
    case 9:
        if (b == 0) return 0xe;
        break;
    case 10:
        if (b == 0) return 0xf;
        break;
    case 0xb:
        return 0x16;
    case 0xc:
        if (b == 0) return 0x11;
        break;
    case 0xd:
        if (b == 0) return 0x12;
    }
    return -1;
}

// @ 0x00729820 — initialise a descriptor (13 dwords). PMeshType ctor.
struct C29820 {
    int   f0;
    int   f1;
    float f2, f3, f4, f5, f6, f7;
    int   f8, f9, f10, f11, f12;
    C29820* Init(int a, float* b, int c, int d);
};

C29820* C29820::Init(int a, float* b, int c, int d)
{
    f0 = a;
    f1 = 0;
    f2 = b[0];
    f3 = b[1];
    f4 = b[2];
    f5 = b[3];
    f6 = b[4];
    f7 = b[5];
    f8 = c;
    f9 = d;
    f10 = 0;
    f11 = 0;
    f12 = 0;
    return this;
}

// @ 0x00729ad0 — find the element (stride 0xc) whose [lo,hi) contains x.
struct C29ad0 {
    char* mpBegin;   // +0
    char* mpEnd;     // +4
    int   Find(int x);
};

int C29ad0::Find(int x)
{
    int* p = (int*)mpBegin;
    int  n = (int)(mpEnd - mpBegin) / 0xc;
    int  i = 0;
    if (0 < n) {
        do {
            if (p[1] <= x && x < p[2])
                return p[0];
            i++;
            p += 3;
        } while (i < n);
    }
    return -1;
}

// @ 0x00729870 — recursively unlink two child lists onto a global free list.
extern "C" void* g_162b1f0;
struct C29a70 {
    char   pad[0x2c];
    C29a70* mp2c;   // +0x2c
    C29a70* mp30;   // +0x30
    void Free();
};

void C29a70::Free()
{
    if (mp2c) {
        mp2c->Free();
        C29a70* n = mp2c;
        *(void**)n = g_162b1f0;
        g_162b1f0 = n;
    }
    if (mp30) {
        mp30->Free();
        C29a70* n = mp30;
        *(void**)n = g_162b1f0;
        g_162b1f0 = n;
    }
}

// Retail is declared void, but its eax is live at both exits: the word stride of the
// source struct (src word at +0xa, already shifted by 2) until a row with a non-empty
// copy runs, then the dword cursor just past the last copied dword.
// @ 0x007296e0
int FUN_007296e0(int* dst, int* src, int rows)
{
    int      srcBase   = src[1];
    int*     d         = (int*)dst[0];
    unsigned dstStride = (unsigned)dst[1] & 0xfffffffc;
    unsigned wordStride = *(unsigned short*)((char*)src + 10) >> 2;
    unsigned count     = *(unsigned short*)((char*)src + 8) >> 2;
    int      last      = (int)wordStride;
    if (rows > 0)
        last = (int)(wordStride * 4);
    for (; rows > 0; --rows) {
        int*      s = (int*)srcBase;
        int*      p = d;
        if (count) {
            for (unsigned i = 0; i < count; ++i)
                p[i] = s[i];
            last = (int)(size_t)(p + count);
        }
        srcBase += (int)(wordStride * 4);
        d = (int*)((char*)d + dstStride);
    }
    return last;
}

// @ 0x00729760 — like FUN_007296e0 but the source row is selected through a mask table.
extern const unsigned int DAT_0140d15c[];
void FUN_00729760(int* dst, int* src, int* sel, int rows)
{
    if (sel[1] == 0) {
        FUN_007296e0(dst, src, rows);
        return;
    }
    int      srcBase   = src[1];
    int*     d         = (int*)dst[0];
    unsigned dstStride = (unsigned)dst[1];
    unsigned srcStride = *(unsigned short*)((char*)src + 10);
    unsigned count     = *(unsigned short*)((char*)src + 8) >> 2;
    unsigned mask      = DAT_0140d15c[*(unsigned short*)((char*)sel + 8)];
    for (int row = 0; row < rows; ++row) {
        unsigned idx = *(unsigned int*)((char*)sel[1] + *(unsigned short*)((char*)sel + 10) * row);
        int* s = (int*)(srcBase + (int)((mask & idx) * (srcStride >> 2) * 4));
        for (unsigned i = 0; i < count; ++i)
            d[i] = s[i];
        d = (int*)((char*)d + (dstStride & 0xfffffffc));
    }
}

// ---------------------------------------------------------------------------
// large functions (partial)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 0x00728c90  SP::CreateUVsAndCharts -- types (retail layouts; EASTL vectors are 0x14 bytes)
// ---------------------------------------------------------------------------
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}
void __cdecl operator_delete__(void* p);           // 0x00f47380

namespace UV {

struct Vec2 { float x, y; };                       // POD: copies go through integer registers
extern Vec2 g_Vec2Zero;                            // 0x0162ae9c

struct Vec2Vec {                                   // eastl::vector<cSPVector2, sp_vector_allocator> (0x14)
    Vec2* mpBegin;
    Vec2* mpEnd;
    Vec2* mpCapacity;
    int   alloc[2];
    void Assign(const Vec2Vec& o);                                 // 0x00722ba0 (ret 4)
    void DoInsertValues(Vec2* pos, unsigned n, const Vec2& v);     // 0x00479830 (ret 0xc)
    inline void erase(Vec2* first, Vec2* last)
    {
        Vec2* dst = first;
        for (Vec2* src = last; src != mpEnd; ++src, ++dst)
            *dst = *src;
        mpEnd -= (last - first);
    }
    inline void clear() { erase(mpBegin, mpEnd); }
    inline void resize(unsigned n, const Vec2& v)
    {
        unsigned cur = (unsigned)(mpEnd - mpBegin);
        if (n > cur) DoInsertValues(mpEnd, n - cur, v);
        else         erase(mpBegin + n, mpEnd);
    }
};

struct ClusterInfo {                               // 0x64
    int   numFaces;                                // +0
    float nx, ny, nz;                              // +4 +8 +0xc
    float cx, cy, cz;                              // +0x10
    float area;                                    // +0x1c
    float projArea;                                // +0x20
    float texArea;                                 // +0x24
    Vec2  minUV;                                   // +0x28
    Vec2  maxUV;                                   // +0x30
    int   pad38[2];
    int   indicesStart, indicesEnd;                // +0x40 +0x44
    int   pad48[2];
    Vec2Vec boundary;                              // +0x50
};

struct Chart {                                     // SP::cTextureChart, 0x68
    int     meshIndex;                             // +0
    float   texArea;                               // +4
    float   primArea;                              // +8
    int     texStart, texEnd;                      // +0xc +0x10
    Vec2Vec boundaries;                            // +0x14
    Vec2    texBound;                              // +0x28
    char    flag;                                  // +0x30
    char    pad31[3];
    int     rest[13];                              // +0x34 horizons etc.
};
void __stdcall DestroyChartRange(Chart* first, Chart* last);       // 0x00721910

struct ChartVec {
    Chart* mpBegin; Chart* mpEnd; Chart* mpCapacity; int alloc[2];
    ChartVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ChartVec()
    {
        DestroyChartRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin);
    }
    void reserve(unsigned n);                      // 0x00728270 (ret 4)
    void push_back0();                             // 0x007289a0 (default-construct one at the end)
};

struct ChartRect {                                 // 0x34, element of the rect-pack list
    int   a, b;
    float prim;
    int   mesh;
    Vec2  minUV, maxUV;
    float w, h;
    float g0; int g1; float g2;                    // never written before the copy
    ChartRect() {}
    ChartRect(int ia, int ib, float p, int m, Vec2 mn, Vec2 mx, float ww, float hh)
        : a(ia), b(ib), prim(p), mesh(m), minUV(mn), maxUV(mx), w(ww), h(hh) {}
    ChartRect(const ChartRect& o)
        : a(o.a), b(o.b), prim(o.prim), mesh(o.mesh), minUV(o.minUV), maxUV(o.maxUV),
          w(o.w), h(o.h), g0(o.g0), g1(o.g1), g2(o.g2) {}
};
struct RectVec {
    ChartRect* mpBegin; ChartRect* mpEnd; ChartRect* mpCapacity; int alloc[2];
    RectVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~RectVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); }
    void DoInsertValue(ChartRect* pos, const ChartRect& v);        // 0x007222f0 (ret 8)
    inline void push_back(const ChartRect& v)
    {
        if (mpEnd < mpCapacity) { ::new (mpEnd++) ChartRect(v); }
        else DoInsertValue(mpEnd, v);
    }
};

struct MeshClusterer {                             // 0x90 (retail)
    MeshClusterer();                               // 0x00722010
    virtual ~MeshClusterer();                      // 0x007220c0
    int          rc;
    void*        meshData;
    ClusterInfo* cBegin;                           // +0xc
    ClusterInfo* cEnd;                             // +0x10
    ClusterInfo* cCap;
    uint32_t     pad[30];
    void Cluster(void* mesh, float f);             // 0x00728af0 (ret 8)
    void AssignCharts(int a, int b, int c);        // 0x00725e40 (ret 0xc)
};

struct PtrVec { void** mpBegin; void** mpEnd; };

struct ClusterMap {                                // 0x264
    ClusterMap();                                  // 0x006dffc0
    ~ClusterMap();                                 // 0x00724700
    char pad[0x274];
    void Build(PtrVec* meshes);                    // 0x006e0ea0 (ret 4)
    void AddCluster(Chart* c);                     // 0x006dfc30 (ret 4)
    void Pack(int mode);                           // 0x006e04d0 (ret 4)
};

struct MeshXform {                                 // per-mesh transform info, 0x38
    unsigned flags;                                // +0
    char  pad4[0xc];
    float scale;                                   // +0x10
    char  pad14[8];
    float vx;                                      // +0x1c
    char  pad20[8];
    float vy;                                      // +0x28
    char  pad2c[8];
    float vz;                                      // +0x34
};

struct PropList { int GetIntProperty(unsigned id); };              // 0x006a2660 (ret 4)
extern PropList* g_AppProps;                                       // 0x015fd918

void __cdecl ThreadSleep(const unsigned& t);                       // 0x00921df0
void __cdecl RectPackCharts(PtrVec* meshes, RectVec* rects, float total, int size);   // 0x006e09d0
void __cdecl FinishMesh(void* mesh);                               // 0x00735a90

} // namespace UV

// @ 0x00728c90  SP::CreateUVsAndCharts
void __cdecl FUN_00728c90(UV::PtrVec* meshes, float clusterParam, const float* scales, const UV::MeshXform* info)
{
    using namespace UV;
    ChartVec charts;
    RectVec  rects;
    charts.reserve(0x20);
    int prop = g_AppProps->GetIntProperty(0x04474195);
    int nMeshes = (int)(meshes->mpEnd - meshes->mpBegin);
    float totalTexArea = 0.0f;

    for (int i = 0; i < nMeshes; ++i) {
        MeshClusterer mc;
        mc.Cluster(meshes->mpBegin[i], clusterParam);
        ThreadSleep(0);
        mc.AssignCharts(1, 1, 1);
        ThreadSleep(0);
        int nClusters = (int)(mc.cEnd - mc.cBegin);
        for (int j = 0; j < nClusters; ++j) {
            ClusterInfo& c = mc.cBegin[j];
            if (info) {
                float sc = info[i].scale;
                float a = c.area * sc;
                c.area = a * sc;
            }
            if (prop == 2) {
                float tex = c.texArea;
                ChartRect r(c.indicesStart, c.indicesEnd, c.area * tex, i, c.minUV, c.maxUV,
                            c.maxUV.x - c.minUV.x, c.maxUV.y - c.minUV.y);
                if (scales) r.prim = scales[i] * r.prim;
                totalTexArea = tex + totalTexArea;
                rects.push_back(r);
            } else {
                charts.push_back0();
                Chart& ch = charts.mpEnd[-1];
                ch.meshIndex = i;
                ch.texArea = c.texArea;
                ch.primArea = c.area;
                ch.texStart = c.indicesStart;
                ch.texEnd = c.indicesEnd;
                ch.boundaries.Assign(c.boundary);
                ch.texBound.x = c.maxUV.x - c.minUV.x;
                ch.texBound.y = c.maxUV.y - c.minUV.y;
                float dot = c.nz;
                if (info && (info[i].flags & 2))
                    dot = (info[i].vy * c.ny + info[i].vx * c.nx) + c.nz * info[i].vz;
                if (dot < -0.95f && c.area > 30.0f) {
                    ch.primArea = 1.0e-4f;
                    ch.boundaries.clear();
                    ch.boundaries.resize((unsigned)(c.boundary.mpEnd - c.boundary.mpBegin), g_Vec2Zero);
                    ch.texBound.x = ch.texBound.x * 1.0e-5f;
                    ch.texBound.y = ch.texBound.y * 1.0e-5f;
                    ch.flag = 1;
                }
                if (scales)
                    ch.primArea = scales[i] * ch.primArea;
            }
        }
        ThreadSleep(0);
    }

    if (prop == 2) {
        RectPackCharts(meshes, &rects, totalTexArea, 0x200);
    } else {
        ClusterMap cm;
        cm.Build(meshes);
        int nCharts = (int)(charts.mpEnd - charts.mpBegin);
        for (int k = 0; k < nCharts; ++k)
            cm.AddCluster(charts.mpBegin + k);
        ThreadSleep(0);
        cm.Pack(prop);
    }

    int n2 = (int)(meshes->mpEnd - meshes->mpBegin);
    for (int k = 0; k < n2; ++k) {
        FinishMesh(meshes->mpBegin[k]);
        ThreadSleep(0);
    }
}

// ---------------------------------------------------------------------------
// 0x00729290  UV job run + its __cdecl adjustor thunk; 0x00729300 the factory
// that installs the thunk into a vtable slot.
// ---------------------------------------------------------------------------

void __cdecl FUN_00722d00(int mesh);                          // 0x00722d00 BuildTextureChart

// The job object 0x00729290 runs on: a mesh-pointer vector, the cluster
// parameter and two optional side vectors.  Only the members it reads are named.
struct UVJob {
    uint8_t   pad00[0xc];
    UV::PtrVec meshes;                                         // +0x0c
    uint8_t   pad14[0xc];
    float     clusterParam;                                    // +0x20
    int       scaleBegin;                                      // +0x24
    int       scaleEnd;                                        // +0x28
    uint8_t   pad2c[0xc];
    int       infoBegin;                                       // +0x38
    int       infoEnd;                                         // +0x3c

    bool Run(int unused);
};

// @ 0x00729290  UVJob::Run -- rebuild one mesh's texture charts
bool UVJob::Run(int unused)
{
    (void)unused;
    int n = (int)(meshes.mpEnd - meshes.mpBegin);
    for (int i = 0; i < n; ++i)
        FUN_00722d00((int)meshes.mpBegin[i]);

    int infoRaw = infoBegin;
    if (infoBegin == infoEnd)
        infoRaw = 0;
    int scalesRaw = scaleBegin;
    if (scaleBegin == scaleEnd)
        scalesRaw = 0;

    const float* scales = (const float*)scalesRaw;
    const UV::MeshXform* info = (const UV::MeshXform*)infoRaw;

    // Retail reaches the 4-parameter CreateUVsAndCharts through a slot that also
    // passes a trailing 0; call it through a 5-argument view of the same address.
    typedef void (__cdecl *CreateUVs5)(UV::PtrVec*, float, const float*, const UV::MeshXform*, int);
    ((CreateUVs5)::FUN_00728c90)(&meshes, clusterParam, scales, info, 0);
    return true;
}

// @ 0x007292f0  the __cdecl adjustor thunk stored in the job record's first slot
int FUN_007292f0(void* mesh, UVJob* self)
{
    return self->Run((int)mesh) ? 1 : 0;
}

// --- the singleton lock the factory brackets the job creation with ----------

struct SingLock {
    virtual void v00();                                        // +0x00
    virtual void v04();                                        // +0x04
    virtual void v08();                                        // +0x08
    virtual void v0c();                                        // +0x0c
    virtual char v10(void* key);                               // +0x10
    virtual void v14();                                        // +0x14
    virtual void v18();                                        // +0x18
    virtual void v1c();                                        // +0x1c
    virtual void v20();                                        // +0x20
    virtual void v24();                                        // +0x24
};
SingLock* __cdecl FUN_0068f4d0();                              // 0x0068f4d0 singleton accessor
void __cdecl FUN_0068f9b0(void* key, void* job);               // 0x0068f9b0

// The 0x4c-byte job info FUN_007280b0 initialises.
struct UVGenJobInfo {
    void** vptr;                                               // +0x00
    UVGenJobInfo* Init(void* a, float b, void* c, void* d);    // 0x007280b0 (this + 5 stack slots)
};

void* __cdecl FUN_00f473a0(unsigned size, const char* name, int f, int df, void* file, int line);  // 0x00f473a0

// The record the factory fills in: a thunk pointer plus the job object, and a
// flag at +0x18.
struct JobRecord {
    void*        mpThunk;                                      // +0x00
    UVGenJobInfo* mpJob;                                       // +0x04
    uint8_t      pad08[0x10];
    unsigned     mFlags;                                       // +0x18
};

// @ 0x00729300  build one UV job and hand it to the consumer
bool __cdecl FUN_00729300(int a1, float a2, JobRecord** a3, int a4, int a5, int a6, int a7)
{
    (void)a1; (void)a4; (void)a6;

    SingLock* lock = FUN_0068f4d0();
    lock->v20();

    UVGenJobInfo* job = 0;
    if (FUN_0068f4d0()->v10(a3)) {
        UVGenJobInfo* mem = (UVGenJobInfo*)FUN_00f473a0(0x4c, "Graphics", 0, 0, 0, 0);
        if (mem != 0)
            job = mem->Init(a3, a2, (void*)a5, (void*)a7);
        if (job != 0)
            ((void(__thiscall*)(void*))job->vptr[0])(job);      // AddRef
        FUN_0068f9b0(a3, job);
        JobRecord* rec = *a3;
        rec->mpThunk  = (void*)&FUN_007292f0;
        rec->mpJob    = job;
        rec->mFlags   = 0x80000000u;
        if (job != 0)
            ((void(__thiscall*)(void*))job->vptr[1])(job);     // Release
        lock->v24();
        return true;
    }

    lock->v24();
    return false;
}

// x87 area helper.  `b` is really a pointer to a struct holding two unsigned
// weights at +8/+0xc and four Vec3s at +0x10/+0x1c/+0x28/+0x34; the three
// edges used are p1-p0 (u), p3-p2 (v) and a1-a0 (w).  The only non-obvious
// part is the scalar built from one edge: (z*y + z*x + x*y), weighted by the
// matching unsigned weight and doubled, over the doubled w scalar times the
// integer weight sum -- i.e. a barycentric-style ratio.
// @ 0x007298b0
double FUN_007298b0(float* a, int b)
{
    float* p = (float*)b;
    float ux = p[7] - p[4], uy = p[8] - p[5], uz = p[9] - p[6];
    float vx = p[13] - p[10], vy = p[14] - p[11], vz = p[15] - p[12];
    float wx = a[3] - a[0], wy = a[4] - a[1], wz = a[5] - a[2];
    unsigned int t0 = *(unsigned int*)(p + 2);
    unsigned int t1 = *(unsigned int*)(p + 3);
    return ((vz * vy + vz * vx + vx * vy) * 2.0f * (float)t1 +
            (uz * uy + uz * ux + ux * uy) * 2.0f * (float)t0) /
           (2.0f * (wz * wy + wz * wx + wx * wy) * (float)(t0 + t1));
}

// ---------------------------------------------------------------------------
// 0x00729990  flatten a cluster graph into 0x20-byte output records
// ---------------------------------------------------------------------------

// A cluster-graph node.  The two child links (mpA/mpB) lead to the same node
// shape but read their per-vertex slot arrays at different offsets, so both
// arrays are modelled on the shared layout.
struct ChartNode {
    uint8_t  pad00[0x08];
    int      mSlotLo[3];                                       // +0x08  (read through mpB)
    int      mSlotHi[3];                                       // +0x14  (read through mpA)
    int      mA20;                                             // +0x20
    int      mA24;                                             // +0x24
    int      mIndex;                                           // +0x28
    ChartNode* mpA;                                            // +0x2c
    ChartNode* mpB;                                            // +0x30
};

// One emitted record (0x20 bytes).  The buffer's first record doubles as the
// head of the {parent, child} link table the builder indexes as ints.
struct OutRec {
    int mNode;                                                 // +0x00
    int mIndex;                                                // +0x04
    int mLoA;                                                  // +0x08
    int mLoB;                                                  // +0x0c
    int mMarkA;                                                // +0x10
    int mMarkB;                                                // +0x14
    int mValA;                                                 // +0x18
    int mValB;                                                 // +0x1c
};
struct OutBuf {
    OutRec* mpRec;                                             // +0x00
    int     mCount;                                            // +0x04
};

// One frame of the explicit stack the builder walks the graph with.
struct Win29990 {
    int        mParent;                                        // +0x00
    int        mFlag;                                          // +0x04
    ChartNode* mpDesc;                                         // +0x08
};

// @ 0x00729990  FUN_00729990  walk the cluster graph rooted at `root`, emitting
// one 0x20-byte record per visited node/edge
void __cdecl FUN_00729990(int root, OutBuf* buf)
{
    if (buf->mCount == 0)
        return;

    // One {parent, flag, descendant} frame; the walk keeps a single stack
    // pointer and moves all three fields together (retail increments the three
    // lockstep pointers once per descendant pushed).
    enum { kSlots = 32 };
    Win29990  win[kSlots];
    win[0].mParent = 0;                                        // sentinel frame
    win[0].mFlag   = 0;
    win[0].mpDesc  = (ChartNode*)root;

    Win29990* sp      = &win[1];
    unsigned  pending = 1;
    int       offset  = 0;
    int       i       = 0;

    do {
        --sp;                                                  // pop one frame
        int        node = sp->mParent;
        int        flag = sp->mFlag;
        ChartNode* desc = sp->mpDesc;
        --pending;

        if (i != 0)
            ((int*)buf->mpRec)[3 + (flag + node * 4) * 2] = i;

        OutRec* out = (OutRec*)((char*)buf->mpRec + offset);
        out->mNode  = node;
        int idx = desc->mIndex;
        out->mIndex = idx;
        out->mValA  = desc->mpA->mSlotHi[idx];
        out->mValB  = desc->mpB->mSlotLo[idx];

        ChartNode* eB = desc->mpB;
        if (eB->mpA == 0) {                                    // B is a leaf
            out->mMarkA = eB->mA24;
            out->mMarkB = eB->mA20;
        } else {                                               // descend into B
            sp->mpDesc  = eB;
            sp->mParent = i;
            sp->mFlag   = 1;
            ++pending;
            ++sp;
            out->mMarkA = -1;
            out->mMarkB = -1;
        }

        ChartNode* eA = desc->mpA;
        if (eA->mpA == 0) {                                    // A is a leaf
            out->mLoA = eA->mA24;
            out->mLoB = eA->mA20;
        } else {                                               // descend into A
            sp->mpDesc  = eA;
            sp->mParent = i;
            sp->mFlag   = 0;
            ++pending;
            ++sp;
            out->mLoA = -1;
            out->mLoB = -1;
        }

        offset += 0x20;
        ++i;
    } while (pending != 0);
}

// ---------------------------------------------------------------------------
// 0x00729b20  lock a vertex buffer, copy it into a fresh element buffer
// ---------------------------------------------------------------------------

// The vertex descriptor only the byte stride of which is read here.
struct VDesc {
    uint8_t pad00[0x0f];
    uint8_t mStride;                                           // +0x0f
};

// rw::graphics::VertexBuffer (the members the helper touches).
struct VBi {
    VDesc*   m_desc;                                           // +0x00
    uint8_t  pad04[4];
    int      m_base;                                           // +0x08
    int      m_numVertices;                                    // +0x0c
    uint8_t  pad10[8];
    void*    m_disposableBuffer;                               // +0x18

    unsigned Lock(unsigned char flag, unsigned start, unsigned count);   // 0x011f3620
    void*    Unlock();                                                   // 0x011f36a0
};

// The buffers hand back bare vtable-bearing pointers; only slot 0 (a no-argument
// refresh) is ever invoked on them.
typedef void (__thiscall *VSlot0)(void*);
static inline void CallSlot0(void* p)
{
    VSlot0* vt = *(VSlot0**)p;
    vt[0](p);
}

void* __cdecl FUN_00720010(int size);                          // 0x00720010 AllocEltBuffer
void* __cdecl MemCopy(void* dst, const void* src, unsigned n); // 0x011e0744 memcpy

// @ 0x00729b20  FUN_00729b20
void* FUN_00729b20(VBi* p1, void* p2, void** p3)
{
    void* rb = p1->m_disposableBuffer;
    if (rb != 0) {
        if (p2 != 0) {
            *p3 = p2;
            CallSlot0(p2);
        }
        return rb;
    }

    VDesc* desc = p1->m_desc;
    void* locked = (void*)p1->Lock(1, desc->mStride * p1->m_base,
                                      desc->mStride * p1->m_numVertices);
    if (locked == 0)
        return rb;

    unsigned size = desc->mStride * p1->m_numVertices;
    void*    seg  = FUN_00720010((int)size);
    if (seg == 0) {
        p1->Unlock();
        return 0;
    }
    void* out = (char*)seg + 0xc;
    MemCopy(out, locked, size);
    *p3 = seg;
    CallSlot0(seg);
    p1->Unlock();
    return out;
}
