// Slice s00c7d120 -- an anonymous "spatial target list" class (vtable 0x01473324,
// ~0x4a0 bytes) built from four containers:
//   +0x04  raw block with a [-4] allocation-count guard
//   +0x38  eastl::vector<uint32_t>   (ids)
//   +0x50  eastl::vector<uint32_t>   (ids)
//   +0x68  eastl::vector<EA::AutoRefCount<cSpatialObject>>  (inline buffer +0x80..0x280)
//   +0x280 eastl::vector<EA::AutoRefCount<cSpatialObject>>  (inline buffer +0x298..0x498)
// plus the distance-sorted target selection helpers (0x00c7d120/0x00c7d240/0x00c7d7a0/
// 0x00c7d940/0x00c7dac0) and the two cVarListSerializer read/write loops.
// No PDB names exist for this range.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc)
#include "types.h"
#include <math.h>
#include <intrin.h>

typedef unsigned int   u32;
typedef unsigned char  u8;

// ---- geometry -------------------------------------------------------------------------
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3 operator-(const Vec3& o) const { return Vec3(x - o.x, y - o.y, z - o.z); }
    Vec3 operator+(const Vec3& o) const { return Vec3(x + o.x, y + o.y, z + o.z); }
};

extern float g_13ec4b8;     // 0x013ec4b8  1e-08f
extern float g_13ef61c;     // 0x013ef61c  -2.0f
extern float g_13f7344;     // 0x013f7344  ~0.7f
extern void* g_1694b70;     // 0x01694b70  current selection / query filter

extern char g_castIdSpatial;   // 0x013f94d4  type-id object passed to Cast

// ---- refcounted objects (AddRef +0xbc, Release +0xc0, Cast +0xb8/+0xc) -----------------
struct RCObj {
#define V(n) virtual void v##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43) V(44) V(45)
#undef V
    virtual void* Cast(void* id);
    virtual void AddRef();
    virtual void Release();
};
inline void RefAddRef(void* p) { ((RCObj*)p)->AddRef(); }
inline void RefRelease(void* p) { ((RCObj*)p)->Release(); }
inline void* RefCast(void* p, void* id) { return ((RCObj*)p)->Cast(id); }
inline void* RefCast2(void* p, void* id)
{
    return ((void* (__thiscall*)(void*, void*))(*(void***)p)[0x0c / 4])(p, id);
}

struct AutoRef {
    void* mp;
    AutoRef() : mp(0) {}
    explicit AutoRef(void* p) : mp(p) { if (mp) RefAddRef(mp); }
    AutoRef(const AutoRef& o) : mp(o.mp) { if (mp) RefAddRef(mp); }
    ~AutoRef() { if (mp) RefRelease(mp); }
    AutoRef& operator=(const AutoRef& o)
    {
        if (mp != o.mp) {
            void* old = mp;
            if (o.mp) RefAddRef(o.mp);
            mp = o.mp;
            if (old) RefRelease(old);
        }
        return *this;
    }
};

// ---- out-of-line eastl / engine helpers ----------------------------------------------
void* __cdecl  LowerBoundU32(u32* first, u32* last, const u32* key, u8 flag); // 0x00555a20
void* __cdecl  MemCpy(void* dst, const void* src, unsigned n);                // 0x011e0744 (msvcr90 memcpy thunk)
void __cdecl  FreeMem(void* p);                                               // 0x00f47380
struct AutoVec {
    void* begin; void* end; void* cap;
    void dtor();                                // 0x00ad92d0
    void erase(void* first, void* last);        // 0x00b48e40
};
bool __cdecl  FilterCand(void* cand, void* ctx);                              // 0x00c7d090
bool __cdecl  PredC0C130(void* c);                                            // 0x00c0c130
bool __cdecl  PredBFC480(void* c);                                            // 0x00bfc480
void* __cdecl PivotSelect(void** a, void** b, void** c, Vec3 v);              // 0x00af9e60
void** __cdecl Partition(void** a, void** b, void* pivot, Vec3 v);            // 0x00c7d8a0
void __cdecl  FinalSort(void** a, void** b, void** c, Vec3 v);                // 0x00b95fe0
void __cdecl  SortVecImpl(void** a, void** b, Vec3 v);                        // 0x00c7dac0
void __cdecl  SortRec(void** a, void** b, int depth, Vec3 v);                 // 0x00c7d940
void __cdecl  SortRefs(void** a, void** b, Vec3 v);                           // 0x00c7d120

// ---- the class -----------------------------------------------------------------------
struct cTargetList {
    void** vptr;            // +0x000
    void*  mp04;            // +0x004  raw block ([p-4] holds an allocation count)
    char   pad08[0x10];     // +0x008..+0x017
    u32    m18;             // +0x018
    char   pad1c[0x08];     // +0x01c..+0x023
    u32    m24;             // +0x024
    char   pad28[0x10];     // +0x028..+0x037
    u32*   m38;             // +0x038
    u32*   m3c;             // +0x03c
    u32*   m40;             // +0x040
    char   pad44[0x08];     // +0x044..+0x04b
    u8     m4c;             // +0x04c
    char   pad4d[0x03];     // +0x04d..+0x04f
    u32*   m50;             // +0x050
    u32*   m54;             // +0x054
    u32*   m58;             // +0x058
    char   pad5c[0x08];     // +0x05c..+0x063
    u8     m64;             // +0x064
    char   pad65[0x03];     // +0x065..+0x067
    void** m68;             // +0x068
    void** m6c;             // +0x06c
    void** m70;             // +0x070
    char   pad74[0x08];     // +0x074..+0x07b
    u32    m7c;             // +0x07c
    char   m80[0x200];      // +0x080 inline storage for m68
    void** m280;            // +0x280
    void** m284;            // +0x284
    void** m288;            // +0x288
    char   pad28c[0x08];    // +0x28c..+0x293
    u32    m294;            // +0x294
    char   m298[0x200];     // +0x298 inline storage for m280
    float  m498;            // +0x498
    void*  m49c;            // +0x49c

    cTargetList();                          // 0x00c7d700
    ~cTargetList();                         // 0x00c7d650
    bool Has(u32 key);                      // 0x00c7d6d0
    void* FindTarget(void* ctx);            // 0x00c7d7a0
    void* FindTargetThunk();                // 0x00c7d930
    bool HasKey(void* obj);                 // 0x00c7da70
    void ClearAll();                        // 0x00c7dba0
    void ClearOne();                        // 0x00c7dc20
    bool UpdateTarget(void* target);        // 0x00c7d240
    void Update();                          // 0x00c7dcb0
    bool Write(void* stream);               // 0x00c7dfe0
    bool Read(void* stream);                // 0x00c7e0a0
    void* Get(int* idx);                    // 0x00c7e1a0
};

// ---- free helpers in this range -------------------------------------------------------
bool IsTargetable(void* self);              // 0x00c7d200 (cdecl)
bool __stdcall AdvanceIndex(void* p);       // 0x00c7e160

// ======================================================================================
// 0x00c7d120 -- insertion sort of an AutoRefCount pointer array by distance to a point
// ======================================================================================
// @ 0x00c7d120
struct DistLess {
    bool __thiscall Less(void* a, void* b) const;
};

void __cdecl SortRefs(void** begin, void** end, Vec3 org)
{
    if (begin == end)
        return;
    for (void** it = begin + 1; it != end; ++it) {
        void* value = *it;
        if (value)
            RefAddRef(value);
        void** j = it;
        while (j != begin && ((DistLess*)&org)->Less(value, j[-1])) {
            void* prev = j[-1];
            void* old  = *j;
            if (prev != old) {
                if (prev)
                    RefAddRef(prev);
                *j = prev;
                if (old)
                    RefRelease(old);
            }
            --j;
        }
        void* old = *j;
        if (value != old) {
            if (value)
                RefAddRef(value);
            *j = value;
            if (old)
                RefRelease(old);
        }
        if (value)
            RefRelease(value);
    }
}

// ======================================================================================
// 0x00c7d200 -- filter: object's selection component matches the active selection
// ======================================================================================
// @ 0x00c7d200
bool __cdecl IsTargetable(void* self)
{
    void* o = *(void**)((char*)self + 0x64);
    if (o) {
        void* c = RefCast2(o, (void*)0x17f243b);
        if (c && c != g_1694b70)
            if (((u32 (__thiscall*)(void*))(*(void***)c)[0x20 / 4])(c) == 0x70703b3)
                return true;
    }
    return false;
}

// ======================================================================================
// 0x00c7d650 -- base destructor (vector cleanup + raw block frees)
// ======================================================================================
// @ 0x00c7d650
cTargetList::~cTargetList()
{
    void* old = m49c;
    *(void**)this = (void*)0x1473324;
    if (old)
        FreeMem(old);
    m49c = 0;
    ((AutoVec*)((char*)this + 0x280))->dtor();
    ((AutoVec*)((char*)this + 0x68))->dtor();
    if (m50) FreeMem(m50);
    if (m38) FreeMem(m38);
    char* p = (char*)mp04;
    if (p && *(int*)(p - 4)) FreeMem(p);
}

// ======================================================================================
// 0x00c7d6d0 -- rbtree<u32> membership test
// ======================================================================================
// @ 0x00c7d6d0
bool cTargetList::Has(u32 key)
{
    ((void (__thiscall*)(void*, void**, const u32*))0x00e5c780)(this, (void**)&key, &key);
    return *(void**)&key != (char*)this + 4;
}

// ======================================================================================
// 0x00c7d700 -- constructor
// ======================================================================================
// @ 0x00c7d700
cTargetList::cTargetList()
{
    float z = 0.0f;
    vptr = (void**)0x1473324;
    mp04 = 0;
    *(u32*)((char*)this + 0x08) = 0;
    *(u32*)((char*)this + 0x0c) = 0;
    m38 = 0; m3c = 0; m40 = 0;
    m50 = 0; m54 = 0; m58 = 0;
    _ReadWriteBarrier();
    m68 = (void**)((char*)this + 0x80);
    m6c = m68;
    _ReadWriteBarrier();
    m7c = 0;
    m70 = (void**)((char*)m68 + 0x200);
    m280 = (void**)((char*)this + 0x298);
    m284 = m280;
    _ReadWriteBarrier();
    m294 = 0;
    m288 = (void**)((char*)m280 + 0x200);
    *(float*)((char*)this + 0x498) = z;
    m49c = 0;
    m18 = 0;
}

// ======================================================================================
// 0x00c7d7a0 -- choose a combatant from the tracked list
// ======================================================================================
// @ 0x00c7d7a0
void* cTargetList::FindTarget(void* ctx)
{
    void* sel = this ? ((void* (__thiscall*)(void*, void*))
                        (*(void***)this)[0x04 / 4])(this, &g_castIdSpatial) : 0;

    void** it  = m68;
    void** end = m6c;
    void* result = 0;
    for (; it != end; ++it) {
        void* o = *it;
        if (!o)
            continue;
        void* c = RefCast(o, (void*)0x17f243b);
        if (!c)
            continue;
        if (((bool (__thiscall*)(void*))(*(void***)c)[0x2c / 4])(c))
            continue;
        if (!FilterCand(c, ctx))
            continue;
        void* cb = RefCast2(c, &g_castIdSpatial);
        if (cb && ((int (__thiscall*)(void*))0x008e7f80)(cb) == 2)
            continue;
        if (!sel || result)
            return c;
        u32 key = *(u32*)((char*)c + 0x24);
        void* out;
        void** node = ((void** (__thiscall*)(void*, void*, const u32*))0x00e5c780)(
            (char*)sel + 0x0c, &out, &key);
        if (*node != (void**)((char*)sel + 0x10))
            return c;
        result = c;
    }
    return result;
}

// @ 0x00c7d930
void* cTargetList::FindTargetThunk()
{
    return FindTarget((char*)this + 0x28);
}

// ======================================================================================
// 0x00c7d940 -- recursive distance sort (median partition + insertion fallback)
// ======================================================================================
// @ 0x00c7d940
void __cdecl SortRec(void** a, void** b, int depth, Vec3 v)
{
    while ((((char*)b - (char*)a) & ~3) > 0x70 && depth > 0) {
        void** p = (void**)PivotSelect(a, a + (b - a) / 2, b - 1, v);
        void* pivot = *p;
        if (pivot)
            RefAddRef(pivot);
        void** mid = Partition(a, b, pivot, v);
        --depth;
        SortRec(mid, b, depth, v);
        b = mid;
    }
    if (depth == 0)
        FinalSort(a, b, b, v);
}

// ======================================================================================
// 0x00c7da70 -- u32-vector membership test (lower_bound)
// ======================================================================================
// @ 0x00c7da70
bool cTargetList::HasKey(void* obj)
{
    u32 key = *(u32*)((char*)obj + 0x24);
    u32* it = (u32*)LowerBoundU32(m38, m3c, &key, m4c);
    if (it == m3c || key < *it || it == it + 1)
        it = m3c;
    return it != m3c;
}

// ======================================================================================
// 0x00c7dba0 -- clear all four containers
// ======================================================================================
static inline void EraseU32Vec(u32** v)
{
    u32* b = v[0];
    u32* e = v[1];
    MemCpy(b, e, (unsigned)((char*)e - (char*)e));
    int count = (int)((char*)e - (char*)b) >> 2;
    int delta = -count;
    delta += delta;
    delta += delta;
    *(int*)((char*)v + 4) += delta;
}

// @ 0x00c7dba0
void cTargetList::ClearAll()
{
    AutoVec* v1 = (AutoVec*)((char*)this + 0x68);
    v1->erase(v1->begin, v1->end);
    EraseU32Vec((u32**)&m38);
    AutoVec* v2 = (AutoVec*)((char*)this + 0x280);
    v2->erase(v2->begin, v2->end);
    EraseU32Vec((u32**)&m50);
}

// @ 0x00c7dc20
void cTargetList::ClearOne()
{
    AutoVec* v = (AutoVec*)((char*)this + 0x280);
    v->erase(v->begin, v->end);
    EraseU32Vec((u32**)&m50);
}

// @ 0x00c7dc70
void __cdecl SortVec(void** a, void** b, Vec3 v)
{
    SortVecImpl(a, b, v);
}

// ======================================================================================
// 0x00c7d240 -- swept selection query (geometry + spatial query + filter)
// ======================================================================================
// @ 0x00c7d240
bool cTargetList::UpdateTarget(void* target)
{
    Vec3 p1 = ((Vec3* (__thiscall*)(void*))
               ((*(void***)this)[0x14 / 4]))(this)[0];
    Vec3 q = ((Vec3* (__thiscall*)(void*))
              (*(void***)((void**)((*(void***)this)[0x14 / 4]))[1]))(0)[0];
    (void)q;

    Vec3 src = *(Vec3*)((char*)&p1);
    float k = m498;
    float inv = 1.0f / sqrtf(src.x * src.x + src.y * src.y + src.z * src.z + g_13ec4b8);
    Vec3 p1m(src.x + src.x * inv * k, src.y + src.y * inv * k, src.z + src.z * inv * k);

    Vec3 p2 = *(Vec3*)((char*)&p1);                 // overwritten below
    p2 = ((Vec3* (__thiscall*)(void*))((*(void***)target)[0x2c / 4]))(target)[0];
    void* shape = ((void* (__thiscall*)(void*))((*(void***)target)[0x68 / 4]))(target);
    float r = *(float*)((char*)shape + 0x14) * g_13f7344;
    float travel = ((float (__thiscall*)(void*))((*(void***)target)[0x74 / 4]))(target) * g_13f7344;

    Vec3 d = p2 - p1m;
    float inv2 = 1.0f / sqrtf(p2.x * p2.x + p2.y * p2.y + p2.z * p2.z + g_13ec4b8);
    Vec3 n2(p2.x * inv2, p2.y * inv2, p2.z * inv2);
    float invd = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + g_13ec4b8);
    Vec3 nd(d.x * invd, d.y * invd, d.z * invd);
    Vec3 cr(n2.y * nd.z - n2.z * nd.y,
            n2.z * nd.x - n2.x * nd.z,
            n2.x * nd.y - n2.y * nd.x);
    float invc = 1.0f / sqrtf(cr.x * cr.x + cr.y * cr.y + cr.z * cr.z + g_13ec4b8);
    cr.x *= invc; cr.y *= invc; cr.z *= invc;

    p2.x += n2.x * r; p2.y += n2.y * r; p2.z += n2.z * r;

    void* spatial = RefCast(target, (void*)0x17f243b);
    if (!spatial)
        return true;

    g_1694b70 = ((void* (__thiscall*)(void*))((*(void***)this)[0x10 / 4]))(this);
    p2.x += cr.x * travel; p2.y += cr.y * travel; p2.z += cr.z * travel;

    void* hit = 0;
    void* mgr = ((void* (__cdecl*)(void))0x00b3d240)();
    ((void (__thiscall*)(void*, void*, void*, void*, void*, void*, int))
     ((*(void***)mgr)[0x50 / 4]))(mgr, &p2, &p1m, (void*)IsTargetable, &hit, &hit, 1);

    if (hit != spatial && hit != 0) {
        p2.x += cr.x * (travel * g_13ef61c);
        p2.y += cr.y * (travel * g_13ef61c);
        p2.z += cr.z * (travel * g_13ef61c);
        ((void (__thiscall*)(void*))((*(void***)hit)[0x04 / 4]))(hit);
        mgr = ((void* (__cdecl*)(void))0x00b3d240)();
        ((void (__thiscall*)(void*, void*, void*, void*, void*, void*, int))
         ((*(void***)mgr)[0x50 / 4]))(mgr, &p2, &p1m, (void*)IsTargetable, &hit, &hit, 1);
        g_1694b70 = 0;
        if (hit)
            ((void (__thiscall*)(void*))((*(void***)hit)[0x04 / 4]))(hit);
        return false;
    }
    g_1694b70 = 0;
    if (hit)
        ((void (__thiscall*)(void*))((*(void***)hit)[0x04 / 4]))(hit);
    return true;
}

// ======================================================================================
// 0x00c7dcb0 -- rebuild the target lists from the current simulation state
// ======================================================================================
// @ 0x00c7dcb0
void cTargetList::Update()
{
    EraseU32Vec((u32**)&m38);
    AutoVec* v1 = (AutoVec*)((char*)this + 0x68);
    v1->erase(v1->begin, v1->end);
    AutoVec* v2 = (AutoVec*)((char*)this + 0x280);
    v2->erase(v2->begin, v2->end);

    void* sel = this ? ((void* (__thiscall*)(void*, void*))
                        ((*(void***)this)[0x04 / 4]))(this, (void*)0x116dd1b) : 0;
    void* list = ((void* (__thiscall*)(void*))0x00c420d0)(sel);
    u32* arr = *(u32**)list;
    int n = (int)(*(u32**)((char*)list + 4) - arr) >> 2;
    for (int i = 0; i < n; ++i) {
        void* o = (void*)arr[i];
        if (!o)
            continue;
        void* c = RefCast(o, (void*)0x17f243b);
        if (!c)
            continue;
        u32 type = ((u32 (__thiscall*)(void*))((*(void***)c)[0x20 / 4]))(c);
        bool add;
        if (type == 0x18eb45e) {
            if (PredC0C130(c))
                continue;
            add = true;
        } else if (type == 0x70703b3) {
            void* cb = RefCast2(c, &g_castIdSpatial);
            add = !PredBFC480(cb);
        } else if (type == 0xf2897537 || type == 0x18c6de8) {
            add = true;
        } else {
            add = false;
        }
        if (add && !UpdateTarget(o))
            continue;

        u32 key = *(u32*)((char*)c + 0x24);
        u32* it = (u32*)LowerBoundU32(m38, m3c, &key, m4c);
        if (it == m3c || key < *it) {
            if (m3c == m40) {
                ((void (__thiscall*)(void*,void*,const u32*))0x005481d0)(&m38, it, &key);
            } else {
                *m3c = key;
                m3c = m3c + 1;
            }
            AutoRef tmp(c);
            if (m6c == m70)
                ((void (__thiscall*)(void*,void*,void**))0x00bab900)(&m68, m6c, &tmp.mp);
            else {
                *m6c = c;
                RefAddRef(c);
                m6c = m6c + 1;
            }
        } else {
            AutoRef tmp(c);
            if (m6c == m70)
                ((void (__thiscall*)(void*,void*,void**))0x00bab900)(&m68, m6c, &tmp.mp);
            else {
                *m6c = c;
                RefAddRef(c);
                m6c = m6c + 1;
            }
        }

        u32* it2 = (u32*)LowerBoundU32(m50, m54, &key, m64);
        if (!(it2 == m54 || key < *it2)) {
            if (it2 == m54) {
                void* pair[2];
                ((void (__thiscall*)(void*,void*,const u32*))0x00554020)(&m50, pair, &key);
                AutoRef tmp(c);
                if (m284 == m288)
                    ((void (__thiscall*)(void*,void*,void**))0x00bab900)(&m280, m284, &tmp.mp);
                else {
                    *m284 = c;
                    RefAddRef(c);
                    m284 = m284 + 1;
                }
            }
        }
    }

    Vec3 pos = ((Vec3* (__thiscall*)(void*))((*(void***)sel)[0x2c / 4]))(sel)[0];
    SortVecImpl((void**)m68, (void**)m6c, pos);
    SortVecImpl((void**)m280, (void**)m284, pos);
}

// ======================================================================================
// 0x00c7dfe0 / 0x00c7e0a0 -- cVarListSerializer read/write loops (0x1428-byte temp)
// ======================================================================================
struct cVarListSerializer {
    char m[0xa14];
    cVarListSerializer* Construct(void* src, void* generic, unsigned id);   // 0x00692f90
    bool Serialize(void* stream);                                          // 0x00692900
    bool Serialize2(void* stream);                                         // 0x00693e10
};

// @ 0x00c7dfe0
bool cTargetList::Write(void* stream)
{
    cVarListSerializer ser1;
    cVarListSerializer ser2;
    ser1.Construct(this, (void*)0x1579c58, 0x1a80d26u);
    bool ok = ser1.Serialize(stream);
    if (ok) {
        char* p = (char*)this + 0x04;
        for (int i = 0; i < 3; ++i) {
            ser2.Construct(p, (void*)0x1579ae8, 0x1a80d26u);
            ser2.Serialize(stream);
            p += 0x10;
        }
        p = (char*)this + 0x34;
        for (int i = 0; i < 2; ++i) {
            ser2.Construct(p, (void*)0x1579ba0, 0x1a80d26u);
            ser2.Serialize(stream);
            p += 0x10;
        }
    }
    return ok;
}

// @ 0x00c7e0a0
bool cTargetList::Read(void* stream)
{
    cVarListSerializer ser1;
    cVarListSerializer ser2;
    ser1.Construct(this, (void*)0x1579c58, 0x1a80d26u);
    bool ok = ser1.Serialize2(stream);
    if (ok) {
        char* p = (char*)this + 0x04;
        for (int i = 0; i < 3; ++i) {
            ser2.Construct(p, (void*)0x1579ae8, 0x1a80d26u);
            ser2.Serialize2(stream);
            p += 0x10;
        }
        p = (char*)this + 0x34;
        for (int i = 0; i < 2; ++i) {
            ser2.Construct(p, (void*)0x1579ba0, 0x1a80d26u);
            ser2.Serialize2(stream);
            p += 0x10;
        }
    }
    return ok;
}

// ======================================================================================
// 0x00c7e160 / 0x00c7e1a0 -- 4-D index stepping and flattening
// ======================================================================================
// @ 0x00c7e160
bool __stdcall AdvanceIndex(void* p)
{
    int* v = (int*)p;
    int one = 1;
    int zero = 0;
    bool ok = true;
    v[3] += 0x54;
    v[0] += one;
    if (v[0] >= 4) {
        v[1] += one;
        v[0] = zero;
        if (v[1] >= 4) {
            v[2] += one;
            v[1] = zero;
            if (v[2] >= 6) {
                v[3] = zero;
                ok = false;
            }
        }
    }
    return ok;
}

// @ 0x00c7e1a0
void* cTargetList::Get(int* idx)
{
    int n = idx[0] + (idx[1] + idx[2] * 4) * 4;
    return (char*)this + n * 0x54;
}
