// Slice s00b47600: the simulator's physics-object bookkeeping.
//   0x00b47730  F_b47730  allocate a handle from the pool, fill in mass/inertia from the model
//                         bounding box, register the object in the world map
//   0x00b47600  Vec44::DoInsertValue  eastl::vector<Elem44> (44-byte elements) insert
//   0x00b47e00  F_b47e00  resolve/register one object through the message-source tree
//   0x00b47ee0  F_b47ee0  refresh (rescale the world box) or drop an object's world record
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <float.h>
#include <xmmintrin.h>
#include <new>

struct V3 { float x, y, z; };
static inline V3 MakeV3(float x, float y, float z) { V3 r; r.x = x; r.y = y; r.z = z; return r; }
template<class T> static inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template<class T> static inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
struct Mat3 { float m[9]; };
struct BBox { V3 mn, mx; };
struct PropHolder;
struct Part25c { uint32_t pad[0x25c / 4]; float f25c; };

struct Obj {
    uint32_t m0;
    uint32_t m4;                    // +4
    uint32_t m8;                    // +8
    int state;                      // +0xc
    float f10, f14, f18;            // +0x10..
    uint32_t pad1[6];               // +0x1c..0x33
    uint8_t b34, b35, b36, b37;
    uint32_t m38, m3c;
    Part25c* m40;
    V3 v44, v50;                    // +0x44, +0x50
    Mat3 m5c;                       // +0x5c
    Mat3 m80;                       // +0x80
    uint32_t pad2[9];               // +0xa4..0xc7
    V3 vc8, vd4, ve0, vec;          // +0xc8..
    uint32_t pad3[9];               // +0xf8..0x11b
    float f11c, f120, f124, f128, f12c, f130, f134;
    float F_b3d630();
    void F_b3f420(BBox* b);
    const BBox* F_b3f730(BBox* b);
    void F_b43290();
    void F_b3dbb0();
};
struct cObj;
struct Pool {
    int F_b72160();
    Obj* F_b72210(int h);
    void F_b72260(int h);           // 0x00b72260  release handle
};
// eastl hashtable node: the stored key is the object pointer itself
struct HashNode {
    void* mpKey;                    // +0x00
    Obj* mpObj;                     // +0x04
};
struct HashIter {
    HashNode* mpNode;               // +0x00
    HashNode** mpBucket;            // +0x04
    bool operator==(const HashIter& x) const { return mpNode == x.mpNode; }
};
struct Map {
    void* mpPad0;                   // +0x00
    HashNode** mpBucketArray;       // +0x04
    uint32_t mnBucketCount;         // +0x08
    HashIter end() const
    {
        HashIter i;
        i.mpNode = mpBucketArray[mnBucketCount];
        i.mpBucket = mpBucketArray + mnBucketCount;
        return i;
    }
    HashIter find(cObj* const& key) const;      // 0x00645ed0
    HashIter erase(HashIter it);                // 0x01068380
    Obj** F_b474c0(const uint32_t* key);
};
struct Mgr {
    uint32_t m0;
    uint32_t m4;                    // +4
    uint32_t pad0[(0x3c - 8) / 4];
    Pool pool;                      // +0x3c
    uint32_t pad1[(0x58 - 0x40) / 4];
    Map map;                        // +0x58
    uint32_t pad2[(0xb4 - 0x64) / 4];
    float ratio;                    // +0xb4
};
extern Mgr* g_mgr;                  // 0x0167eb70
extern V3 g_v;                      // 0x0167eb8c

int GetTutorialToolPrice(PropHolder* p, int key, int def);      // 0x004e1c30
float GetPropertyFloat(PropHolder* p, int key, float def);      // 0x004e1c70
int F_ac8fa0(PropHolder* p, int key, int a);
Mat3* F_4fc990(Mat3* out, const Mat3* in, float* det);
int F_bbc300(uint32_t a, int h, V3* mn, V3* mx);

// @ 0x00b47730
Obj* F_b47730(uint32_t key, Part25c* a2, uint32_t a3, int kind, PropHolder* a5, int a6)
{
    BBox box;
    int h = g_mgr->pool.F_b72160();
    if (h != 0) {
        Obj* o = g_mgr->pool.F_b72210(h);
        o->m40 = a2;
        o->m4 = a3;
        o->b35 = 0;
        o->b34 = 1;
        o->b36 = 0;
        o->b37 = 0;
        o->state = GetTutorialToolPrice(a5, 0x2f5ab240, a6);
        o->f10 = GetPropertyFloat(a5, 0xce3f2a3a, 1.0f);
        o->f14 = GetPropertyFloat(a5, 0xc87942af, 1.0f);
        o->m38 = o->m3c = F_ac8fa0(a5, 0x1970f7f8, kind);
        o->f18 = 0.0f;
        float lim = GetPropertyFloat(a5, 0xb20c1347, FLT_MAX);
        if (o->state == 0 && o->F_b3d630() > lim)
            o->f18 = lim;
        if (kind == 5)
            o->f18 = a2->f25c;

        box.mn = MakeV3(FLT_MAX, FLT_MAX, FLT_MAX);
        box.mx = MakeV3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        o->F_b3f420(&box);

        if (o->state == 4) {
            o->state = 0;
            float d[3];
        d[0] = box.mx.x - box.mn.x;
        d[1] = box.mx.y - box.mn.y;
        d[2] = box.mx.z - box.mn.z;
        float hi = Max(Max(d[0], d[1]), d[2]);
        if (hi > g_mgr->ratio * Min(Min(d[0], d[1]), d[2]))
                o->state = 2;
        }

        if (o->state == 1) {
            float k = o->f14;
            float a = (box.mx.x - box.mn.x) * k;
            float b = (box.mx.y - box.mn.y) * k;
            float c = (box.mx.z - box.mn.z) * k;
            float r = o->f10 * 0.5f;
            V3 p, q;
            p.x = g_v.x; p.y = g_v.y; p.z = g_v.z;
            q.x = g_v.x; q.y = g_v.y; q.z = g_v.z;
            float m;
            if (c > b && c > a) {
                float s = sqrtf(a * a + b * b) * r;
                m = Min(s, lim);
                p.z = c * 0.5f - m;
                q.z = -p.z;
            } else if (b > a) {
                float s = sqrtf(a * a + c * c) * r;
                m = Min(s, lim);
                p.y = b * 0.5f - m;
                q.y = -p.y;
            } else {
                float s = sqrtf(b * b + c * c) * r;
                m = Min(s, lim);
                p.x = a * 0.5f - m;
                q.x = -p.x;
            }
            float dx = p.x - q.x, dy = p.y - q.y, dz = p.z - q.z;
            if (1.5258789e-05f <= sqrtf((dz * dz + dy * dy) + dx * dx)) {
                float cy = (box.mx.y + box.mn.y) * 0.5f;
                float cz = (box.mx.z + box.mn.z) * 0.5f;
                float cx = (box.mx.x + box.mn.x) * 0.5f;
                o->f11c = cx + p.x;
                o->f120 = cy + p.y;
                o->f124 = cz + p.z;
                o->f128 = cx + q.x;
                o->f12c = cy + q.y;
                o->f130 = cz + q.z;
                o->f134 = m;
            } else {
                o->state = 0;
            }
        }

        const BBox* bb = o->F_b3f730(&box);
        box.mn = bb->mn;
        box.mx = bb->mx;
        float ex = box.mx.x - box.mn.x;
        float ey = box.mx.y - box.mn.y;
        float ez = box.mx.z - box.mn.z;
        float ex2 = ex * ex, ey2 = ey * ey, ez2 = ez * ez;
        {
            Mat3 inertia;
            inertia.m[0] = (ez2 + ey2) * 0.083333336f;
            inertia.m[1] = 0.0f;
            inertia.m[2] = 0.0f;
            inertia.m[3] = 0.0f;
            inertia.m[4] = (ez2 + ex2) * 0.083333336f;
            inertia.m[5] = 0.0f;
            inertia.m[6] = 0.0f;
            inertia.m[7] = 0.0f;
            inertia.m[8] = (ey2 + ex2) * 0.083333336f;
            o->m80 = inertia;
            o->v44 = g_v;
            o->v50 = g_v;
            o->vc8 = g_v;
            o->vd4 = g_v;
            o->ve0 = g_v;
            o->vec = g_v;
            float det;
            F_4fc990(&inertia, &o->m80, &det);
            o->m5c = inertia;
        }
        o->F_b43290();
        o->m8 = F_bbc300(g_mgr->m4, h, &box.mn, &box.mx);
        *g_mgr->map.F_b474c0(&key) = o;
        o->F_b3dbb0();
        return o;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00b47600 -- eastl::vector<Elem44>::DoInsertValue (thiscall, ret 8).
// 44-byte elements; `value` may point into the vector itself, in which case it
// is advanced past the shifted element before the tail is moved up.
// ---------------------------------------------------------------------------
struct Elem44 { uint32_t w[11]; };                  // 44 bytes
struct Vec44 {
    Elem44* mpBegin;                                // +0x00
    Elem44* mpEnd;                                  // +0x04
    Elem44* mpCapacity;                             // +0x08
    void DoInsertValue(Elem44* position, const Elem44& value);   // 0x00b47600
};

void* F_f473a0(unsigned size, const char* pName, int flags, int dbgFlags,
               const char* pFile, int line);        // 0x00f473a0  operator new
void  F_f47380(void* p);                            // 0x00f47380  operator delete
Elem44* F_b3d890(Elem44* first, Elem44* last, Elem44* dest);   // 0x00b3d890

static inline void CopyBackward44(Elem44* first, Elem44* last, Elem44* result)
{
    while (last != first)
        *--result = *--last;
}

static Elem44* DoAllocate44(unsigned n)
{
    return n ? (Elem44*)F_f473a0(n * sizeof(Elem44), "Simulator", 0, 0,
                                 "eastl/allocator.h", 0xd1) : 0;
}

// @ 0x00b47600
void Vec44::DoInsertValue(Elem44* position, const Elem44& value)
{
    if (mpEnd != mpCapacity) {
        const Elem44* pValue = &value;
        if ((&value >= position) && (&value < mpEnd))
            ++pValue;
        new(mpEnd) Elem44(*(mpEnd - 1));
        CopyBackward44(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? 2 * nPrevSize : 1;
        Elem44* const pNewData = DoAllocate44(nNewSize);
        Elem44* pNewPosition = F_b3d890(mpBegin, position, pNewData);
        new(pNewPosition) Elem44(value);
        Elem44* pNewEnd = F_b3d890(position, mpEnd, pNewPosition + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            F_f47380(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// 0x00b47e00 -- bring one simulator object into (or refresh it in) the world.
// The object is first resolved through the message-source tree, registered with
// the property node, and finally released through its own vtable.
// ---------------------------------------------------------------------------
struct cObj {
    void** mpVtbl;                  // +0x00
    uint8_t pad04[0x50 - 0x04];
    uint8_t b50;                    // +0x50  bit 7 suppresses the property pass
    uint8_t pad51[0x54 - 0x51];
    int32_t m54;                    // +0x54  message-source handle
    int32_t m58;                    // +0x58  override handle
    uint8_t pad5c[0x70 - 0x5c];
    uint8_t b70;                    // +0x70
    uint8_t pad71[0x75 - 0x71];
    uint8_t b75;                    // +0x75
};

#define VSLOT(p, off) (*(void***)(p))[(off) / 4]

static __forceinline void* ObjSubTag(cObj* p, uint32_t id)
{
    return ((void* (__thiscall*)(cObj*, uint32_t))VSLOT(p, 0xb8))(p, id);
}
static __forceinline uint32_t ObjId(cObj* p)
{
    return ((uint32_t (__thiscall*)(cObj*))VSLOT(p, 0x20))(p);
}
static __forceinline void ObjBox(cObj* p, BBox* pBox)
{
    ((void (__thiscall*)(cObj*, BBox*))VSLOT(p, 0x6c))(p, pBox);
}
static __forceinline void ObjVCall0(void* p)
{
    ((void (__thiscall*)(void*))VSLOT(p, 0))(p);
}
static __forceinline void ObjVCall1(void* p)
{
    ((void (__thiscall*)(void*))VSLOT(p, 4))(p);
}

struct cSim {
    void* GetMsgSource(uint32_t id);                // 0x00b532f0
};
cSim* GetSim();                                     // 0x00b3d310

void* F_b41ee0(void* a, void* b);                   // 0x00b41ee0
char  F_64f350(void* p, uint32_t id, int flag);     // 0x0064f350
int   F_ac8fa0(void* p, uint32_t id, int v);        // 0x00ac8fa0
void  F_bbc320(int self, int h, const V3* mn, const V3* mx);   // 0x00bbc320
void  F_bbc330(int self, int h);                    // 0x00bbc330

// @ 0x00b47e00
void F_b47e00(void* a1, cObj* a2, void* a3)
{
    void* sub = a2 ? ObjSubTag(a2, 0x17f243bu) : 0;
    void* o = F_b41ee0(sub, a3);
    if (!o)
        return;
    ObjVCall0(o);
    if ((a2->b50 & 0x80) == 0 && F_64f350(o, 0xcf3b981du, 1)) {
        int v = a2->m58 ? a2->m58 : a2->m54;
        v = F_ac8fa0(o, 0x93336c12u, v);
        a2->m54 = v;
        void* pParent;
        uint32_t bOwn;
        if (a1) {
            pParent = a1;
            bOwn = 0;
        } else {
            pParent = a2;
            bOwn = 1;
        }
        Obj* r = F_b47730((uint32_t)a2, (Part25c*)pParent, bOwn, 1,
                          (PropHolder*)o, 0);
        if (r)
            r->b35 = (ObjSubTag(a2, 0xe9cb8bau) != 0);
        ObjVCall1(o);
        return;
    }
    ObjVCall1(o);
}

// ---------------------------------------------------------------------------
// 0x00b47ee0 -- refresh (or drop) the world record of one simulator object.
// ---------------------------------------------------------------------------
// @ 0x00b47ee0
void F_b47ee0(cObj* key)
{
    Mgr* w = g_mgr;
    HashIter it = w->map.find(key);
    if (key->b75 && key->b70) {
        if (it == w->map.end()) {
            void* pA = ObjSubTag(key, 0x17f243bu);
            void* pB = ObjSubTag(key, 0x116dd1bu);
            if (pA)
                F_b47e00(pB, key, GetSim()->GetMsgSource(ObjId((cObj*)pA)));
            return;
        }
        BBox box;
        ObjBox(key, &box);
        Obj* o = it.mpNode->mpObj;
        float s = o->f14;
        float cx = (box.mn.x + box.mx.x) * 0.5f;
        float cy = (box.mn.y + box.mx.y) * 0.5f;
        float cz = (box.mn.z + box.mx.z) * 0.5f;
        box.mn.x = cx + (box.mn.x - cx) * s;
        box.mn.y = cy + (box.mn.y - cy) * s;
        box.mn.z = cz + (box.mn.z - cz) * s;
        box.mx.x = cx + (box.mx.x - cx) * s;
        box.mx.y = cy + (box.mx.y - cy) * s;
        box.mx.z = cz + (box.mx.z - cz) * s;
        F_bbc320(w->m4, o->m8, &box.mn, &box.mx);
        o->F_b3dbb0();
        return;
    }
    if (it == w->map.end())
        return;
    Obj* o = it.mpNode->mpObj;
    F_bbc330(w->m4, o->m8);
    g_mgr->pool.F_b72260(o->m0);
    it = w->map.erase(it);
}
