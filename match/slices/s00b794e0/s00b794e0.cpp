// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Slice s00b794e0: Simulator::cObstacleManager.  Construction, node insertion,
// teardown and the three cHierGrid sphere queries that walk the buffered hit
// list.

#include <string.h>
#include <math.h>

// ---------------------------------------------------------------- types
struct V3 { float x, y, z; };

// The 0x18-byte wrapper the queries hand to cHierGrid::QuerySphereResult.  It
// is a fixed vector over a caller supplied 0x100-element buffer.
struct BufferedVec {
    void* begin;
    void* end;
    void* cap;
    int   pad0;
    int   pad1;
    int   pad2;
    void Init(void* buf, unsigned n, int* zero);      // 0xb97280
    void Resize(int n);                               // 0xb98ea0
};

// eastl::vector<void*> layout.
struct PointerVec {
    int* begin;
    int* end;
    int* cap;
    void Reserve(int n);                              // 0xd01790
    void Resize(int n);                               // 0x473270
    void Grow(int* pos, int** value);                 // 0xaea5d0
    void Push(int* pos, int* value);                   // 0xb96600
};

struct Grid {
    int QuerySphereResult(float radius, float* dir, int maxN, void** out);   // 0x702760
    Grid* Construct();                                                       // 0x703ce0
};

struct PlanetModel {
    void DirectionToSurfacePosition(V3* out, V3* dir);  // 0xb815a0
};

struct FixedPoolBase {
    void Init(void* buf, unsigned size, unsigned elem, int a, int b);  // 0x921260
};

struct PoolDesc {
    void* head;
    int   pad;
    void* begin;
    void* end;
    int   elem;
    void* alloc;
};

struct PoolBase {
    int SizeFor(int n);                                // 0x9213c0
};

struct BucketAlloc {
    void Find(void* out, int a, int b, int c);         // 0x921440
};

struct FindRes {
    char found;
    char p0, p1, p2;
    int  value;
};

struct F2 { float a, b; F2() {} F2(float x, float y) { a = x; b = y; } };

struct Gonzago {
    void Ctor();                                       // 0xb5b960
};

struct Sub;

struct Sim {
    void Teardown();                                   // 0xb781d0
};

// The cGonzagoSubsystem half of the manager; its `this` is the host object + 4.
struct Sub {
    void Detach();                                     // 0xb79a60
};

struct ObMgr {
    void* Construct();                                 // 0xb79740
    void* Init(int* a, int* b);                        // 0xb794e0
    int*  Insert(int* out, int* key, int unused);      // 0xb795c0
    int*  FindNode(int* bucket, int* key, unsigned h); // 0xb72f10
    void  Destroy();                                   // 0xb79aa0
    void  Query(V3* dir, PointerVec* out, unsigned mask, float radius,
                char flag, V3* p);                     // 0xb79c30
    int   Count(V3* dir, float radius, char filter);   // 0xb79e50
    void  QueryNear(V3* dir, float radius, unsigned mask,
                    PointerVec* out);                  // 0xb7a1d0
    void* NewNode(int* key);                           // 0xb78020
    void  FreeNode(int node);                          // 0xb72e50
    void  DoFreeNodes(int n);                          // 0xc76610
};

typedef void (__thiscall *FnV)(void* self);
typedef void (__thiscall *FnV2)(void* self, int a, int b);
typedef int  (__thiscall *FnCount)(void* self, void* out);

// ---------------------------------------------------------------- globals
extern float g_156b390, g_156b394, g_156b398, g_156b39c;
extern float g_156b3a0, g_156b3a4, g_156b3a8;
extern float g_16880d4, g_16880d8, g_16880dc;
extern float g_1485720;                // 1.0f
extern float g_1470f1c;                // 2.0f
extern int   g_154df28;
extern unsigned g_156b3ac;             // noun count cap

// ---------------------------------------------------------------- callees
void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b,
                         const char* file, int line);                     // 0xf473a0
void __cdecl operator delete(void*);                                      // 0xf47380
void* __cdecl FUN_00921340(int n);                                        // 0x921340
void __stdcall FUN_00b745f0(int h, void* a, void** pb, void** pb2, void* bv,
                            void** pb3, void* desc);                      // 0xb745f0
int __stdcall FUN_00b72f10(int* head, int* key, unsigned h);              // 0xb72f10
void __stdcall FUN_00b77b60(void* self, int a, int b);                    // 0xb77b60
void __cdecl RemoveHandler(int h, int a, int b, int c, int d);             // 0x571db0
void __cdecl FUN_00b779c0(int* begin, int* end, float x, float y, float z); // 0xb779c0
void* __cdecl PlanetModelGet();                                           // 0xb3d350
void* __stdcall NounManager(unsigned key);                                // 0xb3d300
void* __fastcall CreateNoun(void* self);                                  // 0xb20c60
void __cdecl CopyPtrs(void* first, void* last, void* dst);                // 0x5f4e10
float __cdecl QuatDist(V3* a, V3* b, V3* c);                              // 0x698b30
void __fastcall FUN_00b74130(ObMgr* self);                                // 0xb74130
void __fastcall FUN_00b76160(ObMgr* self);                                // 0xb76160

struct HashtableOps {
    void FreeTable(int* buckets, unsigned n);                              // 0xb759b0
    void Free70(int* buckets, unsigned n);                                 // 0xb75b80
    void Free68(int* buckets, unsigned n);                                 // 0xb75bf0
};
struct PoolCtor2 {
    void Init(int* a, int* b);                                             // 0xb77780
};

// ======================================================================
// 0xb794e0   fixed-pool hashtable constructor
// ======================================================================
// @ 0x00b794e0 Init
void* ObMgr::Init(int* a, int* b)
{
    PoolDesc d;
    char* base = (char*)this + 0x43c;

    d.head = 0;
    ((FixedPoolBase*)&d)->Init(base, 0x1800, 0x18, 8, 0);
    d.begin = base;
    d.end = base + 0x1800;
    d.elem = 0x18;
    d.alloc = (char*)this + 0x34;

    int h = (int)FUN_00921340(0x101);
    FUN_00b745f0(h, a, (void**)&b, (void**)&b, b, (void**)&b, &d);

    *(F2*)((char*)this + 0x10) = F2(10000.0f, 2.0f);
    *(int*)((char*)this + 0x18) = 0;

    unsigned n = (unsigned)((PoolBase*)&d)->SizeFor(*(int*)((char*)this + 0xc));
    if (n > *(unsigned*)((char*)this + 8))
        DoFreeNodes((int)n);
    return this;
}

// ======================================================================
// 0xb795c0   bucket-list insert
// ======================================================================
// @ 0x00b795c0 Insert
int* ObMgr::Insert(int* out, int* key, int unused)
{
    FindRes fr;
    ((BucketAlloc*)((char*)this + 0x10))->Find(&fr, *(int*)((char*)this + 8),
                                               *(int*)((char*)this + 0xc), 1);
    if (fr.found)
        FreeNode(fr.value);

    unsigned h = (unsigned)(key[2] ^ key[0]);
    unsigned idx = h % (unsigned)*(int*)((char*)this + 8);
    int* node = (int*)NewNode(key);
    idx *= 4;
    int bucket = *(int*)(*(int*)((char*)this + 4) + idx);
    int* e = FindNode((int*)bucket, key, h);

    if (e == 0) {
        *(int*)((char*)node + 0xc70) = bucket;
        *(int*)(*(int*)((char*)this + 4) + idx) = (int)node;
    } else {
        *(int*)((char*)node + 0xc70) = *(int*)((char*)e + 0xc70);
        *(int*)((char*)e + 0xc70) = (int)node;
    }

    ++*(int*)((char*)this + 0xc);
    out[0] = (int)node;
    out[1] = *(int*)((char*)this + 4) + idx;
    (void)unused;
    return out;
}

// ======================================================================
// 0xb79740   manager constructor
// ======================================================================
// @ 0x00b79740 Construct
void* ObMgr::Construct()
{
    int one;

    *(void**)this = (void*)0x13eb384;
    ((Gonzago*)((char*)this + 4))->Ctor();
    *(void**)((char*)this + 4) = (void*)0x14650e8;
    *(void**)this = (void*)0x14650cc;
    *(void**)((char*)this + 8) = (void*)0x14650c8;

    *(int*)((char*)this + 0x20) = 0;
    *(int*)((char*)this + 0x24) = 0;
    *(int*)((char*)this + 0x28) = 0;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 0x30) = 0;
    *(int*)((char*)this + 0x34) = 0;

    ((ObMgr*)((char*)this + 0x38))->Init(&one, &one);
    ((ObMgr*)((char*)this + 0x2094))->Init(&one, &one);

    *(void**)((char*)this + 0x40f0) = (char*)this + 0x4108;
    *(void**)((char*)this + 0x40f4) = (char*)this + 0x4108;
    *(void**)((char*)this + 0x40f8) = (char*)this + 0x4908;
    *(int*)((char*)this + 0x4104) = 0;

    *(void**)((char*)this + 0x4908) = (char*)this + 0x4920;
    *(void**)((char*)this + 0x490c) = (char*)this + 0x4920;
    *(int*)((char*)this + 0x491c) = 0;
    *(void**)((char*)this + 0x4910) = (char*)this + 0x49e0;

    ((PoolCtor2*)((char*)this + 0x49e0))->Init(&one, &one);
    ((PoolCtor2*)((char*)this + 0x4f30))->Init(&one, &one);

    *(float*)((char*)this + 0x5480) = g_156b390;
    *(float*)((char*)this + 0x5484) = g_156b394;
    *(float*)((char*)this + 0x5488) = g_156b398;
    *(float*)((char*)this + 0x548c) = g_16880d4;
    *(float*)((char*)this + 0x5490) = g_16880d8;
    *(float*)((char*)this + 0x5494) = g_16880dc;
    *(float*)((char*)this + 0x5498) = g_156b39c;
    *(float*)((char*)this + 0x549c) = g_156b3a0;
    *(float*)((char*)this + 0x54a0) = g_156b3a4;
    *(float*)((char*)this + 0x54a4) = g_156b3a8;

    *(float*)((char*)this + 0x54b8) = g_1485720;
    *(float*)((char*)this + 0x54bc) = g_1470f1c;
    *(int*)((char*)this + 0x54b0) = 1;
    *(int*)((char*)this + 0x54ac) = (int)&g_154df28;
    *(int*)((char*)this + 0x54b4) = 0;
    *(int*)((char*)this + 0x54c0) = 0;

    *(float*)((char*)this + 0x54d8) = g_1485720;
    *(float*)((char*)this + 0x54dc) = g_1470f1c;
    *(int*)((char*)this + 0x54d0) = 1;
    *(int*)((char*)this + 0x54cc) = (int)&g_154df28;
    *(int*)((char*)this + 0x54d4) = 0;
    *(int*)((char*)this + 0x54e0) = 0;

    *(float*)((char*)this + 0x54f8) = g_1485720;
    *(float*)((char*)this + 0x54fc) = g_1470f1c;
    *(int*)((char*)this + 0x54f0) = 1;
    *(int*)((char*)this + 0x54ec) = (int)&g_154df28;
    *(int*)((char*)this + 0x54f4) = 0;
    *(int*)((char*)this + 0x5500) = 0;

    *(int*)((char*)this + 0x551c) = 0;
    *(void**)((char*)this + 0x5508) = (char*)this + 0x5520;
    *(void**)((char*)this + 0x550c) = (char*)this + 0x5520;
    *(void**)((char*)this + 0x5510) = (char*)this + 0x55a0;
    *(int*)((char*)this + 0x55a0) = 0;

    *(int*)((char*)this + 0x55bc) = 0;
    *(void**)((char*)this + 0x55a8) = (char*)this + 0x55c0;
    *(void**)((char*)this + 0x55ac) = (char*)this + 0x55c0;
    *(void**)((char*)this + 0x55b0) = (char*)this + 0x56c0;
    *(float*)((char*)this + 0x56d0) = g_1485720;
    *(float*)((char*)this + 0x56d4) = g_1470f1c;
    *(int*)((char*)this + 0x56c8) = 1;
    *(int*)((char*)this + 0x56c4) = (int)&g_154df28;
    *(int*)((char*)this + 0x56cc) = 0;
    *(int*)((char*)this + 0x56d8) = 0;

    *(int*)((char*)this + 0x20) |= 1;

    void* p = EAAllocate(0x84, "Simulator/cObstacleManager", 0, 0, 0, 0);
    if (p != 0)
        *(void**)((char*)this + 0x55a4) = ((Grid*)p)->Construct();
    else
        *(void**)((char*)this + 0x55a4) = 0;
    return this;
}

// ======================================================================
// 0xb79a60   drop the messaging handler, then hand off to Simulator teardown
// ======================================================================
// @ 0x00b79a60 Detach
void Sub::Detach()
{
    int h = *(int*)((char*)this + 0x20);
    if (h != 0) {
        *(int*)((char*)this + 0x20) = 0;
        RemoveHandler(h, *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28),
                      *(int*)((char*)this + 0x2c), *(int*)((char*)this + 0x30));
    }
    ((Sim*)((char*)this - 4))->Teardown();
}

// ======================================================================
// 0xb79aa0   manager destruction
// ======================================================================
// @ 0x00b79aa0 Destroy
void ObMgr::Destroy()
{
    char* p = (char*)this + 0x38;
    char* q = (char*)this + 0x2094;

    FUN_00b77b60(p, 0, 0);
    FUN_00b77b60(q, 0, 0);

    ((HashtableOps*)p)->FreeTable(*(int**)(p + 4), *(unsigned*)(p + 8));
    *(int*)(p + 0xc) = 0;

    ((HashtableOps*)q)->FreeTable(*(int**)(q + 4), *(unsigned*)(q + 8));
    *(int*)(q + 0xc) = 0;

    char* r = (char*)this + 0x54a8;
    ((HashtableOps*)r)->Free70(*(int**)(r + 4), *(unsigned*)(r + 8));
    *(int*)(r + 0xc) = 0;

    r = (char*)this + 0x54c8;
    ((HashtableOps*)r)->Free68(*(int**)(r + 4), *(unsigned*)(r + 8));
    *(int*)(r + 0xc) = 0;

    r = (char*)this + 0x54e8;
    ((HashtableOps*)r)->Free68(*(int**)(r + 4), *(unsigned*)(r + 8));
    *(int*)(r + 0xc) = 0;

    FUN_00b74130(this);

    void* pm = PlanetModelGet();
    void* sub = *(void**)((char*)pm + 0x24);
    void** vt = *(void***)sub;
    int* arr;
    int cnt = ((FnCount)vt[0xb0 / 4])(sub, &arr);

    ((PointerVec*)((char*)this + 0x55a8))->Resize(cnt);
    CopyPtrs(arr, (char*)arr + cnt * 4, *(void**)((char*)this + 0x55a8));

    FUN_00b76160(this);

    int n = (*(int*)((char*)this + 0x40f4) - *(int*)((char*)this + 0x40f0)) >> 2;
    while (n < g_156b3ac) {
        void* nm = NounManager(0x3ed8573);
        int* noun = (int*)CreateNoun(nm);
        if (noun != 0) {
            void** nvt = *(void***)noun;
            ((FnV)nvt[0])(noun);
        }
        {
            void** nvt = *(void***)noun;
            ((FnV)nvt[0x44 / 4])(noun);
        }
        int* end = *(int**)((char*)this + 0x40f4);
        if (end != *(int**)((char*)this + 0x40f8)) {
            *(int**)((char*)this + 0x40f4) = end + 1;
            if (end != 0) {
                *end = (int)noun;
                if (noun != 0) {
                    void** nvt = *(void***)noun;
                    ((FnV)nvt[0])(noun);
                }
            }
        } else {
            ((PointerVec*)((char*)this + 0x40f0))->Grow(end, &noun);
        }
        if (noun != 0) {
            void** nvt = *(void***)noun;
            ((FnV)nvt[1])(noun);
        }
        ++n;
    }

    void* self = (char*)this + 4;
    void** svt = *(void***)self;
    ((FnV2)svt[0x38 / 4])(self, 0, 0);
}

// ======================================================================
// 0xb79c30   sphere query: collect matching objects
// ======================================================================
// @ 0x00b79c30 Query
void ObMgr::Query(V3* dir, PointerVec* out, unsigned mask, float radius,
                  char flag, V3* p7)
{
    if (*(int*)(*(int*)((char*)this + 0x55a4) + 0x24) ==
        *(int*)(*(int*)((char*)this + 0x55a4) + 0x28))
        return;

    V3 pos;
    ((PlanetModel*)PlanetModelGet())->DirectionToSurfacePosition(&pos, dir);

    int zero = 0;
    int mem[0x100];
    BufferedVec buf;
    buf.begin = mem;
    buf.end = mem;
    buf.cap = (char*)mem + 0x400;
    buf.pad0 = 0;
    buf.pad1 = 0;
    buf.pad2 = 0;
    buf.Init(mem, 0x100, &zero);

    int n = (*(Grid**)((char*)this + 0x55a4))->QuerySphereResult(
        radius, (float*)&pos, 0x100, (void**)&buf);
    buf.Resize(n);

    memcpy(out->begin, out->end, 0);
    out->end -= out->end - out->begin;
    out->Reserve(n);

    for (int i = 0; i < n; ++i) {
        int o = ((int*)buf.begin)[i];
        if ((mask & (1u << *(int*)(o + 0x88))) == 0)
            continue;
        int w = *(int*)(o + 0x70);
        if (w != 0 && ((*(unsigned*)(w + 4) >> 15) & 1) == 0)
            continue;
        float dx = dir->x - *(float*)(o + 0x38);
        float dy = dir->y - *(float*)(o + 0x3c);
        float dz = dir->z - *(float*)(o + 0x40);
        float r = *(float*)(o + 0x44) + radius;
        if (dx * dx + dy * dy + dz * dz < r * r) {
            int* end = out->end;
            if (end < out->cap) {
                out->end = end + 1;
                if (end != 0)
                    *end = o;
            } else {
                out->Push(end, &o);
            }
        }
    }

    if (flag != 0) {
        V3* v = p7;
        if (v == 0)
            v = &pos;
        FUN_00b779c0(out->begin, out->end, v->x, v->y, v->z);
    }

    if (buf.begin != 0 && *(int*)((char*)buf.begin - 4) != 0)
        operator delete(buf.begin);
}

// ======================================================================
// 0xb79e50   sphere query: count matching objects
// ======================================================================
// One object's contribution to the count: mesh/state filter, then sphere test.
#define OB_COUNT_TEST(q)                                                      \
    {                                                                         \
        int o_ = (q);                                                         \
        if (!(filter != 0 && *(int*)(o_ + 0x88) > 2)) {                       \
            int w_ = *(int*)(o_ + 0x70);                                      \
            if (!(w_ != 0 && ((*(unsigned*)(w_ + 4) >> 15) & 1) == 0)) {      \
                float dx_ = dir->x - *(float*)(o_ + 0x38);                    \
                float dy_ = dir->y - *(float*)(o_ + 0x3c);                    \
                float dz_ = dir->z - *(float*)(o_ + 0x40);                    \
                float r_ = *(float*)(o_ + 0x44) + radius;                     \
                if (dx_ * dx_ + dy_ * dy_ + dz_ * dz_ < r_ * r_)              \
                    ++count;                                                  \
            }                                                                 \
        }                                                                     \
    }

// @ 0x00b79e50 Count
int ObMgr::Count(V3* dir, float radius, char filter)
{
    int count = 0;
    int i = 0;
    if (*(int*)(*(int*)((char*)this + 0x55a4) + 0x24) ==
        *(int*)(*(int*)((char*)this + 0x55a4) + 0x28))
        return count;

    V3 pos;
    ((PlanetModel*)PlanetModelGet())->DirectionToSurfacePosition(&pos, dir);

    int zero = 0;
    int mem[0x100];
    BufferedVec buf;
    buf.begin = mem;
    buf.end = mem;
    buf.cap = (char*)mem + 0x400;
    buf.pad0 = 0;
    buf.pad1 = 0;
    buf.pad2 = 0;
    buf.Init(mem, 0x100, &zero);

    int n = (*(Grid**)((char*)this + 0x55a4))->QuerySphereResult(
        radius, (float*)&pos, 0x100, (void**)&buf);
    buf.Resize(n);

    if (n > 3) {
        int* p = (int*)buf.begin + 2;
        int blocks = (int)(((unsigned)(n - 4) >> 2) + 1);
        i = blocks * 4;
        do {
            OB_COUNT_TEST(p[-2]);
            OB_COUNT_TEST(p[-1]);
            OB_COUNT_TEST(p[0]);
            OB_COUNT_TEST(p[1]);
            p += 4;
        } while (--blocks != 0);
    }
    if (i < n) {
        do {
            OB_COUNT_TEST(((int*)buf.begin)[i]);
            ++i;
        } while (i < n);
    }
    if (buf.begin != 0 && *(int*)((char*)buf.begin - 4) != 0)
        operator delete(buf.begin);

    return count;
}

// ======================================================================
// 0xb7a1d0   sphere query over an object-type mask
// ======================================================================
// @ 0x00b7a1d0 QueryNear
void ObMgr::QueryNear(V3* dir, float radius, unsigned mask, PointerVec* out)
{
    if (*(int*)(*(int*)((char*)this + 0x55a4) + 0x24) ==
        *(int*)(*(int*)((char*)this + 0x55a4) + 0x28))
        return;

    V3 pos;
    ((PlanetModel*)PlanetModelGet())->DirectionToSurfacePosition(&pos, dir);

    int zero = 0;
    int mem[0x100];
    BufferedVec buf;
    buf.begin = mem;
    buf.end = mem;
    buf.cap = (char*)mem + 0x400;
    buf.pad0 = 0;
    buf.pad1 = 0;
    buf.pad2 = 0;
    buf.Init(mem, 0x100, &zero);

    int n = (*(Grid**)((char*)this + 0x55a4))->QuerySphereResult(
        radius, (float*)&pos, 0x100, (void**)&buf);
    buf.Resize(n);

    memcpy(out->begin, out->end, 0);
    out->end -= out->end - out->begin;
    out->Reserve(n);

    for (int i = 0; i < n; ++i) {
        int o = ((int*)buf.begin)[i];
        if ((mask & (1u << *(int*)(o + 0x88))) == 0)
            continue;
        int w = *(int*)(o + 0x70);
        if (w != 0 && ((*(unsigned*)(w + 4) >> 15) & 1) == 0)
            continue;

        float ox = *(float*)(o + 0x38);
        float oy = *(float*)(o + 0x3c);
        float oz = *(float*)(o + 0x40);
        float dx = dir->x - ox;
        float dy = dir->y - oy;
        float dz = dir->z - oz;
        if (sqrtf(dz * dz + (dx * dx + dy * dy)) <
            *(float*)(o + 0x4c) + *(float*)(o + 0x48)) {
            float len = sqrtf(oy * oy + oz * oz + ox * ox) + *(float*)(o + 0x4c);
            float inv = 1.0f / sqrtf(oy * oy + oz * oz + ox * ox);
            V3 qP;
            qP.x = (ox * inv) * len;
            qP.y = (inv * oy) * len;
            qP.z = (inv * oz) * len;
            V3 qB;
            qB.x = (ox + qP.x) * 0.5f;
            qB.y = (oy + qP.y) * 0.5f;
            qB.z = (oz + qP.z) * 0.5f;

            if (QuatDist(dir, &qB, &qP) < *(float*)(o + 0x48) + radius ||
                QuatDist(dir, (V3*)(o + 0x38), &qB) < *(float*)(o + 0x44) + radius) {
                int* end = out->end;
                if (end < out->cap) {
                    out->end = end + 1;
                    if (end != 0)
                        *end = o;
                } else {
                    out->Push(end, &o);
                }
            }
        }
    }

    if (buf.begin != 0 && *(int*)((char*)buf.begin - 4) != 0)
        operator delete(buf.begin);
}
