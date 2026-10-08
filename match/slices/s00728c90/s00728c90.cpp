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

// @ 0x007296e0 — copy `rows` rows of dword data from src to dst with independent strides.
void FUN_007296e0(int* dst, int* src, int rows)
{
    int      srcBase   = src[1];
    int*     d         = (int*)dst[0];
    unsigned dstStride = (unsigned)dst[1];
    unsigned srcStride = *(unsigned short*)((char*)src + 10);
    unsigned count     = *(unsigned short*)((char*)src + 8) >> 2;
    for (; rows > 0; --rows) {
        int* s = (int*)srcBase;
        for (unsigned i = 0; i < count; ++i)
            d[i] = s[i];
        srcBase += (int)(srcStride >> 2) * 4;
        d = (int*)((char*)d + (dstStride & 0xfffffffc));
    }
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

// @ 0x00729290  (PARTIAL)
int FUN_00729290(void* self)
{
    (void)self;
    return 1;
}

// @ 0x00729300  (PARTIAL)
int FUN_00729300(int a, int b, int* c, int d, int e, int f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return 0;
}

// @ 0x007298b0  (PARTIAL: x87 area/size helper)
double FUN_007298b0(float* a, int b)
{
    (void)a; (void)b;
    return 0.0;
}

// @ 0x00729990  (PARTIAL)
int FUN_00729990(void* a, void* b)
{
    (void)a; (void)b;
    return 0;
}

// @ 0x00729b20  (PARTIAL: VertexBuffer lock/copy)
int* FUN_00729b20(void* vb, int* a, int* b)
{
    (void)vb; (void)a; (void)b;
    return 0;
}
