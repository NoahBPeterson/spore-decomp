// Slice s00b509b0 -- planet terrain collision helpers: plane projection onto the cube-mapped terrain,
// Havok packfile shape loader, planet rigid body create/update, tuning-property loader, and the
// EASTL hashtable instances (erase / equal_range / insert) used by the Havok resource cache.
// Built /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"
#include <math.h>
#include <intrin.h>
#include <new.h>
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP
#define VP16 VP4 VP4 VP4 VP4

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

struct RefObj {
    virtual int AddRef();
    virtual int Release();
};

// ------------------------------------------------------------------ plane projection
struct UV { float u, v; int face; };
struct TerrainMapF {
    float GetFloat(UV* uv);                                     // 0x00f8d620
};
struct TerrainMapV {
    void GetVector4(Vec4* out, UV* uv);                         // 0x00f89e50
};
struct PlanetModelT {
    char pad[0xf0];
    u8   hasWater;                                              // 0xf0
    float GetWaterHeight();                                     // 0xb7e390
};
struct Plane { float x, y, z, w; };
struct PlaneList {
    Plane* data;                                                // 0
    int    count;                                               // 4
    float  maxDist;                                             // 8
};
struct TerrainSampler {
    char pad0[0x34];
    PlanetModelT* planet;                                       // 0x34
    TerrainMapV*  normals;                                      // 0x38
    TerrainMapF*  heights;                                      // 0x3c
    char pad1[0x4c - 0x40];
    float bias;                                                 // 0x4c
    float scale;                                                // 0x50

    void ProjectPlanes(PlaneList* in, Plane* out);              // 0xb509b0
};
extern Vec3 g_normalBias;                                       // 0x1569b1c

// @ 0x00b509b0
void TerrainSampler::ProjectPlanes(PlaneList* in, Plane* out)
{
    int count = in->count;   // read once (the original counts down a copy)
    for (int i = 0; i < count; ++i) {
        float maxd = in->maxDist;
        Plane* p = &in->data[i];
        float px = p->x, py = p->y, pz = p->z;
        float inv = 1.0f / sqrtf(px * px + (py * py + pz * pz) + 1e-08f);
        float uy = py * inv;
        float ux = inv * px;
        float uz = pz * inv;
        float ax = fabsf(px), ay = fabsf(py), az = fabsf(pz);
        UV uv;
        if (az < ax || az < ay) {
            if (ay < ax) {
                uv.u = (py / px + 1.0f) * 0.5f;
                uv.v = (pz / ax + 1.0f) * 0.5f;
                uv.face = 2;
                if (px < 0.0f) uv.face = 3;
            } else {
                uv.u = (pz / py + 1.0f) * 0.5f;
                uv.v = (px / ay + 1.0f) * 0.5f;
                if (py < 0.0f) uv.face = 5; else uv.face = 4;
            }
        } else {
            uv.u = (px / pz + 1.0f) * 0.5f;
            uv.v = (py / az + 1.0f) * 0.5f;
            if (pz < 0.0f) uv.face = 1; else uv.face = 0;
        }
        float h = heights->GetFloat(&uv) * scale + bias;
        float h2 = h;
        if (planet->hasWater) {
            float wh = planet->GetWaterHeight();
            const float* pf = &h;
            if (wh > h) pf = &wh;    // unordered keeps h, as the original's ja
            h2 = *pf;
        }
        Vec3 n;
        if (!planet->hasWater || !(planet->GetWaterHeight() > h2)) {   // unordered -> normal path (jbe)
            Vec4 v;
            normals->GetVector4(&v, &uv);
            float nx = v.x * 2.0f - g_normalBias.x;
            float ny = v.y * 2.0f - g_normalBias.y;
            float nz = v.z * 2.0f - g_normalBias.z;
            float ninv = 1.0f / sqrtf((nx * nx + nz * nz) + ny * ny + 1e-08f);
            n.x = ninv * nx;
            n.y = ny * ninv;
            n.z = nz * ninv;
        } else {
            n.x = ux; n.y = uy; n.z = uz;
        }
        float d = ((n.y * py + n.z * pz) + n.x * px) + -((n.x * (ux * h2) + n.z * (uz * h2)) + n.y * (uy * h2)) - p->w;
        if (d < maxd) {      // NaN d takes the FLT_MAX path, as in the original (comiss maxd,d; jbe)
            out[i].x = n.x; out[i].y = n.y; out[i].z = n.z;
        } else {
            d = 3.40282e+38f;
        }
        out[i].w = d;
    }
}

// ------------------------------------------------------------------ memory + Havok bits
typedef short s16;
// Havok allocator (global pointer at 0x16e4178): slot 4 allocates a chunk, slot 5 frees it.
struct hkMemory {
    VP4
    virtual void* allocateChunk(int size, int type);            // 0x10
    virtual void  deallocateChunk(void* p, int size, int type); // 0x14
};
extern hkMemory* g_hkMemory;                                    // 0x16e4178

struct hkReferencedObject {
    virtual ~hkReferencedObject() {}
    u16 memSize;                                                // +4
    s16 refCount;                                               // +6
    void addReference() { if (memSize) ++refCount; }
    void removeReference() {
        if (memSize) {
            --refCount;
            if (refCount == 0)
                delete this;
        }
    }
    static void operator delete(void* p) {
        g_hkMemory->deallocateChunk(p, ((hkReferencedObject*)p)->memSize, 0x24);
    }
};

// ------------------------------------------------------------------ small classes
// Intrusive ref-counted object (EA::RefCountTemplate): count at +4, deleted through slot 0.
struct RCObj {
    virtual ~RCObj() {}
    int rc;
    void Release() {
        int n = (*(volatile int*)&rc += -1);
        if (n == 0) {
            rc = 1;
            delete this;
        }
    }
};

// @ 0x00b50de0 (destructor) and @ 0x00b50e30 (scalar deleting destructor)
struct AutoRC {
    RCObj* p;
    ~AutoRC() { if (p) p->Release(); }
};
struct HkOwner : hkReferencedObject {
    char pad[0x30];
    AutoRC a;                                                   // 0x38
    AutoRC b;                                                   // 0x3c
    HkOwner();
};
HkOwner::HkOwner() { a.p = 0; b.p = 0; }

// @ 0x00b50e80
int __stdcall GetResourceTypes(u32* out, u32 n)
{
    if (out && n >= 1)
        *out = 0x448ae7e2;
    return 1;
}

// @ 0x00b50ea0
bool __stdcall IsResourceType(u32 a, u32 b)
{
    if (a == 0x448ae7e2 && b == 0x448ae7e2)
        return true;
    return false;
}

// ------------------------------------------------------------------ Havok resource + factory
struct cResourceBase {
    virtual int AddRef();
    virtual int Release();
    virtual ~cResourceBase() {}
    long rc;                                                    // 4
    long f8, fc, f10;
    cResourceBase() {
        _InterlockedExchange(&rc, 0);
        f8 = 0; fc = 0; f10 = 0;
    }
};
struct cHavokResource : cResourceBase {
    RCObj* p14;                                                 // 0x14 owned, deleted through slot 0
    int*   arr;                                                 // 0x18 owned array (count cookie at -4)
    int    f1c, f20, f24, f28;
    cHavokResource() {
        p14 = 0; arr = 0; f1c = 0; f20 = 0;
    }
    virtual ~cHavokResource();
};
// @ 0x00b50ef0 (scalar deleting destructor)
cHavokResource::~cHavokResource()
{
    if (p14) delete p14;
    if (arr && arr[-1] != 0)
        ::operator delete(arr);
}

void* __cdecl operator_new(unsigned, const char*, int, int, int, int);
inline void* operator new(unsigned n, const char* name, int a, int b, int c, int d) {
    return operator_new(n, name, a, b, c, d);
}
inline void operator delete(void*, const char*, int, int, int, int) {}

struct ResLoader {
    VP4 VP4 VP
    virtual bool Load(int a0, cHavokResource* res, int a2, int a3);   // 0x24
    // @ 0x00b50f40
    bool Create(int a0, cResourceBase** out, int a2, int a3);
};
bool ResLoader::Create(int a0, cResourceBase** out, int a2, int a3)
{
    cHavokResource* r = new ("Simulator/cHavokResource", 0, 0, 0, 0) cHavokResource();
    if (!r)
        return false;
    r->AddRef();
    if (Load(a0, r, a2, a3)) {
        *out = r;
        r->AddRef();
        r->Release();
        return true;
    }
    r->Release();
    return false;
}

struct ZoneObject {
    static void* operator new(unsigned n, const char* name, int a, int b, int c, int d);   // 0x926020
    static void operator delete(void*, const char*, int, int, int, int) {}
};
struct ZoneRC : ZoneObject {
    virtual int AddRef();
    virtual int Release();
    long rc;
    ZoneRC() { _InterlockedExchange(&rc, 0); }
};
struct cHavokResourceFactory : ZoneRC {
    virtual int Release();
};
struct ResMan {
    VP VP VP
    virtual bool Get(u32 key, RefObj** out, int a, int b, int c, int d);   // 0xc
    VP4 VP4 VP4 VP
    virtual void AddFactory(int kind, cHavokResourceFactory* f, int c);    // 0x44
};
ResMan* __cdecl GetResMan();                                    // 0x67dcd0

// @ 0x00b50ff0
void RegisterHavokResourceFactory()
{
    cHavokResourceFactory* f = new ("Simulator/cHavokResourceFactory", 0, 0, 0, 0) cHavokResourceFactory();
    GetResMan()->AddFactory(1, f, 0);
}

// ------------------------------------------------------------------ lookups in the shape cache
struct NodeA {                                                  // 0xa0 bytes
    u32 key[3];
    u32 pad0;
    char value[0x10];                                           // +0x10 (returned by FindNear)
    float f;                                                    // +0x20
    char pad1[0x90 - 0x24];
    NodeA* next;                                                // +0x90
    NodeA(const void* v);                                       // 0xb4d980
};
struct Cursor {
    char pad0[8];
    NodeA* end;                                                 // 8
    char pad1[4];
    NodeA* cur;                                                 // 0x10
    NodeA** bucket;                                             // 0x14
};

// @ 0x00b51040
void* __cdecl FindNear(Cursor* c, float x)
{
    NodeA* n = c->cur;
    if (n != c->end) {
        do {
            if (fabs((double)n->f - (double)x) <= 1.5258789e-05f)
                return &n->value;
            n = c->cur->next;
            c->cur = n;
            while (!n) {
                c->bucket += 1;
                n = *c->bucket;
                c->cur = n;
            }
            n = c->cur;
        } while (n != c->end);
    }
    return 0;
}

// ------------------------------------------------------------------ Havok packfile shape loader
struct hkStreamReader : hkReferencedObject {};
struct hkMemoryStreamReader : hkStreamReader {
    char pad[0x1c - 8];
    hkMemoryStreamReader(const void* buf, int size, int mode);  // 0x10801d0
    static void* operator new(unsigned n) {
        void* p = g_hkMemory->allocateChunk((int)n, 0x17);
        ((hkReferencedObject*)p)->memSize = (u16)n;
        return p;
    }
    static void operator delete(void* p) {
        g_hkMemory->deallocateChunk(p, ((hkReferencedObject*)p)->memSize, 0x17);
    }
};
struct hkBinaryPackfileReader : hkReferencedObject {
    char pad[0x6c - 8];
    hkBinaryPackfileReader();                                   // 0x112b6c0
    virtual void p1();
    virtual void loadEntireFile(hkStreamReader* r);             // 0x8
    VP4 VP VP
    virtual hkReferencedObject* getContents();                  // 0x24
    static void* operator new(unsigned n) {
        void* p = g_hkMemory->allocateChunk((int)n, 6);
        ((hkReferencedObject*)p)->memSize = (u16)n;
        return p;
    }
    static void operator delete(void* p) {
        g_hkMemory->deallocateChunk(p, ((hkReferencedObject*)p)->memSize, 6);
    }
};
struct HkResData : RefObj {
    char pad[0x14];
    int* begin;                                                 // 0x18
    int* end;                                                   // 0x1c
};
struct ResObj : RefObj {
    VP
    virtual RefObj* Query(u32 id);                              // 0xc
};
struct hkShape;
hkShape* __cdecl GetShapeFromPackfile(hkBinaryPackfileReader* pk);   // 0xb63fb0
void __cdecl BuildShapeBody(hkShape* shape, float scale, void* dst);   // 0x1127680
// Per-load scratch handed to the holder.
__declspec(align(16)) struct ShapeInit {
    RefObj* out;                                                // 0
    u32 a, b;                                                   // 4, 8
    hkShape* shape;                                             // 0xc
    float one;                                                  // 0x10
    int kind;                                                   // 0x14
    hkReferencedObject* contents;                               // 0x18
    u32 pad1c;
    float f20, f24;
    u32 p28, p2c;
    float f30, f34, f38, f3c, f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64, f68, f6c;
    u32 z70;
};
struct ShapeHolder {
    char pad[0x20];
    char dst[1];                                                // 0x20
    void Prepare(ShapeInit* s);                                 // 0xb4f610
};

// @ 0x00b510b0
bool __cdecl LoadHavokShape(u32 key, ShapeHolder* holder)
{
    RefObj* res = 0;
    ResMan* mgr = GetResMan();
    {
        RefObj* old = res;
        if (old) {
            res = 0;
            old->Release();
        }
    }
    if (mgr->Get(key, &res, 0, 0, 0, 0) && res) {
        HkResData* hr = (HkResData*)((ResObj*)res)->Query(0x532dc8b);
        if (hr) {
            hr->AddRef();
            hkMemoryStreamReader* rd = new hkMemoryStreamReader(hr->begin, (int)(hr->end - hr->begin), 2);
            hkBinaryPackfileReader* pk = new hkBinaryPackfileReader();
            pk->loadEntireFile(rd);
            hkReferencedObject* contents = pk->getContents();
            if (contents->memSize)
                ++contents->refCount;
            hkShape* shape = GetShapeFromPackfile(pk);
            delete pk;
            if (rd)
                delete rd;
            hr->Release();
            if (shape) {
                ShapeInit s;
                s.a = 0; s.b = 0;
                s.z70 = 0;
                s.one = 1.0f;
                s.contents = contents;
                s.out = 0;
                s.shape = shape;
                s.kind = 2;
                s.f20 = 0.0f; s.f24 = 0.0f;
                s.f3c = 0.0f; s.f38 = 0.0f; s.f34 = 0.0f; s.f30 = 0.0f;
                s.f40 = 0.0f; s.f44 = 0.0f; s.f48 = 0.0f; s.f4c = 0.0f; s.f50 = 0.0f; s.f54 = 0.0f;
                s.f58 = 0.0f; s.f5c = 0.0f; s.f60 = 0.0f; s.f64 = 0.0f; s.f68 = 0.0f; s.f6c = 0.0f;
                holder->Prepare(&s);
                BuildShapeBody(shape, 1.0f, holder->dst);
                if (s.out)
                    s.out->Release();
                return true;
            }
        }
    }
    if (res)
        res->Release();
    return false;
}

// ------------------------------------------------------------------ planet rigid body
__declspec(align(16)) struct hkVector4 { float x, y, z, w; };
struct hkShape2 : hkReferencedObject {
    u32 pad[(0x60 - 8) / 4];
    hkShape2(void* planetModel);                                // 0xb4ffb0
    static void* operator new(unsigned n) {
        void* p = g_hkMemory->allocateChunk((int)n, 0x24);
        ((hkReferencedObject*)p)->memSize = (u16)n;
        return p;
    }
};
struct hkRigidBodyCinfo {
    u32 filter;                                                 // 0
    hkShape2* shape;                                            // 4
    u32 pad0[(0x94 - 8) / 4];
    float v[4];                                                 // 0x94 (hkVector4 scale: 1,1,1,0)
    u32 pad1[(0xac - 0xa4) / 4];
    float f;                                                    // 0xac
    u8 motion;                                                  // 0xb0
    u8 m1, m2, m3;
    u32 pad2[2];
    hkRigidBodyCinfo();                                         // 0x1087ed0
};
struct hkRigidBody {
    void setPosition(const hkVector4& p);                       // 0x1087820
    void addProperty(u32 key, unsigned __int64 value);          // 0x10825a0
};
struct hkWorld {
    void* addEntity(hkRigidBody* b, int mode);                  // 0x1082ee0
    void updateCollisionFilterOnWorld(int a, int b);            // 0x10869e0
};
struct PlanetModelB { char pad[0x24]; };
PlanetModelB* __cdecl GetPlanetModel();                         // 0xb3d350
hkRigidBody* __cdecl CreateRigidBody(hkRigidBodyCinfo* info);   // 0xb4d880
extern hkWorld*     g_hkWorld;                                  // 0x167ecd0
extern hkRigidBody* g_planetBody;                               // 0x167ecd4
extern float g_bodyF;                                           // 0x1488874

// @ 0x00b512f0
void CreatePlanetBody()
{
    if (g_hkWorld && !g_planetBody && GetPlanetModel()) {
        hkRigidBodyCinfo info;
        hkShape2* shape = new hkShape2(GetPlanetModel());
        info.v[1] = 1.0f;
        info.v[0] = 1.0f;
        info.v[2] = 1.0f;
        info.v[3] = 0.0f;
        info.shape = shape;
        info.motion = 7;
        info.filter = 1;
        info.f = g_bodyF;
        hkRigidBody* body = CreateRigidBody(&info);
        info.shape->removeReference();
        g_planetBody = body;
        hkVector4 zero;
        zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f; zero.w = 0.0f;
        body->setPosition(zero);
        g_planetBody->addProperty(0, 1);
        g_planetBody->addProperty(1, (u32)GetPlanetModel());
        g_hkWorld->addEntity(body, 1);
        g_hkWorld->updateCollisionFilterOnWorld(0, 1);
    }
}

// ------------------------------------------------------------------ tuning properties
struct PropSet;
u8    __cdecl GetPropBool (PropSet* p, u32 id, u8 def);       // 0x64f350
float __cdecl GetPropFloat(PropSet* p, u32 id, float def);      // 0x4e1c70
extern u8 g_b0, g_b1, g_b2;                                     // 0x167ecd9 / ecda / ecd8
extern float g_t0, g_t1, g_t2, g_t3, g_t4, g_t5, g_t6, g_t7, g_t8, g_t9;

// @ 0x00b51460
void __cdecl LoadPlanetTuning(PropSet* p)
{
    g_b0 = GetPropBool(p, 0xdaeb0c3, g_b0);
    g_t0 = GetPropFloat(p, 0x48ae581d, g_t0);
    g_t1 = GetPropFloat(p, 0x35a44d51, g_t1);
    g_t2 = GetPropFloat(p, 0x45d6c96b, g_t2);
    g_t3 = GetPropFloat(p, 0x68e23f96, g_t3);
    g_b1 = GetPropBool(p, 0x99d89285, g_b1);
    g_t4 = GetPropFloat(p, 0x85f3d491, g_t4);
    g_t5 = GetPropFloat(p, 0x7161041a, g_t5);
    g_t6 = GetPropFloat(p, 0xd339bde9, g_t6);
    g_t7 = GetPropFloat(p, 0x9a1e6eb8, g_t7);
    g_t8 = GetPropFloat(p, 0xd55b5929, g_t8);
    g_t9 = GetPropFloat(p, 0x14750a09, g_t9);
    g_b2 = GetPropBool(p, 0x3ac2d33a, g_b2);
}

// ------------------------------------------------------------------ update
struct PlanetBodyData { char pad[0x34]; PlanetModelB* planet; char pad2[4]; void* mapOwner; };
struct PlanetMapOwner { VP VP VP virtual void* GetMap(); };
struct PlanetModelC { char pad[0x24]; PlanetMapOwner* owner; };
struct MapObj { char pad[8]; void* ptr; };
struct PlanetWatcher {
    char pad[0x30];
    u8 created;                                                 // 0x30
    void Update();                                              // 0xb515e0
};
void __cdecl RebuildPlanetBody();                               // 0xb4f7f0

// @ 0x00b515e0
void PlanetWatcher::Update()
{
    if (g_hkWorld) {
        if (g_planetBody) {
            PlanetBodyData* d = *(PlanetBodyData**)((char*)g_planetBody + 0x1c);
            bool diff = d->planet != GetPlanetModel();
            if (!diff) {
                PlanetModelC* pm = (PlanetModelC*)GetPlanetModel();
                PlanetMapOwner* ow = pm->owner;
                MapObj* m = (MapObj*)ow->GetMap();
                diff = d->mapOwner != m->ptr;
            }
            if (diff)
                RebuildPlanetBody();
            if (g_planetBody)
                return;
        }
        CreatePlanetBody();
        created = 1;
    }
}

// ------------------------------------------------------------------ EASTL hashtable instances
struct NodeS { u32 first, b; NodeS* next; };
struct IterS { NodeS* node; NodeS** bucket; };
struct TblS {
    char pad0[0xc];
    int count;                                                  // 0xc
    char pad1[0x1c - 0x10];
    NodeS* freeList;                                            // 0x1c
    char pad2[0x24 - 0x20];
    NodeS* poolBegin;                                           // 0x24
    NodeS* poolEnd;                                             // 0x28
    char pad3[0x30 - 0x2c];
    NodeS* inlineNode;                                          // 0x30
    IterS* erase(IterS* out, NodeS* node, NodeS** bucket);      // 0xb51640
};

// @ 0x00b51640
IterS* TblS::erase(IterS* out, NodeS* node, NodeS** bucket)
{
    NodeS* nx = node->next;
    out->bucket = bucket;
    out->node = nx;
    while (!nx) {
        out->bucket += 1;
        nx = *out->bucket;
        out->node = nx;
    }
    NodeS* cur = *bucket;
    if (cur == node) {
        *bucket = cur->next;
    } else {
        NodeS* prev = cur;
        cur = cur->next;
        while (cur != node) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
    }
    if (node != inlineNode) {
        if (node >= poolBegin && node < poolEnd) {
            *(NodeS**)node = freeList;
            freeList = node;
            --count;
            return out;
        }
        ::operator delete(node);
    }
    --count;
    return out;
}

struct RangeOut { NodeA* first; NodeA** firstBucket; NodeA* last; NodeA** lastBucket; };
struct RehashResult { bool need; u32 newCount; };
struct RehashPolicy { void GetRehashRequired(RehashResult* out, u32 buckets, u32 count, u32 add); };   // 0x921440
void* __cdecl operator_new_a(unsigned n, unsigned align, int a, const char* name, int b, int c, const char* file, int line);   // 0xf473d0
extern const char g_ehFile[];                                   // 0x13ebb38
void* __cdecl operator_new_b(unsigned n, const char* name, int a, int b, const char* file, int line);   // 0xf473a0
struct TblA {
    char pad0[4];
    NodeA** buckets;                                            // 4
    u32 bucketCount;                                            // 8
    int count;                                                  // 0xc
    RehashPolicy policy;                                        // 0x10
    NodeA* DoFindNode(NodeA* head, const void* key, u32 code);  // 0xb4fae0
    void DoRehash(u32 n);                                       // 0xb4fa20
    void equal_range(RangeOut* out, const u32* key);            // 0xb51780
    void* DoInsertValue(void* out, const void* v, int tag);     // 0xb51840
};

// @ 0x00b51780
void TblA::equal_range(RangeOut* out, const u32* key)
{
    u32 c3 = key[2];
    u32 code = key[0] ^ c3;
    u32 idx = code % bucketCount;
    NodeA** b = &buckets[idx];
    NodeA* n = DoFindNode(buckets[idx], key, code);
    if (n) {
        NodeA* e = n->next;
        while (e && key[0] == e->key[0] && key[1] == e->key[1] && c3 == e->key[2])
            e = e->next;
        NodeA** pb = b;
        if (!e) {
            pb = b + 1;
            if (!*pb) {
                do { ++pb; } while (!*pb);
            }
            e = *pb;
        }
        out->first = n;
        out->firstBucket = b;
        out->last = e;
        out->lastBucket = pb;
        return;
    }
    NodeA* endn = buckets[bucketCount];
    NodeA** endb = &buckets[bucketCount];
    out->first = endn;
    out->firstBucket = endb;
    out->last = endn;
    out->lastBucket = endb;
}

struct IterA { NodeA* node; NodeA** bucket; };

// @ 0x00b51840
void* TblA::DoInsertValue(void* outp, const void* vp, int tag)
{
    IterA* out = (IterA*)outp;
    const u32* v = (const u32*)vp;
    RehashResult rr;
    policy.GetRehashRequired(&rr, bucketCount, count, 1);
    if (rr.need)
        DoRehash(rr.newCount);
    u32 code = v[2] ^ v[0];
    u32 idx = code % bucketCount;
    NodeA* nn = (NodeA*)operator_new_a(0xa0, 0x10, 0, "Simulator", 0, 0, g_ehFile, 0xe5);
    if (nn)
        new (nn) NodeA(vp);
    nn->next = 0;
    NodeA* head = buckets[idx];
    NodeA* found = DoFindNode(head, vp, code);
    if (!found) {
        nn->next = head;
        buckets[idx] = nn;
    } else {
        nn->next = found->next;
        found->next = nn;
    }
    ++count;
    out->node = nn;
    out->bucket = buckets + idx;
    return out;
}

struct NodeB { u32 key[4]; NodeB* next; };                      // 0x14 bytes
struct InsertOut { NodeB* node; NodeB** bucket; u8 inserted; };
struct TblB {
    char pad0[4];
    NodeB** buckets;                                            // 4
    u32 bucketCount;                                            // 8
    int count;                                                  // 0xc
    RehashPolicy policy;                                        // 0x10
    void DoRehash(u32 n);                                       // 0xb4fb20
    InsertOut* DoInsertKey(InsertOut* out, const u32* key, int tag);   // 0xb51930
};

// @ 0x00b51930
InsertOut* TblB::DoInsertKey(InsertOut* out, const u32* key, int tag)
{
    u32 code = key[0] ^ key[2];
    u32 idx = code % bucketCount;
    NodeB** b = &buckets[idx];
    NodeB* p = *b;
    for (; p; p = p->next) {
        if (key[0] == p->key[0] && key[1] == p->key[1] && key[2] == p->key[2])
            break;
    }
    if (!p) {
        RehashResult rr;
        policy.GetRehashRequired(&rr, bucketCount, count, 1);
        NodeB* nn = (NodeB*)operator_new_b(0x14, "Simulator", 0, 0, g_ehFile, 0xd1);
        if (nn) {
            nn->key[0] = key[0];
            nn->key[1] = key[1];
            nn->key[2] = key[2];
            nn->key[3] = key[3];
        }
        nn->next = 0;
        if (rr.need) {
            idx = code % rr.newCount;
            DoRehash(rr.newCount);
        }
        nn->next = buckets[idx];
        buckets[idx] = nn;
        ++count;
        out->node = nn;
        out->inserted = 1;
        out->bucket = &buckets[idx];
        return out;
    }
    out->node = p;
    out->inserted = 0;
    out->bucket = b;
    return out;
}
