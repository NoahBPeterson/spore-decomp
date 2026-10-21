// Slice s010c3860: Havok 3.1.0 hkSphereShape / hkTriangleShape / hkGroupFilter methods.
// Range 0x010c3860..0x010c44c3. Flags: /vc71 /O2 /MD /Gy /TP (Havok 3.1.0 = VC .NET 2003).
#include "types.h"
#include <intrin.h>
#include <math.h>

// ---------------------------------------------------------------------------
// monitor-stream tick helpers (same shape as the sibling s010c2890 capsule slice)
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // 0x0149cc34
extern const char hkTtrcSphere[];                   // 0x014a2934 ("TtrcSphere")
extern const char hkTtrcTriangle[];                 // 0x014a3bf0 ("TriangleShp")
extern const float hkRayEpsilon;                    // 0x01485378
extern const float hkOne;                           // 0x01485720

struct hkMonitorCommand { const char* m_command; uint32_t m_time0; uint32_t m_pad; };
static __forceinline void hkTimerCommand(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
    {
        hkMonitorCommand* c = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        c->m_command = name;
        volatile uint32_t t = (uint32_t)__rdtsc();
        c->m_time0 = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, c + 1);
    }
}

class hkBool
{
public:
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
    char m_bool;
};

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };

// A collision sphere is a hkVector4 whose w holds the radius (same 16-byte layout).
class __declspec(align(16)) hkSphere { public: float x, y, z, w; };

struct hkShapeRayCastInput
{
    hkVector4 m_from;                   // +0
    hkVector4 m_to;                     // +0x10
    uint32_t m_filterInfo;              // +0x20
    void* m_rayShapeCollectionFilter;   // +0x24
};
struct hkShapeRayCastOutput
{
    float m_normal[4];                  // +0
    uint32_t m_shapeKey;                // +0x10
    float m_hitFraction;                // +0x14
};

class hkAabb
{ public:
    hkVector4 m_min;
    hkVector4 m_max;
};

class hkTransform;

// hkVector4::setTransformedPos (0x01081360, thiscall)
extern "C" void hkVector4__setTransformedPos(hkVector4* self, const hkTransform* t, const hkVector4* v);

class hkShape
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;
    virtual void getAabb(const hkTransform& t, float tolerance, hkAabb& aabb) const;
    virtual void getSupportingVertex(const hkVector4& dir, void* v) const;
    virtual hkSphere* getCollisionSpheres(hkSphere* spheres) const;
    uint32_t m_memSizeAndFlags;         // +4
    uint32_t m_userData;                // +8
};

class hkSphereShape : public hkShape
{
public:
    virtual hkSphere* getCollisionSpheres(hkSphere* spheres) const;                                  // 0x010c3860
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;    // 0x010c3880
    float m_radius;                     // +0xc
};

class hkTriangleShape : public hkShape
{
public:
    virtual void getAabb(const hkTransform& t, float tolerance, hkAabb& aabb) const;                 // 0x010c4140
    virtual hkSphere* getCollisionSpheres(hkSphere* spheres) const;                                  // 0x010c4390
    virtual void getSupportingVertex(const hkVector4& dir, void* v) const;                           // 0x010c4400
    void initShape(void* shape);                                                                     // 0x010c3fc0
    float m_radius;                     // +0xc
    hkVector4 m_vertexA;                // +0x10
    hkVector4 m_vertexB;                // +0x20
    hkVector4 m_vertexC;                // +0x30
};

// ---------------------------------------------------------------------------
// @ 0x010c3860
// ---------------------------------------------------------------------------
hkSphere* hkSphereShape::getCollisionSpheres(hkSphere* spheres) const
{
    spheres->w = m_radius;
    spheres->x = 0.0f;
    spheres->y = 0.0f;
    spheres->z = 0.0f;
    return spheres;
}
// ---------------------------------------------------------------------------
// @ 0x010c4390
// ---------------------------------------------------------------------------
hkSphere* hkTriangleShape::getCollisionSpheres(hkSphere* spheres) const
{
    spheres[0].x = m_vertexA.x; spheres[0].y = m_vertexA.y; spheres[0].z = m_vertexA.z; spheres[0].w = m_vertexA.w;
    spheres[0].w = m_radius;
    spheres[1].x = m_vertexB.x; spheres[1].y = m_vertexB.y; spheres[1].z = m_vertexB.z; spheres[1].w = m_vertexB.w;
    spheres[1].w = m_radius;
    spheres[2].x = m_vertexC.x; spheres[2].y = m_vertexC.y; spheres[2].z = m_vertexC.z; spheres[2].w = m_vertexC.w;
    spheres[2].w = m_radius;
    return spheres;
}

// ---------------------------------------------------------------------------
// @ 0x010c4400
// ---------------------------------------------------------------------------
void hkTriangleShape::getSupportingVertex(const hkVector4& dir, void* v) const
{
    const float dx = dir.x, dy = dir.y, dz = dir.z;
    float dA = dx * m_vertexA.x + (dy * m_vertexA.y + dz * m_vertexA.z);
    float dB = dx * m_vertexB.x + (dy * m_vertexB.y + dz * m_vertexB.z);
    float dC = dx * m_vertexC.x + (dy * m_vertexC.y + dz * m_vertexC.z);

    unsigned int sel;
    float best;
    if (dC <= dB) { sel = 0x10; best = dB; }
    else          { sel = 0x20; best = dC; }
    if (best < dA) sel = 0;

    const hkVector4* src = (const hkVector4*)((const char*)this + sel + 0x10);
    float* out = (float*)v;
    out[0] = src->x;
    out[1] = src->y;
    out[2] = src->z;
    out[3] = src->w;
    *(unsigned int*)(out + 3) = sel | 0x3f000000;
}

// ---------------------------------------------------------------------------
// hkGroupFilter: 32 bit-words of group masks at +0x1c, the group-filter vtable
// and two helper pointers at +8/+0xc/+0x10/+0x14.
// ---------------------------------------------------------------------------
struct hkCollisionInput;
class hkCdBody;
struct hkShapeCollection;

class hkGroupFilter
{
public:
    hkGroupFilter();                    // 0x010c3cb0
    virtual void v0();
    virtual void v1();
    virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& bodyA,
                                      const hkCdBody& bodyB, const hkShapeCollection& collection,
                                      uint32_t filterInfo) const;                          // 0x010c3df0
    hkBool testAgainstBody(hkBool* out, hkCdBody* body, void* collection, uint32_t key);   // 0x010c3bf0
    hkGroupFilter* destroy(char flags);                                                    // 0x010c3ef0
    void enableCollisionsBetween(int a, int b);   // 0x010c3c20
    uint16_t m_refCount;                // +4
    uint16_t m_lockCount;               // +6
    void* m_filter0;                    // +8
    void* m_filter1;                    // +0xc
    void* m_filter2;                    // +0x10
    void* m_filter3;                    // +0x14
    uint32_t m_defaultIsColliding;      // +0x18
    uint32_t m_groupBits[32];           // +0x1c
};

// @ 0x010c3b80  hkGroupFilter helper: is there a direct group pair overlap?
// __thiscall: ecx = base such that the 32 mask words start at ecx+0x1c.
// Stack args (after `push esi`): out, c, d.
extern "C" void hkGroupFilter__isGroupColliding(hkBool* out, char* self, uint32_t c, uint32_t d);

// ---------------------------------------------------------------------------
// @ 0x010c3b80  free helper: hkGroupFilterTestEnabled(out, self, c, d)
// ecx = self; masks live at self+0x1c.
// ---------------------------------------------------------------------------
class hkGroupFilterBase
{
public:
    char pad[0x1c];
    uint32_t m_groupBits[32];           // +0x1c
    void testEnabled(hkBool* out, uint32_t c, uint32_t d) const;
    void disableCollisionsBetween(uint32_t a, uint32_t b);   // 0x010c3c60
};

// @ 0x010c3b80
void hkGroupFilterBase::testEnabled(hkBool* out, uint32_t c, uint32_t d) const
{
    if ((((c ^ d) & 0xffff0000u) != 0) || ((c & 0xffff0000u) == 0))
    {
        uint32_t bit = 1u << (d & 0x1f);
        uint32_t word = m_groupBits[c & 0x1f];
        out->m_bool = (word & bit) != 0;
        return;
    }
    if ((((d >> 5) ^ c) & 0x3e0u) == 0)
    {
        out->m_bool = 0;
        return;
    }
    if ((((c >> 5) ^ d) & 0x3e0u) == 0)
    {
        out->m_bool = 0;
        return;
    }
    out->m_bool = 1;
}

// ---------------------------------------------------------------------------
// @ 0x010c3c20  ?enableCollisionsBetween@hkGroupFilter@@QAEXHH@Z
// ---------------------------------------------------------------------------
void hkGroupFilter::enableCollisionsBetween(int a, int b)
{
    m_groupBits[a] |= 1 << b;
    m_groupBits[b] |= 1 << a;
}

// ---------------------------------------------------------------------------
// @ 0x010c3c60  hkGroupFilter::disableCollisionsBetween
// ---------------------------------------------------------------------------
void hkGroupFilterBase::disableCollisionsBetween(uint32_t a, uint32_t b)
{
    int i = 0;
    uint32_t* w = m_groupBits;
    do
    {
        uint32_t bit = 1 << i;
        if ((a & bit) != 0)
            *w &= ~b;
        if ((b & bit) != 0)
            *w &= ~a;
        i++;
        w++;
    } while (i < 32);
}

// ---------------------------------------------------------------------------
// @ 0x010c3cb0  ??0hkGroupFilter@@QAE@XZ
// ---------------------------------------------------------------------------
extern char hkGroupFilter_vtbl_filters[];      // 0x013ef82c
extern char hkGroupFilter_vtbl_addref[];       // 0x013ef824
extern char hkGroupFilter_vtbl0[];             // 0x014a2970
extern char hkGroupFilter_vtbl1[];             // 0x014a2968
extern char hkGroupFilter_vtbl2[];             // 0x014a2960
extern char hkGroupFilter_vtbl3[];             // 0x014a2958
extern char hkGroupFilter_vtbl4[];             // 0x014a2950

hkGroupFilter::hkGroupFilter()
{
    m_lockCount = 1;
    *(const void**)((char*)this + 8) = hkGroupFilter_vtbl_filters;
    *(const void**)((char*)this + 0xc) = hkGroupFilter_vtbl_addref;
    *(const void**)((char*)this + 0x10) = hkGroupFilter_vtbl_addref;
    *(const void**)((char*)this + 0x14) = hkGroupFilter_vtbl_filters;
    *(const void**)((char*)this + 0x00) = hkGroupFilter_vtbl0;
    *(const void**)((char*)this + 0x08) = hkGroupFilter_vtbl1;
    *(const void**)((char*)this + 0x0c) = hkGroupFilter_vtbl2;
    *(const void**)((char*)this + 0x10) = hkGroupFilter_vtbl3;
    *(const void**)((char*)this + 0x14) = hkGroupFilter_vtbl4;
    for (int i = 0; i < 32; i++)
        m_groupBits[i] = 0xffffffffu;
    m_defaultIsColliding = 0;
}

// ---------------------------------------------------------------------------
// shared externs for the group-filter helpers
// ---------------------------------------------------------------------------
extern "C" void hkCollisionFilter__dtor(void* self);          // 0x005efd40
extern void* hkMemory_s_instance;                             // 0x016e4178

class hkCollisionFilterBase
{
public:
    void dtor();        // 0x005efd40, __thiscall (ecx = this)
};

// vtable slots used by the group-filter combination helpers
struct hkShapeFilterVtbl
{
    void* slots[16];
};

class hkCdBody
{ public:
    void* m_shape;          // +0
    int   m_shapeKey;       // +4
    void* m_motion;         // +8
    void* m_child;          // +0xc
};

// ---------------------------------------------------------------------------
// @ 0x010c3bf0  hkGroupFilter helper for one body pair
// __thiscall: ecx = this (mask base = this-0x10); stack: out, body, keyA, keyB.
// ---------------------------------------------------------------------------
hkBool hkGroupFilter::testAgainstBody(hkBool* out, hkCdBody* body, void* collection, uint32_t key)
{
    typedef uint32_t (__stdcall *FilterInfoFn)(uint32_t);
    uint32_t fi = ((FilterInfoFn)(*(void***)collection)[0x2c / 4])(key);
    ((hkGroupFilterBase*)((char*)this - 0x10))->testEnabled(out, *(uint32_t*)((char*)body + 0x20), fi);
    return *out;
}

// ---------------------------------------------------------------------------
// @ 0x010c3df0  hkGroupFilter::isCollisionEnabled
// __thiscall: ecx = this (mask base = this-0xc).
// ---------------------------------------------------------------------------
hkBool hkGroupFilter::isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& bodyA,
                                         const hkCdBody& bodyB, const hkShapeCollection& collection,
                                         uint32_t filterInfo) const
{
    typedef uint32_t (__stdcall *FilterInfoFn)(uint32_t);
    typedef int      (__stdcall *ShapeKeyFn)();
    void** cvt = *(void***)&collection;
    uint32_t fi = ((FilterInfoFn)cvt[0x2c / 4])(filterInfo);

    uint32_t a;
    const hkCdBody* b = &bodyA;
    if (bodyA.m_shapeKey == -1)
    {
        const void* p = *(const void**)((const char*)b + 0xc);
        while (p)
        {
            b = (const hkCdBody*)p;
            p = *(const void**)((const char*)p + 0xc);
        }
        a = *(const uint32_t*)((const char*)b + 0x1c);
    }
    else
    {
        const char* n = *(const char**)((const char*)b + 0xc);
        int key = 0;
        for (;;)
        {
            void** svt = *(void***)n;
            key = ((ShapeKeyFn)svt[8 / 4])();
            uint32_t bits = *(const uint32_t*)((const char*)*(const void**)&input + 0x10c + key * 4);
            if ((bits >> 2) & 1)
            {
                a = ((FilterInfoFn)(*(void***)n)[0x2c / 4])(*(uint32_t*)((const char*)b + 4));
                break;
            }
            if ((bits >> 3) & 1)
            {
                a = ((FilterInfoFn)(*(void***)(*(const char**)(n + 0xc)))[0x2c / 4])(*(uint32_t*)((const char*)b + 4));
                break;
            }
            if ((bits >> 0xb) & 1)
            {
                const char* p = n;
                const char* q = *(const char**)(p + 0xc);
                while (q) { p = q; q = *(const char**)(q + 0xc); }
                a = *(const uint32_t*)(p + 0x1c);
                break;
            }
            n = *(const char**)(n + 0xc);
            if (!n) { a = 0; break; }
        }
    }
    hkBool r;
    ((hkGroupFilterBase*)((char*)this - 0xc))->testEnabled(&r, a, fi);
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x010c3ef0  hkGroupFilter scalar deleting destructor
// ---------------------------------------------------------------------------
hkGroupFilter* hkGroupFilter::destroy(char flags)
{
    *(void**)((char*)this + 0x00) = hkGroupFilter_vtbl0;
    *(void**)((char*)this + 0x08) = hkGroupFilter_vtbl1;
    *(void**)((char*)this + 0x0c) = hkGroupFilter_vtbl2;
    *(void**)((char*)this + 0x10) = hkGroupFilter_vtbl3;
    *(void**)((char*)this + 0x14) = hkGroupFilter_vtbl4;
    ((hkCollisionFilterBase*)this)->dtor();
    if (flags & 1)
    {
        void** mem = *(void***)hkMemory_s_instance;
        typedef void (__stdcall *FreeFn)(void*, unsigned, int);
        ((FreeFn)mem[0x14 / 4])(this, (unsigned)*(unsigned short*)((char*)this + 4), 0x24);
    }
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x010c3fc0  helper: name a shape and run its vtable slot 6.
// __thiscall: ecx = this (passed through as the 3rd vtable argument);
// [esp+4] = the shape to initialise (its vtable is called with ecx = shape).
// ---------------------------------------------------------------------------
struct hkShapeVtbl
{
    virtual void t0();
    virtual void setName(const char* name, int a, void* self);
    virtual void t2();
    virtual void t3();
    virtual void t4();
    virtual void t5();
    virtual void tInit();
};

void hkTriangleShape::initShape(void* shape)
{
    ((hkShapeVtbl*)shape)->setName(hkTtrcTriangle, 1, this);
    ((hkShapeVtbl*)shape)->tInit();
}

// ---------------------------------------------------------------------------
// @ 0x010c4000  expand a uint16 index list into a packed hkVector4 array// ---------------------------------------------------------------------------
void hkShape__expandIndices(const uint16_t* idx, char* verticesBase, unsigned count, void* outp)
{
    float* out = (float*)outp;
    int remaining = (int)count - 1;
    if ((int)count > 3)
    {
        unsigned n = count >> 2;
        remaining = remaining - (int)n * 4;
        do
        {
            unsigned e0 = idx[0];
            const float* v0 = (const float*)(verticesBase + e0 + 0x10);
            out[0] = v0[0]; out[1] = v0[1]; out[2] = v0[2]; out[3] = v0[3];
            *(unsigned*)(out + 3) = e0 | 0x3f000000u;

            unsigned e1 = idx[1];
            const float* v1 = (const float*)(verticesBase + e1 + 0x10);
            out[4] = v1[0]; out[5] = v1[1]; out[6] = v1[2]; out[7] = v1[3];
            *(unsigned*)(out + 7) = e1 | 0x3f000000u;

            unsigned e2 = idx[2];
            const float* v2 = (const float*)(verticesBase + e2 + 0x10);
            out[8] = v2[0]; out[9] = v2[1]; out[10] = v2[2]; out[11] = v2[3];
            *(unsigned*)(out + 11) = e2 | 0x3f000000u;

            unsigned e3 = idx[3];
            const float* v3 = (const float*)(verticesBase + e3 + 0x10);
            out[12] = v3[0]; out[13] = v3[1]; out[14] = v3[2]; out[15] = v3[3];
            *(unsigned*)(out + 15) = e3 | 0x3f000000u;

            idx += 4;
            out += 0x10;
        } while (--n);
    }
    if (remaining >= 0)
    {
        int k = 0;
        do
        {
            unsigned e = idx[k];
            const float* v = (const float*)(verticesBase + e + 0x10);
            out[k * 4 + 0] = v[0];
            out[k * 4 + 1] = v[1];
            out[k * 4 + 2] = v[2];
            out[k * 4 + 3] = v[3];
            *(unsigned*)(out + k * 4 + 3) = e | 0x3f000000u;
            k++;
        } while (k <= remaining);
    }
}

// ---------------------------------------------------------------------------
// @ 0x010c3880  ?castRay@hkSphereShape@@UBE?AVhkBool@@ABUhkShapeRayCastInput@@AAUhkShapeRayCastOutput@@@Z
// Ray-vs-sphere closest approach.  `input.m_from`/`m_to` hold the segment; the
// sphere centre is the shape origin (radius at +0xc).
// ---------------------------------------------------------------------------
extern const float hkRayEpsilon;                     // 0x01485378
extern const float hkOne;                            // 0x01485720

hkBool hkSphereShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
    hkTimerCommand(hkTtrcSphere);

    const hkVector4& from = input.m_from;
    const hkVector4& to   = input.m_to;

    const float radius2 = m_radius * m_radius;

    const float dx = to.x - from.x;
    const float dy = to.y - from.y;
    const float dz = to.z - from.z;
    const float dot = dz * from.z + (dy * from.y + dx * from.x);

    if (dot < 0.0f)
    {
        const float len2 = dx * dx + (dy * dy + dz * dz);
        float px, py, pz, vs, vo;
        if (dot * dot <= (len2 * radius2) * 100.0f)
        {
            px = from.x; py = from.y; pz = from.z;
            vs = dot;
            vo = 0.0f;
        }
        else
        {
            if (len2 < radius2)
            {
                hkTimerCommand(hkMonitorTimerEndTag);
                return false;
            }
            vs = 0.0f;
            vo = -dot;
            const float t = vo / len2;
            const float s = 1.0f - t;
            px = t * to.x + s * from.x;
            py = s * from.y + t * to.y;
            pz = s * from.z + t * to.z;
        }
        const float c = (vs * vs) - ((px * px + (py * py + pz * pz)) - radius2) * len2;
        if (c < 0.0f)
        {
            hkTimerCommand(hkMonitorTimerEndTag);
            return false;
        }
        float hit = (-vs - sqrtf(c)) + vo;
        if (!(len2 * output.m_hitFraction < hit) || !(hit >= 0.0f))
        {
            hkTimerCommand(hkMonitorTimerEndTag);
            return false;
        }
        hit = hit / len2;
        output.m_hitFraction = hit;
        const float s = 1.0f - hit;
        output.m_normal[0] = s * from.x + hit * to.x;
        output.m_normal[1] = s * from.y + hit * to.y;
        output.m_normal[2] = s * from.z + hit * to.z;
        output.m_normal[3] = s * from.w + hit * to.w;
        const float invR = 1.0f / m_radius;
        output.m_shapeKey = 0xffffffff;
        output.m_normal[0] = invR * output.m_normal[0];
        output.m_normal[1] = invR * output.m_normal[1];
        output.m_normal[2] = invR * output.m_normal[2];
        output.m_normal[3] = invR * output.m_normal[3];
        hkTimerCommand(hkMonitorTimerEndTag);
        return true;
    }

    hkTimerCommand(hkMonitorTimerEndTag);
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x010c4140  ?getAabb@hkTriangleShape@@UBEXABVhkTransform@@MAAVhkAabb@@@Z
// Transform the three vertices and take the componentwise min/max, expanded by
// (tolerance + m_radius).
// ---------------------------------------------------------------------------
void hkTriangleShape::getAabb(const hkTransform& t, float tolerance, hkAabb& aabb) const
{
    const float tol = tolerance + m_radius;

    hkVector4 a, b, c;
    hkVector4__setTransformedPos(&a, &t, &m_vertexA);
    hkVector4__setTransformedPos(&b, &t, &m_vertexB);
    hkVector4__setTransformedPos(&c, &t, &m_vertexC);

    aabb.m_min.x = (c.x <= b.x) ? c.x : b.x;    // fold A/B later
    aabb.m_min.y = (c.y <= b.y) ? c.y : b.y;
    aabb.m_min.z = (c.z <= b.z) ? c.z : b.z;
    aabb.m_min.w = (c.w <= b.w) ? c.w : b.w;
    aabb.m_max.x = (c.x > b.x) ? c.x : b.x;
    aabb.m_max.y = (c.y > b.y) ? c.y : b.y;
    aabb.m_max.z = (c.z > b.z) ? c.z : b.z;
    aabb.m_max.w = (c.w > b.w) ? c.w : b.w;

    // fold in A
    if (a.x <= aabb.m_min.x) aabb.m_min.x = a.x;
    if (a.y <= aabb.m_min.y) aabb.m_min.y = a.y;
    if (a.z <= aabb.m_min.z) aabb.m_min.z = a.z;
    if (a.w <= aabb.m_min.w) aabb.m_min.w = a.w;
    if (a.x > aabb.m_max.x) aabb.m_max.x = a.x;
    if (a.y > aabb.m_max.y) aabb.m_max.y = a.y;
    if (a.z > aabb.m_max.z) aabb.m_max.z = a.z;
    if (a.w > aabb.m_max.w) aabb.m_max.w = a.w;

    aabb.m_min.x -= tol; aabb.m_min.y -= tol; aabb.m_min.z -= tol; aabb.m_min.w -= tol;
    aabb.m_max.x += tol; aabb.m_max.y += tol; aabb.m_max.z += tol; aabb.m_max.w += tol;
}
