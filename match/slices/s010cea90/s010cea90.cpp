// Slice s010cea90 — 0x010cea90 .. 0x010cfc70.
//
// Havok collision agents for the creature "multi-ray convex" shape: the
// hkBvTreeStreamAgent ctor/dtor pair, contact-point flipping, and the
// multi-ray convex query/process entry points.
//
// Compile with /O2 /MD /Gy /EHsc /TP (x87 TU: no /arch:SSE, no /fp:fast).

#include <intrin.h>

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

// ---------------------------------------------------------------------------
// Imports / Havok singletons
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned idx);
extern "C" __declspec(dllimport) void* __stdcall TlsSetValue(unsigned idx, void* v);

extern "C" void  FUN_0107db10(void* self, int dummy, void* p, int bytes, int align); // __thiscall deallocateChunk
extern "C" void* FUN_0107f4a0(void* arr, int n, int elem);                // hkArrayUtil::_reserveExactly
extern "C" void  FUN_010cdd30(int a, int b, int c, int* d);               // __thiscall processCollision core
extern "C" void  FUN_010e49c0(int a, int b, void* cp, void* c1, void* c2);
extern "C" void  FUN_010e4d50(int a, int b, int c, void* collector);
extern "C" void  FUN_010810f0(void* dst, int dummy, float* a, float* b);  // __thiscall setMulInverseMul
extern "C" void  FUN_01081360(void* dst, int dummy, void* tr, float* v);  // __thiscall setTransformedPos
extern "C" void  FUN_010814a0(void* dst, int dummy, void* tr, void* v);   // __thiscall setRotatedDir
extern "C" void __stdcall FUN_01103bc0(void* p);                          // hkAgent1nMachine::Create

// hkMemory singleton: [0x016e4178] -> instance -> vtable
struct HkMemory {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* alloc(int size, int align);                 // vtbl +0x10
    virtual void  release(void* p, unsigned short f, int a);  // vtbl +0x14
};
#define HKMEM (*(HkMemory**)0x016e4178)

struct HkThreadMemory {
    void __thiscall deallocateChunk(void* p, int bytes, int align);
};
#define THREADMEM(p) ((HkThreadMemory*)(p))

// Contact manager: vtable +0x10 releases a proxy id, +0x08 creates one.
struct BvAgentApi {
    void __thiscall processCollision(int a, int b, int c, int* d);   // 0x010cdd30
};

struct ContactMgr {
    virtual void v0();
    virtual void v1();
    virtual unsigned short makeContact(int* a, int* b, int* in, void* pt); // vtbl +8
    virtual void v2();
    virtual void release(int id);                                       // vtbl +0x10
};

// Collision shape used for the ray query: vtable +0x14 casts a ray.
struct RayShape {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual char castRay(char* hit, float* p0, float* nrm);             // vtbl +0x14
};

// Point collector: vtable +0x04 receives a finished hkCdPoint.
struct PointCollector {
    virtual void v0();
    virtual char addPoint(void* pt);                                    // vtbl +4
};

struct HkTransform {
    float m[16];
};

struct CdPoint {
    float pos[4];     // +0x00
    float nrm[3];     // +0x10
    float dist;       // +0x1c
    int   pad[4];     // +0x20 .. +0x2f
};

struct HkArray {
    void* begin;      // +0x00
    int   count;      // +0x04
    int   cap;        // +0x08
};

// Agent with the 4-element inline short array at +0x0c (hkMultiRayConvexAgent).
struct MRayAgent {
    void*        vtbl;   // +0x00
    unsigned short tag4;  // +0x04 class tag (0x20)
    unsigned short flags; // +0x06
    int          mgr;    // +0x08
    unsigned short* map; // +0x0c
    int          count;  // +0x10
    int          cap;    // +0x14
};

// Agent with the 16-element inline vector array at +0x30 (hkBvTreeStreamAgent).
struct BvStreamAgent {
    void*        vtbl;       // +0x00
    unsigned short tag4;     // +0x04 class tag (0x40)
    unsigned short flags;    // +0x06
    int          mgr;        // +0x08
    int          field0c;    // +0x0c
    int          pad10[8];   // +0x10 .. +0x2f
    void*        arr;        // +0x30 begin
    int          arrCount;   // +0x34
    int          arrCap;     // +0x38
};
#define BV_ARR(p) (*(HkArray*)((char*)(p) + 0x30))

// The two "contact point with flipped normal" helpers.
struct V4 { float v[4]; };
struct ContactPoint {
    V4 p;   // +0x00
    V4 n;   // +0x10
};

static void __fastcall cpSetFlipped(ContactPoint* self, int, const ContactPoint* o)
{
    float d = o->n.v[3];
    self->p = o->p;
    self->p.v[0] = d * o->n.v[0] + self->p.v[0];
    self->p.v[1] = d * o->n.v[1] + self->p.v[1];
    self->p.v[2] = d * o->n.v[2] + self->p.v[2];
    self->p.v[3] = d * o->n.v[3] + self->p.v[3];
    self->n.v[0] = -o->n.v[0];
    self->n.v[1] = -o->n.v[1];
    self->n.v[2] = -o->n.v[2];
    *(int*)&self->n.v[3] = *(int*)&o->n.v[3];
}

// hkMonitorStream begin/end marker (TLS ring buffer).
static void monMark(int tag)
{
    void* end = TlsGetValue(0x016e42a8);
    void* cur = TlsGetValue(0x016e42a4);
    if (cur < end) {
        int* p = (int*)TlsGetValue(0x016e42a4);
        p[0] = tag;
        p[1] = (int)__rdtsc();
        TlsSetValue(0x016e42a4, p + 3);
    }
}

// ---------------------------------------------------------------------------
// 0x010cea90 — hkBvTreeStreamAgent destructor (deleting form).
// ---------------------------------------------------------------------------
// @ 0x010cea90
void* __fastcall FUN_010cea90(BvStreamAgent* self, int, unsigned flags)
{
    self->vtbl = (void*)0x14a43f8;
    {
        int cap = *(int*)((char*)self + 0x38);
        if ((cap & 0x80000000) == 0) {
            void* tm = TlsGetValue(*(unsigned*)0x016e4174);
            THREADMEM(tm)->deallocateChunk(*(void**)((char*)self + 0x30),
                (*(int*)((char*)self + 0x38) & 0x3fffffff) << 2, 0x14);
        }
    }
    self->vtbl = (void*)0x13ef094;
    if (flags & 1)
        HKMEM->release(self, self->flags, 0x1c);
    return self;
}

// ---------------------------------------------------------------------------
// 0x010ceaf0 — hkBvTreeStreamAgent constructor with the agent-machine array.
// ---------------------------------------------------------------------------
// @ 0x010ceaf0
BvStreamAgent* __fastcall FUN_010ceaf0(BvStreamAgent* self, int, int a, int b, int* c, int d)
{
    self->mgr = d;
    self->flags = 1;
    self->vtbl = (void*)0x14a43f8;
    BV_ARR(self).begin = (char*)self + 0x3c;
    BV_ARR(self).count = 0;
    BV_ARR(self).cap = 0x80000001;
    self->field0c = *c;
    *(int*)((char*)self + 0x10) = 0;
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0x18) = 0;
    *(int*)((char*)self + 0x1c) = 0;
    *(int*)((char*)self + 0x20) = 0;
    *(int*)((char*)self + 0x24) = 0;
    *(int*)((char*)self + 0x28) = 0;
    *(int*)((char*)self + 0x2c) = 0;
    FUN_01103bc0((char*)self + 0x30);
    return self;
}

// ---------------------------------------------------------------------------
// 0x010ceb50 — allocate and construct the 0x40-byte tree-stream agent.
// ---------------------------------------------------------------------------
// @ 0x010ceb50
void* FUN_010ceb50(int a, int b, int* c, int d)
{
    BvStreamAgent* p = (BvStreamAgent*)HKMEM->alloc(0x40, 0x1c);
    *(unsigned short*)((char*)p + 4) = 0x40;
    return FUN_010ceaf0(p, 0, a, b, c, d);
}

// ---------------------------------------------------------------------------
// 0x010ceb90 — non-deleting hkBvTreeStreamAgent destructor.
// ---------------------------------------------------------------------------
// @ 0x010ceb90
void __fastcall FUN_010ceb90(BvStreamAgent* self, int)
{
    self->vtbl = (void*)0x14a43f8;
    {
        int cap = *(int*)((char*)self + 0x38);
        if ((cap & 0x80000000) == 0) {
            void* tm = TlsGetValue(*(unsigned*)0x016e4174);
            THREADMEM(tm)->deallocateChunk(*(void**)((char*)self + 0x30),
                (*(int*)((char*)self + 0x38) & 0x3fffffff) << 2, 0x14);
        }
    }
    self->vtbl = (void*)0x13ef094;
}

// ---------------------------------------------------------------------------
// 0x010cec10 — one-shot closest-points query through a temporary collector.
// ---------------------------------------------------------------------------
// @ 0x010cec10
void __stdcall FUN_010cec10(int a, int b, int c, int d)
{
    int local[3];
    local[2] = d;
    local[1] = 0x7f7fffee;
    local[0] = 0x14a43a4;
    FUN_010e4d50(b, a, c, local);
}

// ---------------------------------------------------------------------------
// 0x010cec70 — run the pair query and flip the normals of every new contact.
// ---------------------------------------------------------------------------
// @ 0x010cec70
void __fastcall FUN_010cec70(void* self, int, int a, int b, int c, int* d)
{
    float old = *(float*)((char*)d + 0x3034);
    int* first = (int*)*d;

    ((BvAgentApi*)self)->processCollision(b, a, c, d);
    while (first < (int*)*d) {
        cpSetFlipped((ContactPoint*)first, 0, (ContactPoint*)first);
        first += 0xc;
    }
    if (old != *(float*)((char*)d + 0x3034)) {
        *(float*)((char*)d + 0x20) = -*(float*)((char*)d + 0x20);
        *(float*)((char*)d + 0x24) = -*(float*)((char*)d + 0x24);
        *(float*)((char*)d + 0x28) = -*(float*)((char*)d + 0x28);
    }
}

// ---------------------------------------------------------------------------
// 0x010cecf0 — hkContactPoint::setFlipped.
// ---------------------------------------------------------------------------
// @ 0x010cecf0
void __fastcall FUN_010cecf0(ContactPoint* self, int, const ContactPoint* o)
{
    float d = o->n.v[3];
    self->p = o->p;
    self->p.v[0] = d * o->n.v[0] + self->p.v[0];
    self->p.v[1] = d * o->n.v[1] + self->p.v[1];
    self->p.v[2] = d * o->n.v[2] + self->p.v[2];
    self->p.v[3] = d * o->n.v[3] + self->p.v[3];
    self->n.v[0] = -o->n.v[0];
    self->n.v[1] = -o->n.v[1];
    self->n.v[2] = -o->n.v[2];
    *(int*)&self->n.v[3] = *(int*)&o->n.v[3];
}

// ---------------------------------------------------------------------------
// 0x010ced60 — build two collectors around a normal-flipped contact point.
// ---------------------------------------------------------------------------
struct QueryResult {
    void* vtbl;   // +0x00
    int   dist;   // +0x04
    float p[4];   // +0x08 .. +0x17
    int   user;   // +0x18
};

// @ 0x010ced60
void __stdcall FUN_010ced60(int a, int b, float* c, int d, int e)
{
    float cp[12];
    QueryResult col1;
    QueryResult col2;
    int i;

    cp[0] = c[0];
    cp[1] = c[1];
    cp[2] = c[2];
    cp[3] = c[3];
    cp[4] = -c[4];
    cp[5] = -c[5];
    cp[6] = -c[6];
    cp[7] = -c[7];
    cp[8] = c[8];
    cp[9] = c[9];
    cp[10] = c[10];
    cp[11] = c[11];

    col1.vtbl = (void*)0x14a43ac;
    col1.dist = 0x7f7fffee;
    for (i = 0; i < 4; i++)
        col1.p[i] = c[i];
    col1.user = d;

    if (e != 0) {
        col2.vtbl = (void*)0x14a43ac;
        col2.dist = 0x7f7fffee;
        for (i = 0; i < 4; i++)
            col2.p[i] = c[4 + i];
        col2.user = e;
        FUN_010e49c0(b, a, cp, &col1, &col2);
        return;
    }
    FUN_010e49c0(b, a, cp, &col1, 0);
}

// ---------------------------------------------------------------------------
// 0x010ceea0 — allocate and construct the 0x40-byte shape-stream agent.
// ---------------------------------------------------------------------------
// @ 0x010ceea0
void* FUN_010ceea0(int a, int b, int* c, int d)
{
    BvStreamAgent* p = (BvStreamAgent*)HKMEM->alloc(0x40, 0x1c);
    *(unsigned short*)((char*)p + 4) = 0x40;
    FUN_010ceaf0(p, 0, b, a, c, d);
    p->vtbl = (void*)0x14a442c;
    return p;
}

// ---------------------------------------------------------------------------
// 0x010cf090 — hkMultiRayConvexAgent::cleanup.
// ---------------------------------------------------------------------------
// @ 0x010cf090
void __fastcall FUN_010cf090(MRayAgent* self, int)
{
    int n = self->count;
    int i;
    for (i = 0; i < n; i++) {
        unsigned short raw = self->map[i];
        int id = raw;
        if (id != 0xffff)
            ((ContactMgr*)self->mgr)->release(id);
    }
    (*(void (__thiscall**)(MRayAgent*, int))self->vtbl)(self, 1);
}

// ---------------------------------------------------------------------------
// 0x010cf0d0 / 0x010cf470 — ray/shape closest-point queries.  Both entry
// points run the identical loop; the second is the static wrapper.
// ---------------------------------------------------------------------------
static __forceinline void mrClosestPoints(int* bodyA, int* bodyB, int* input, int* collector)
{
    int* shapeA = (int*)*bodyA;
    RayShape* shapeB = (RayShape*)*bodyB;
    HkTransform t;
    int n;
    float* ray;
    int i;

    monMark(0x14a4478);   // "TtmultiRay-cvx"
    FUN_010810f0(&t, 0, (float*)bodyB[2], (float*)bodyA[2]);

    n = shapeA[4];
    ray = (float*)shapeA[3];
    for (i = 0; i < n; i++) {
        __declspec(align(16)) float p0[4], p1[4], nrm[4];
        char hit;

        p0[0] = t.m[0] * ray[0] + (t.m[4] * ray[1] + t.m[8] * ray[2]) + t.m[12];
        p0[1] = t.m[1] * ray[0] + (t.m[5] * ray[1] + t.m[9] * ray[2]) + t.m[13];
        p0[2] = t.m[2] * ray[0] + (t.m[6] * ray[1] + t.m[10] * ray[2]) + t.m[14];
        p0[3] = 0.0f;

        p1[0] = t.m[0] * ray[4] + (t.m[4] * ray[5] + t.m[8] * ray[6]) + t.m[12];
        p1[1] = t.m[1] * ray[4] + (t.m[5] * ray[5] + t.m[9] * ray[6]) + t.m[13];
        p1[2] = t.m[2] * ray[4] + (t.m[6] * ray[5] + t.m[10] * ray[6]) + t.m[14];
        p1[3] = 0.0f;

        shapeB->castRay(&hit, p0, nrm);
        if (hit) {
            float* T = (float*)bodyB[2];
            CdPoint pt;
            float f;
            int j;

            f = 1.0f - 1.0f;
            pt.pos[0] = (p1[0] * 1.0f + p0[0] * f) * T[0]
                      + ((p1[1] * 1.0f + p0[1] * f) * T[4]
                      +  (p1[2] * 1.0f + p0[2] * f) * T[8]) + T[12];
            pt.pos[1] = (p1[0] * 1.0f + p0[0] * f) * T[1]
                      + ((p1[1] * 1.0f + p0[1] * f) * T[5]
                      +  (p1[2] * 1.0f + p0[2] * f) * T[9]) + T[13];
            pt.pos[2] = (p1[0] * 1.0f + p0[0] * f) * T[2]
                      + ((p1[1] * 1.0f + p0[1] * f) * T[6]
                      +  (p1[2] * 1.0f + p0[2] * f) * T[10]) + T[14];
            pt.pos[3] = 0.0f;
            pt.nrm[0] = nrm[0] * T[0] + (nrm[1] * T[4] + nrm[2] * T[8]);
            pt.nrm[1] = nrm[0] * T[1] + (nrm[1] * T[5] + nrm[2] * T[9]);
            pt.nrm[2] = nrm[0] * T[2] + (nrm[1] * T[6] + nrm[2] * T[10]);
            pt.dist = (1.0f - 1.0f) * ray[3] + *(float*)((char*)shapeA + 0x18);
            for (j = 0; j < 4; j++)
                pt.pad[j] = 0;
            ((PointCollector*)collector)->addPoint(&pt);
        }
        ray += 8;
    }
    monMark(0x149cc34);
}

// @ 0x010cf0d0
void __fastcall FUN_010cf0d0(int, int, int* bodyA, int* bodyB, int* input, int* collector)
{
    mrClosestPoints(bodyA, bodyB, input, collector);
}

// @ 0x010cf470
void __stdcall FUN_010cf470(int* bodyA, int* bodyB, int* input, int* collector)
{
    mrClosestPoints(bodyA, bodyB, input, collector);
}

// ---------------------------------------------------------------------------
// 0x010cf850 — hkMultiRayConvexAgent constructor (proxy-id array).
// ---------------------------------------------------------------------------
// @ 0x010cf850
MRayAgent* __fastcall FUN_010cf850(MRayAgent* self, int, int* a, int b, int c, int d)
{
    int n;
    int i;

    self->mgr = d;
    self->flags = 1;
    self->vtbl = (void*)0x14a4488;
    self->map = (unsigned short*)((char*)self + 0x18);
    self->count = 0;
    self->cap = 0x80000004;

    n = *(int*)(*a + 0x10);
    if ((self->cap & 0x3fffffff) < n) {
        int m = (self->cap & 0x3fffffff) * 2;
        if (m <= n)
            m = n;
        FUN_0107f4a0(&self->map, m, 2);
    }
    self->count = n;
    for (i = 0; i < n; i++)
        self->map[i] = -1;
    return self;
}

// ---------------------------------------------------------------------------
// 0x010cf8d0 — hkMultiRayConvexAgent::processCollision.
// ---------------------------------------------------------------------------
// @ 0x010cf8d0
void __fastcall FUN_010cf8d0(MRayAgent* self, int, int* bodyA, int* bodyB, int* input, int** out)
{
    int* shapeA = (int*)*bodyA;
    RayShape* shapeB = (RayShape*)*bodyB;
    HkTransform t;
    int n;
    float* ray;
    int i;

    monMark(0x14a4478);
    FUN_010810f0(&t, 0, (float*)bodyB[2], (float*)bodyA[2]);

    n = shapeA[4];
    ray = (float*)shapeA[3];
    for (i = 0; i < n; i++) {
        __declspec(align(16)) float p0[4], p1[4], nrm[4];
        char hit;

        p0[0] = t.m[0] * ray[0] + (t.m[4] * ray[1] + t.m[8] * ray[2]) + t.m[12];
        p0[1] = t.m[1] * ray[0] + (t.m[5] * ray[1] + t.m[9] * ray[2]) + t.m[13];
        p0[2] = t.m[2] * ray[0] + (t.m[6] * ray[1] + t.m[10] * ray[2]) + t.m[14];
        p0[3] = 0.0f;

        p1[0] = t.m[0] * ray[4] + (t.m[4] * ray[5] + t.m[8] * ray[6]) + t.m[12];
        p1[1] = t.m[1] * ray[4] + (t.m[5] * ray[5] + t.m[9] * ray[6]) + t.m[13];
        p1[2] = t.m[2] * ray[4] + (t.m[6] * ray[5] + t.m[10] * ray[6]) + t.m[14];
        p1[3] = 0.0f;

        shapeB->castRay(&hit, p0, nrm);
        if (!hit) {
            int id = self->map[i];
            if (id != -1) {
                ((ContactMgr*)self->mgr)->release(id);
                self->map[i] = -1;
            }
        } else {
            ContactPoint* pt = (ContactPoint*)*out;
            float f = 1.0f - 1.0f;
            int id;

            pt->p.v[0] = p1[0] * 1.0f + p0[0] * f;
            pt->p.v[1] = p1[1] * 1.0f + p0[1] * f;
            pt->p.v[2] = p1[2] * 1.0f + p0[2] * f;
            pt->p.v[3] = p1[3] * 1.0f + p0[3] * f;
            FUN_01081360(pt, 0, (void*)bodyB[2], pt->p.v);
            FUN_010814a0(pt->n.v, 0, (void*)bodyB[2], nrm);
            pt->n.v[3] = (1.0f - 1.0f) * ray[3] + *(float*)((char*)shapeA + 0x18);

            id = self->map[i];
            if (id == -1) {
                id = ((ContactMgr*)self->mgr)->makeContact(bodyA, bodyB, input, pt);
                self->map[i] = id;
            }
            if (self->map[i] != -1) {
                *out = (int*)((char*)*out + 0x30);
                *(short*)((char*)pt + 0x20) = self->map[i];
            }
        }
        ray += 8;
    }
    monMark(0x149cc34);
}

// ---------------------------------------------------------------------------
// 0x010cfc70 — allocate and construct the 0x20-byte multi-ray convex agent.
// ---------------------------------------------------------------------------
// @ 0x010cfc70
void* FUN_010cfc70(int a, int b, int c, int d)
{
    MRayAgent* p = (MRayAgent*)HKMEM->alloc(0x20, 0x1c);
    *(unsigned short*)((char*)p + 4) = 0x20;
    return FUN_010cf850(p, 0, (int*)a, b, c, d);
}
